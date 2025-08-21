#ifndef GUARDMET_H
#define GUARDMET_H

#include "../include/RecoilCorrections/MetSystematics.hxx"
#include "../include/RecoilCorrections/RecoilCorrector.hxx"
#include "../include/basefunctions.hxx"
#include "../include/defaults.hxx"
#include "../include/utility/Logger.hxx"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include "bitset"
#include <Math/Vector4D.h>
#include <Math/VectorUtil.h>
#include <cmath>
#include "correction.h"
typedef std::bitset<20> IntBits;

namespace met {
/**
 * @brief function used to calculate the GenBosonVector and the
visibleGenBosonVector for an event.

The meaning of the genparticle statusflag codes is listed in the table below.

 Meaning                             | Value | Bit (value used in the config)
-------------------------------------|-------|-------
 isPrompt                            | 1     | 0
 isDecayedLeptonHadron               | 2     | 1
 isTauDecayProduct                   | 4     | 2
 isPromptTauDecayProduct             | 8     | 3
 isDirectTauDecayProduct             | 16    | 4
 isDirectPromptTauDecayProduct       | 32    | 5
 isDirectHadronDecayProduct          | 64    | 6
 isHardProcess                       | 128   | 7
 fromHardProcess                     | 256   | 8
 isHardProcessTauDecayProduct        | 512   | 9
 isDirectHardProcessTauDecayProduct  | 1024  | 10
 fromHardProcessBeforeFSR            | 2048  | 11
 isFirstCopy                         | 4096  | 12
 isLastCopy                          | 8192  | 13
 isLastCopyBeforeFSR                 | 16384 | 14

 *
 * @param df the input dataframe
 * @param genparticle_pt genparticle pt
 * @param genparticle_eta genparticle eta
 * @param genparticle_phi genparticle phi
 * @param genparticle_mass genparticle mass
 * @param genparticle_id genparticle PDG ID
 * @param genparticle_status genparticle status
 * @param genparticle_statusflag genparticle statusflag bit (see above)
 * @param outputname name of the new column containing the corrected met
 * @param is_data for data we cant calculate a genBoson vector, so a default
value is returned
 * @return a new dataframe containing a pair of lorentz vectors, first is the
GenBosonVector, second is the visibleGenBosonVector
 */
ROOT::RDF::RNode calculateGenBosonVector(
    ROOT::RDF::RNode df, const std::string &genparticle_pt,
    const std::string &genparticle_eta, const std::string &genparticle_phi,
    const std::string &genparticle_mass, const std::string &genparticle_id,
    const std::string &genparticle_status,
    const std::string &genparticle_statusflag, const std::string outputname,
    bool is_data) {
    auto calculateGenBosonVector =
        [](const ROOT::RVec<float> &genparticle_pt,
           const ROOT::RVec<float> &genparticle_eta,
           const ROOT::RVec<float> &genparticle_phi,
           const ROOT::RVec<float> &genparticle_mass,
           const ROOT::RVec<int> &genparticle_id,
           const ROOT::RVec<int> &genparticle_status,
           const ROOT::RVec<UShort_t> &genparticle_statusflag) {
            ROOT::Math::PtEtaPhiMVector genBoson;
            ROOT::Math::PtEtaPhiMVector visgenBoson;
            ROOT::Math::PtEtaPhiMVector genparticle;
            // now loop though all genparticles in the event
            for (std::size_t index = 0; index < genparticle_id.size();
                 ++index) {
                // consider a genparticle,
                // 1. if it is a lepton and fromHardProcessFinalState -->
                // bit 8 from statusflag and 1 from status
                // 2. if it is isDirectHardProcessTauDecayProduct --> bit 10
                // in statusflag
                Logger::get("getGenMet")
                    ->debug("Checking particle {} ", genparticle_id.at(index));
                if ((abs(genparticle_id.at(index)) >= 11 &&
                     abs(genparticle_id.at(index)) <= 16 &&
                     (IntBits(genparticle_statusflag.at(index)).test(8)) &&
                     genparticle_status.at(index) == 1) ||
                    (IntBits(genparticle_statusflag.at(index)).test(10))) {
                    Logger::get("getGenMet")->debug("Adding to gen p*");
                    genparticle = ROOT::Math::PtEtaPhiMVector(
                        genparticle_pt.at(index), genparticle_eta.at(index),
                        genparticle_phi.at(index), genparticle_mass.at(index));
                    genBoson = genBoson + genparticle;
                    // if the genparticle is no neutrino, we add the x and y
                    // component to the visible generator component as well
                    if (abs(genparticle_id.at(index)) != 12 &&
                        abs(genparticle_id.at(index)) != 14 &&
                        abs(genparticle_id.at(index)) != 16) {
                        Logger::get("getGenMet")->debug("Adding to vis p*");
                        visgenBoson = visgenBoson + genparticle;
                    }
                }
            }

            std::pair<ROOT::Math::PtEtaPhiMVector, ROOT::Math::PtEtaPhiMVector>
                metpair = {genBoson, visgenBoson};
            return metpair;
        };
    if (!is_data) {
        return df.Define(outputname, calculateGenBosonVector,
                         {genparticle_pt, genparticle_eta, genparticle_phi,
                          genparticle_mass, genparticle_id, genparticle_status,
                          genparticle_statusflag});
    } else {
        return df.Define(outputname, []() {
            std::pair<ROOT::Math::PtEtaPhiMVector, ROOT::Math::PtEtaPhiMVector>
                metpair = {default_lorentzvector, default_lorentzvector};
            return metpair;
        });
    }
}

/// Function to calculate the recoil component for dilepton channels and add it
/// to the dataframe
///
/// \param df the dataframe to add the quantity to
/// \param paralell_outputname name of the new column containing the parallell
/// recoil \param perpendicular_outputname name of the new column containing the
/// perpendicilar recoil \param lepton1 name of the column containing the
/// leading lepton lorentz vector \param lepton2 name of the column containing
/// the trailing lepton lorentz vector \param met_p4 name of the column
/// containing the MET lorentz vector
///
/// \returns a dataframe with the new column
ROOT::RDF::RNode DefineRecoilsDilep(ROOT::RDF::RNode df,
                                    const std::string &paralell_outputname,
                                    const std::string &perpendicular_outputname,
                                    const std::string &lepton1,
                                    const std::string &lepton2,
                                    const std::string &met_p4) {

    // paralell
    auto df1 = df.Define(
        paralell_outputname,
        [](const ROOT::Math::PtEtaPhiMVector &lepton1,
           const ROOT::Math::PtEtaPhiMVector &lepton2,
           const ROOT::Math::PtEtaPhiMVector &met_p4) {
            const ROOT::Math::PtEtaPhiMVector dilepton_vector =
                lepton1 + lepton2;
            double corrMet = met_p4.Et();
            double corrMetPhi = met_p4.Phi();

            double pUX = -corrMet * cos(corrMetPhi) -
                         dilepton_vector.Pt() * cos(dilepton_vector.Phi());
            double pUY = -corrMet * sin(corrMetPhi) -
                         dilepton_vector.Pt() * sin(dilepton_vector.Phi());
            double pU = sqrt(pUX * pUX + pUY * pUY);
            double pCos = (pUX * cos(dilepton_vector.Phi()) +
                           pUY * sin(dilepton_vector.Phi())) /
                          pU;
            double pSin = -(pUX * sin(dilepton_vector.Phi()) -
                            pUY * cos(dilepton_vector.Phi())) /
                          pU;

            return pU * pCos;
        },
        {lepton1, lepton2, met_p4});

    // perpendicular
    return df1.Define(perpendicular_outputname,
                      [](const ROOT::Math::PtEtaPhiMVector &lepton1,
                         const ROOT::Math::PtEtaPhiMVector &lepton2,
                         const ROOT::Math::PtEtaPhiMVector &met_p4) {
                          const ROOT::Math::PtEtaPhiMVector dilepton_vector =
                              lepton1 + lepton2;
                          double corrMet = met_p4.Et();
                          double corrMetPhi = met_p4.Phi();

                          double pUX =
                              corrMet * cos(corrMetPhi) +
                              dilepton_vector.Pt() * cos(dilepton_vector.Phi());
                          double pUY =
                              corrMet * sin(corrMetPhi) +
                              dilepton_vector.Pt() * sin(dilepton_vector.Phi());
                          double pU = sqrt(pUX * pUX + pUY * pUY);
                          double pCos = -(pUX * cos(dilepton_vector.Phi()) +
                                          pUY * sin(dilepton_vector.Phi())) /
                                        pU;
                          double pSin = (pUX * sin(dilepton_vector.Phi()) -
                                         pUY * cos(dilepton_vector.Phi())) /
                                        pU;

                          return pU * pSin;
                      },
                      {lepton1, lepton2, met_p4});
}

/// Function to calculate the recoil component for single lepton channels and
/// add it to the dataframe
///
/// \param df the dataframe to add the quantity to
/// \param paralell_outputname name of the new column containing the parallell
/// recoil \param perpendicular_outputname name of the new column containing the
/// perpendicilar recoil \param lepton1 name of the column containing the
/// leading lepton lorentz vector \param met_p4 name of the column containing
/// the MET lorentz vector
///
/// \returns a dataframe with the new column
ROOT::RDF::RNode
DefineRecoilsSinglelep(ROOT::RDF::RNode df,
                       const std::string &paralell_outputname,
                       const std::string &perpendicular_outputname,
                       const std::string &lepton1, const std::string &met_p4) {

    // paralell
    auto df1 = df.Define(
        paralell_outputname,
        [](const ROOT::Math::PtEtaPhiMVector &lepton1,
           const ROOT::Math::PtEtaPhiMVector &met_p4) {
            double corrMet = met_p4.Et();
            double corrMetPhi = met_p4.Phi();

            double pUX =
                -corrMet * cos(corrMetPhi) - lepton1.Pt() * cos(lepton1.Phi());
            double pUY =
                -corrMet * sin(corrMetPhi) - lepton1.Pt() * sin(lepton1.Phi());
            double pU = sqrt(pUX * pUX + pUY * pUY);
            double pCos =
                (pUX * cos(lepton1.Phi()) + pUY * sin(lepton1.Phi())) / pU;
            double pSin =
                -(pUX * sin(lepton1.Phi()) - pUY * cos(lepton1.Phi())) / pU;

            return pU * pCos;
        },
        {lepton1, met_p4});

    // perpendicular
    return df1.Define(
        perpendicular_outputname,
        [](const ROOT::Math::PtEtaPhiMVector &lepton1,
           const ROOT::Math::PtEtaPhiMVector &met_p4) {
            double corrMet = met_p4.Et();
            double corrMetPhi = met_p4.Phi();

            double pUX =
                corrMet * cos(corrMetPhi) + lepton1.Pt() * cos(lepton1.Phi());
            double pUY =
                corrMet * sin(corrMetPhi) + lepton1.Pt() * sin(lepton1.Phi());
            double pU = sqrt(pUX * pUX + pUY * pUY);
            double pCos =
                -(pUX * cos(lepton1.Phi()) + pUY * sin(lepton1.Phi())) / pU;
            double pSin =
                (pUX * sin(lepton1.Phi()) - pUY * cos(lepton1.Phi())) / pU;

            return pU * pSin;
        },
        {lepton1, met_p4});
}

/// Function to calculate the mass from the genboson double vector and add it to
/// the dataframe
///
/// \param df the dataframe to add the quantity to
/// \param outputname name of the new column containing the mass value
/// \param inputvector name of the column containing the genboson vector
///
/// \returns a dataframe with the new column

ROOT::RDF::RNode genBosonMass(ROOT::RDF::RNode df,
                              const std::string &outputname,
                              const std::string &inputvector) {
    return df.Define(outputname,
                     [](const std::pair<ROOT::Math::PtEtaPhiMVector,
                                        ROOT::Math::PtEtaPhiMVector> &metpair) {
                         if (metpair.first.pt() <
                             0.0) // negative pt is used to mark invalid LVs
                             return default_float;
                         return (float)metpair.first.mass();
                     },
                     {inputvector});
}
/// Function to calculate the pt from the genboson double vector and add it to
/// the dataframe
///
/// \param df the dataframe to add the quantity to
/// \param outputname name of the new column containing the pt value
/// \param inputvector name of the column containing the genboson vector
///
/// \returns a dataframe with the new column

ROOT::RDF::RNode genBosonPt(ROOT::RDF::RNode df, const std::string &outputname,
                            const std::string &inputvector) {
    return df.Define(outputname,
                     [](const std::pair<ROOT::Math::PtEtaPhiMVector,
                                        ROOT::Math::PtEtaPhiMVector> &metpair) {
                         if (metpair.first.pt() <
                             0.0) // negative pt is used to mark invalid LVs
                             return default_float;
                         return (float)metpair.first.pt();
                     },
                     {inputvector});
}

/// Function to calculate the eta from the genboson double vector and add it to
/// the dataframe
///
/// \param df the dataframe to add the quantity to
/// \param outputname name of the new column containing the eta value
/// \param inputvector name of the column containing the genboson vector
///
/// \returns a dataframe with the new column

ROOT::RDF::RNode genBosonEta(ROOT::RDF::RNode df, const std::string &outputname,
                             const std::string &inputvector) {
    return df.Define(outputname,
                     [](const std::pair<ROOT::Math::PtEtaPhiMVector,
                                        ROOT::Math::PtEtaPhiMVector> &metpair) {
                         if (metpair.first.pt() <
                             0.0) // negative pt is used to mark invalid LVs
                             return default_float;
                         return (float)metpair.first.eta();
                     },
                     {inputvector});
}

/// Function to calculate the phi from the genboson double vector and add it to
/// the dataframe
///
/// \param df the dataframe to add the quantity to
/// \param outputname name of the new column containing the phi value
/// \param inputvector name of the column containing the genboson vector
///
/// \returns a dataframe with the new column

ROOT::RDF::RNode genBosonPhi(ROOT::RDF::RNode df, const std::string &outputname,
                             const std::string &inputvector) {
    return df.Define(outputname,
                     [](const std::pair<ROOT::Math::PtEtaPhiMVector,
                                        ROOT::Math::PtEtaPhiMVector> &metpair) {
                         if (metpair.first.pt() <
                             0.0) // negative pt is used to mark invalid LVs
                             return default_float;
                         return (float)metpair.first.phi();
                     },
                     {inputvector});
}

/// Function to calculate the rapidity from the genboson double vector and add
/// it to the dataframe
///
/// \param df the dataframe to add the quantity to
/// \param outputname name of the new column containing the rapidity value
/// \param inputvector name of the column containing the genboson vector
///
/// \returns a dataframe with the new column

ROOT::RDF::RNode genBosonRapidity(ROOT::RDF::RNode df,
                                  const std::string &outputname,
                                  const std::string &inputvector) {
    return df.Define(outputname,
                     [](const std::pair<ROOT::Math::PtEtaPhiMVector,
                                        ROOT::Math::PtEtaPhiMVector> &metpair) {
                         if (metpair.first.pt() <
                             0.0) // negative pt is used to mark invalid LVs
                             return default_float;
                         return (float)metpair.first.Rapidity();
                     },
                     {inputvector});
}
/**
 * @brief Function used to propagate lepton corrections to the met. If the
 energy of a lepton is corrected (via some scale factor) or due to a shift,
 this change in energy has to be propagated to the met vector, and the met
 vector has to be adapted accordingly. The met is recalculated via
 @code
  Recalculate Met with corrected lepton energies :
  MetX_corrected = MetX + Px - Px_corrected
  MetY_corrected = MetY + Py - Py_corrected
  Met_corrected = sqrt(MetX_corrected * MetX_corrected + MetY_corrected *
 MetY_corrected)
 @endcode
 * @param df the input dataframe
 * @param met the uncorrected met lorentz vector
 * @param p4_1_uncorrected the uncorrected lorentz vector of the first
 lepton
 * @param p4_2_uncorrected the uncorrected lorentz vector of the second
 lepton
  * @param p4_3_uncorrected the uncorrected lorentz vector of the third
 lepton
 * @param p4_1 the corrected lorentz vector of the first lepton
 * @param p4_2 the corrected lorentz vector of the second lepton
 * @param p4_3 the corrected lorentz vector of the third lepton
 * @param outputname name of the column containing the corrected met lorentz
 * @param apply_propagation if bool is set, the propagation is applied, if
 not, the outputcolumn contains the original met value vector
 * @return a new df containing the corrected met lorentz vector
 */
ROOT::RDF::RNode propagateLeptonsToMet(
    ROOT::RDF::RNode df, const std::string &met,
    const std::string &p4_1_uncorrected, const std::string &p4_2_uncorrected,
    const std::string &p4_3_uncorrected, const std::string &p4_1,
    const std::string &p4_2, const std::string &p4_3,
    const std::string &outputname, bool apply_propagation) {
    auto scaleMet = [](const ROOT::Math::PtEtaPhiMVector &met,
                       const ROOT::Math::PtEtaPhiMVector &uncorrected_object,
                       const ROOT::Math::PtEtaPhiMVector &corrected_object) {
        // We propagate the lepton corrections to the Met by scaling the x
        // and y component of the Met according to the correction of the
        // lepton Recalculate Met with corrected lepton energies :
        // MetX_corrected = MetX + Px - Px_corrected
        // MetY_corrected = MetY + Py - Py_corrected
        // Met_corrected = sqrt(MetX_corrected * MetX_corrected +
        // MetY_corrected
        // * MetY_corrected)
        float corr_x = uncorrected_object.Px() - corrected_object.Px();
        float corr_y = uncorrected_object.Py() - corrected_object.Py();
        float MetX = met.Px() + corr_x;
        float MetY = met.Py() + corr_y;
        Logger::get("propagateLeptonsToMet")->debug("corr_x {}", corr_x);
        Logger::get("propagateLeptonsToMet")->debug("corr_y {}", corr_y);
        Logger::get("propagateLeptonsToMet")->debug("MetX {}", MetX);
        Logger::get("propagateLeptonsToMet")->debug("MetY {}", MetY);
        ROOT::Math::PtEtaPhiMVector corrected_met;
        corrected_met.SetPxPyPzE(MetX, MetY, 0,
                                 std::sqrt(MetX * MetX + MetY * MetY));
        Logger::get("propagateLeptonsToMet")
            ->debug("corrected_object pt - {}", corrected_object.Pt());
        Logger::get("propagateLeptonsToMet")
            ->debug("uncorrected_object pt - {}", uncorrected_object.Pt());
        Logger::get("propagateLeptonsToMet")->debug("old met {}", met.Pt());
        Logger::get("propagateLeptonsToMet")
            ->debug("corrected met {}", corrected_met.Pt());
        return corrected_met;
    };
    if (apply_propagation) {
        // first correct for the first lepton, store the met in an
        // intermediate1 column
        Logger::get("propagateLeptonsToMet")
            ->debug("Setting up correction for first lepton {}", p4_1);
        Logger::get("propagateLeptonsToMet")
            ->debug("p4 uncorr. {}, p4 corr {}", p4_1_uncorrected, p4_1);
        auto df1 = df.Define(outputname + "_intermediate1", scaleMet,
                             {met, p4_1_uncorrected, p4_1});
        // second correct for the second lepton with the p4_1 corrected met as
        // input, store the met in an intermediate2 column
        Logger::get("propagateLeptonsToMet")
            ->debug("Setting up correction for second lepton {}", p4_2);
        Logger::get("propagateLeptonsToMet")
            ->debug("p4 uncorr. {}, p4 corr {}", p4_2_uncorrected, p4_2);
        auto df2 =
            df1.Define(outputname + "_intermediate2", scaleMet,
                       {outputname + "_intermediate1", p4_2_uncorrected, p4_2});
        // after the third lepton correction, the correct output column is
        // used
        Logger::get("propagateLeptonsToMet")
            ->debug("Setting up correction for third lepton {}", p4_3);
        Logger::get("propagateLeptonsToMet")
            ->debug("p4 uncorr. {}, p4 corr {}", p4_3_uncorrected, p4_3);
        return df2.Define(
            outputname, scaleMet,
            {outputname + "_intermediate2", p4_3_uncorrected, p4_3});
    } else {
        // if we do not apply the propagation, just rename the met column to
        // the new outputname and dont change anything else
        return basefunctions::rename<ROOT::Math::PtEtaPhiMVector>(df, met,
                                                                  outputname);
    }
}
/**
 * @brief Function used to propagate lepton corrections to the met. If the
 energy of a lepton is corrected (via some scale factor) or due to a shift,
 this change in energy has to be propagated to the met vector, and the met
 vector has to be adapted accordingly. The met is recalculated via
 @code
  Recalculate Met with corrected lepton energies :
  MetX_corrected = MetX + Px - Px_corrected
  MetY_corrected = MetY + Py - Py_corrected
  Met_corrected = sqrt(MetX_corrected * MetX_corrected + MetY_corrected *
 MetY_corrected)
 @endcode
 * @param df the input dataframe
 * @param met the uncorrected met lorentz vector
 * @param p4_1_uncorrected the uncorrected lorentz vector of the first
 lepton
 * @param p4_2_uncorrected the uncorrected lorentz vector of the second
 lepton
 * @param p4_1 the corrected lorentz vector of the first lepton
 * @param p4_2 the corrected lorentz vector of the second lepton
 * @param outputname name of the column containing the corrected met lorentz
 * @param apply_propagation if bool is set, the propagation is applied, if
 not, the outputcolumn contains the original met value vector
 * @return a new df containing the corrected met lorentz vector
 */
ROOT::RDF::RNode
propagateLeptonsToMet(ROOT::RDF::RNode df, const std::string &met,
                      const std::string &p4_1_uncorrected,
                      const std::string &p4_2_uncorrected,
                      const std::string &p4_1, const std::string &p4_2,
                      const std::string &outputname, bool apply_propagation) {
    auto scaleMet = [](const ROOT::Math::PtEtaPhiMVector &met,
                       const ROOT::Math::PtEtaPhiMVector &uncorrected_object,
                       const ROOT::Math::PtEtaPhiMVector &corrected_object) {
        // We propagate the lepton corrections to the Met by scaling the x
        // and y component of the Met according to the correction of the
        // lepton Recalculate Met with corrected lepton energies :
        // MetX_corrected = MetX + Px - Px_corrected
        // MetY_corrected = MetY + Py - Py_corrected
        // Met_corrected = sqrt(MetX_corrected * MetX_corrected +
        // MetY_corrected
        // * MetY_corrected)
        float corr_x = uncorrected_object.Px() - corrected_object.Px();
        float corr_y = uncorrected_object.Py() - corrected_object.Py();
        float MetX = met.Px() + corr_x;
        float MetY = met.Py() + corr_y;
        Logger::get("propagateLeptonsToMet")->debug("corr_x {}", corr_x);
        Logger::get("propagateLeptonsToMet")->debug("corr_y {}", corr_y);
        Logger::get("propagateLeptonsToMet")->debug("MetX {}", MetX);
        Logger::get("propagateLeptonsToMet")->debug("MetY {}", MetY);
        ROOT::Math::PtEtaPhiMVector corrected_met;
        corrected_met.SetPxPyPzE(MetX, MetY, 0,
                                 std::sqrt(MetX * MetX + MetY * MetY));
        Logger::get("propagateLeptonsToMet")
            ->debug("corrected_object pt - {}", corrected_object.Pt());
        Logger::get("propagateLeptonsToMet")
            ->debug("uncorrected_object pt - {}", uncorrected_object.Pt());
        Logger::get("propagateLeptonsToMet")->debug("old met {}", met.Pt());
        Logger::get("propagateLeptonsToMet")
            ->debug("corrected met {}", corrected_met.Pt());
        return corrected_met;
    };
    if (apply_propagation) {
        // first correct for the first lepton, store the met in an
        // intermediate column
        Logger::get("propagateLeptonsToMet")
            ->debug("Setting up correction for first lepton {}", p4_1);
        auto df1 = df.Define(outputname + "_intermediate", scaleMet,
                             {met, p4_1_uncorrected, p4_1});
        // after the second lepton correction, the correct output column is
        // used
        Logger::get("propagateLeptonsToMet")
            ->debug("Setting up correction for second lepton {}", p4_2);
        return df1.Define(
            outputname, scaleMet,
            {outputname + "_intermediate", p4_2_uncorrected, p4_2});
    } else {
        // if we do not apply the propagation, just rename the met column to
        // the new outputname and dont change anything else
        return basefunctions::rename<ROOT::Math::PtEtaPhiMVector>(df, met,
                                                                  outputname);
    }
}

/**
 * @brief Function used to propagate lepton corrections to the met. If the
 energy of a lepton is corrected (via some scale factor) or due to a shift,
 this change in energy has to be propagated to the met vector, and the met
 vector has to be adapted accordingly. The met is recalculated via
 @code
  Recalculate Met with corrected lepton energies :
  MetX_corrected = MetX + Px - Px_corrected
  MetY_corrected = MetY + Py - Py_corrected
  Met_corrected = sqrt(MetX_corrected * MetX_corrected + MetY_corrected *
 MetY_corrected)
 @endcode
 * @param df the input dataframe
 * @param met the uncorrected met lorentz vector
 * @param p4_1_uncorrected the uncorrected lorentz vector of the first
 lepton
 * @param p4_1 the corrected lorentz vector of the first lepton
 * @param outputname name of the column containing the corrected met lorentz
 * @param apply_propagation if bool is set, the propagation is applied, if
 not, the outputcolumn contains the original met value vector
 * @return a new df containing the corrected met lorentz vector
 */
ROOT::RDF::RNode propagateLeptonsToMet(ROOT::RDF::RNode df,
                                       const std::string &met,
                                       const std::string &p4_1_uncorrected,
                                       const std::string &p4_1,
                                       const std::string &outputname,
                                       bool apply_propagation) {
    auto scaleMet = [](const ROOT::Math::PtEtaPhiMVector &met,
                       const ROOT::Math::PtEtaPhiMVector &uncorrected_object,
                       const ROOT::Math::PtEtaPhiMVector &corrected_object) {
        // We propagate the lepton corrections to the Met by scaling the x
        // and y component of the Met according to the correction of the
        // lepton Recalculate Met with corrected lepton energies :
        // MetX_corrected = MetX + Px - Px_corrected
        // MetY_corrected = MetY + Py - Py_corrected
        // Met_corrected = sqrt(MetX_corrected * MetX_corrected +
        // MetY_corrected
        // * MetY_corrected)
        float corr_x = uncorrected_object.Px() - corrected_object.Px();
        float corr_y = uncorrected_object.Py() - corrected_object.Py();
        float MetX = met.Px() + corr_x;
        float MetY = met.Py() + corr_y;
        Logger::get("propagateLeptonsToMet")->debug("corr_x {}", corr_x);
        Logger::get("propagateLeptonsToMet")->debug("corr_y {}", corr_y);
        Logger::get("propagateLeptonsToMet")->debug("MetX {}", MetX);
        Logger::get("propagateLeptonsToMet")->debug("MetY {}", MetY);
        ROOT::Math::PtEtaPhiMVector corrected_met;
        corrected_met.SetPxPyPzE(MetX, MetY, 0,
                                 std::sqrt(MetX * MetX + MetY * MetY));
        Logger::get("propagateLeptonsToMet")
            ->debug("corrected_object pt - {}", corrected_object.Pt());
        Logger::get("propagateLeptonsToMet")
            ->debug("uncorrected_object pt - {}", uncorrected_object.Pt());
        Logger::get("propagateLeptonsToMet")->debug("old met {}", met.Pt());
        Logger::get("propagateLeptonsToMet")
            ->debug("corrected met {}", corrected_met.Pt());
        return corrected_met;
    };
    if (apply_propagation) {
        // first correct for the first lepton, store the met in an
        // intermediate column
        Logger::get("propagateLeptonsToMet")
            ->debug("Setting up correction for first lepton {}", p4_1);
        return df.Define(outputname, scaleMet, {met, p4_1_uncorrected, p4_1});
    } else {
        // if we do not apply the propagation, just rename the met column to
        // the new outputname and dont change anything else
        return basefunctions::rename<ROOT::Math::PtEtaPhiMVector>(df, met,
                                                                  outputname);
    }
}

/**
 * @brief Function used to propagate jet corrections to the met. If the
 energy of a jet is corrected, this
 change in energy has to be propagated to the met vector, and the met vector
 has to be adapted accordingly. The met is recalculated via
 @code
  Recalculate Met with corrected jet energies :
  MetX_corrected = MetX + Px - Px_corrected
  MetY_corrected = MetY + Py - Py_corrected
  Met_corrected = sqrt(MetX_corrected * MetX_corrected + MetY_corrected *
 MetY_corrected)
 @endcode
 The correction is done for all valid jets.
 * @param df the input dataframe
 * @param met the uncorrected met lorentz vector
 * @param jet_pt_corrected pt of the corrected jet
 * @param jet_eta_corrected eta of the corrected jet
 * @param jet_phi_corrected phi of the corrected jet
 * @param jet_mass_corrected mass of the corrected jet
 * @param jet_pt pt of the uncorrected jet
 * @param jet_eta eta of the uncorrected jet
 * @param jet_phi phi of the uncorrected jet
 * @param jet_mass mass of the uncorrected jet
 * @param outputname name of the column containing the corrected met lorentz
 vector
  * @param apply_propagation if bool is set, the propagation is applied, if
 not, the outputcolumn contains the original met value
 * @param min_jet_pt minimal pt, the corrected jet has to have, in order for
 the met propagation to be applied
 * @return a new df containing the corrected met lorentz vector
 */
ROOT::RDF::RNode propagateJetsToMet(
    ROOT::RDF::RNode df, const std::string &met,
    const std::string &jet_pt_corrected, const std::string &jet_eta_corrected,
    const std::string &jet_phi_corrected, const std::string &veto_mask,
    const std::string &jet_mass_corrected,
    const std::string &jet_pt, const std::string &jet_eta, 
    const std::string &jet_phi, const std::string &jet_mass,
    const std::string &outputname, bool apply_propagation, float min_jet_pt) {
    // propagate jet corrections to met, since we can have an arbitrary
    // amount of jets, this has to be done per event
    auto scaleMet = [min_jet_pt](const ROOT::Math::PtEtaPhiMVector &met,
                                 const ROOT::RVec<float> &jet_pt_corrected,
                                 const ROOT::RVec<float> &jet_eta_corrected,
                                 const ROOT::RVec<float> &jet_phi_corrected,
                                 const ROOT::RVec<int> &veto_mask,
                                 const ROOT::RVec<float> &jet_mass_corrected,
                                 const ROOT::RVec<float> &jet_pt,
                                 const ROOT::RVec<float> &jet_eta,
                                 const ROOT::RVec<float> &jet_phi,
                                 const ROOT::RVec<float> &jet_mass) {
        ROOT::Math::PtEtaPhiMVector corrected_met;
        ROOT::Math::PtEtaPhiMVector uncorrected_jet;
        ROOT::Math::PtEtaPhiMVector corrected_jet;
        float corr_x = 0.0;
        float corr_y = 0.0;
        float veto_met = -999.0;
        Logger::get("propagateJetsToMet")
                    ->debug("Checking jet pt size  {} ", jet_pt.size());
        Logger::get("propagateJetsToMet")
                    ->debug("Checking jet corrected pt size  {} ", jet_pt_corrected.size());  
        // now loop through all jets in the event
        
        
        
        for (std::size_t index = 0; index < jet_pt.size(); ++index) {

            Logger::get("propagateJetsToMet")
                    ->debug("Checking jet index {}  ",index);
            Logger::get("propagateJetsToMet")
                    ->debug("Checking jet index {} pt {} ",index, jet_pt.at(index));
            Logger::get("propagateJetsToMet")
                    ->debug("Checking jet corrected index {} pt {} ", index, jet_pt_corrected.at(index));     
            Logger::get("propagateJetsToMet")
                    ->debug("Checking jet corrected index {} mask {} ", index, veto_mask.at(index));                    
            // only propagate jets above the given pt threshold
            if (jet_pt_corrected.at(index) <= -900.0) {
                // jet vetoed is given pt -999, any events with vetoded jets should be vetoed as well
                // save this as -999
                corrected_met=ROOT::Math::PtEtaPhiMVector(veto_met, veto_met, veto_met,veto_met);
                return corrected_met;
            }
            float min_jet_pt_tmp =0;
            if (veto_mask.at(index) == 1){
                if (abs(jet_eta_corrected.at(index)) > 3.0 || abs(jet_eta_corrected.at(index)) <2.5     ){
                    min_jet_pt_tmp = 40.0;
                }    
                else min_jet_pt_tmp =50.0;
                if (jet_pt_corrected.at(index) > min_jet_pt_tmp) {
                
                    // construct the uncorrected and the corrected lorentz
                    // vectors
                    corrected_jet = ROOT::Math::PtEtaPhiMVector(
                        jet_pt_corrected.at(index), jet_eta_corrected.at(index),
                        jet_phi_corrected.at(index), jet_mass_corrected.at(index));
                    uncorrected_jet = ROOT::Math::PtEtaPhiMVector(
                        jet_pt.at(index), jet_eta.at(index), jet_phi.at(index),
                        jet_mass.at(index));
                    // update the correction factors that are applied to the met
                    corr_x += uncorrected_jet.Px() - corrected_jet.Px();
                    corr_y += uncorrected_jet.Py() - corrected_jet.Py();
                // }
                // }
                }
            }    
        }
        float MetX = met.Px() + corr_x;
        float MetY = met.Py() + corr_y;
        Logger::get("propagateJetsToMet")
            ->debug("corr_x {}, corr_y {}", corr_x, corr_y);
        Logger::get("propagateJetsToMet")
            ->debug("MetX {}, MetY {}", MetX, MetY);
        corrected_met.SetPxPyPzE(MetX, MetY, 0,
                                 std::sqrt(MetX * MetX + MetY * MetY));
        Logger::get("propagateJetsToMet")->debug("old met {}", met.Pt());
        Logger::get("propagateJetsToMet")
            ->debug("corrected met {}", corrected_met.Pt());
        return corrected_met;
    };
    if (apply_propagation) {
        return df.Define(outputname, scaleMet,
                         {met, jet_pt_corrected, jet_eta_corrected,
                          jet_phi_corrected, veto_mask, jet_mass_corrected, jet_pt,
                          jet_eta, jet_phi, jet_mass});
    } else {
        // if we do not apply the propagation, just rename the met column to
        // the new outputname and dont change anything else
        return basefunctions::rename<ROOT::Math::PtEtaPhiMVector>(df, met,
                                                                  outputname);
    }
}
/**
 * @brief function used to apply Recoil corrections on a given sample. For
more information on recoil corrections, check [this
repo](https://github.com/KIT-CMS/RecoilCorrections/). The code for the
application of these corrections can be found in `src/RecoilCorrections`.
 *
 * @param df the input dataframe
 * @param met the input met
 * @param genboson the genboson vector, this is a std::pair where the first
value is the genboson vector and the seconds value is the visible genboson
vector
 * @param jet_pt the pt of all jets
 * @param outputname name of the new column containing the corrected met
 * @param recoilfile path to the recoil corrections file
 * @param systematicsfile path to the systematics corrections file
 * @param applyRecoilCorrections if bool is set, the recoil correction is
applied, if not, the outputcolumn contains the original met value
 * @param resolution bool - if set, resolution corrections are applied
 * @param response bool - if set, response corrections are applied
 * @param shiftUp bool - if set, the up shift is applied
 * @param shiftDown bool - if set, the down shift is applied
 * @param isWjets bool - if set, the number of jets is incrased by one (this
is only needed for WJets samples)
 * @return a new dataframe containing the new met column
 */
ROOT::RDF::RNode applyRecoilCorrections(
    ROOT::RDF::RNode df, const std::string &met, const std::string &genboson,
    const std::string &jet_pt, const std::string &jet_eta, const std::string &veto_mask,  const std::string &outputname,
    const std::string &recoilfile, const std::string &systematicsfile,
    bool applyRecoilCorrections, bool resolution, bool response, bool shiftUp,
    bool shiftDown, bool isWjets) {
    if (applyRecoilCorrections) {
        Logger::get("RecoilCorrections")->debug("Will run recoil corrections");
        // const auto corrector = new RecoilCorrector(recoilfile);
        // const auto systematics = new MetSystematic(systematicsfile);
        
        auto evaluator = correction::CorrectionSet::from_file(recoilfile)->at("Recoil_correction_Rescaling");
        auto evaluator_syst = correction::CorrectionSet::from_file(recoilfile)->at("Recoil_correction_Uncertainty"); 
        // warning!!!!!!!!! only for testing, put back recoil correction uncertainty once ready!!!    
        // auto shiftType = MetSystematic::SysShift::Nominal;
        // if (shiftUp) {
        //     shiftType = MetSystematic::SysShift::Up;
        // } else if (shiftDown) {
        //     shiftType = MetSystematic::SysShift::Down;
        // }
        // auto sysType = MetSystematic::SysType::None;
        // if (response) {
        //     sysType = MetSystematic::SysType::Response;
        // } else if (resolution) {
        //     sysType = MetSystematic::SysType::Resolution;
        // }
        auto RecoilCorrections = [resolution, response, shiftUp, shiftDown, evaluator, evaluator_syst,
                                  isWjets](
                                     ROOT::Math::PtEtaPhiMVector &met,
                                     std::pair<ROOT::Math::PtEtaPhiMVector,
                                               ROOT::Math::PtEtaPhiMVector>
                                         &genboson,
                                     const ROOT::RVec<float> &jet_pt, const ROOT::RVec<float> &jet_eta,  const ROOT::RVec<int> &veto_mask) {
            // TODO is this the correct number of jets ?
            float MetX = met.Px();
            float MetY = met.Py();
            float METpt = met.pt();
            float METphi = met.phi();
            float correctedMetX = 0.;
            float correctedMetY = 0.;
            float veto_met = -999.0;
            ROOT::Math::PtEtaPhiMVector genparticle;
            ROOT::Math::PtEtaPhiMVector corrected_met;
            float genPx = genboson.first.Px();  // generator Z(W) px
            float FullGenPt = genboson.first.pt(); 
            float FullGenPhi = genboson.first.phi(); 
            float genPy = genboson.first.Py();  // generator Z(W) py
            float VisGenPt= genboson.second.pt(); 
            float VisGenPhi= genboson.second.phi(); 
            float visPx = genboson.second.Px(); // visible (generator) Z(W) px
            float visPy = genboson.second.Py(); // visible (generator) Z(W) py
            float nJets30 = 0;

            // Loop through all jets
            for (size_t i = 0; i < jet_pt.size(); ++i) {
                const float pt = jet_pt[i];
                const float eta = jet_eta[i];
                const int mask = veto_mask[i];
                

                Logger::get("RecoilCorrections")->debug("checking for jet with index {} ", i);
                Logger::get("RecoilCorrections")->debug("jet pt {} ", pt);
                Logger::get("RecoilCorrections")->debug("jet eta {} ", eta);
                Logger::get("RecoilCorrections")->debug("jet veto mask {} ", mask );


                if (pt <= -900.0) {
                    // jet vetoed is given pt -999, any events with vetoded jets should be vetoed as well
                    // save this as -999
                    corrected_met=ROOT::Math::PtEtaPhiMVector(veto_met, veto_met, veto_met,veto_met);
                    return corrected_met;
                }
                // Check if jet satisfies the criteria
                // veto mask 1: pass veto, not overlapping with leptons
                if (mask == 1){
                    if ((pt > 30 && std::abs(eta) < 2.5) || (pt > 50)) {
                        nJets30++;
                    }
                }
                
            }
        
            // Adjust for W+jets category
            if (isWjets) {
                nJets30 += 1;
            }
        
            // Cap at 2
            if (nJets30 >= 2) {
                nJets30 = 2;
            }

  
            Logger::get("RecoilCorrections")->debug("Corrector Inputs");
            Logger::get("RecoilCorrections")->debug("nJets30 {} ", nJets30);
            Logger::get("RecoilCorrections")->debug("genPt {} ", FullGenPt);
            Logger::get("RecoilCorrections")->debug("genPhi {} ", FullGenPhi);
            Logger::get("RecoilCorrections")->debug("visPt {} ", VisGenPt);
            Logger::get("RecoilCorrections")->debug("visPhi {} ", VisGenPhi);
            // Logger::get("RecoilCorrections")->debug("MetX {} ", MetX);
            // Logger::get("RecoilCorrections")->debug("MetY {} ", MetY);
            // Logger::get("RecoilCorrections")
            //     ->debug("correctedMetX {} ", correctedMetX);
            // Logger::get("RecoilCorrections")
            //     ->debug("correctedMetY {} ", correctedMetY);
            Logger::get("RecoilCorrections")->debug("old met {} ", met.Pt());
            Logger::get("RecoilCorrections")->debug("old met phi {} ", met.Phi());
            
            
            // define some helper functions
            auto GetXYfromPTPHI = [](float pt, float phi) -> std::pair<float, float> {
                return {pt * std::cos(phi), pt * std::sin(phi)};
            };

            auto GetPTPHIfromXY = [](float x, float y) -> std::pair<float, float> {
                return {std::hypot(x, y), std::atan2(y, x)}; // return square root of square sum x, y
            };

            auto GetU = [&](float METpt, float METphi, 
                            float FullVPt, float FullVPhi,
                            float VisVPt, float VisVPhi) -> std::pair<float, float> {
                auto [METx, METy] = GetXYfromPTPHI(METpt, METphi);
                auto [FullVx, FullVy] = GetXYfromPTPHI(FullVPt, FullVPhi);
                auto [VisVx, VisVy] = GetXYfromPTPHI(VisVPt, VisVPhi);
                
                float Ux = METx + VisVx - FullVx;
                float Uy = METy + VisVy - FullVy;
                auto [Upt, Uphi] = GetPTPHIfromXY(Ux, Uy);
                auto [Upara, Uperp] = GetXYfromPTPHI(Upt, Uphi - FullVPhi);
                return {Upara, Uperp};
            };

            auto GetMETfromU = [&](float Upara, float Uperp,
                                float FullVPt, float FullVPhi,
                                float VisVPt, float VisVPhi) -> std::pair<float, float> {
                auto [FullVx, FullVy] = GetXYfromPTPHI(FullVPt, FullVPhi);
                auto [VisVx, VisVy] = GetXYfromPTPHI(VisVPt, VisVPhi);
                
                auto [Upt, UphiMinusFullVPhi] = GetPTPHIfromXY(Upara, Uperp);
                float Uphi = UphiMinusFullVPhi + FullVPhi;
                auto [Ux, Uy] = GetXYfromPTPHI(Upt, Uphi);
                
                float METx = Ux - VisVx + FullVx;
                float METy = Uy - VisVy + FullVy;
                return GetPTPHIfromXY(METx, METy);
            };

            auto GetH = [&](float METpt, float METphi,
                        float FullVPt, float FullVPhi,
                        float VisVPt, float VisVPhi) -> std::pair<float, float> {
                auto [METx, METy] = GetXYfromPTPHI(METpt, METphi);
                auto [VisVx, VisVy] = GetXYfromPTPHI(VisVPt, VisVPhi);
                
                float Hx = -METx - VisVx;
                float Hy = -METy - VisVy;
                auto [Hpt, Hphi] = GetPTPHIfromXY(Hx, Hy);
                auto [Hpara, Hperp] = GetXYfromPTPHI(Hpt, Hphi - FullVPhi);
                return {Hpara, Hperp};
            };

            auto GetMETfromH = [&](float Hpara, float Hperp,
                                float FullVPt, float FullVPhi,
                                float VisVPt, float VisVPhi) -> std::pair<float, float> {
                auto [VisVx, VisVy] = GetXYfromPTPHI(VisVPt, VisVPhi);
                auto [Hpt, HphiMinusFullVPhi] = GetPTPHIfromXY(Hpara, Hperp);
                float Hphi = HphiMinusFullVPhi + FullVPhi;
                auto [Hx, Hy] = GetXYfromPTPHI(Hpt, Hphi);
                
                float METx = -Hx - VisVx;
                float METy = -Hy - VisVy;
                return GetPTPHIfromXY(METx, METy);
            };
            
            
            // corrector->CorrectWithHist(MetX, MetY, genPx, genPy, visPx, visPy,
            //                            nJets30, correctedMetX, correctedMetY);
            
            auto [upara, uperp] = GetU(METpt, METphi, FullGenPt, FullGenPhi, VisGenPt, VisGenPhi);
            float upara_new = evaluator->evaluate({"NLO", nJets30, FullGenPt, "Upara", upara});
            float uperp_new = evaluator->evaluate({"NLO", nJets30, FullGenPt, "Uperp", uperp});
            auto [METpt_new, METphi_new] = GetMETfromU(upara_new, uperp_new, FullGenPt, FullGenPhi,VisGenPt, VisGenPhi);
            auto [hpara,hperp] = GetH(METpt_new, METphi_new, FullGenPt, FullGenPhi, VisGenPt, VisGenPhi);
            if (resolution) {
                if (shiftUp) {
                    // Resolution Up variation
                    auto hParaResoUp = evaluator_syst->evaluate({"NLO", nJets30, FullGenPt, "Hpara", hpara, "ResolUp"});
                    auto hPerpResoUp = evaluator_syst->evaluate({"NLO", nJets30, FullGenPt, "Hperp", hperp, "ResolUp"});
                    auto [METpt_ResoUp, METphi_ResoUp] = GetMETfromH(hParaResoUp, hPerpResoUp, FullGenPt, FullGenPhi, VisGenPt, VisGenPhi);
                    corrected_met= ROOT::Math::PtEtaPhiMVector(METpt_ResoUp, 0, METphi_ResoUp, 0);
                } else if (shiftDown) {
                    // Resolution Down variation
                    auto hParaResoDn = evaluator_syst->evaluate({"NLO", nJets30, FullGenPt, "Hpara", hpara, "ResolDown"});
                    auto hPerpResoDn = evaluator_syst->evaluate({"NLO", nJets30, FullGenPt, "Hperp", hperp, "ResolDown"});
                    auto [METpt_ResoDn, METphi_ResoDn] = GetMETfromH(hParaResoDn, hPerpResoDn, FullGenPt, FullGenPhi, VisGenPt, VisGenPhi);
                    corrected_met= ROOT::Math::PtEtaPhiMVector(METpt_ResoDn, 0, METphi_ResoDn, 0);
                } else {
                    // Handle error: No shift direction specified for resolution
                    // Example: Set MET to nominal or throw an exception
                }
            } else if (response){
                // Handle response systematics
                if (shiftUp) {
                    // Response Up variation
                    auto hParaRespUp = evaluator_syst->evaluate({"NLO", nJets30, FullGenPt, "Hpara", hpara, "RespUp"});
                    auto hPerpRespUp = evaluator_syst->evaluate({"NLO", nJets30, FullGenPt, "Hperp", hperp, "RespUp"});
                    auto [METpt_RespUp, METphi_RespUp] = GetMETfromH(hParaRespUp, hPerpRespUp, FullGenPt, FullGenPhi, VisGenPt, VisGenPhi);
                    corrected_met= ROOT::Math::PtEtaPhiMVector(METpt_RespUp, 0, METphi_RespUp, 0);
                } else if (shiftDown) {
                    // Response Down variation
                    auto hParaRespDn = evaluator_syst->evaluate({"NLO", nJets30, FullGenPt, "Hpara", hpara, "RespDown"});
                    auto hPerpRespDn = evaluator_syst->evaluate({"NLO", nJets30, FullGenPt, "Hperp", hperp, "RespDown"});
                    auto [METpt_RespDn, METphi_RespDn] = GetMETfromH(hParaRespDn, hPerpRespDn, FullGenPt, FullGenPhi, VisGenPt, VisGenPhi);
                    corrected_met= ROOT::Math::PtEtaPhiMVector(METpt_RespDn, 0, METphi_RespDn, 0);
                } else {
                    // Handle error: No shift direction specified for response
                    // Example: Set MET to nominal or throw an exception
                }
            }
            else{

                // nominal
                Logger::get("RecoilCorrections")
                ->debug("setting for new nominal met {} ", METpt_new);
                Logger::get("RecoilCorrections")
                ->debug("setting for new nominal met phi {} ", METphi_new);
                corrected_met= ROOT::Math::PtEtaPhiMVector(METpt_new, 0, METphi_new, 0);
            }

            
            // // only apply shifts if the correpsonding variables are set
            // if (sysType != MetSystematic::SysType::None &&
            //     shiftType != MetSystematic::SysShift::Nominal) {
            //     Logger::get("RecoilCorrections")
            //         ->debug(" apply systematics {} {}", sysType, shiftType);
            //     systematics->ApplyMetSystematic(
            //         correctedMetX, correctedMetY, genPx, genPy, visPx, visPy,
            //         nJets30, sysType, shiftType, correctedMetX, correctedMetY);
            // }
            // corrected_met.SetPxPyPzE(correctedMetX, correctedMetY, 0,
            //                          std::sqrt(correctedMetX * correctedMetX +
            //                                    correctedMetY * correctedMetY));
            Logger::get("RecoilCorrections")
                ->debug("shifted and corrected met {} ", corrected_met.Pt());
            Logger::get("RecoilCorrections")
                ->debug("shifted and corrected met {} ", corrected_met.Phi());

            return corrected_met;
        };
        return df.Define(outputname, RecoilCorrections,
                         {met, genboson, jet_pt, jet_eta, veto_mask});
    } else {
        // if we do not apply the recoil corrections, just rename the met
        // column to the new outputname and dont change anything else
        return basefunctions::rename<ROOT::Math::PtEtaPhiMVector>(df, met,
                                                                  outputname);
    }
}
} // end namespace met
#endif /* GUARDMET_H */
