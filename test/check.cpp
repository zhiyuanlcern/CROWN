// #include "include/Higgs_trained_model.hxx"
#include "et_test.hxx"
#include "data/pnn/mt_even_lowmass.hxx"
#include "data/pnn/mt_odd_lowmass.hxx"
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

int check() {
    ROOT::EnableImplicitMT(); 
    std::string inputFile = "./test_mt_allsyst.root";

    ROOT::RDataFrame df1("ntuple", inputFile);
    auto df2 = df1.Define("pnn_mass", []() { return float(100); }).Define("index", []() { return uint(0); } ).Define("njets_float", "float(njets)").Define("deta_12", "eta_1 - eta_2").Define("dphi_12", "phi_1 - phi_2");
    // .Redefine("mt_tot", "float(mt_tot)").Redefine("pt_vis", "float(pt_vis)").Redefine("m_vis", "float(m_vis)").Redefine("phi_1", "float(phi_1)").Redefine("phi_2", "float(phi_2)").Redefine("eta_1", "float(eta_1)").Redefine("eta_2", "float(eta_2)").Redefine("met", "float(met)").Redefine("pt_1", "float(pt_1)").Redefine("pt_2", "float(pt_2)").Redefine("pt_tt", "float(pt_tt)").Redefine("mt_1", "float(mt_1)").Redefine("mt_2", "float(mt_2)").Redefine("deltaR_ditaupair", "float(deltaR_ditaupair)").Redefine("metSumEt", "float(metSumEt)").Redefine("pzetamissvis", "float(pzetamissvis)").Redefine("dxy_1", "float(dxy_1)").Redefine("metphi", "float(metphi)").Redefine("mTdileptonMET", "float(mTdileptonMET)");

    // Known base variable names (without version suffixes)
    std::vector<std::string> base_vars = {"mt_tot", "pt_vis", "m_vis", /* ... other base variable names ... */};

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
            if (suffix.find("_pf") == std::string::npos) {
                // Add the extracted version suffix to the set
                version_suffixes.insert(suffix);
            }
        }
    }
    // Convert the set to a vector
    std::vector<std::string> versions(version_suffixes.begin(), version_suffixes.end());
    for (const auto& ver : versions) {
        std::cout << ver << std::endl;
    }

    // Read the scaling JSON file
    std::ifstream ifs("data/pnn/mt_scaling.json");
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
            // Define the scaled variable for this version
            df_scaled = df_scaled.Define("scaled_" + var_ver, [scale_map, var_ver](float value) {
                auto scale_info = scale_map.at(var_ver);
                return (value - scale_info.first) / scale_info.second;
            }, {var_ver_input});
            input_vars_ver.push_back("scaled_" + var_ver);
        }

        // Define the NN score for this version
        std::string nnScoreName = "DNN100" + (ver.empty() ? "" : "_" + ver);
        df_scaled = df_scaled.DefineSlot(nnScoreName + "_even", SofieFunctor<26, TMVA_SOFIE_mt_even_lowmass::Session>(32), input_vars_ver)
                             .DefineSlot(nnScoreName + "_odd", SofieFunctor<26, TMVA_SOFIE_mt_odd_lowmass::Session>(32), input_vars_ver)
                             .Define(nnScoreName, "event %2 == 0 ? " + nnScoreName + "_odd : " + nnScoreName + "_even");
    }
     df_scaled.Snapshot("ntuple", "testallsystsoutput.root"); 
    return 0;

}