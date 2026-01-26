#ifndef GUARD_SCALEFACTORS_H
#define GUARD_SCALEFACTORS_H

#include "../include/basefunctions.hxx"
#include "../include/utility/Logger.hxx"
#include "../include/utility/RooFunctorThreadsafe.hxx"
#include "ROOT/RDataFrame.hxx"
#include "RooFunctor.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "correction.h"
#include <bitset>
#include <Math/Vector3D.h>
#include <Math/VectorUtil.h>
/// namespace used for scale factor related functions
namespace scalefactor {

/**
 * @brief Function used to try and match a object with a trigger object.
 * Copied from triggers.cxx to avoid namespace issues.
 */
// Non-modifying version of matchParticle for use in RDataFrame lambdas
// This version does NOT erase elements from the vectors to avoid memory corruption
inline bool matchParticleNoModify(const ROOT::Math::PtEtaPhiMVector &particle,
                                   const ROOT::RVec<float> &triggerobject_pts,
                                   const ROOT::RVec<float> &triggerobject_etas,
                                   const ROOT::RVec<float> &triggerobject_phis,
                                   ROOT::RVec<ULong64_t> &triggerobject_bits,
                                   const ROOT::RVec<UShort_t> &triggerobject_ids,
                                   const float &matchDeltaR,
                                   const float &pt_cut,
                                   const float &eta_cut,
                                   const UShort_t &trigger_particle_id_cut,
                                   const int &triggerbit_cut) {
    for (std::size_t idx = 0; idx < triggerobject_pts.size(); ++idx) {
        auto triggerobject = ROOT::Math::RhoEtaPhiVectorF(
            0, triggerobject_etas[idx], triggerobject_phis[idx]);
        bool deltaR = ROOT::Math::VectorUtil::DeltaR(triggerobject, particle) <
                      matchDeltaR;
        bool bit = (triggerbit_cut == -1) ||
                   (std::bitset<30>(triggerobject_bits[idx]).test(triggerbit_cut));
        bool id = triggerobject_ids[idx] == trigger_particle_id_cut;
        bool pt = particle.pt() > pt_cut;
        bool eta = abs(particle.eta()) < eta_cut;
        
        if ((deltaR && bit && id && pt && eta) || (triggerbit_cut == -1)) {
            // Return true WITHOUT erasing elements to avoid memory corruption in RDataFrame
            return true;
        }
    }
    return false;
}

namespace muon {
/**
 * @brief Function used to evaluate id scale factors from muons
 *
 * @param df The input dataframe
 * @param pt muon pt
 * @param eta muon eta
 * @param id_output name of the id scale factor column
 * @param workspace_name path to the Rooworkspace
 * @param id_functor_name name of the function from the workspace
 * @param id_arguments arguments of the function
 * @return a new dataframe containing the new column
 */
ROOT::RDF::RNode id_rooworkspace(ROOT::RDF::RNode df, const std::string &pt,
                                 const std::string &eta,
                                 const std::string &id_output,
                                 const std::string &workspace_name,
                                 const std::string &id_functor_name,
                                 const std::string &id_arguments) {

    Logger::get("muonsf")->debug("Setting up functions for muon sf");
    Logger::get("muonsf")->debug("ID - Function {} // argset {}",
                                 id_functor_name, id_arguments);

    const std::shared_ptr<RooFunctorThreadsafe> id_function =
        loadFunctor(workspace_name, id_functor_name, id_arguments);
    auto df1 = basefunctions::evaluateWorkspaceFunction(df, id_output,
                                                        id_function, pt, eta);
    return df1;
}
/**
 * @brief Function used to evaluate iso scale factors from muons
 *
 * @param df The input dataframe
 * @param pt muon pt
 * @param eta muon eta
 * @param iso muon iso
 * @param iso_output name of the iso scale factor column
 * @param workspace_name path to the Rooworkspace
 * @param iso_functor_name name of the function from the workspace
 * @param iso_arguments arguments of the function
 * @return a new dataframe containing the new column
 */
ROOT::RDF::RNode iso_rooworkspace(ROOT::RDF::RNode df, const std::string &pt,
                                  const std::string &eta,
                                  const std::string &iso,
                                  const std::string &iso_output,
                                  const std::string &workspace_name,
                                  const std::string &iso_functor_name,
                                  const std::string &iso_arguments) {

    Logger::get("muonsf")->debug("Setting up functions for muon sf");
    Logger::get("muonsf")->debug("Iso - Function {} // argset {}",
                                 iso_functor_name, iso_arguments);

    const std::shared_ptr<RooFunctorThreadsafe> iso_function =
        loadFunctor(workspace_name, iso_functor_name, iso_arguments);
    auto df1 = basefunctions::evaluateWorkspaceFunction(
        df, iso_output, iso_function, pt, eta, iso);
    return df1;
}
/**
 * @brief Function used to evaluate id scale factors from muons with
 * correctionlib. Configuration:
 * - [UL2018 Muon
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/MUO_muon_Z_Run2_UL/MUO_muon_Z_2018_UL.html)
 * - [UL2017 Muon
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/MUO_muon_Z_Run2_UL/MUO_muon_Z_2017_UL.html)
 * - [UL2016preVFP Muon
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/MUO_muon_Z_Run2_UL/MUO_muon_Z_2016preVFP_UL.html)
 * - [UL2016postVFP Muon
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/MUO_muon_Z_Run2_UL/MUO_muon_Z_2016postVFP_UL.html)
 *
 * @param df The input dataframe
 * @param pt muon pt
 * @param eta muon eta
 * @param year_id id for the year of data taking and mc compaign
 * @param variation id for the variation of the scale factor "sf" for nominal
 * and "systup"/"systdown" for up/down variation
 * @param id_output name of the id scale factor column
 * @param sf_file path to the file with the muon scale factors
 * @param idAlgorithm name of the muon id scale factor
 * @return a new dataframe containing the new column
 */
ROOT::RDF::RNode id(ROOT::RDF::RNode df, const std::string &pt,
                    const std::string &eta,
                    const std::string &variation, const std::string &id_output,
                    const std::string &sf_file,
                    const std::string &idAlgorithm) {

    Logger::get("muonIdSF")->debug("Setting up functions for muon id sf");
    Logger::get("muonIdSF")->debug("ID - Name {}", idAlgorithm);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(idAlgorithm);

    Logger::get("muonIdSF")->debug("ID - Name {} test evaluate {}", idAlgorithm, evaluator->evaluate({1.0, 50,variation} ) );
    auto df1 = df.Define(
        id_output,
        [evaluator, variation]( const float &eta, const float &pt) {
            Logger::get("muonIdSF")->debug("ID - pt {}, eta {}", pt, eta);
            float sf = 1.;
            float tmp_pt = 0.;
            // preventing muons with default values due to tau energy correction
            // shifts below good tau pt selection
            // current 2022 Muon SF only supports muon with pt 15--200 GeVf
            if (pt >= 23.0 && std::abs(eta) < 2.5 ) {
                if (pt >=200) tmp_pt = 199.9;
                else tmp_pt = pt;
                sf = evaluator->evaluate(
                    { std::abs(eta), tmp_pt, variation});
            }
            return sf;
        },
        {pt, eta});
    return df1;
}
/**
 * @brief Function used to evaluate iso scale factors from muons with
 * correctionlib. Configurations:
 * - [UL2018 Muon
 * Iso](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/MUO_muon_Z_Run2_UL/MUO_muon_Z_2018_UL.html)
 * - [UL2017 Muon
 * Iso](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/MUO_muon_Z_Run2_UL/MUO_muon_Z_2017_UL.html)
 * - [UL2016preVFP Muon
 * Iso](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/MUO_muon_Z_Run2_UL/MUO_muon_Z_2016preVFP_UL.html)
 * - [UL2016postVFP Muon
 * Iso](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/MUO_muon_Z_Run2_UL/MUO_muon_Z_2016postVFP_UL.html)
 *
 * @param df The input dataframe
 * @param pt muon pt
 * @param eta muon eta
 * @param year_id id for the year of data taking and mc compaign
 * @param variation id for the variation of the scale factor "sf" for nominal
 * and "systup"/"systdown" the up/down variation
 * @param iso_output name of the iso scale factor column
 * @param sf_file path to the file with the muon scale factors
 * @param idAlgorithm name of the muon iso scale factor
 * @return a new dataframe containing the new column
 */
ROOT::RDF::RNode iso(ROOT::RDF::RNode df, const std::string &pt,
                     const std::string &eta,
                     const std::string &variation,
                     const std::string &iso_output, const std::string &sf_file,
                     const std::string &idAlgorithm) {

    Logger::get("muonIsoSF")->debug("Setting up functions for muon iso sf");
    Logger::get("muonIsoSF")->debug("ISO - Name {}", idAlgorithm);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(idAlgorithm);
    
    Logger::get("muonIsoSF")->debug("ISO - Name {} test evaluate {}", idAlgorithm, evaluator->evaluate({1.0, 50.0,variation} ) );
    auto df1 = df.Define(
        iso_output,
        [evaluator, variation](const float &pt, const float &eta) {
            Logger::get("muonIsoSF")->debug("ISO - pt {}, eta {}", pt, eta);
            float sf = 1.;
            float tmp_pt = 0.;
            // preventing muons with default values due to tau energy correction
            // shifts below good tau pt selection
            // current 2022 Muon SF only supports muon with pt 15--200 GeVf
            if (pt >= 23.0 && std::abs(eta) < 2.5) {
                if (pt >=200) tmp_pt = 199.9;
                else tmp_pt = pt;
                sf = evaluator->evaluate(
                    { std::abs(eta), tmp_pt, variation});
            }
            return sf;
        },
        {pt, eta});
    return df1;
}
} // namespace muon
namespace tau {
/**
 * @brief Function used to evaluate vsJets tau id scale factors in the lt
channel with
 * correctionlib

Description of the bit map used to define the tau id working points of the
DeepTau2017v2p1 tagger.
vsJets                              | Value | Bit (value used in the config)
------------------------------------|-------|-------
no ID selection (takes every tau)   |  0    | -
VVVLoose                            |  1    | 1
VVLoose                             |  2    | 2
VLoose                              |  4    | 3
Loose                               |  8    | 4
Medium                              |  16   | 5
Tight                               |  32   | 6
VTight                              |  64   | 7
VVTight                             |  128  | 8
 * @param df The input dataframe
 * @param pt tau pt
 * @param decayMode decay mode of the tau
 * @param genMatch column with genmatch values (from prompt e, prompt mu,
 * tau->e, tau->mu, had. tau)
 * @param selectedDMs list of allowed decay modes for which a scale factor
 * should be calculated
 * @param wp working point of the ID cut
 * @param sf_vsjet_tau30to35 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsjet_tau35to40 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsjet_tau40to500 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsjet_tau500to1000 id for the variation of the scale factor "sf"
for nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsjet_tau1000toinf id for the variation of the scale factor "sf"
for nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_dependence "pt", "dm" or "eta" based scale factors
 * @param id_output name of the id scale factor column
 * @param sf_file path to the file with the tau scale factors
 * @param idAlgorithm name of the tau id scale factor
 * @return a new dataframe containing the new column
 */
ROOT::RDF::RNode
id_vsJet_lt(ROOT::RDF::RNode df, const std::string &pt,
            const std::string &decayMode, const std::string &genMatch,
            const std::vector<UChar_t> &selectedDMs, const std::string &wp,
            const std::string &VSe_wp,
            const std::string &sf_vsjet_tau30to35,
            const std::string &sf_vsjet_tau35to40,
            const std::string &sf_vsjet_tau40to500,
            const std::string &sf_vsjet_tau500to1000,
            const std::string &sf_vsjet_tau1000toinf,
            const std::string &sf_dependence, const std::string &id_output,
            const std::string &sf_file, const std::string &idAlgorithm) {

    Logger::get("TauIDvsJet_lt_SF")
        ->debug("Setting up function for tau id vsJet sf");
    Logger::get("TauIDvsJet_lt_SF")->debug("ID - Name {}", idAlgorithm);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(idAlgorithm);
    auto idSF_calculator = [evaluator, wp, VSe_wp,sf_vsjet_tau30to35,
                            sf_vsjet_tau35to40, sf_vsjet_tau40to500,
                            sf_vsjet_tau500to1000, sf_vsjet_tau1000toinf,
                            sf_dependence, selectedDMs,
                            idAlgorithm](const float &pt, const UChar_t &decayMode,
                                         const UChar_t &genMatch) {
        Logger::get("TauIDvsJet_lt_SF")->debug("ID - decayMode {}", decayMode);
        // only calculate SFs for allowed tau decay modes (also excludes default
        // values due to tau energy correction shifts below good tau pt
        // selection)
        float sf = 1.;
        if (std::find(selectedDMs.begin(), selectedDMs.end(), decayMode) !=
            selectedDMs.end()) {
            Logger::get("TauIDvsJet_lt_SF")
                ->debug("ID {} - pt {}, decayMode {}, genMatch {}, wp {}, "
                        "sf_vsjet_tau30to35 {}, sf_vsjet_tau35to40 {}, "
                        "sf_vsjet_tau40to500{}, sf_vsjet_tau500to1000 {}, "
                        "sf_vsjet_tau1000toinf {}, sf_dependence {}",
                        idAlgorithm, pt, decayMode, genMatch, wp,
                        sf_vsjet_tau30to35, sf_vsjet_tau35to40,
                        sf_vsjet_tau40to500, sf_vsjet_tau500to1000,
                        sf_vsjet_tau1000toinf, sf_dependence);
            if (pt >= 30.0 && pt < 35.0) {
                sf = evaluator->evaluate({pt, decayMode,
                                          static_cast<int>(genMatch), wp,VSe_wp,
                                          sf_vsjet_tau30to35, sf_dependence});
            } else if (pt >= 35.0 && pt < 40.0) {
                sf = evaluator->evaluate({pt, decayMode,
                                          static_cast<int>(genMatch), wp,VSe_wp,
                                          sf_vsjet_tau35to40, sf_dependence});
            } else if (pt >= 40.0 && pt < 500.0) {
                sf = evaluator->evaluate({pt, decayMode,
                                          static_cast<int>(genMatch), wp,VSe_wp, 
                                          sf_vsjet_tau40to500, sf_dependence});
            } else if (pt >= 500.0 && pt < 1000.0) {
                sf = evaluator->evaluate(
                    {pt, decayMode, static_cast<int>(genMatch), wp,VSe_wp,
                     sf_vsjet_tau500to1000, sf_dependence});
            } else if (pt >= 1000.0 && pt < 2000.0) {
                sf = evaluator->evaluate(
                    {pt, decayMode, static_cast<int>(genMatch), wp,VSe_wp,
                     sf_vsjet_tau1000toinf, sf_dependence});
            } else {
                sf = 1.;
            }
        }
        Logger::get("TauIDvsJet_lt_SF")->debug("Scale Factor {}", sf);
        return sf;
    };
    auto df1 = df.Define(id_output, idSF_calculator, {pt, decayMode, genMatch});
    return df1;
}
/**
 * @brief Function used to evaluate vsJets tau id scale factors in the lt
channel with the correctionlib for tauembedded samples


 * @param df The input dataframe
 * @param pt tau pt
 * @param wp working point of the ID cut
 * @param sf_vsjet_tau20to25 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsjet_tau25to30 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsjet_tau30to35 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsjet_tau35to40 id for the variation of the scale factor "sf"
for nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsjet_tau40toInf id for the variation of the scale factor "sf"
for nominal
 * and "systup"/"systdown" the up/down variation
 * @param id_output name of the id scale factor column
 * @param sf_file path to the file with the tau scale factors
 * @param correctionset name of the correction set containing the tau id scale
factor
 * @return a new dataframe containing the new column
 */
ROOT::RDF::RNode id_vsJet_lt_embedding(
    ROOT::RDF::RNode df, const std::string &pt, const std::string &wp,
    const std::string &sf_vsjet_tau20to25,
    const std::string &sf_vsjet_tau25to30,
    const std::string &sf_vsjet_tau30to35,
    const std::string &sf_vsjet_tau35to40,
    const std::string &sf_vsjet_tau40toInf, const std::string &id_output,
    const std::string &sf_file, const std::string &correctionset) {

    Logger::get("TauIDvsJet_lt_SF_embedding")
        ->debug("Setting up function for tau id vsJet sf");
    Logger::get("TauIDvsJet_lt_SF_embedding")
        ->debug("ID - Name {}", correctionset);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(correctionset);
    auto idSF_calculator = [evaluator, wp, sf_vsjet_tau20to25,
                            sf_vsjet_tau25to30, sf_vsjet_tau30to35,
                            sf_vsjet_tau35to40, sf_vsjet_tau40toInf,
                            correctionset](const float &pt) {
        float sf = 1.;
        Logger::get("TauIDvsJet_lt_SF_embedding")
            ->debug("ID {} - pt {}, wp {} "
                    "sf_vsjet_tau20to25 {}, sf_vsjet_tau25to30 {}, "
                    "sf_vsjet_tau30to35{}, sf_vsjet_tau35to40 {}, "
                    "sf_vsjet_tau40toInf {},",
                    correctionset, pt, wp, sf_vsjet_tau20to25,
                    sf_vsjet_tau25to30, sf_vsjet_tau30to35, sf_vsjet_tau35to40,
                    sf_vsjet_tau40toInf);
        // if (pt >= 20.0 && pt < 25.0) {
        //     sf = evaluator->evaluate({pt, sf_vsjet_tau20to25, wp});
        // } else 
        if (pt >= 25.0 && pt < 30.0) {
            sf = evaluator->evaluate({pt, sf_vsjet_tau25to30, wp});
        } else if (pt >= 30.0 && pt < 35.0) {
            sf = evaluator->evaluate({pt, sf_vsjet_tau30to35, wp});
        } else if (pt >= 35.0 && pt < 40.0) {
            sf = evaluator->evaluate({pt, sf_vsjet_tau35to40, wp});
        } else if (pt >= 40.0 && pt < 10000.0) {
            sf = evaluator->evaluate({pt, sf_vsjet_tau40toInf, wp});
        } else {
            sf = 1.;
        }
        Logger::get("TauIDvsJet_lt_SF_embedding")->debug("Scale Factor {}", sf);
        return sf;
    };
    auto df1 = df.Define(id_output, idSF_calculator, {pt});
    return df1;
}
/**
 * @brief Function used to evaluate vsJets tau id scale factors in the tt
channel with the correctionlib for tauembedded samples

 * @param df The input dataframe
 * @param decaymode decay mode of the tau
 * @param wp working point of the ID cut
 * @param sf_vsjet_tauDM0 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsjet_tauDM1 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsjet_tauDM10 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsjet_tauDM11 id for the variation of the scale factor "sf"
for nominal
 * and "systup"/"systdown" the up/down variation
 * @param id_output name of the id scale factor column
 * @param sf_file path to the file with the tau scale factors
 * @param correctionset name of the correction set containing the tau id scale
factor
 * @return a new dataframe containing the new column
 */
ROOT::RDF::RNode id_vsJet_tt_embedding(
    ROOT::RDF::RNode df, const std::string &decaymode, const std::string &wp,
    const std::string &sf_vsjet_tauDM0, const std::string &sf_vsjet_tauDM1,
    const std::string &sf_vsjet_tauDM10, const std::string &sf_vsjet_tauDM11,
    const std::string &id_output, const std::string &sf_file,
    const std::string &correctionset) {

    Logger::get("TauIDvsJet_tt_SF_embedding")
        ->debug("Setting up function for tau id vsJet sf");
    Logger::get("TauIDvsJet_tt_SF_embedding")
        ->debug("ID - Name {}", correctionset);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(correctionset);
    auto idSF_calculator = [evaluator, wp, sf_vsjet_tauDM0, sf_vsjet_tauDM1,
                            sf_vsjet_tauDM10, sf_vsjet_tauDM11,
                            correctionset](const UChar_t &decaymode) {
        float sf = 1.;
        Logger::get("TauIDvsJet_tt_SF_embedding")
            ->debug("ID {} - decaymode {}, wp {} "
                    "sf_vsjet_tauDM0 {}, sf_vsjet_tauDM1 {}, "
                    "sf_vsjet_tauDM10{}, sf_vsjet_tauDM11 {}, ",
                    correctionset, decaymode, wp, sf_vsjet_tauDM0,
                    sf_vsjet_tauDM1, sf_vsjet_tauDM10, sf_vsjet_tauDM11);
        if (decaymode == 0) {
            sf = evaluator->evaluate({decaymode, sf_vsjet_tauDM0, wp});
        } else if (decaymode == 1) {
            sf = evaluator->evaluate({decaymode, sf_vsjet_tauDM1, wp});
        } else if (decaymode == 10) {
            sf = evaluator->evaluate({decaymode, sf_vsjet_tauDM10, wp});
        } else if (decaymode == 11) {
            sf = evaluator->evaluate({decaymode, sf_vsjet_tauDM11, wp});
        } else {
            sf = 1.;
        }
        Logger::get("TauIDvsJet_tt_SF_embedding")->debug("Scale Factor {}", sf);
        return sf;
    };
    auto df1 = df.Define(id_output, idSF_calculator, {decaymode});
    return df1;
}
/**
 * @brief Function used to evaluate vsJets tau id scale factors in the tt
channel with
 * correctionlib

Description of the bit map used to define the tau id working points of the
DeepTau2017v2p1 tagger.
vsJets                              | Value | Bit (value used in the config)
------------------------------------|-------|-------
no ID selection (takes every tau)   |  0    | -
VVVLoose                            |  1    | 1
VVLoose                             |  2    | 2
VLoose                              |  4    | 3
Loose                               |  8    | 4
Medium                              |  16   | 5
Tight                               |  32   | 6
VTight                              |  64   | 7
VVTight                             |  128  | 8
 * @param df The input dataframe
 * @param pt tau pt
 * @param decayMode decay mode of the tau
 * @param genMatch column with genmatch values (from prompt e, prompt mu,
 * tau->e, tau->mu, had. tau)
 * @param selectedDMs list of allowed decay modes for which a scale factor
 * should be calculated
 * @param wp working point of the ID cut
 * @param sf_vsjet_tauDM0 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsjet_tauDM1 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsjet_tauDM10 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsjet_tauDM11 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_dependence "pt", "dm" or "eta" based scale factors
 * @param id_output name of the id scale factor column
 * @param sf_file path to the file with the tau scale factors
 * @param idAlgorithm name of the tau id scale factor
 * @return a new dataframe containing the new column
 */
ROOT::RDF::RNode id_vsJet_tt(
    ROOT::RDF::RNode df, const std::string &pt, const std::string &decayMode,
    const std::string &genMatch, const std::vector<UChar_t> &selectedDMs,
    const std::string &wp, const std::string &VSe_wp,
    const std::string &sf_vsjet_tauDM0,
    const std::string &sf_vsjet_tauDM1, const std::string &sf_vsjet_tauDM10,
    const std::string &sf_vsjet_tauDM11, const std::string &sf_dependence,
    const std::string &id_output, const std::string &sf_file,
    const std::string &idAlgorithm) {

    Logger::get("TauIDvsJet_tt_SF")
        ->debug("Setting up function for tau id vsJet sf");
    Logger::get("TauIDvsJet_tt_SF")->debug("ID - Name {}", idAlgorithm);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(idAlgorithm);
    auto idSF_calculator = [evaluator, wp, VSe_wp,sf_vsjet_tauDM0, sf_vsjet_tauDM1,
                            sf_vsjet_tauDM10, sf_vsjet_tauDM11, sf_dependence,
                            selectedDMs,
                            idAlgorithm](const float &pt, const UChar_t &decayMode,
                                         const UChar_t &genMatch) {
        Logger::get("TauIDvsJet_tt_SF")->debug("ID - decayMode {}", decayMode);
        // only calculate SFs for allowed tau decay modes (also excludes default
        // values due to tau energy correction shifts below good tau pt
        // selection)
        float sf = 1.;
        if (std::find(selectedDMs.begin(), selectedDMs.end(), decayMode) !=
            selectedDMs.end() && pt >=25.0) {
            Logger::get("TauIDvsJet_tt_SF")->debug("ID {} - pt {}",idAlgorithm, pt);
            Logger::get("TauIDvsJet_tt_SF")->debug(" decayMode {}, genMatch {}, wp {}, ",decayMode, genMatch, wp);
            Logger::get("TauIDvsJet_tt_SF")->debug("sf_vsjet_tauDM0 {}, sf_vsjet_tauDM1 {},  sf_vsjet_tauDM10{}, sf_vsjet_tauDM11 {}, sf_dependence {}",
                        sf_vsjet_tauDM0, sf_vsjet_tauDM1, sf_vsjet_tauDM10,
                        sf_vsjet_tauDM11, sf_dependence);
            if (decayMode == 0) {
                sf = evaluator->evaluate({pt, decayMode,
                                          static_cast<int>(genMatch), wp,VSe_wp,
                                          sf_vsjet_tauDM0, sf_dependence});
            } else if (decayMode == 1) {
                sf = evaluator->evaluate({pt, decayMode,
                                          static_cast<int>(genMatch), wp,VSe_wp,
                                          sf_vsjet_tauDM1, sf_dependence});
            } else if (decayMode == 10) {
                sf = evaluator->evaluate({pt, decayMode,
                                          static_cast<int>(genMatch), wp,VSe_wp,
                                          sf_vsjet_tauDM10, sf_dependence});
            } else if (decayMode == 11) {
                sf = evaluator->evaluate({pt, decayMode,
                                          static_cast<int>(genMatch), wp,VSe_wp,
                                          sf_vsjet_tauDM11, sf_dependence});
            } else {
                sf = 1.;
            }
        }
        Logger::get("TauIDvsJet_tt_SF")->debug("Scale Factor {}", sf);
        return sf;
    };
    auto df1 = df.Define(id_output, idSF_calculator, {pt, decayMode, genMatch});
    return df1;
}
/**
 * @brief Function used to evaluate vsEle tau id scale factors with
 * correctionlib

Description of the bit map used to define the tau id working points of the
DeepTau2017v2p1 tagger.
vsElectrons                         | Value | Bit (value used in the config)
------------------------------------|-------|-------
no ID selection (takes every tau)   |  0    | -
VVVLoose                            |  1    | 1
VVLoose                             |  2    | 2
VLoose                              |  4    | 3
Loose                               |  8    | 4
Medium                              |  16   | 5
Tight                               |  32   | 6
VTight                              |  64   | 7
VVTight                             |  128  | 8

vsMuons                             | Value | Bit (value used in the config)
------------------------------------|-------|-------
no ID selection (takes every tau)   |  0    | -
VLoose                              |  1    | 1
Loose                               |  2    | 2
Medium                              |  4    | 3
Tight                               |  8    | 4
 * @param df The input dataframe
 * @param eta tau eta
 * @param decayMode decay mode of the tau
 * @param genMatch column with genmatch values (from prompt e, prompt mu,
 * tau->e, tau->mu, had. tau)
 * @param selectedDMs list of allowed decay modes for which a scale factor
 * should be calculated
 * @param wp working point of the ID cut
 * @param sf_vsele_barrel id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsele_endcap id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param id_output name of the id scale factor column
 * @param sf_file path to the file with the tau scale factors
 * @param idAlgorithm name of the tau id scale factor
 * @return a new dataframe containing the new column
 */
ROOT::RDF::RNode
id_vsEle(ROOT::RDF::RNode df, const std::string &eta,
         const std::string &decayMode, const std::string &genMatch,
         const std::vector<UChar_t> &selectedDMs, const std::string &wp,
         const std::string &sf_vsele_barrel, const std::string &sf_vsele_endcap,
         const std::string &id_output, const std::string &sf_file,
         const std::string &idAlgorithm) {

    Logger::get("TauIDvsEleSF")
        ->debug("Setting up function for tau id vsEle sf");
    Logger::get("TauIDvsEleSF")->debug("ID - Name {}", idAlgorithm);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(idAlgorithm);
    auto idSF_calculator = [evaluator, wp, sf_vsele_barrel, sf_vsele_endcap,
                            selectedDMs,
                            idAlgorithm](const float &eta, const UChar_t &decayMode,
                                         const UChar_t &genMatch) {
        float sf = 1.;
        Logger::get("TauIDvsEleSF")->debug("ID - decayMode {}", decayMode);
        // only calculate SFs for allowed tau decay modes (also excludes
        // default values due to tau energy correction shifts below good tau
        // pt selection)
        if (std::find(selectedDMs.begin(), selectedDMs.end(), decayMode) !=
            selectedDMs.end()) {
            Logger::get("TauIDvsEleSF")
                ->debug("ID {} - eta {}, genMatch {}, wp {}, sf_vsele_barrel "
                        "{}, sf_vsele_endcap {}",
                        idAlgorithm, eta, genMatch, wp, sf_vsele_barrel,
                        sf_vsele_endcap);
            if (std::abs(eta) < 1.46) {
                sf = evaluator->evaluate(
                    {eta, decayMode, static_cast<int>(genMatch), wp, sf_vsele_barrel});
            } else if (std::abs(eta) >= 1.56 && std::abs(eta) < 2.5) {
                sf = evaluator->evaluate(
                    {eta, decayMode, static_cast<int>(genMatch), wp, sf_vsele_endcap});
            } else {
                sf = 1.;
            }
        }
        Logger::get("TauIDvsEleSF")->debug("Scale Factor {}", sf);
        return sf;
    };
    auto df1 =
        df.Define(id_output, idSF_calculator, {eta, decayMode, genMatch});
    return df1;
}
/**
 * @brief Function used to evaluate vsMu tau id scale factors with
 * correctionlib

Description of the bit map used to define the tau id working points of the
DeepTau2017v2p1 tagger.
vsElectrons                         | Value | Bit (value used in the config)
------------------------------------|-------|-------
no ID selection (takes every tau)   |  0    | -
VVVLoose                            |  1    | 1
VVLoose                             |  2    | 2
VLoose                              |  4    | 3
Loose                               |  8    | 4
Medium                              |  16   | 5
Tight                               |  32   | 6
VTight                              |  64   | 7
VVTight                             |  128  | 8

vsMuons                             | Value | Bit (value used in the config)
------------------------------------|-------|-------
no ID selection (takes every tau)   |  0    | -
VLoose                              |  1    | 1
Loose                               |  2    | 2
Medium                              |  4    | 3
Tight                               |  8    | 4
 * @param df The input dataframe
 * @param eta tau eta
 * @param decayMode decay mode of the tau
 * @param genMatch column with genmatch values (from prompt e, prompt mu,
 * tau->e, tau->mu, had. tau)
 * @param selectedDMs list of allowed decay modes for which a scale factor
 * should be calculated
 * @param wp working point of the ID cut
 * @param sf_vsmu_wheel1 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsmu_wheel2 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsmu_wheel3 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsmu_wheel4 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param sf_vsmu_wheel5 id for the variation of the scale factor "sf" for
nominal
 * and "systup"/"systdown" the up/down variation
 * @param id_output name of the id scale factor column
 * @param sf_file path to the file with the tau scale factors
 * @param idAlgorithm name of the tau id scale factor
 * @return a new dataframe containing the new column
 */
ROOT::RDF::RNode
id_vsMu(ROOT::RDF::RNode df, const std::string &eta,
        const std::string &decayMode, const std::string &genMatch,
        const std::vector<UChar_t> &selectedDMs, const std::string &wp,
        const std::string &sf_vsmu_wheel1, const std::string &sf_vsmu_wheel2,
        const std::string &sf_vsmu_wheel3, const std::string &sf_vsmu_wheel4,
        const std::string &sf_vsmu_wheel5, const std::string &id_output,
        const std::string &sf_file, const std::string &idAlgorithm) {

    Logger::get("TauIDvsMuSF")->debug("Setting up function for tau id vsMu sf");
    Logger::get("TauIDvsMuSF")->debug("ID - Name {}", idAlgorithm);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(idAlgorithm);
    auto idSF_calculator = [evaluator, wp, sf_vsmu_wheel1, sf_vsmu_wheel2,
                            sf_vsmu_wheel3, sf_vsmu_wheel4, sf_vsmu_wheel5,
                            selectedDMs,
                            idAlgorithm](const float &eta, const UChar_t &decayMode,
                                         const UChar_t &genMatch) {
        float sf = 1.;
        Logger::get("TauIDvsMuSF")->debug("ID - decayMode {}", decayMode);
        // only calculate SFs for allowed tau decay modes (also excludes
        // default values due to tau energy correction shifts below good tau
        // pt selection)
        if (std::find(selectedDMs.begin(), selectedDMs.end(), decayMode) !=
            selectedDMs.end()) {
            Logger::get("TauIDvsMuSF")
                ->debug("ID {} - eta {}, genMatch {}, wp {}, sf_vsmu_wheel1 "
                        "{}, sf_vsmu_wheel2 {}, sf_vsmu_wheel3 {}, "
                        "sf_vsmu_wheel4 {}, sf_vsmu_wheel5 {}",
                        idAlgorithm, eta, genMatch, wp, sf_vsmu_wheel1,
                        sf_vsmu_wheel2, sf_vsmu_wheel3, sf_vsmu_wheel4,
                        sf_vsmu_wheel5);
            if (std::abs(eta) < 0.4) {
                sf = evaluator->evaluate(
                    {eta, static_cast<int>(genMatch), wp, sf_vsmu_wheel1});
            } else if (std::abs(eta) >= 0.4 && std::abs(eta) < 0.8) {
                sf = evaluator->evaluate(
                    {eta, static_cast<int>(genMatch), wp, sf_vsmu_wheel2});
            } else if (std::abs(eta) >= 0.8 && std::abs(eta) < 1.2) {
                sf = evaluator->evaluate(
                    {eta, static_cast<int>(genMatch), wp, sf_vsmu_wheel3});
            } else if (std::abs(eta) >= 1.2 && std::abs(eta) < 1.7) {
                sf = evaluator->evaluate(
                    {eta, static_cast<int>(genMatch), wp, sf_vsmu_wheel4});
            } else if (std::abs(eta) >= 1.7 && std::abs(eta) < 2.4) {
                sf = evaluator->evaluate(
                    {eta, static_cast<int>(genMatch), wp, sf_vsmu_wheel5});
            } else {
                sf = 1.0;
            }
        }
        Logger::get("TauIDvsMuSF")->debug("Scale Factor {}", sf);
        return sf;
    };
    auto df1 =
        df.Define(id_output, idSF_calculator, {eta, decayMode, genMatch});
    return df1;
}

/**
 * @brief Function to evaluate the tau trigger scale factor from a xpog file
 *
 * @param df the input dataframe
 * @param decaymode the name of the column containing the tau decay mode
 * variable
 * @param wp the name of the the tau id working point
 * @param type the type of the tau trigger scale factor, available are emb and
 * mc
 * @param pt the name of the column containing the tau pt variable
 * @param id_output name of the id scale factor column
 * @param sf_file path to the file with the tau scale factors
 * @param correctionset name of the tau trigger scale factor
 * @return ROOT::RDF::RNode a new dataframe containing the new sf column
 */

ROOT::RDF::RNode
tau_trigger_sf(ROOT::RDF::RNode df, const std::string &decaymode,
               const std::string &pt, const std::string &wp,
               const std::string &type, const std::string &id_output,
               const std::string &sf_file, const std::string &correctionset) {

    Logger::get("tau_trigger_sf")
        ->info("Setting up function for tau trigger sf");
    Logger::get("tau_trigger_sf")
        ->info("ID - Name {}, file {}", correctionset, sf_file);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(correctionset);
    Logger::get("tau_trigger_sf")->info("WP {} - type {}", wp, type);
    auto trigger_sf_calculator = [evaluator, wp, type, correctionset](
                                     const UChar_t &decaymode, const float &pt) {
        float sf = 1.;
        Logger::get("tau_trigger_sf")
            ->info("ID {} - decaymode {}, wp {} "
                   "pt {}, type {}, ",
                   correctionset, decaymode, wp, pt, type);
        sf = evaluator->evaluate({decaymode, wp, type, pt});
        Logger::get("tau_trigger_sf")->info("Scale Factor {}", sf);
        return sf;
    };
    auto df1 = df.Define(id_output, trigger_sf_calculator, {decaymode, pt});
    return df1;
}
} // namespace tau

namespace electron {
/**
 * @brief Function used to evaluate id scale factors of electrons with
 * correctionlib, configurations:
 * - [UL2018 Electron
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/EGM_electron_Run2_UL/EGM_electron_2018_UL.html)
 * - [UL2017 Electron
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/EGM_electron_Run2_UL/EGM_electron_2017_UL.html)
 * - [UL2016preVFP Electron
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/EGM_electron_Run2_UL/EGM_electron_2016preVFP_UL.html)
 * - [UL2016postVFP Electron
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/EGM_electron_Run2_UL/EGM_electron_2016postVFP_UL.html)
 * @param df The input dataframe
 * @param pt electron pt
 * @param eta electron eta
 * @param year_id id for the year of data taking and mc compaign
 * @param wp wp of the electron id
 * @param variation id for the variation of the scale factor. Available Values:
 * sf, sfdown, sfup
 * @param id_output name of the id scale factor column
 * @param sf_file path to the file with the electron scale factors
 * @param idAlgorithm name of the electron id scale factor
 * @return a new dataframe containing the new column
 */
ROOT::RDF::RNode id(ROOT::RDF::RNode df, const std::string &pt,
                    const std::string &eta, const std::string &year_id,
                    const std::string &wp, const std::string &variation,
                    const std::string &id_output, const std::string &sf_file,
                    const std::string &idAlgorithm) {

    Logger::get("electronIDSF")
        ->debug("Setting up functions for electron id sf with correctionlib");
    Logger::get("electronIDSF")->debug("ID - Name {}", idAlgorithm);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(idAlgorithm);
    auto df1 = df.Define(
        id_output,
        [evaluator, year_id, idAlgorithm, wp, variation](const float &pt,
                                                         const float &eta) {
            Logger::get("electronIDSF")
                ->debug("Year {}, Name {}, WP {}", year_id, idAlgorithm, wp);
            Logger::get("electronIDSF")->debug("ID - pt {}, eta {}", pt, eta);
            float sf = 1.;
            // in 2022 the order of input is year_id, variation, wp, eta, pt
            if (pt >= 25.0) {
                sf = evaluator->evaluate({year_id, variation, wp, eta, pt});
            }
            Logger::get("electronIDSF")->debug("Scale Factor {}", sf);
            return sf;
        },
        {pt, eta});
    return df1;
}
ROOT::RDF::RNode id_2023(ROOT::RDF::RNode df, const std::string &pt,
                    const std::string &eta, const std::string &phi, const std::string &year_id,
                    const std::string &wp, const std::string &variation,
                    const std::string &id_output, const std::string &sf_file,
                    const std::string &idAlgorithm) {

    Logger::get("electronIDSF")
        ->debug("Setting up functions for electron id sf with correctionlib");
    Logger::get("electronIDSF")->debug("ID - Name {}", idAlgorithm);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(idAlgorithm);
    auto df1 = df.Define(
        id_output,
        [evaluator, year_id, idAlgorithm, wp, variation](const float &pt,
                                                         const float &eta, const float &phi) {
            Logger::get("electronIDSF")
                ->debug("Year {}, Name {}, WP {}", year_id, idAlgorithm, wp);
            Logger::get("electronIDSF")->debug("ID - pt {}, eta {}, phi {}", pt, eta, phi);
            float sf = 1.;
            // in 2022 the order of input is year_id, variation, wp, eta, pt
            if (pt >= 25.0) {
                sf = evaluator->evaluate({year_id, variation, wp, eta, pt, phi});
            }
            Logger::get("electronIDSF")->debug("Scale Factor {}", sf);
            return sf;
        },
        {pt, eta, phi});
    return df1;
}

} // namespace electron
namespace jet {
/**
 * @brief Function used to evaluate b-tagging scale factors of jets with
 * correctionlib, configurations:
 * - [UL2018 b-tagging
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/BTV_btagging_Run2_UL/BTV_btagging_2018_UL.html)
 * - [UL2017 b-tagging
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/BTV_btagging_Run2_UL/BTV_btagging_2017_UL.html)
 * - [UL2016preVFP b-tagging
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/BTV_btagging_Run2_UL/BTV_btagging_2016preVFP_UL.html)
 * - [UL2016postVFP b-tagging
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/BTV_btagging_Run2_UL/BTV_btagging_2016postVFP_UL.html)
 * @param df The input dataframe
 * @param pt jet pt
 * @param eta jet eta
 * @param btag_discr btag value of a jet based on a b-jet tagger (e.g. DeepJet)
 * @param flavor flavor of the jet
 * @param jet_mask mask for good/selected jets
 * @param bjet_mask mask for good/selected b jets
 * @param jet_veto_mask veto mask for overlapping jets
 * @param variation id for the variation of the scale factor. Available Values:
 * central, down_*, up_* (* name of variation)
 * @param sf_output name of the scale factor column
 * @param sf_file path to the file with the btagging scale factors
 * @param corr_algorithm name of the btagging correction algorithm
 * @return a new dataframe containing the new column
 */
ROOT::RDF::RNode
btagSF(ROOT::RDF::RNode df, const std::string &pt, const std::string &eta,
       const std::string &btag_discr, const std::string &flavor,
       const std::string &jet_mask, const std::string &bjet_mask,
       const std::string &jet_veto_mask, const std::string &variation,
       const std::string &sf_output, const std::string &sf_file,
       const std::string &corr_algorithm) {
    Logger::get("btagSF")->debug(
        "Setting up functions for b-tag sf with correctionlib");
    Logger::get("btagSF")->debug("Correction algorithm - Name {}",
                                 corr_algorithm);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(corr_algorithm);
    Logger::get("btagSF")->debug("ID - Name {} test evaluate {}", corr_algorithm, evaluator->evaluate({"central", 5, 1.0, 50.0,0.2} ) );

    auto btagSF_lambda = [evaluator,
                          variation](const ROOT::RVec<float> &pt_values,
                                     const ROOT::RVec<float> &eta_values,
                                     const ROOT::RVec<float> &btag_values,
                                     const ROOT::RVec<UChar_t> &flavors,
                                     const ROOT::RVec<int> &jet_mask,
                                     const ROOT::RVec<int> &bjet_mask,
                                     const ROOT::RVec<int> &jet_veto_mask) {
        Logger::get("btagSF")->debug("Vatiation - Name {}", variation);
        float sf = 1.;
        for (int i = 0; i < pt_values.size(); i++) {
            Logger::get("btagSF")->debug(
                "jet masks - jet {}, bjet {}, jet veto {}", jet_mask.at(i),
                bjet_mask.at(i), jet_veto_mask.at(i));
            // considering only good jets/bjets, this is needed since jets and
            // bjets might have different cuts depending on the analysis
            if ((jet_mask.at(i) || bjet_mask.at(i)) && jet_veto_mask.at(i)) {
                Logger::get("btagSF")->debug(
                    "SF - pt {}, eta {}, btag value {}, flavor {}",
                    pt_values.at(i), eta_values.at(i), btag_values.at(i),
                    flavors.at(i));
                float jet_sf = 1.;
                // considering only phase space where the scale factors are
                // defined
                float btag_tmp_values = btag_values.at(i);
                if (btag_values.at(i) < 0){
                    btag_tmp_values = 0;
                }
                Logger::get("btagSF")->debug("btag_tmp_values {}", btag_tmp_values);
                if (pt_values.at(i) >= 20.0 && pt_values.at(i) < 10000.0 &&
                    std::abs(eta_values.at(i)) < 2.5) {
                    // for c jet related uncertainties only scale factors of
                    // c-jets are varied, the rest is nominal/central
                    if (variation.find("cferr") != std::string::npos) {
                        // flavor=4 means c-flavor
                        if (flavors.at(i) == 4) {
                            jet_sf = evaluator->evaluate(
                                {variation, flavors.at(i),
                                 std::abs(eta_values.at(i)), pt_values.at(i),
                                 btag_tmp_values});
                        } else {
                            jet_sf = evaluator->evaluate(
                                {"central", flavors.at(i),
                                 std::abs(eta_values.at(i)), pt_values.at(i),
                                 btag_tmp_values});
                        }
                    }
                    // for nominal/central and all other uncertainties c-jets
                    // have a scale factor of 1 (only for central defined in
                    // json file from BTV)
                    else {
                        if (flavors.at(i) != 4) {
                            jet_sf = evaluator->evaluate(
                                {variation, flavors.at(i),
                                 std::abs(eta_values.at(i)), pt_values.at(i),
                                 btag_tmp_values});
                        } else {
                            jet_sf = evaluator->evaluate(
                                {"central", flavors.at(i),
                                 std::abs(eta_values.at(i)), pt_values.at(i),
                                 btag_tmp_values});
                        }
                    }
                }
                Logger::get("btagSF")->debug("Jet Scale Factor {}", jet_sf);
                sf *= jet_sf;
            }
        };
        Logger::get("btagSF")->debug("Event Scale Factor {}", sf);
        return sf;
    };
    auto df1 = df.Define(
        sf_output, btagSF_lambda,
        {pt, eta, btag_discr, flavor, jet_mask, bjet_mask, jet_veto_mask});
    return df1;
}



/**
 * @brief Function used to evaluate b-tagging scale factors of jets with
 * correctionlib, configurations:
 * - [UL2018 b-tagging
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/BTV_btagging_Run2_UL/BTV_btagging_2018_UL.html)
 * - [UL2017 b-tagging
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/BTV_btagging_Run2_UL/BTV_btagging_2017_UL.html)
 * - [UL2016preVFP b-tagging
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/BTV_btagging_Run2_UL/BTV_btagging_2016preVFP_UL.html)
 * - [UL2016postVFP b-tagging
 * ID](https://cms-nanoaod-integration.web.cern.ch/commonJSONSFs/BTV_btagging_Run2_UL/BTV_btagging_2016postVFP_UL.html)
 * @param df The input dataframe
 * @param pt jet pt
 * @param eta jet eta
 * @param btag_discr btag value of a jet based on a b-jet tagger (e.g. DeepJet)
 * @param flavor flavor of the jet
 * @param jet_mask mask for good/selected jets
 * @param bjet_mask mask for good/selected b jets
 * @param jet_veto_mask veto mask for overlapping jets
 * @param variation id for the variation of the scale factor. Available Values:
 * central, down_*, up_* (* name of variation)
 * @param sf_output name of the scale factor column
 * @param sf_file path to the file with the btagging scale factors
 * @return a new dataframe containing the new column
 */
 ROOT::RDF::RNode
 btagSF_FixedWP(ROOT::RDF::RNode df, const std::string &pt, const std::string &eta,
        const std::string &btag_discr, const std::string &flavor,
        const std::string &jet_mask, const std::string &bjet_mask,
        const std::string &jet_veto_mask, const std::string &variation,
        const std::string &sf_output, const std::string &sf_file, const std::string &eff_file, const std::string &btag_eff_type,
        const std::string &year, const std::string &channel, const float &btag_cut, const std::string &btag_sf_flavour) {
     
     

     
     std::string eff_file_local = eff_file + "/" + btag_eff_type + "/btagging_effciency.json";
     
     auto evaluator_bc = correction::CorrectionSet::from_file(sf_file)->at("particleNet_comb");
     auto evaluator_light = correction::CorrectionSet::from_file(sf_file)->at("particleNet_light");
     auto btag_eff = correction::CorrectionSet::from_file(eff_file_local)->at("Btagging effciency[pt,eta,flavor]");
     
 
     auto btagSF_lambda = [evaluator_bc, evaluator_light, btag_eff,variation, year, channel, btag_cut,btag_sf_flavour](const ROOT::RVec<float> &pt_values,
                                      const ROOT::RVec<float> &eta_values,
                                      const ROOT::RVec<float> &btag_values,
                                      const ROOT::RVec<UChar_t> &flavors,
                                      const ROOT::RVec<int> &jet_mask,
                                      const ROOT::RVec<int> &bjet_mask,
                                      const ROOT::RVec<int> &jet_veto_mask) {
         Logger::get("btagSF")->debug("Vatiation - Name {}", variation);
         float sf = 1.;
         for (int i = 0; i < pt_values.size(); i++) {
             Logger::get("btagSF")->debug(
                 "jet masks - jet {}, bjet {}, jet veto {}", jet_mask.at(i),
                 bjet_mask.at(i), jet_veto_mask.at(i));
             // considering only good jets/bjets, this is needed since jets and
             // bjets might have different cuts depending on the analysis
             if ((jet_mask.at(i) || bjet_mask.at(i)) && jet_veto_mask.at(i) && pt_values.at(i) >= 20.0 && pt_values.at(i) < 10000.0 && std::abs(eta_values.at(i)) < 2.5 &&  btag_values.at(i) > 0 ) {
                auto bjet_sf = 1.0;
                auto pt_tmp = 0.0;
                if ( pt_values.at(i) >= 200) {pt_tmp = 199.99; } else pt_tmp=  pt_values.at(i) ;


                // for difference case: if evaluate light variation, use light SF and light flavor, vice versa. 
                if (btag_sf_flavour.find("light") != std::string::npos) {
                    if ( flavors.at(i) == 0) {
                        bjet_sf = evaluator_light->evaluate({variation, "M", flavors.at(i), std::abs(eta_values.at(i)), pt_values.at(i)  });}
                    else {
                        bjet_sf = evaluator_bc->evaluate({"central", "M", flavors.at(i), std::abs(eta_values.at(i)), pt_values.at(i)  });}
                }   
                else {
                    if ( flavors.at(i) == 0) {
                        bjet_sf = evaluator_light->evaluate({"central", "M", flavors.at(i), std::abs(eta_values.at(i)), pt_values.at(i)  });}
                    else {
                        bjet_sf = evaluator_bc->evaluate({variation, "M", flavors.at(i), std::abs(eta_values.at(i)), pt_values.at(i)  });}
                }

                auto  bjet_eff =  btag_eff->evaluate({year, "btagging-eff", channel, pt_tmp, eta_values.at(i), flavors.at(i)  });
                if (btag_values.at(i) > btag_cut) { sf *= (bjet_sf * bjet_eff/bjet_eff); }
                else{  sf *= ( (1 - bjet_sf * bjet_eff) /(1 - bjet_eff));   }
             }
         };
         
         return sf;
     };
     auto df1 = df.Define(
         sf_output, btagSF_lambda,
         {pt, eta, btag_discr, flavor, jet_mask, bjet_mask, jet_veto_mask});
     return df1;
     } 


ROOT::RDF::RNode
btagSF_FixedWP_signal(ROOT::RDF::RNode df, const std::string &pt, const std::string &eta,
                 const std::string &btag_discr, const std::string &flavor,
                 const std::string &jet_mask, const std::string &bjet_mask,
                 const std::string &jet_veto_mask, const std::string &gen_higgs_mass,  
                 const std::string &variation,
                 const std::string &sf_output, const std::string &sf_file, const std::string &eff_file,
                 const std::string &year, const float &btag_cut,  const std::string &btag_sf_flavour) {
              
              auto evaluator_bc = correction::CorrectionSet::from_file(sf_file)->at("particleNet_comb");
              auto evaluator_light = correction::CorrectionSet::from_file(sf_file)->at("particleNet_light");
             //  auto btag_eff = correction::CorrectionSet::from_file(eff_file)->at("Btagging effciency[pt,eta,flavor]");
             std::map<float, std::shared_ptr<const correction::Correction>> btag_eff;
             
             std::vector<int> mass_points = {60, 80, 100, 120};
     
             for (int mass : mass_points) {
                 std::string modified_eff_file = eff_file;
                 // Replace .json with _mass.json (equivalent to Python's f"eff_file".replace(".json", key))
                 size_t pos = modified_eff_file.find(".json");
                 if (pos != std::string::npos) {
                     modified_eff_file = modified_eff_file.substr(0, pos) + "_ggH_" + std::to_string(mass) + ".json";
                 }
                 btag_eff[mass] = correction::CorrectionSet::from_file(modified_eff_file)->at("Btagging effciency[pt,eta,flavor]");
             }
              
          
             auto btagSF_lambda = [evaluator_bc, evaluator_light, btag_eff, variation, year, btag_cut,btag_sf_flavour]
                 (const ROOT::RVec<float> &pt_values,
                 const ROOT::RVec<float> &eta_values,
                 const ROOT::RVec<float> &btag_values,
                 const ROOT::RVec<UChar_t> &flavors,
                 const ROOT::RVec<int> &jet_mask,
                 const ROOT::RVec<int> &bjet_mask,
                 const ROOT::RVec<int> &jet_veto_mask, 
                 const float &gen_higgs_mass
               ) {
                 Logger::get("btagSF")->debug("Vatiation - Name {}", variation);
                 float sf = 1.;
                 float higgs_mass = gen_higgs_mass;
     
                 // Find the nearest mass point in btag_eff
                 auto nearest_mass = std::min_element(
                    btag_eff.begin(), btag_eff.end(),
                    [higgs_mass](const auto& a, const auto& b) {return std::abs(a.first - higgs_mass) < std::abs(b.first - higgs_mass);
                    }
                );
     
                 auto btag_eff_evaluator = nearest_mass->second;
     
                  for (int i = 0; i < pt_values.size(); i++) {
                      Logger::get("btagSF")->debug(
                          "jet masks - jet {}, bjet {}, jet veto {}", jet_mask.at(i),
                          bjet_mask.at(i), jet_veto_mask.at(i));
                      // considering only good jets/bjets, this is needed since jets and
                      // bjets might have different cuts depending on the analysis
                      if ((jet_mask.at(i) || bjet_mask.at(i)) && jet_veto_mask.at(i) && pt_values.at(i) >= 20.0 && pt_values.at(i) < 10000.0 && std::abs(eta_values.at(i)) < 2.5 &&  btag_values.at(i) > 0 ) {
                         auto bjet_sf = 1.0;
                         auto pt_tmp = 0.0;
                         if ( pt_values.at(i) >= 200) {pt_tmp = 199.99; } else pt_tmp=  pt_values.at(i) ;
         
         
                         // for difference case: if evaluate light variation, use light SF and light flavor, vice versa. 
                         if (btag_sf_flavour.find("light") != std::string::npos) {
                             if ( flavors.at(i) == 0) {
                                 bjet_sf = evaluator_light->evaluate({variation, "M", flavors.at(i), std::abs(eta_values.at(i)), pt_values.at(i)  });}
                             else {
                                 bjet_sf = evaluator_bc->evaluate({"central", "M", flavors.at(i), std::abs(eta_values.at(i)), pt_values.at(i)  });}
                         }   
                         else {
                             if ( flavors.at(i) == 0) {
                                 bjet_sf = evaluator_light->evaluate({"central", "M", flavors.at(i), std::abs(eta_values.at(i)), pt_values.at(i)  });}
                             else {
                                 bjet_sf = evaluator_bc->evaluate({variation, "M", flavors.at(i), std::abs(eta_values.at(i)), pt_values.at(i)  });}
                         }
         
                         auto  bjet_eff =  btag_eff_evaluator->evaluate({year, "btagging-eff",  pt_tmp, eta_values.at(i), flavors.at(i)  });
                         
                         if (btag_values.at(i) > btag_cut) { sf *= (bjet_sf * bjet_eff/bjet_eff); }
                         else{  sf *= ( (1 - bjet_sf * bjet_eff) /(1 - bjet_eff));   }
                         Logger::get("btagSF")->debug(
                          "btag SF, btag eff, bjet flavour, updated SF - sf {}, eff  {}, jet flavour {}, updated SF {}", bjet_sf, bjet_eff, flavors.at(i), sf);
                      }
                  };
                  
                  return sf;
              };
              auto df1 = df.Define(
                  sf_output, btagSF_lambda,
                  {pt, eta, btag_discr, flavor, jet_mask, bjet_mask, jet_veto_mask, gen_higgs_mass});
              return df1;
     } 
     
     



} // namespace jet

namespace embedding {
/**
 * @brief Function used to readout the embedding selection trigger scalefactors
 *
 * @param df the input dataframe
 * @param pt_1 the pt of the leading generator particle in the event. This
 * corresponds to the leading muon selected by the embedding selection
 * @param eta_1 the eta of the leading generator particle in the event. This
 * corresponds to the leading muon selected by the embedding selection
 * @param pt_2 the pt of the subleading generator particle in the event. This
 * corresponds to the subleading muon selected by the embedding selection
 * @param eta_2 the eta of the subleading generator particle in the event. This
 * corresponds to the subleading muon selected by the embedding selection
 * @param output name of the output column
 * @param sf_file path to the correctionlib file containing the scale factor
 * @param idAlgorithm name of the scale factor in the correctionlib file
 * @return ROOT::RDF::RNode
 */
ROOT::RDF::RNode
selection_trigger(ROOT::RDF::RNode df, const std::string &pt_1,
                  const std::string &eta_1, const std::string &pt_2,
                  const std::string &eta_2, const std::string &output,
                  const std::string &sf_file, const std::string &idAlgorithm) {

    Logger::get("EmbeddingSelectionTriggerSF")
        ->debug("Correction - Name {}", idAlgorithm);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(idAlgorithm);
    auto df1 = df.Define(
        output,
        [evaluator](const float &pt_1, const float &eta_1, const float &pt_2,
                    const float &eta_2) {
            Logger::get("EmbeddingSelectionTriggerSF")
                ->debug(" pt_1 {}, eta_1 {}, pt_2 {}, eta_2 {}", pt_1, eta_1,
                        pt_2, eta_2);
            float sf = 1.;
            if (pt_1 > 25.0) {sf = evaluator->evaluate(
                {pt_1, std::abs(eta_1), pt_2, std::abs(eta_2)});
            }
            Logger::get("EmbeddingSelectionTriggerSF")->debug("sf {}", sf);
            return sf;
        },
        {pt_1, eta_1, pt_2, eta_2});
    return df1;
}
/**
 * @brief Function used to readout the embedding selection trigger scalefactors.
 *
 * @param df the input dataframe
 * @param pt the pt of the generator particle in the event. This corresponds to
 * one of the muons selected by the embedding selection
 * @param eta the eta of the generator particle in the event. This corresponds
 * to one of the muons selected by the embedding selection
 * @param output the name of the output column
 * @param sf_file the path to the correctionlib file containing the scale factor
 * @param idAlgorithm the name of the scale factor in the correctionlib
 * file
 * @return ROOT::RDF::RNode
 */
ROOT::RDF::RNode selection_id(ROOT::RDF::RNode df, const std::string &pt,
                              const std::string &eta, const std::string &output,
                              const std::string &sf_file,
                              const std::string &idAlgorithm) {

    Logger::get("EmbeddingSelectionIDSF")
        ->debug("Correction - Name {}", idAlgorithm);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(idAlgorithm);
    auto df1 =
        df.Define(output,
                  [evaluator](const float &pt, const float &eta) {
                      Logger::get("EmbeddingSelectionIDSF")
                          ->debug(" pt {}, eta {},", pt, eta);
                      float sf = 1.;
                      if (pt > 25.0) {
                        sf = evaluator->evaluate({pt, std::abs(eta)});
                      }
                      
                      Logger::get("EmbeddingSelectionIDSF")->debug("sf {}", sf);
                      return sf;
                  },
                  {pt, eta});
    return df1;
}
/**
 * @brief Function used to readout SFs from the muon scale factor measurements
 *
 * @param df the input dataframe
 * @param pt the pt of the muon
 * @param eta the eta of the muon
 * @param output the name of the output column
 * @param sf_file the path to the correctionlib file containing the scale factor
 * @param correctiontype the type of the correction. Use `emb` for embedding and
 * `mc` for monte carlo
 * @param idAlgorithm the name of the scale factor in the correctionlib
 * file
 * @param extrapolation_factor The extrapolation factor to be used for the scale
 * factor, defaults to 1.
 * @return ROOT::RDF::RNode
 */
ROOT::RDF::RNode muon_sf(ROOT::RDF::RNode df, const std::string &pt,
                         const std::string &eta, const std::string &output,
                         const std::string &sf_file,
                         const std::string correctiontype,
                         const std::string &idAlgorithm,
                         const float &extrapolation_factor = 1.0) {

    Logger::get("EmbeddingMuonSF")->debug("Correction - Name {}", idAlgorithm);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(idAlgorithm);
    Logger::get("EmbeddingMuonSF")->debug("Correction - Name {} test evaluate {}", idAlgorithm, evaluator->evaluate({1.0, 50.0,correctiontype} ) );
    auto df1 = df.Define(
        output,
        [evaluator, correctiontype, extrapolation_factor](const float &pt,
                                                          const float &eta) {
            Logger::get("EmbeddingMuonSF")
                ->debug(" pt {}, eta {}, correctiontype {}, extrapolation "
                        "factor {}",
                        pt, eta, correctiontype, extrapolation_factor);
            float sf = 1.;
            auto pt_tmp = pt;
            if (pt < 26 ) pt_tmp = 26;
            if (std::abs(eta) < 2.5){
                sf = extrapolation_factor *
                evaluator->evaluate({std::abs(eta), pt_tmp, correctiontype});
            // change the order of pt and eta
            }     
            Logger::get("EmbeddingMuonSF")->debug("sf {}", sf);
            
            return sf;
        },
        {pt, eta});
    return df1;
}
/**
 * @brief Function used to readout SFs from the electron scale factor
 * measurements
 *
 * @param df the input dataframe
 * @param pt the pt of the electron
 * @param eta the eta of the electron
 * @param output the name of the output column
 * @param sf_file the path to the correctionlib file containing the scale factor
 * @param correctiontype the type of the correction. Use `emb` for embedding and
 * `mc` for monte carlo
 * @param idAlgorithm the name of the scale factor in the correctionlib
 * file
 * @param extrapolation_factor The extrapolation factor to be used for the scale
 * factor, defaults to 1.
 * @return ROOT::RDF::RNode
 */
ROOT::RDF::RNode electron_sf(ROOT::RDF::RNode df, const std::string &pt,
                             const std::string &eta, const std::string &output,
                             const std::string &sf_file,
                             const std::string correctiontype,
                             const std::string &idAlgorithm,
                             const float &extrapolation_factor,
                             const std::string &year,
                             const std::string &trigger) {

    Logger::get("EmbeddingElectronSF")
        ->debug("Correction - Name {}", idAlgorithm);
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at(idAlgorithm);
    
    Logger::get("EmbeddingElectronSF")->debug("Correction - Name {} test evaluate {}", idAlgorithm, evaluator->evaluate({year,correctiontype, trigger, 1.0, 50.0} ) );
    auto df1 = df.Define(
        output,
        [evaluator, correctiontype, extrapolation_factor, year, trigger](const float &pt,
                                                          const float &eta) {
            Logger::get("EmbeddingElectronSF")
                ->debug(" pt {}, eta {}, correctiontype {}, extrapolation "
                        "factor {}",
                        pt, eta, correctiontype, extrapolation_factor);
            float sf = 1.;
            // sf = extrapolation_factor *
            //      evaluator->evaluate({pt, eta, correctiontype});
            if(pt < 25){
                return sf;
            }
            else{

                if (pt > 1000){
                    sf = sf = extrapolation_factor * evaluator->evaluate({year, correctiontype, trigger, eta, 999.99});
                }
                else {
                    sf = extrapolation_factor * evaluator->evaluate({year, correctiontype, trigger, eta, pt}); 
                }
                
            }
            Logger::get("EmbeddingElectronSF")->debug("sf {}", sf);
            return sf;
        },
        {pt, eta});
    return df1;
}
/**
 * @brief Function to evaluate the di-tau trigger or etau/mutau cross trigger
 * scale factor for embedded events from a xpog file
 *
 * @param df the input dataframe
 * @param pt the name of the column containing the tau pt variable
 * @param decaymode the name of the column containing the tau decay mode
 * variable
 * @param output name of the scale factor column
 * @param wp the name of the the tau id working point VVVLoose-VVTight
 * @param sf_file path to the file with the tau trigger scale factors
 * @param type the type of the tau trigger, available are "ditau", "etau",
 * "mutau", "ditauvbf"
 * @param corrtype name of the tau trigger correction type, available are
 * "eff_data", "eff_mc", "sf"
 * @param syst name of the systematic variation, options are "nom", "up", "down"
 * @return ROOT::RDF::RNode a new dataframe containing the new sf column
 */

ROOT::RDF::RNode
ditau_trigger_sf(ROOT::RDF::RNode df, const std::string &pt,
                 const std::string &decaymode, const std::string &output,
                 const std::string &wp, const std::string &sf_file,
                 const std::string &type, const std::string &corrtype,
                 const std::string &syst) {

    Logger::get("ditau_trigger")
        ->debug("Setting up function for di-tau trigger sf");
    Logger::get("ditau_trigger")
        ->debug("trigger type {}, correction type {}, file {}",type, corrtype, sf_file);
    // tauTriggerSF is the only correction set in the file for now, might change
    // with official sf release -> change into additional input parameter
    auto evaluator =
        correction::CorrectionSet::from_file(sf_file)->at("tau_trigger");
    Logger::get("ditau_trigger")->debug("WP {} - trigger type {}, systematic {}", wp, type, syst);
    auto trigger_sf_calculator = [evaluator, wp, type, corrtype,
                                  syst](const float &pt, const UChar_t &decaymode) {
        float sf = 1.;
        float pt_threshold = 25.0;
        if (type == "ditau") pt_threshold = 39.6;
        else if (type == "etau") pt_threshold = 25.0;
        else if (type == "mutau") pt_threshold = 25.0;
        else pt_threshold = 25.0;
        Logger::get("ditau_trigger")
            ->debug("decaymode {}, pt {}, pt_threshold {}" , decaymode, pt, pt_threshold);
        if (pt > pt_threshold) {
            if (decaymode == 0 || decaymode == 1 || decaymode == 10 ||
                decaymode == 11) {
                sf = evaluator->evaluate(
                    {pt, decaymode, type, wp, corrtype, syst});
                    
            } else {
                sf = evaluator->evaluate({pt, -1, type, wp, corrtype, syst});
                
            }
        }
        Logger::get("ditau_trigger")->debug("Scale Factor {}", sf);
        return sf;
    };
    auto df1 = df.Define(output, trigger_sf_calculator, {pt, decaymode});
    return df1;
}
} // namespace embedding

namespace trigger {
/**
 * @brief Function used to evaluate OR trigger scale factor for single electron trigger OR electron-tau cross trigger
 *
 * This function computes trigger scale factors for electron-tau channel using
 * the OR method. It first calculates single electron and cross trigger
 * flags internally, then applies the OR trigger SF formula.
 *
 * Formula:
 * OR_eff_mc = (passSingle * single_ele_effMc
 *              - passCross * passSingle * min(single_ele_effMc, ele_leg_effMc) * tau_leg_effMc
 *              + passCross * ele_leg_effMc * tau_leg_effMc)
 * OR_eff_data = (passSingle * single_ele_effData
 *                - passCross * passSingle * min(single_ele_effData, ele_leg_effData) * tau_leg_effData
 *                + passCross * ele_leg_effData * tau_leg_effData)
 * trigger_sf = OR_eff_data / OR_eff_mc
 *
 * @param df The input dataframe
 * @param ele_p4 name of electron 4-momentum column
 * @param tau_p4 name of tau 4-momentum column
 * @param triggerobject_bits name of trigger object bits column
 * @param triggerobject_id name of trigger object id column
 * @param triggerobject_pt name of trigger object pt column
 * @param triggerobject_eta name of trigger object eta column
 * @param triggerobject_phi name of trigger object phi column
 * @param tau_dm name of tau decay mode column
 * @param sf_output name of output scale factor column
 * @param single_ele_eff_file path to single electron trigger SF file
 * @param ele_leg_file path to electron leg of cross trigger SF file
 * @param tau_leg_file path to tau leg of cross trigger SF file
 * @param tau_wp tau ID working point
 * @param single_ele_hlt_path HLT path for single electron trigger
 * @param cross_ele_hlt_path HLT path for cross e-tau trigger
 * @return a new dataframe containing the scale factor column
 */
ROOT::RDF::RNode
et_or_trigger_sf(ROOT::RDF::RNode df,
               const std::string &ele_p4, const std::string &tau_p4,
               const std::string &triggerobject_bits,
               const std::string &triggerobject_id,
               const std::string &triggerobject_pt,
               const std::string &triggerobject_eta,
               const std::string &triggerobject_phi,
               const std::string &tau_dm,
               const std::string &sf_output,
               const std::string &ele_sf_year_id,
               const std::string &ele_leg_file,
               const std::string &tau_leg_file,
               const std::string &single_ele_eff_file,
               const std::string &tau_wp,
               const std::string &single_ele_hlt_path,
               const std::string &cross_ele_hlt_path) {

    Logger::get("et_or_trigger_sf")->info("Setting up e-tau OR trigger SF function");
    Logger::get("et_or_trigger_sf")->info("HLT paths: single={}, cross={}",
                                        single_ele_hlt_path, cross_ele_hlt_path);

    auto evaluator_single_ele_mc =
        correction::CorrectionSet::from_file(single_ele_eff_file)->at("Electron-HLT-McEff");
    auto evaluator_single_ele_data =
        correction::CorrectionSet::from_file(single_ele_eff_file)->at("Electron-HLT-DataEff");
    auto evaluator_ele_leg_mc =
        correction::CorrectionSet::from_file(ele_leg_file)->at("Electron-HLT-McEff");
    auto evaluator_ele_leg_data =
        correction::CorrectionSet::from_file(ele_leg_file)->at("Electron-HLT-DataEff");
    auto evaluator_tau_leg =
        correction::CorrectionSet::from_file(tau_leg_file)->at("tau_trigger");

    // First, calculate single electron trigger flag internally
    auto single_ele_match_calculator =
        [](bool hltpath_match,
           const ROOT::Math::PtEtaPhiMVector &ele_p4,
           ROOT::RVec<ULong64_t> &triggerobject_bits,
           const ROOT::RVec<UShort_t> &triggerobject_ids,
           const ROOT::RVec<float> &triggerobject_pts,
           const ROOT::RVec<float> &triggerobject_etas,
           const ROOT::RVec<float> &triggerobject_phis) {
            bool result = false;
            bool match_result = false;
            if (hltpath_match) {
                match_result = matchParticleNoModify(
                    ele_p4, triggerobject_pts, triggerobject_etas,
                    triggerobject_phis, triggerobject_bits, triggerobject_ids,
                    0.4, 31.0, 2.5, 11, 1);
            }
            result = hltpath_match && match_result;
            return result;
        };

    ROOT::RDF::RNode df1 = df.Define("trg_single_ele28_tmp", single_ele_match_calculator,
                       {single_ele_hlt_path, ele_p4,
                        triggerobject_bits, triggerobject_id, triggerobject_pt,
                        triggerobject_eta, triggerobject_phi});

    // Then, calculate cross trigger flag internally
    auto cross_ele_match_calculator =
        [](bool hltpath_match,
           const ROOT::Math::PtEtaPhiMVector &ele_p4,
           const ROOT::Math::PtEtaPhiMVector &tau_p4,
           ROOT::RVec<ULong64_t> &triggerobject_bits,
           const ROOT::RVec<UShort_t> &triggerobject_ids,
           const ROOT::RVec<float> &triggerobject_pts,
           const ROOT::RVec<float> &triggerobject_etas,
           const ROOT::RVec<float> &triggerobject_phis) {
            bool result = false;
            bool match_result_ele = false;
            bool match_result_tau = false;
            if (hltpath_match) {
                match_result_ele = matchParticleNoModify(
                    ele_p4, triggerobject_pts, triggerobject_etas,
                    triggerobject_phis, triggerobject_bits, triggerobject_ids,
                    0.4, 25.0, 2.5, 11, 1);
                match_result_tau = matchParticleNoModify(
                    tau_p4, triggerobject_pts, triggerobject_etas,
                    triggerobject_phis, triggerobject_bits, triggerobject_ids,
                    0.4, 32.0, 2.5, 15, 12);
            }
            result = hltpath_match && match_result_ele && match_result_tau;
            return result;
        };

    ROOT::RDF::RNode df2 = df1.Define("trg_cross_ele25tau27_hps_tmp", cross_ele_match_calculator,
                       {cross_ele_hlt_path, ele_p4,
                        tau_p4,
                        triggerobject_bits, triggerobject_id, triggerobject_pt,
                        triggerobject_eta, triggerobject_phi});

    // Now calculate the OR trigger SF
    auto et_or_trigger_sf_calculator = [evaluator_single_ele_mc, evaluator_single_ele_data,
                                      evaluator_ele_leg_mc, evaluator_ele_leg_data,
                                      evaluator_tau_leg, tau_wp,ele_sf_year_id](
                                                                     const ROOT::Math::PtEtaPhiMVector &ele_p4,
                                                                     const ROOT::Math::PtEtaPhiMVector &tau_p4,
                                                                     const UChar_t &tau_dm_val,
                                                                     const bool &passSingle_val,
                                                                     const bool &passCross_val) {
        float sf = 1.0;
        float tau_pt_val = tau_p4.pt();
        float ele_pt_val = ele_p4.pt();
        float ele_eta_val = ele_p4.eta();

        // Get MC efficiencies
        // etau tau threshold: pt 25
        // etau electron threshold: pt 28
        // etau electron eta threshold: abs(eta) < 2.1
        if (tau_pt_val < 25.0) {
            tau_pt_val = 25.0;
        }
        if (ele_pt_val < 25.0) {
            ele_pt_val = 25.0;
        }
        if (std::abs(ele_eta_val) > 2.1) {
            ele_eta_val = std::abs(ele_eta_val) < 2.1 ? ele_eta_val : 2.1 * ele_eta_val / std::abs(ele_eta_val);
        }
        float single_ele_effMc = evaluator_single_ele_mc->evaluate({ele_sf_year_id, "nom", "HLT_SF_Ele30_TightID", ele_eta_val, ele_pt_val});
        float ele_leg_effMc = evaluator_ele_leg_mc->evaluate({ele_sf_year_id, "nom", "HLT_SF_Ele24_TightID", ele_eta_val, ele_pt_val});
        float tau_leg_effMc = evaluator_tau_leg->evaluate({tau_pt_val, tau_dm_val, "etau", tau_wp, "eff_mc", "nom"});

        // Get Data efficiencies - use "nominal_DATAeff" for data eff
        float single_ele_effData = evaluator_single_ele_data->evaluate({ele_sf_year_id, "nom", "HLT_SF_Ele30_TightID", ele_eta_val, ele_pt_val});
        float ele_leg_effData = evaluator_ele_leg_data->evaluate({ele_sf_year_id, "nom", "HLT_SF_Ele24_TightID", ele_eta_val, ele_pt_val});
        float tau_leg_effData = evaluator_tau_leg->evaluate({tau_pt_val, tau_dm_val, "etau", tau_wp, "eff_data", "nom"});

        // Calculate OR efficiency for MC
        float OR_eff_mc = (passSingle_val * single_ele_effMc
                          - passCross_val * passSingle_val * std::min(single_ele_effMc, ele_leg_effMc) * tau_leg_effMc
                          + passCross_val * ele_leg_effMc * tau_leg_effMc);

        // Calculate OR efficiency for Data
        float OR_eff_data = (passSingle_val * single_ele_effData
                            - passCross_val * passSingle_val * std::min(single_ele_effData, ele_leg_effData) * tau_leg_effData
                            + passCross_val * ele_leg_effData * tau_leg_effData);

        // Calculate scale factor
        if (OR_eff_mc > 0) {
            sf = OR_eff_data / OR_eff_mc;
        }

        Logger::get("et_or_trigger_sf")->debug("ele_pt={}, ele_eta={}, tau_pt={}, tau_dm={}, passSingle={}, passCross={}, sf={}",
                                           ele_pt_val, ele_eta_val, tau_pt_val, tau_dm_val, passSingle_val, passCross_val, sf);
        return sf;
    };

    auto df3 = df2.Define(sf_output, et_or_trigger_sf_calculator,
                        {ele_p4, tau_p4, tau_dm, "trg_single_ele28_tmp", "trg_cross_ele25tau27_hps_tmp"});
    return df3;
}

/**
 * @brief Function to calculate mu-tau OR trigger scale factor
 *
 * This function computes trigger scale factors for mu-tau channel using
 * the OR method. It first calculates single muon and cross trigger
 * flags internally, then applies the OR trigger SF formula.
 *
 * @param df The input dataframe
 * @param muon_p4 name of muon 4-momentum column
 * @param triggerobject_bits name of trigger object bits column
 * @param triggerobject_id name of trigger object id column
 * @param triggerobject_pt name of trigger object pt column
 * @param triggerobject_eta name of trigger object eta column
 * @param triggerobject_phi name of trigger object phi column
 * @param mu_pt name of muon pt column
 * @param mu_eta name of muon eta column
 * @param tau_pt name of tau pt column
 * @param tau_dm name of tau decay mode column
 * @param sf_output name of output scale factor column
 * @param single_mu_file path to single muon trigger SF file
 * @param mu_leg_file path to muon leg trigger SF file
 * @param tau_leg_file path to tau leg trigger SF file
 * @param tau_wp tau ID working point
 * @return a new dataframe containing the scale factor column
 */
ROOT::RDF::RNode
mt_or_trigger_sf(ROOT::RDF::RNode df, 
               const std::string &muon_p4, const std::string &tau_p4,
               const std::string &triggerobject_bits,
               const std::string &triggerobject_id,
               const std::string &triggerobject_pt,
               const std::string &triggerobject_eta,
               const std::string &triggerobject_phi,
               const std::string &tau_dm,
               const std::string &sf_output,
               const std::string &mu_leg_file,
               const std::string &tau_leg_file, 
               const std::string &single_mu_eff_file, 
               const std::string &tau_wp, const std::string &single_mu_hlt_path,
               const std::string &cross_mu_hlt_path) {

    Logger::get("mt_or_trigger_sf")->info("Setting up mu-tau OR trigger SF function");
    Logger::get("mt_or_trigger_sf")->info("HLT paths: single={}, cross={}",
                                        single_mu_hlt_path, cross_mu_hlt_path);

    auto evaluator_single_mu_mc =
        correction::CorrectionSet::from_file(single_mu_eff_file)->at("NUM_IsoMu24_DEN_CutBasedIdMedium_and_PFIsoMedium");
    auto evaluator_single_mu_data =
        correction::CorrectionSet::from_file(single_mu_eff_file)->at("NUM_IsoMu24_DEN_CutBasedIdMedium_and_PFIsoMedium");
    auto evaluator_mu_leg_mc =
        correction::CorrectionSet::from_file(mu_leg_file)->at("NUM_IsoMu20_DEN_CutBasedIdMedium_and_PFIsoMedium_MCeff");
    auto evaluator_mu_leg_data =
        correction::CorrectionSet::from_file(mu_leg_file)->at("NUM_IsoMu20_DEN_CutBasedIdMedium_and_PFIsoMedium_DATAeff");
    auto evaluator_tau_leg =
        correction::CorrectionSet::from_file(tau_leg_file)->at("tau_trigger");


    // First, calculate single muon trigger flag internally
    auto single_mu_match_calculator =
        [](bool hltpath_match,
           const ROOT::Math::PtEtaPhiMVector &muon_p4,
           ROOT::RVec<ULong64_t> &triggerobject_bits,
           const ROOT::RVec<UShort_t> &triggerobject_ids,
           const ROOT::RVec<float> &triggerobject_pts,
           const ROOT::RVec<float> &triggerobject_etas,
           const ROOT::RVec<float> &triggerobject_phis) {
            bool result = false;
            bool match_result = false;
            if (hltpath_match) {
                match_result = matchParticleNoModify(
                    muon_p4, triggerobject_pts, triggerobject_etas,
                    triggerobject_phis, triggerobject_bits, triggerobject_ids,
                    0.4, 25.0, 2.4, 13, 3);
            }
            result = hltpath_match && match_result;
            return result;
        };

    ROOT::RDF::RNode df1 = df.Define("trg_single_mu24_tmp", single_mu_match_calculator,
                       {single_mu_hlt_path, muon_p4,
                        triggerobject_bits, triggerobject_id, triggerobject_pt,
                        triggerobject_eta, triggerobject_phi});

    // Then, calculate cross trigger flag internally
    auto cross_mu_match_calculator =
        [](bool hltpath_match,
           const ROOT::Math::PtEtaPhiMVector &muon_p4,
           const ROOT::Math::PtEtaPhiMVector &tau_p4,
           ROOT::RVec<ULong64_t> &triggerobject_bits,
           const ROOT::RVec<UShort_t> &triggerobject_ids,
           const ROOT::RVec<float> &triggerobject_pts,
           const ROOT::RVec<float> &triggerobject_etas,
           const ROOT::RVec<float> &triggerobject_phis) {
            bool result = false;
            bool match_result_mu = false;
            bool match_result_tau = false;
            if (hltpath_match) {
                match_result_mu = matchParticleNoModify(
                    muon_p4, triggerobject_pts, triggerobject_etas,
                    triggerobject_phis, triggerobject_bits, triggerobject_ids,
                    0.4, 20.0, 2.4, 13, 3);
                match_result_tau = matchParticleNoModify(
                    tau_p4, triggerobject_pts, triggerobject_etas,
                    triggerobject_phis, triggerobject_bits, triggerobject_ids,
                    0.4, 27.0, 2.5, 15, 13);
            }
            result = hltpath_match && match_result_mu && match_result_tau;
            return result;
        };

    ROOT::RDF::RNode df2 = df1.Define("trg_cross_mu20tau27_hps_tmp", cross_mu_match_calculator,
                       {cross_mu_hlt_path, muon_p4,
                        tau_p4,
                        triggerobject_bits, triggerobject_id, triggerobject_pt,
                        triggerobject_eta, triggerobject_phi});

    // Now calculate the OR trigger SF

    auto mt_or_trigger_sf_calculator = [evaluator_single_mu_mc, evaluator_single_mu_data,
                                      evaluator_mu_leg_mc, evaluator_mu_leg_data,
                                      evaluator_tau_leg,   tau_wp](
                                                                     const ROOT::Math::PtEtaPhiMVector &muon_p4,
                                                                     const ROOT::Math::PtEtaPhiMVector &tau_p4,
                                                                     const UChar_t &tau_dm_val,
                                                                     const bool &passSingle_val,
                                                                     const bool &passCross_val) {
        float sf = 1.0;
        float tau_pt_val = tau_p4.pt();
        float mu_pt_val = muon_p4.pt();
        float mu_eta_val = muon_p4.eta();

        // Get MC efficiencies
        // the evaluate 
        // Get MC efficiencies - order: eta, pt, scale_factors
        /// mutau tau threshold: pt 25
        /// etau tau thresold: pt 25
        /// ditau tau threshold: pt 35
        /// mutau mu threshold: pt 26
        /// mutau mu eta threshold: abs(eta) < 2.1
        if (tau_pt_val < 25.0) {
            tau_pt_val = 25.0;
        }
        if (mu_pt_val < 26.0) {
            mu_pt_val = 26.0;
        }
        if (std::abs(mu_eta_val) > 2.1) {
            mu_eta_val = std::abs(mu_eta_val) < 2.1 ? mu_eta_val : 2.1 * mu_eta_val / std::abs(mu_eta_val);
        }
        float single_mu_effMc = evaluator_single_mu_mc->evaluate({mu_eta_val, mu_pt_val, "nominal"});
        float mu_leg_effMc = evaluator_mu_leg_mc->evaluate({std::abs(mu_eta_val), mu_pt_val, "nominal"});
        float tau_leg_effMc = evaluator_tau_leg->evaluate({tau_pt_val, tau_dm_val, "mutau", tau_wp, "eff_mc", "nom"});

        // Get Data efficiencies - use "nominal_DATAeff" for data eff
        float single_mu_effData = evaluator_single_mu_data->evaluate({mu_eta_val, mu_pt_val, "nominal_DATAeff"});
        float mu_leg_effData = evaluator_mu_leg_data->evaluate({std::abs(mu_eta_val), mu_pt_val, "nominal"});
        float tau_leg_effData = evaluator_tau_leg->evaluate({tau_pt_val, tau_dm_val, "mutau", tau_wp, "eff_data", "nom"});                                                                    
        // Calculate OR efficiency for MC
        float OR_eff_mc = (passSingle_val * single_mu_effMc
                          - passCross_val * passSingle_val * std::min(single_mu_effMc, mu_leg_effMc) * tau_leg_effMc
                          + passCross_val * mu_leg_effMc * tau_leg_effMc);

        // Calculate OR efficiency for Data
        float OR_eff_data = (passSingle_val * single_mu_effData
                            - passCross_val * passSingle_val * std::min(single_mu_effData, mu_leg_effData) * tau_leg_effData
                            + passCross_val * mu_leg_effData * tau_leg_effData);
            
        // Calculate scale factor
        if (OR_eff_mc > 0) {
            sf = OR_eff_data / OR_eff_mc;
        }

        Logger::get("mt_or_trigger_sf")->debug("mu_pt={}, mu_eta={}, tau_pt={}, tau_dm={}, passSingle={}, passCross={}, sf={}",
                                           mu_pt_val, mu_eta_val, tau_pt_val, tau_dm_val, passSingle_val, passCross_val, sf);
        return sf;
    };

    auto df3 = df2.Define(sf_output, mt_or_trigger_sf_calculator,
                        {muon_p4, tau_p4, tau_dm, "trg_single_mu24_tmp", "trg_cross_mu20tau27_hps_tmp"});
    return df3;
}

/**
 * @brief Function to calculate ditau OR trigger scale factor
 *
 * This function computes trigger scale factors for ditau channel using
 * the OR method. It calculates ditau and ditau+jet trigger flags
 * internally, then applies the OR trigger SF formula.
 *
 * Formula:
 * OR_eff_mc = (passDiTau * eff_tautau
 *              - passDiTau * passDiTauJet * min(eff_tautau_ditaujetTrg, eff_tautau_ditauTrg) * eff_jet_ditaujetTrg
 *              + passDiTauJet * eff_tautau_ditaujetTrg * eff_jet_ditaujetTrg)
 * OR_eff_data = (passDiTau * eff_tautau_data
 *                - passDiTau * passDiTauJet * min(eff_tautau_ditaujetTrg, eff_tautau_ditauTrg) * eff_jet_ditaujetTrg
 *                + passDiTauJet * eff_tautau_ditaujetTrg * eff_jet_ditaujetTrg)
 * trigger_sf = OR_eff_data / OR_eff_mc
 *
 * @param df The input dataframe
 * @param tau1_p4 name of first tau 4-momentum column
 * @param tau2_p4 name of second tau 4-momentum column
 * @param triggerobject_bits name of trigger object bits column
 * @param triggerobject_id name of trigger object id column
 * @param triggerobject_pt name of trigger object pt column
 * @param triggerobject_eta name of trigger object eta column
 * @param triggerobject_phi name of trigger object phi column
 * @param tau1_dm name of first tau decay mode column
 * @param tau2_dm name of second tau decay mode column
 * @param jet_pt name of jet pt column
 * @param sf_output name of output scale factor column
 * @param ditau_eff_file path to ditau trigger SF file
 * @param ditaujet_eff_file path to ditau+jet trigger SF file
 * @param tau_wp tau ID working point
 * @param ditau_hlt_path HLT path for ditau trigger
 * @param ditaujet_hlt_path HLT path for ditau+jet trigger
 * @return a new dataframe containing the scale factor column
 */
ROOT::RDF::RNode
ditau_or_trigger_sf(ROOT::RDF::RNode df,
                 const std::string &tau1_p4, const std::string &tau2_p4,
                 const std::string &jet_p4,
                 const std::string &triggerobject_bits,
                 const std::string &triggerobject_id,
                 const std::string &triggerobject_pt,
                 const std::string &triggerobject_eta,
                 const std::string &triggerobject_phi,
                 const std::string &tau1_dm,
                 const std::string &tau2_dm,
                 const std::string &sf_output,
                 const std::string &ditau_eff_file,
                 const std::string &ditaujet_eff_file,
                 const std::string &tau_wp,
                 const std::string &ditau_hlt_path,
                 const std::string &ditaujet_hlt_path) {

    Logger::get("ditau_or_trigger_sf")->info("Setting up ditau OR trigger SF function");
    Logger::get("ditau_or_trigger_sf")->info("HLT paths: ditau={}, ditau+jet={}",
                                        ditau_hlt_path, ditaujet_hlt_path);

    auto evaluator_ditau_mc =
        correction::CorrectionSet::from_file(ditau_eff_file)->at("tau_trigger");
    auto evaluator_ditau_data =
        correction::CorrectionSet::from_file(ditau_eff_file)->at("tau_trigger");
    auto evaluator_ditaujet_mc =
        correction::CorrectionSet::from_file(ditaujet_eff_file)->at("jetlegSFs");
    auto evaluator_ditaujet_data =
        correction::CorrectionSet::from_file(ditaujet_eff_file)->at("jetlegSFs");


    // First, calculate ditau trigger flag internally
    auto ditau_match_calculator =
        [](bool hltpath_match,
           const ROOT::Math::PtEtaPhiMVector &tau1_p4,
           const ROOT::Math::PtEtaPhiMVector &tau2_p4,
           ROOT::RVec<ULong64_t> &triggerobject_bits,
           const ROOT::RVec<UShort_t> &triggerobject_ids,
           const ROOT::RVec<float> &triggerobject_pts,
           const ROOT::RVec<float> &triggerobject_etas,
           const ROOT::RVec<float> &triggerobject_phis) {
            bool result = false;
            bool match_result_tau1 = false;
            bool match_result_tau2 = false;
            if (hltpath_match) {
                match_result_tau1 = matchParticleNoModify(
                    tau1_p4, triggerobject_pts, triggerobject_etas,
                    triggerobject_phis, triggerobject_bits, triggerobject_ids,
                    0.4, 40.0, 2.5, 15, 11);
                match_result_tau2 = matchParticleNoModify(
                    tau2_p4, triggerobject_pts, triggerobject_etas,
                    triggerobject_phis, triggerobject_bits, triggerobject_ids,
                    0.4, 40.0, 2.5, 15, 11);
            }
            result = hltpath_match && match_result_tau1 && match_result_tau2;
            return result;
        };

    ROOT::RDF::RNode df1 = df.Define("trg_ditau_tmp", ditau_match_calculator,
                       {ditau_hlt_path, tau1_p4, tau2_p4,
                        triggerobject_bits, triggerobject_id, triggerobject_pt,
                        triggerobject_eta, triggerobject_phi});

    // Then, calculate ditau+jet trigger flag internally
    auto ditaujet_match_calculator =
        [](bool hltpath_match,
           const ROOT::Math::PtEtaPhiMVector &tau1_p4,
           const ROOT::Math::PtEtaPhiMVector &tau2_p4,
           const ROOT::Math::PtEtaPhiMVector &jet_p4,
           ROOT::RVec<ULong64_t> &triggerobject_bits,
           const ROOT::RVec<UShort_t> &triggerobject_ids,
           const ROOT::RVec<float> &triggerobject_pts,
           const ROOT::RVec<float> &triggerobject_etas,
           const ROOT::RVec<float> &triggerobject_phis) {
            bool result = false;
            bool match_result_tau1 = false;
            bool match_result_tau2 = false;
            bool match_result_jet = false;
            if (hltpath_match) {
                match_result_tau1 = matchParticleNoModify(
                    tau1_p4, triggerobject_pts, triggerobject_etas,
                    triggerobject_phis, triggerobject_bits, triggerobject_ids,
                    0.4, 35.0, 2.5, 15, 14);
                match_result_tau2 = matchParticleNoModify(
                    tau2_p4, triggerobject_pts, triggerobject_etas,
                    triggerobject_phis, triggerobject_bits, triggerobject_ids,
                    0.4, 35.0, 2.5, 15, 14);
                match_result_jet = matchParticleNoModify(
                    jet_p4, triggerobject_pts, triggerobject_etas,
                    triggerobject_phis, triggerobject_bits, triggerobject_ids,
                    0.4, 30.0, 2.5, 1, 17);
            }
            
            // result = hltpath_match && match_result_tau1 && match_result_tau2 && match_result_jet;
            result = hltpath_match && match_result_tau1 && match_result_tau2 ; // the jet matching is not done in trigger setup, only match for ditau
            return result;
        };

    ROOT::RDF::RNode df2 = df1.Define("trg_ditaujet_tmp", ditaujet_match_calculator,
                       {ditaujet_hlt_path, tau1_p4, tau2_p4, jet_p4,
                        triggerobject_bits, triggerobject_id, triggerobject_pt,
                        triggerobject_eta, triggerobject_phi});

    // Now calculate the OR trigger SF
    auto ditau_or_trigger_sf_calculator = [evaluator_ditau_mc, evaluator_ditau_data,
                                       evaluator_ditaujet_mc, evaluator_ditaujet_data,
                                       tau_wp](
                                                                     const ROOT::Math::PtEtaPhiMVector &tau1_p4,
                                                                     const ROOT::Math::PtEtaPhiMVector &tau2_p4,
                                                                     const ROOT::Math::PtEtaPhiMVector &jet_p4,
                                                                     const UChar_t &tau1_dm_val,
                                                                     const UChar_t &tau2_dm_val,
                                                                     const bool &passDiTau_val,
                                                                     const bool &passDiTauJet_val) {
        float sf = 1.0;
        float tau1_pt_val = tau1_p4.pt();
        float tau2_pt_val = tau2_p4.pt();
        float jet_pt_val = jet_p4.pt();
        float jet_eta_val = std::abs(jet_p4.eta());

        // Get MC efficiencies
        // ditau tau threshold: pt 35 (first), pt 40 (second for ditau+jet)
        if (tau1_pt_val < 40.0) {
            tau1_pt_val = 40.0;
        }
        if (tau2_pt_val < 40.0) {
            tau2_pt_val = 40.0;
        }
        if (jet_pt_val < 30.0) {
            jet_pt_val = 30.0;
        }
        float eff_tautau_mc = evaluator_ditau_mc->evaluate({tau1_pt_val, tau1_dm_val, "ditau", tau_wp,  "eff_mc", "nom"}) * evaluator_ditau_mc->evaluate({tau2_pt_val, tau2_dm_val, "ditau", tau_wp, "eff_mc", "nom"});
        float eff_ditaujetTrg_mc = evaluator_ditaujet_mc->evaluate({jet_pt_val, jet_eta_val, "nom", "mc"}) * eff_tautau_mc;

        // Get Data efficiencies
        float eff_tautau_data = evaluator_ditau_data->evaluate({tau1_pt_val, tau1_dm_val, "ditau",tau_wp, "eff_data", "nom"}) * evaluator_ditau_data->evaluate({tau2_pt_val, tau2_dm_val, "ditau",tau_wp, "eff_data", "nom"});
        float eff_ditaujetTrg_data = evaluator_ditaujet_data->evaluate({jet_pt_val, jet_eta_val, "nom", "data"}) * eff_tautau_data;
      
        // Calculate OR efficiency for MC
        float OR_eff_mc = (passDiTau_val * eff_tautau_mc
                          - passDiTau_val * passDiTauJet_val * std::min(eff_ditaujetTrg_mc, eff_tautau_mc) * eff_ditaujetTrg_mc
                          + passDiTauJet_val * eff_ditaujetTrg_mc );

        // Calculate OR efficiency for Data
        float OR_eff_data = (passDiTau_val * eff_tautau_data
                            - passDiTau_val * passDiTauJet_val * std::min(eff_ditaujetTrg_data, eff_tautau_data) * eff_ditaujetTrg_data
                            + passDiTauJet_val * eff_ditaujetTrg_data );

        // Calculate scale factor
        if (OR_eff_mc > 0) {
            sf = OR_eff_data / OR_eff_mc;
        }

        Logger::get("ditau_or_trigger_sf")->debug("tau1_pt={}, tau2_pt={}, jet_pt={}, tau1_dm={}, tau2_dm={}, passDiTau={}, passDiTauJet={}, sf={}",
                                           tau1_pt_val, tau2_pt_val, jet_pt_val, tau1_dm_val, tau2_dm_val, passDiTau_val, passDiTauJet_val, sf);
        return sf;
    };

    auto df3 = df2.Define(sf_output, ditau_or_trigger_sf_calculator,
                        {tau1_p4, tau2_p4, jet_p4, tau1_dm, tau2_dm, "trg_ditau_tmp", "trg_ditaujet_tmp"});
    return df3;
}

} // namespace trigger
} // namespace scalefactor

#endif /* GUARD_SCALEFACTORS_H */