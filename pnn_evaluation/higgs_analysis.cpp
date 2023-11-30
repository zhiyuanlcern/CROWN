#include <ROOT/RDataFrame.hxx>
#include "ROOT/RDFHelpers.hxx"
#include "TMVA/SOFIEHelpers.hxx"
#include "ROOT/RVec.hxx"
#include <TApplication.h>
#include <iostream>
#include "data/pnn/mt_even_lowmass.hxx"
#include "data/pnn/mt_odd_lowmass.hxx"
#include "data/pnn/et_even_lowmass.hxx"
#include "data/pnn/et_odd_lowmass.hxx"
#include "data/pnn/tt_even_lowmass.hxx"
#include "data/pnn/tt_odd_lowmass.hxx"
#include "data/pnn/em_even_lowmass.hxx"
#include "data/pnn/em_odd_lowmass.hxx"
R__ADD_INCLUDE_PATH($PWD)
R__ADD_INCLUDE_PATH($ROOTSYS/runtutorials)
#include <nlohmann/json.hpp>
#include <fstream>
#include <map>
#include <vector>
#include <string>
using namespace TMVA::Experimental;
// Function to check if a column exists in the DataFrame
bool ColumnExists(ROOT::RDataFrame &df, const std::string &colName) {
    auto columnNames = df.GetColumnNames();
    return std::find(columnNames.begin(), columnNames.end(), colName) != columnNames.end();
}

void higgs_analysis(const std::string& inputFile, int mass, const std::string& channel, const std::string& path) {
    ROOT::EnableImplicitMT(10); 
    // std::string inputFile = "./test_mt_allsyst.root";

    ROOT::RDataFrame df1("ntuple", inputFile);
    auto df2 = df1.Define("pnn_mass", [mass]() { return float(mass); }).Define("index", []() { return uint(0); } ).Define("njets_float", "float(njets)").Define("deta_12", "eta_1 - eta_2").Define("dphi_12", "phi_1 - phi_2");
    
     // Read the scaling JSON file
    std::string json_file;  
    std::string weight_file_even; 
    std::string weight_file_odd; 
    if (channel ==  "mt"){
        json_file = path + "data/pnn/mt_scaling.json";
        weight_file_even = path + "data/pnn/mt_even_lowmass.dat";
        weight_file_odd = path + "data/pnn/mt_odd_lowmass.dat";
    }
    else if (channel ==  "et"){
        json_file = path + "data/pnn/et_scaling.json";
        weight_file_even = path + "data/pnn/et_even_lowmass.dat";
        weight_file_odd = path + "data/pnn/et_odd_lowmass.dat";
    }
    else if (channel ==  "tt"){
        json_file = path +  "data/pnn/tt_scaling.json";
        weight_file_even = path + "data/pnn/tt_even_lowmass.dat";
        weight_file_odd = path + "data/pnn/tt_odd_lowmass.dat";
    }
    else if (channel ==  "em"){
        json_file = path + "data/pnn/em_scaling.json";
        weight_file_even = path + "data/pnn/em_even_lowmass.dat";
        weight_file_odd = path + "data/pnn/em_odd_lowmass.dat";
    }
    else {
        std::cerr<< "Usage:  <channel> is mt, et, tt, or em" << std::endl;
    }
    std::cout<< json_file << std::endl;
    std::ifstream ifs(json_file);
    nlohmann::json json_data;
    ifs >> json_data;
    // Extract the center and scale values
    std::map<std::string, std::pair<float, float>> scale_map;
    std::vector<std::string> input_vars = json_data["input_vars"];
    std::vector<float> centers = json_data["center"];
    std::vector<float> scales = json_data["scale"];
    for (size_t i = 0; i < input_vars.size(); ++i) {
    scale_map[input_vars[i]] = std::make_pair(centers[i], scales[i]);}

    auto df_scaled = df2;
    std::string mass_name = std::to_string(int(mass));


    // this following block of code creates a vector of strings storing all ntuple systematics 
    // (excluding weight systematics)
    // Known base variable names (without version suffixes)
    std::vector<std::string> base_vars = {"mt_tot","pt_vis","m_vis","phi_1","phi_2","eta_1","eta_2","met","pt_1","pt_2","pt_tt","mt_1","mt_2","deltaR_ditaupair","metSumEt","pzetamissvis","dxy_1","metphi","mTdileptonMET","m_fastmtt","pt_fastmtt","eta_fastmtt", /* ... other base variable names ... */};

    // Use a set to store unique version suffixes
    std::set<std::string> version_suffixes;

    // Regular expression to match base variable names and extract suffixes
    std::regex base_var_regex("(" + std::accumulate(next(base_vars.begin()), base_vars.end(), base_vars[0],
                            [](std::string a, std::string b) { return a + "|" + b; }) + ")(.*)");

   // Loop over all column names in the DataFrame
    for (const auto& colName : df1.GetColumnNames()) {
        std::smatch match;
        if (std::regex_match(colName, match, base_var_regex) && match.size() > 2) {
            std::string suffix = match[2];

            // Check if the suffix matches the pattern to exclude
            // _pf variables are not used. Puppi MET is more reliable that the nominal MET (which is _pf variables)
            // suffix shuold start with '__'
            if (suffix.rfind("__", 0) == 0 && suffix.find("_pf") == std::string::npos) {
                // Add the extracted version suffix to the set
                version_suffixes.insert(suffix);
            }
        }
    }
    // Create the vector and add the nominal version
    std::vector<std::string> versions;
    versions.push_back("");

    // Then, add the contents of the set to the vector
    versions.insert(versions.end(), version_suffixes.begin(), version_suffixes.end());
    for (const auto& ver : versions) {
        std::cout << ver << std::endl;
    }

   


    // For each version, compute NN scores
    for (const auto &ver : versions) {
        std::vector<std::string> input_vars_ver;
        for (const auto &var : input_vars) {
            std::string var_ver = var + ver;
            std::string var_ver_input = var_ver;
            // Check if the version exists, else use the nominal version
            if (!ColumnExists(df1, var_ver)) {
                var_ver_input = var; // Use the nominal version
            }
            auto scale_info = scale_map.at(var);
            // Define the scaled variable for this version
            df_scaled = df_scaled.Define("scaled_" + var_ver, 
            [scale_info, var_ver_input](float value) {
                return (value - scale_info.first) / scale_info.second;
            }, {var_ver_input});
        input_vars_ver.push_back("scaled_" + var_ver);
        }
        
        
    // Define the NN score for this version
    std::string nnScoreName = "pnn_" +  mass_name+ (ver.empty() ? "" : "_" + ver);
    

    if (channel ==  "mt"){
        df_scaled = df_scaled.DefineSlot(nnScoreName + "_even", SofieFunctor<26, TMVA_SOFIE_mt_even_lowmass::Session>(32, weight_file_even), input_vars_ver)
                            .DefineSlot(nnScoreName + "_odd", SofieFunctor<26, TMVA_SOFIE_mt_odd_lowmass::Session>(32, weight_file_odd), input_vars_ver)
                            .Define(nnScoreName, "event %2 == 0 ? " + nnScoreName + "_odd : " + nnScoreName + "_even");
    }       
    else if (channel ==  "et"){
        df_scaled = df_scaled.DefineSlot(nnScoreName + "_even", SofieFunctor<26, TMVA_SOFIE_et_even_lowmass::Session>(32, weight_file_even), input_vars_ver)
                            .DefineSlot(nnScoreName + "_odd", SofieFunctor<26, TMVA_SOFIE_et_odd_lowmass::Session>(32, weight_file_odd), input_vars_ver)
                            .Define(nnScoreName, "event %2 == 0 ? " + nnScoreName + "_odd : " + nnScoreName + "_even");
    }
    else if (channel ==  "tt"){
        df_scaled = df_scaled.DefineSlot(nnScoreName + "_even", SofieFunctor<26, TMVA_SOFIE_tt_even_lowmass::Session>(32, weight_file_even), input_vars_ver)
                            .DefineSlot(nnScoreName + "_odd", SofieFunctor<26, TMVA_SOFIE_tt_odd_lowmass::Session>(32, weight_file_odd), input_vars_ver)
                            .Define(nnScoreName, "event %2 == 0 ? " + nnScoreName + "_odd : " + nnScoreName + "_even");
    }
    else if (channel ==  "em"){
        df_scaled = df_scaled.DefineSlot(nnScoreName + "_even", SofieFunctor<26, TMVA_SOFIE_em_even_lowmass::Session>(32, weight_file_even), input_vars_ver)
                            .DefineSlot(nnScoreName + "_odd", SofieFunctor<26, TMVA_SOFIE_em_odd_lowmass::Session>(32, weight_file_odd), input_vars_ver)
                            .Define(nnScoreName, "event %2 == 0 ? " + nnScoreName + "_odd : " + nnScoreName + "_even");
    }
    else {
        std::cerr<< "Usage:  <channel> is mt, et, tt, or em" << std::endl;
    }
        
    //  key step: systematics shifts result in different # of events. The event's variable are saved as -10 if the event is not passing selections. 
    // so we defined the nn score to be -10 if any of the input variables is < -9.9, excluding the nominal variables 
    std::string condition = "";  // Start with a condition that is initially false
    for (const auto& var : input_vars_ver) {
        // Skip nominal variables
        if (var.find("__") == std::string::npos) {
            continue;
        }
        if (!condition.empty()) {
            condition += " || ";
        }
        condition += "(" + var + " < -9.9)";
    }
    if (condition.empty()){
        // when evaluating for nominal, the condition list is empty
        for (const auto& var : input_vars_ver) {
        
            if (!condition.empty()) {
                condition += " || ";
            }
            condition += "(" + var + " < -9.9)";
        
        }             
    }
    if (!condition.empty()) df_scaled = df_scaled.Redefine(nnScoreName, "(" + condition + ") ? -10.0 : " + nnScoreName);


        // following the simiar logic, we now multiply the weight to the pnn score and the corresponding systematics



    // this following block of code creates a vector of strings storing all ntuple systematics 
    // (excluding weight systematics)
    // Known base variable names (without version suffixes)
    std::vector<std::string> base_vars = {"mt_tot","pt_vis","m_vis","phi_1","phi_2","eta_1","eta_2","met","pt_1","pt_2","pt_tt","mt_1","mt_2","deltaR_ditaupair","metSumEt","pzetamissvis","dxy_1","metphi","mTdileptonMET","m_fastmtt","pt_fastmtt","eta_fastmtt", /* ... other base variable names ... */};

    // Use a set to store unique version suffixes
    std::set<std::string> version_suffixes;

    // Regular expression to match base variable names and extract suffixes
    std::regex base_var_regex("(" + std::accumulate(next(base_vars.begin()), base_vars.end(), base_vars[0],
                            [](std::string a, std::string b) { return a + "|" + b; }) + ")(.*)");

   // Loop over all column names in the DataFrame
    for (const auto& colName : df1.GetColumnNames()) {
        std::smatch match;
        if (std::regex_match(colName, match, base_var_regex) && match.size() > 2) {
            std::string suffix = match[2];

            // Check if the suffix matches the pattern to exclude
            // _pf variables are not used. Puppi MET is more reliable that the nominal MET (which is _pf variables)
            // suffix shuold start with '__'
            if (suffix.rfind("__", 0) == 0 && suffix.find("_pf") == std::string::npos) {
                // Add the extracted version suffix to the set
                version_suffixes.insert(suffix);
            }
        }
    }
    // Create the vector and add the nominal version
    std::vector<std::string> versions;
    versions.push_back("");

    // Then, add the contents of the set to the vector
    versions.insert(versions.end(), version_suffixes.begin(), version_suffixes.end());
    for (const auto& ver : versions) {
        std::cout << ver << std::endl;
    }

   


    // For each version, compute NN scores
    for (const auto &ver : versions) {
        std::vector<std::string> input_vars_ver;
        for (const auto &var : input_vars) {
            std::string var_ver = var + ver;
            std::string var_ver_input = var_ver;
            // Check if the version exists, else use the nominal version
            if (!ColumnExists(df1, var_ver)) {
                var_ver_input = var; // Use the nominal version
            }
            auto scale_info = scale_map.at(var);
            // Define the scaled variable for this version
            df_scaled = df_scaled.Define("scaled_" + var_ver, 
            [scale_info, var_ver_input](float value) {
                return (value - scale_info.first) / scale_info.second;
            }, {var_ver_input});
        input_vars_ver.push_back("scaled_" + var_ver);
        }
        
        

















    }



    auto originalColumns = df_scaled.GetColumnNames();
    std::vector<std::string> columnsToSave;

    // Filter out columns starts with 'scaled_' and ends with  "_even/odd"
    for (const auto& colName : originalColumns) {
        
        if ((colName.rfind("scaled_", 0) != 0) && (colName.rfind("_even") != colName.length() - std::string("_even").length()) && (colName.rfind("_odd") != colName.length() - std::string("_odd").length()) ) { // Check if the column name starts with 'scaled_'
            if (colName.rfind("pnn", 0) == 0) {
                columnsToSave.push_back(colName);
            }
        }
    }
     // Replace ".root" with "pnn" + mass + ".root"
    std::string suffix = "_pnn_" + channel + "_" + mass_name + ".root";
    std::string newFileName = inputFile.substr(0, inputFile.find_last_of(".")) + suffix;

     df_scaled.Snapshot("ntuple",  newFileName ,columnsToSave); 

}

int main(int argc, char** argv) {
    if (argc < 5) {
        std::cout << "Usage: " << argv[0] << " <inputFile> <mass> <channel> <path: working directory path>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    int mass = std::stoi(argv[2]);
    std::string channel = argv[3];
    std::string path = argv[4];

    higgs_analysis(inputFile, mass, channel,path);
    return 0;
}