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
bool ColumnExists(ROOT::RDF::RInterface<ROOT::Detail::RDF::RLoopManager> &df, const std::string &colName) {
    auto columnNames = df.GetColumnNames();
    return std::find(columnNames.begin(), columnNames.end(), colName) != columnNames.end();
}

void higgs_analysis(const std::string& inputFile, const std::vector<int>& masses, const std::string& channel, const std::string& path) {
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

    ROOT::EnableImplicitMT(10); 
    // std::string inputFile = "./test_mt_allsyst.root";

    ROOT::RDataFrame df1("ntuple", inputFile);
    
    // auto df2 = df1.Define("pnn_mass", [mass]() { return float(mass); }).Define("index", []() { return uint(0); } ).Define("njets_float", "float(njets)").Define("deta_12", "eta_1 - eta_2").Define("dphi_12", "phi_1 - phi_2");
    auto df2 = df1.Define("index", []() { return uint(0); } ).Define("njets_float", "float(njets)").Define("deta_12", "eta_1 - eta_2").Define("dphi_12", "phi_1 - phi_2");
    
    // std::vector<int> masses = {100, 120, 200};
    std::vector<std::string> columnsToSave;

    for (int mass : masses) {    df2 = df2.Define("pnn_mass_" + std::to_string(mass), [mass]() { return float(mass); });}
    auto df_scaled = df2;
    for (int mass : masses) {
    columnsToSave.clear();

    std::cout<< json_file << std::endl;
    std::ifstream ifs(json_file);
    nlohmann::json json_data;
    ifs >> json_data;
    // Extract the center and scale values
    std::map<std::string, std::pair<float, float>> scale_map;
    std::vector<std::string> input_vars = json_data["input_vars"];
    if (!input_vars.empty()) {
    input_vars.back() = "pnn_mass_" + std::to_string(mass);
    }
    std::vector<float> centers = json_data["center"];
    std::vector<float> scales = json_data["scale"];
    for (size_t i = 0; i < input_vars.size(); ++i) {
    scale_map[input_vars[i]] = std::make_pair(centers[i], scales[i]);}

    // auto df_scaled = df2;
    std::string mass_name = std::to_string(int(mass));

       
    // for (const std::string& var : input_vars) {
    // std::cout << var << std::endl;
    // }

    // this following block of code creates a vector of strings storing all ntuple systematics 
    // (excluding weight systematics)
    // Known base variable names (without systematics suffixes)
    std::vector<std::string> base_vars = {"mt_tot","pt_vis","m_vis","phi_1","phi_2","eta_1","eta_2","met","pt_1","pt_2","pt_tt","mt_1","mt_2","deltaR_ditaupair","metSumEt","pzetamissvis","dxy_1","metphi","mTdileptonMET","m_fastmtt","pt_fastmtt","eta_fastmtt", /* ... other base variable names ... */};

    // Use a set to store unique systematics suffixes
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
    // std::cout<< "I am here 0" ;
    // Then, add the contents of the set to the vector
    versions.insert(versions.end(), version_suffixes.begin(), version_suffixes.end());
    // for (const auto& ver : versions) {
    //     std::cout << ver << std::endl;
    // }
    // std::cout<< "I am here 1" ;

   


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
            if (!ColumnExists(df_scaled,"scaled_" + var_ver)){
                df_scaled = df_scaled.Define("scaled_" + var_ver, 
                                [scale_info, var_ver_input](float value) {
                    return (value - scale_info.first) / scale_info.second;
            }, {var_ver_input});}
            
        input_vars_ver.push_back("scaled_" + var_ver);
        }
        
        //   for (const std::string& var : input_vars_ver) {
        //     std::cout << var << std::endl;
        //     }

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
    }


    auto originalColumns = df_scaled.GetColumnNames();

    
    // Filter out columns starts with 'scaled_' and ends with  "_even/odd" 
    // if the variable name is shorter than '_even' also save this var
    for (const auto& colName : originalColumns) {
        // if ((colName.rfind("scaled_", 0) != 0) && (colName.rfind("_even") != colName.length() - std::string("_even").length()) && (colName.rfind("_odd") != colName.length() - std::string("_odd").length()) ) { // Check if the column name starts with 'scaled_'
    if ((colName.rfind("scaled_", 0) != 0) && 
        ((colName.length() < std::string("_even").length() || colName.rfind("_even") != colName.length() - std::string("_even").length()) &&
        (colName.length() < std::string("_odd").length() || colName.rfind("_odd") != colName.length() - std::string("_odd").length()))) {
            if (colName.rfind("pnn", 0) == 0 ||
            colName.find("weight") != std::string::npos ||
            colName.find("genEventSumW") != std::string::npos ||
            colName.find("Xsec") != std::string::npos ||
            colName.find("wgt") != std::string::npos ||
            colName.find("id_tau_vsJet_Medium") != std::string::npos ||
            colName.find("id_tau_vsMu_Loose") != std::string::npos ||
            colName.find("id_tau_vsMu_Tight") != std::string::npos ||
            colName.find("id_tau_vsEle_VVLoose") != std::string::npos ||
            colName.find("id_tau_vsMu_VLoose") != std::string::npos ||
            colName.find("id_tau_vsEle_Tight") != std::string::npos ||
            colName.find("trg") != std::string::npos ||
            colName.find("eta") != std::string::npos ||
            colName.find("dz") != std::string::npos ||
            colName.find("nbtag") != std::string::npos ||
            colName.find("pt") != std::string::npos ||
            colName.find("mt") != std::string::npos ||
            colName.find("q_") != std::string::npos ||
            colName.find("dxy_") != std::string::npos ||
            colName.find("iso_") != std::string::npos ||
            colName.find("deltaR") != std::string::npos ||
            colName.find("gen_match") != std::string::npos ||
            colName.find("_veto") != std::string::npos ||
            colName.find("is_fake") != std::string::npos ||
            colName.find("is_wjets") != std::string::npos ||
            colName.find("is_ttbar") != std::string::npos ||
            colName.find("Weight") != std::string::npos) {
                columnsToSave.push_back(colName);
            }
        }
        
    }
    
    }

     // Replace ".root" with "pnn" + mass + ".root"
    std::string suffix = "_pnn_" + std::to_string(masses[0]) + "_" + channel + ".root";
    std::string newFileName = inputFile.substr(0, inputFile.find_last_of(".")) + suffix;
    // remove columns of pnn_mass 
    std::vector<std::string> substringsToRemove = {"pnn_mass", "id_wgt_tau_vsMu", "id_wgt_tau_vsEle", "deta_12", "dphi_12", "njets_float", "index"};

    columnsToSave.erase(std::remove_if(columnsToSave.begin(), columnsToSave.end(),
        [&substringsToRemove](const std::string& colName) {
            // Check if colName contains any of the specified substrings
            return std::any_of(substringsToRemove.begin(), substringsToRemove.end(),
                [&colName](const std::string& substr) {
                    return colName.find(substr) != std::string::npos;
                });
        }),
        columnsToSave.end());
    columnsToSave.erase(std::remove_if(columnsToSave.begin(), columnsToSave.end(),
    [](const std::string& colName) {
        // Check if colName contains "__" and does not contain "pnn"
        bool containsDoubleUnderscore = colName.find("__") != std::string::npos;
        bool doesNotContainPnn = colName.find("pnn") == std::string::npos 
        && colName.find("wgt") == std::string::npos
        && colName.find("weight") == std::string::npos
        && colName.find("id_wgt_tau_vsJet") == std::string::npos
        && colName.find("id_wgt_mu") == std::string::npos
        && colName.find("id_wgt_ele") == std::string::npos
        && colName.find("Weight") == std::string::npos;
        return containsDoubleUnderscore && doesNotContainPnn;
    }),
    columnsToSave.end());

     df_scaled.Snapshot("ntuple",  newFileName ,columnsToSave); 
    //   df_scaled.Snapshot("ntuple",  inputFile ,columnsToSave); 

}

int main(int argc, char** argv) {
    if (argc < 5) {
        std::cout << "Usage: " << argv[0] << " <inputFile> <mass1,mass2,mass3,...> <channel> <path: working directory path>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string massArg = argv[2];
    std::string channel = argv[3];
    std::string path = argv[4];

    std::vector<int> masses;
    // Parse the comma-separated mass values and store them in the 'masses' vector
    std::istringstream massStream(massArg);
    std::string massToken;
    while (std::getline(massStream, massToken, ',')) {
        masses.push_back(std::stoi(massToken));
    }

    // Call higgs_analysis with the 'masses' vector
    higgs_analysis(inputFile, masses, channel, path);

    return 0;
}
