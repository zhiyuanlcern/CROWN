#include <ROOT/RDataFrame.hxx>
#include "TMVA/SOFIEHelpers.hxx"
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

int higgs_analysis() {
    std::string inputFile = "./test_mt_latest.root";

    ROOT::RDataFrame df1("ntuple", inputFile);
    auto df2 = df1.Define("pnn_mass", []() { return float(100); }).Define("index", []() { return uint(0); } ).Define("njets_float", "float(njets)").Define("deta_12", "eta_1 - eta_2").Define("dphi_12", "phi_1 - phi_2");
    // .Redefine("mt_tot", "float(mt_tot)").Redefine("pt_vis", "float(pt_vis)").Redefine("m_vis", "float(m_vis)").Redefine("phi_1", "float(phi_1)").Redefine("phi_2", "float(phi_2)").Redefine("eta_1", "float(eta_1)").Redefine("eta_2", "float(eta_2)").Redefine("met", "float(met)").Redefine("pt_1", "float(pt_1)").Redefine("pt_2", "float(pt_2)").Redefine("pt_tt", "float(pt_tt)").Redefine("mt_1", "float(mt_1)").Redefine("mt_2", "float(mt_2)").Redefine("deltaR_ditaupair", "float(deltaR_ditaupair)").Redefine("metSumEt", "float(metSumEt)").Redefine("pzetamissvis", "float(pzetamissvis)").Redefine("dxy_1", "float(dxy_1)").Redefine("metphi", "float(metphi)").Redefine("mTdileptonMET", "float(mTdileptonMET)");

      // Read the JSON file
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
    // Define the scaled variables in the DataFrame
    auto df_scaled = df2;
    for (const auto &var : input_vars) {
        df_scaled = df_scaled.Define(   "scaled_" + var, [scale_map, var](float value) {
            auto scale_info = scale_map.at(var);
            return (value - scale_info.first) / scale_info.second;
        }, {var});
    }

    std::vector<std::string> input_vars_list =  { 
                    "index",
                    "scaled_mt_tot",
                    "scaled_pt_vis",
                    "scaled_m_vis",
                    "scaled_phi_1",
                    "scaled_phi_2",
                    "scaled_eta_1",
                    "scaled_eta_2",
                    "scaled_met",
                    "scaled_pt_1",
                    "scaled_pt_2",
                    "scaled_pt_tt",
                    "scaled_mt_1",
                    "scaled_mt_2",
                    "scaled_deta_12",
                    "scaled_dphi_12",
                    "scaled_deltaR_ditaupair",
                    "scaled_metSumEt",
                    "scaled_njets_float",
                    "scaled_pzetamissvis",
                    "scaled_dxy_1",
                    "scaled_metphi",
                    "scaled_mTdileptonMET",
                    "scaled_m_fastmtt",
                    "scaled_pt_fastmtt",
                    "scaled_eta_fastmtt",
                    "scaled_pnn_mass" };               
    auto df3 = df_scaled.Define("DNN100_Value_even", SofieFunctor<26, TMVA_SOFIE_mt_even_lowmass::Session>(32), input_vars_list)
            .Define("DNN100_Value_odd", SofieFunctor<26, TMVA_SOFIE_mt_odd_lowmass::Session>(32), input_vars_list)
            .Define("DNN100",  "event %2 == 0 ? DNN100_Value_odd : DNN100_Value_even");
    df3.Snapshot("ntuple", "testoutput.root"); 
    return 0;
}