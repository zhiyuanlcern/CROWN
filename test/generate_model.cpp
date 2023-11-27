#include <ROOT/RDataFrame.hxx>
#include "TMVA/SOFIEHelpers.hxx"
#include "include/Higgs_trained_model.hxx"
R__ADD_INCLUDE_PATH($PWD)
R__ADD_INCLUDE_PATH($ROOTSYS/runtutorials)
using namespace TMVA::Experimental;

int generate_model() {
RSofieReader model("testmodel.h5")
  ROOT::RDataFrame  df1("Xtohh100", "./mutau-fastmtt-processed-nob-evaluatedtestmodel.h5adam/Xtohh100.root");
df2 = df1.Define("mass", []() { return float(0.21052631578947367); }).Redefine("mt_tot", "float(mt_tot)").Redefine("pt_vis", "float(pt_vis)").Redefine("m_vis", "float(m_vis)").Redefine("phi_1", "float(phi_1)").Redefine("phi_2", "float(phi_2)").Redefine("eta_1", "float(eta_1)").Redefine("eta_2", "float(eta_2)").Redefine("met", "float(met)").Redefine("pt_1", "float(pt_1)").Redefine("pt_2", "float(pt_2)").Redefine("pt_tt", "float(pt_tt)").Redefine("mt_1", "float(mt_1)").Redefine("mt_2", "float(mt_2)").Redefine("deltaR_ditaupair", "float(deltaR_ditaupair)").Redefine("metSumEt", "float(metSumEt)").Redefine("njets", "float(njets)").Redefine("pzetamissvis", "float(pzetamissvis)").Redefine("dxy_1", "float(dxy_1)").Redefine("metphi", "float(metphi)").Redefine("mTdileptonMET", "float(mTdileptonMET)")
df3 = df2.Define("PNN100", Compute<24, float>(model),{"mt_tot","pt_vis","m_vis","phi_1","phi_2","eta_1","eta_2","met","pt_1","pt_2","pt_tt","mt_1","mt_2","deltaR_ditaupair","metSumEt","njets","pzetamissvis","dxy_1","metphi","mTdileptonMET","m_fastmtt","pt_fastmtt","eta_fastmtt","mass"})
df4 = df3.Define("PNN100_output", "PNN100[0]")
df4.Snapshot("Xto100", "./testSOFIE100.root")

    return 0;



}