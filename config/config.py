from __future__ import annotations  # needed for type annotations in > python 3.7

from typing import List

import code_generation.producers.electrons as electrons
import code_generation.producers.embedding as emb
import code_generation.producers.event as event
import code_generation.producers.genparticles as genparticles
import code_generation.producers.jets as jets
import code_generation.producers.met as met
import code_generation.producers.muons as muons
import code_generation.producers.pairquantities as pairquantities
import code_generation.producers.pairselection as pairselection
import code_generation.producers.scalefactors as scalefactors
import code_generation.producers.taus as taus
import code_generation.producers.triggers as triggers
import code_generation.quantities.nanoAOD as nanoAOD
import code_generation.quantities.output as q
from config.tau_triggersetup import add_diTauTriggerSetup
from code_generation.configuration import Configuration
from code_generation.modifiers import EraModifier, SampleModifier
from code_generation.rules import AppendProducer, RemoveProducer
from code_generation.systematics import SystematicShift, SystematicShiftByQuantity


def build_config(
    era: str,
    sample: str,
    channels: List[str],
    shifts: List[str],
    available_sample_types: List[str],
    available_eras: List[str],
    available_channels: List[str],
):

    configuration = Configuration(
        era,
        sample,
        channels,
        shifts,
        available_sample_types,
        available_eras,
        available_channels,
    )

    # first add default parameters necessary for all scopes
    configuration.add_config_parameters(
        "global",
        {
            "RunLumiEventFilter_Quantities": ["event", "luminosityBlock"],
            "RunLumiEventFilter_Quantity_Types": ["ULong64_t", "UInt_t"],
            "RunLumiEventFilter_Selections": ["3", "318"],
            "PU_reweighting_file": EraModifier(
                {
                    "2016": "data/pileup/Data_Pileup_2016_271036-284044_13TeVMoriond17_23Sep2016ReReco_69p2mbMinBiasXS.root",
                    "2017": "data/pileup/Data_Pileup_2017_294927-306462_13TeVSummer17_PromptReco_69p2mbMinBiasXS.root",
                    "2018": "data/pileup/Data_Pileup_2018_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18.root",
                }
            ),
            "golden_json_file": EraModifier(
                {
                    "2016": "data/golden_json/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt",
                    "2017": "data/golden_json/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt",
                    "2018": "data/golden_json/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt",
                }
            ),
            "PU_reweighting_hist": "pileup",
            "met_filters": EraModifier(
                {
                    "2016": [
                        "Flag_goodVertices",
                        "Flag_globalSuperTightHalo2016Filter",
                        "Flag_HBHENoiseFilter",
                        "Flag_HBHENoiseIsoFilter",
                        "Flag_EcalDeadCellTriggerPrimitiveFilter",
                        "Flag_BadPFMuonFilter",
                        # "Flag_BadPFMuonDzFilter", # only since nanoAODv9 available
                        "Flag_eeBadScFilter",
                    ],
                    "2017": [
                        "Flag_goodVertices",
                        "Flag_globalSuperTightHalo2016Filter",
                        "Flag_HBHENoiseFilter",
                        "Flag_HBHENoiseIsoFilter",
                        "Flag_EcalDeadCellTriggerPrimitiveFilter",
                        "Flag_BadPFMuonFilter",
                        # "Flag_BadPFMuonDzFilter", # only since nanoAODv9 available
                        "Flag_eeBadScFilter",
                        "Flag_ecalBadCalibFilter",
                    ],
                    "2018": [
                        "Flag_goodVertices",
                        "Flag_globalSuperTightHalo2016Filter",
                        "Flag_HBHENoiseFilter",
                        "Flag_HBHENoiseIsoFilter",
                        "Flag_EcalDeadCellTriggerPrimitiveFilter",
                        "Flag_BadPFMuonFilter",
                        # "Flag_BadPFMuonDzFilter", # only since nanoAODv9 available
                        "Flag_eeBadScFilter",
                        "Flag_ecalBadCalibFilter",
                    ],
                }
            ),
        },
    )
    # Tau base selection:
    configuration.add_config_parameters(
        ["global"],
        {
            "min_tau_pt": 30.0,
            "max_tau_eta": 2.3,
            "max_tau_dz": 0.2,
            "tau_dms": "0,1,10,11",
            "tau_sf_file": EraModifier(
                {
                    "2016": "data/jsonpog-integration/POG/TAU/2016postVFP_UL/tau.json.gz",
                    "2017": "data/jsonpog-integration/POG/TAU/2017_UL/tau.json.gz",
                    "2018": "data/jsonpog-integration/POG/TAU/2018_UL/tau.json.gz",
                }
            ),
            "tau_ES_json_name": "tau_energy_scale",
            "tau_id_algorithm": "DeepTau2017v2p1",
            "tau_ES_variation": "nom",  # or "up"/"down" for up/down variation
        },
    )
    # muon base selection:
    configuration.add_config_parameters(
        "global",
        {
            "min_muon_pt": 10.0,
            "max_muon_eta": 2.4,
            "max_muon_dxy": 0.045,
            "max_muon_dz": 0.2,
            "muon_id": "Muon_mediumId",
            "muon_iso_cut": 0.3,
        },
    )
    # electron base selection:
    configuration.add_config_parameters(
        "global",
        {
            "min_ele_pt": 10.0,
            "max_ele_eta": 2.5,
            "max_ele_dxy": 0.045,
            "max_ele_dz": 0.2,
            "max_ele_iso": 0.3,
            "ele_id": "Electron_mvaFall17V2noIso_WP90",
        },
    )
    # jet base selection:
    configuration.add_config_parameters(
        "global",
        {
            "min_jet_pt": 30,
            "max_jet_eta": 4.7,
            "jet_id": 2,  # second bit is tight JetID
            "jet_puid": 4,  # 0==fail, 4==pass(loose), 6==pass(loose,medium), 7==pass(loose,medium,tight) !check 2016 -> inverted ID
            "jet_puid_max_pt": 50,  # recommended to apply puID only for jets below 50 GeV
            "JEC_shift_sources": '{""}',
            "JE_scale_shift": 0,
            "JE_reso_shift": 0,
        },
    )
    # bjet base selection:
    configuration.add_config_parameters(
        "global",
        {
            "min_bjet_pt": 20,
            "max_bjet_eta": 2.4,
            "btag_cut": 0.2783,  # medium
        },
    )
    # leptonveto base selection:
    configuration.add_config_parameters(
        "global",
        {
            "min_dielectronveto_pt": 15.0,
            "dielectronveto_id": "Electron_cutBased",
            "dielectronveto_id_wp": 1,
            "min_dimuonveto_pt": 15.0,
            "dimuonveto_id": "Muon_looseId",
            "dileptonveto_dR": 0.15,
        },
    )
    ###### Channel Specifics ######
    # MT/TT/ET channel tau ID flags and SFs
    configuration.add_config_parameters(
        ["mt", "tt", "et"],
        {
            "tau_dms": "0,1,10,11",
            "tau_sf_file": EraModifier(
                {
                    "2016": "data/jsonpog-integration/POG/TAU/2016postVFP_UL/tau.json.gz",
                    "2017": "data/jsonpog-integration/POG/TAU/2017_UL/tau.json.gz",
                    "2018": "data/jsonpog-integration/POG/TAU/2018_UL/tau.json.gz",
                }
            ),
            "vsjet_tau_id": [
                {
                    "tau_id_discriminator": "DeepTau2017v2p1VSjet",
                    "tau_1_vsjet_sf_outputname": "id_wgt_tau_vsJet_{wp}_1".format(
                        wp=wp
                    ),
                    "tau_2_vsjet_sf_outputname": "id_wgt_tau_vsJet_{wp}_2".format(
                        wp=wp
                    ),
                    "vsjet_tau_id_WP": "{wp}".format(wp=wp),
                    "tau_1_vsjet_id_outputname": "id_tau_vsJet_{wp}_1".format(wp=wp),
                    "tau_2_vsjet_id_outputname": "id_tau_vsJet_{wp}_2".format(wp=wp),
                    "vsjet_tau_id_WPbit": bit,
                }
                for wp, bit in {
                    "VVVLoose": 1,
                    "VVLoose": 2,
                    "VLoose": 3,
                    "Loose": 4,
                    "Medium": 5,
                    "Tight": 6,
                    "VTight": 7,
                    "VVTight": 8,
                }.items()
            ],
            "vsele_tau_id": [
                {
                    "tau_id_discriminator": "DeepTau2017v2p1VSe",
                    "tau_1_vsele_sf_outputname": "id_wgt_tau_vsEle_{wp}_1".format(
                        wp=wp
                    ),
                    "tau_2_vsele_sf_outputname": "id_wgt_tau_vsEle_{wp}_2".format(
                        wp=wp
                    ),
                    "vsele_tau_id_WP": "{wp}".format(wp=wp),
                    "tau_1_vsele_id_outputname": "id_tau_vsEle_{wp}_1".format(wp=wp),
                    "tau_2_vsele_id_outputname": "id_tau_vsEle_{wp}_2".format(wp=wp),
                    "vsele_tau_id_WPbit": bit,
                }
                for wp, bit in {
                    "VVLoose": 2,
                    "VLoose": 3,
                    "Loose": 4,
                    "Medium": 5,
                    "Tight": 6,
                    "VTight": 7,
                    "VVTight": 8,
                }.items()
            ],
            "vsmu_tau_id": [
                {
                    "tau_id_discriminator": "DeepTau2017v2p1VSmu",
                    "tau_1_vsmu_sf_outputname": "id_wgt_tau_vsMu_{wp}_1".format(wp=wp),
                    "tau_2_vsmu_sf_outputname": "id_wgt_tau_vsMu_{wp}_2".format(wp=wp),
                    "vsmu_tau_id_WP": "{wp}".format(wp=wp),
                    "tau_1_vsmu_id_outputname": "id_tau_vsMu_{wp}_1".format(wp=wp),
                    "tau_2_vsmu_id_outputname": "id_tau_vsMu_{wp}_2".format(wp=wp),
                    "vsmu_tau_id_WPbit": bit,
                }
                for wp, bit in {
                    "VLoose": 1,
                    "Loose": 2,
                    "Medium": 3,
                    "Tight": 4,
                }.items()
            ],
            "tau_sf_variation": "nom",  # or "up"/"down" for up/down variation
            "tau_vsjet_sf_dependence": "pt",  # or "dm", "eta"
        },
    )

    # MT / ET tau selection
    configuration.add_config_parameters(
        ["et", "mt"],
        {
            "min_tau_pt": 30.0,
            "max_tau_eta": 2.3,
            "max_tau_dz": 0.2,
            "tau_dms": "0,1,10,11",
            "vsjet_tau_id_bit": 4,
            "vsele_tau_id_bit": 4,
            "vsmu_tau_id_bit": 1,
            "tau_sf_file": EraModifier(
                {
                    "2016": "data/jsonpog-integration/POG/TAU/2016postVFP_UL/tau.json.gz",
                    "2017": "data/jsonpog-integration/POG/TAU/2017_UL/tau.json.gz",
                    "2018": "data/jsonpog-integration/POG/TAU/2018_UL/tau.json.gz",
                }
            ),
            "tau_ES_json_name": "tau_energy_scale",
            "tau_id_algorithm": "DeepTau2017v2p1",
            "tau_ES_variation": "nom",  # or "up"/"down" for up/down variation
        },
    )
    # TT tau selection:
    configuration.add_config_parameters(
        ["tt"],
        {
            "min_tau_pt": 35.0,
            "max_tau_eta": 2.3,
            "max_tau_dz": 0.2,
            "tau_dms": "0,1,10,11",
            "vsjet_tau_id_bit": 4,
            "vsele_tau_id_bit": 4,
            "vsmu_tau_id_bit": 1,
            "tau_sf_file": EraModifier(
                {
                    "2016": "data/jsonpog-integration/POG/TAU/2016postVFP_UL/tau.json.gz",
                    "2017": "data/jsonpog-integration/POG/TAU/2017_UL/tau.json.gz",
                    "2018": "data/jsonpog-integration/POG/TAU/2018_UL/tau.json.gz",
                }
            ),
            "tau_ES_json_name": "tau_energy_scale",
            "tau_id_algorithm": "DeepTau2017v2p1",
            "tau_ES_variation": "nom",  # or "up"/"down" for up/down variation
        },
    )

    # MT/MM channel Muon selection
    configuration.add_config_parameters(
        ["mt", "mm"],
        {
            "muon_index_in_pair": 0,
            "min_muon_pt": 23.0,
            "max_muon_eta": 2.1,
            "muon_iso_cut": 0.15,
            "muon_sf_file": EraModifier(
                {
                    "2016": "data/jsonpog-integration/POG/MUO/2016postVFP_UL/muon_Z.json.gz",
                    "2017": "data/jsonpog-integration/POG/MUO/2017_UL/muon_Z.json.gz",
                    "2018": "data/jsonpog-integration/POG/MUO/2018_UL/muon_Z.json.gz",
                }
            ),
            "muon_id_sf_name": "NUM_MediumID_DEN_TrackerMuons",
            "muon_iso_sf_name": "NUM_TightRelIso_DEN_MediumID",
            "muon_sf_year_id": EraModifier(
                {
                    "2016": "2016postVFP_UL",
                    "2017": "2017_UL",
                    "2018": "2018_UL",
                }
            ),
            "muon_sf_varation": "sf",  # "sf" is nominal, "systup"/"systdown" are up/down variations
        },
    )
    # ET/EM channel electron selection
    configuration.add_config_parameters(
        ["et", "em"],
        {
            "electron_index_in_pair": 0,
            "min_electron_pt": 25.0,
            "max_electron_eta": 2.1,
            "electron_iso_cut": 0.3,
            # "muon_sf_workspace": "data/muon_corrections/htt_scalefactors_legacy_2018_muons.root",
            # "muon_sf_id_name": "m_id_kit_ratio",
            # "muon_sf_id_args": "m_pt,m_eta",
            # "muon_sf_iso_name": "m_iso_binned_kit_ratio",
            # "muon_sf_iso_args": "m_pt,m_eta,m_iso",
        },
    )
    configuration.add_config_parameters(
        ["mm"],
        {
            "min_muon_pt": 20.0,
            "max_muon_eta": 2.1,
            "muon_iso_cut": 0.15,
            "second_muon_index_in_pair": 1,
        },
    )
    ## all channels misc settings
    configuration.add_config_parameters(
        channels,
        {
            "deltaR_jet_veto": 0.5,
            "pairselection_min_dR": 0.5,
        },
    )
    ## all channels MET selection
    configuration.add_config_parameters(
        channels,
        {
            "propagateLeptons": SampleModifier(
                {"data": False, "emb": False},
                default=True,
            ),
            "propagateJets": SampleModifier(
                {"data": False, "emb": False},
                default=True,
            ),
            "recoil_corrections_file": EraModifier(
                {
                    "2016": "data/recoil_corrections/Type1_PuppiMET_2016.root",
                    "2017": "data/recoil_corrections/Type1_PuppiMET_2017.root",
                    "2018": "data/recoil_corrections/Type1_PuppiMET_2018.root",
                }
            ),
            "recoil_systematics_file": EraModifier(
                {
                    "2016": "data/recoil_corrections/PuppiMETSys_2016.root",
                    "2017": "data/recoil_corrections/PuppiMETSys_2017.root",
                    "2018": "data/recoil_corrections/PuppiMETSys_2018.root",
                }
            ),
            "applyRecoilCorrections": SampleModifier({"wj": True}, default=False),
            "apply_recoil_resolution_systematic": False,
            "apply_recoil_response_systematic": False,
            "recoil_systematic_shift_up": False,
            "recoil_systematic_shift_down": False,
            "min_jetpt_met_propagation": 15,
        },
    )

    configuration.add_config_parameters(
        channels,
        {
            "ggHNNLOweightsRootfile": "data/htxs/NNLOPS_reweight.root",
            "ggH_generator": "powheg",
            "zptmass_file": EraModifier(
                {
                    "2016": "data/zpt/htt_scalefactors_legacy_2016.root",
                    "2017": "data/zpt/htt_scalefactors_legacy_2017.root",
                    "2018": "data/zpt/htt_scalefactors_legacy_2018.root",
                }
            ),
            "zptmass_functor": "zptmass_weight_nom",
            "zptmass_arguments": "z_gen_mass,z_gen_pt",
        },
    )
    configuration.add_producers(
        "global",
        [
            # event.RunLumiEventFilter,
            event.SampleFlags,
            event.Lumi,
            event.npartons,
            event.MetFilter,
            event.PUweights,
            taus.TauEnergyCorrection,  # or TauEnergyCorrection_byValue for previous implementation
            taus.BaseTaus,
            muons.BaseMuons,
            electrons.BaseElectrons,
            jets.JetEnergyCorrection,
            jets.GoodJets,
            jets.GoodBJets,
            event.DiLeptonVeto,
            met.MetBasics,
        ],
    )
    ## add prefiring
    if era != "2018":
        configuration.add_producers(
            "global",
            [
                event.PrefiringWeight,
            ],
        )
    # common
    configuration.add_producers(
        channels,
        [
            jets.JetCollection,
            jets.BasicJetQuantities,
            jets.BJetCollection,
            jets.BasicBJetQuantities,
            met.MetCorrections,
            met.PFMetCorrections,
            pairquantities.DiTauPairMETQuantities,
        ],
    )
    configuration.add_producers(
        "mm",
        [
            muons.GoodMuons,
            muons.VetoMuons,
            muons.VetoSecondMuon,
            muons.ExtraMuonsVeto,
            muons.NumberOfGoodMuons,
            pairselection.ZMMPairSelection,
            pairselection.GoodMMPairFilter,
            pairselection.LVMu1,
            pairselection.LVMu2,
            pairselection.LVMu1Uncorrected,
            pairselection.LVMu2Uncorrected,
            pairquantities.MMDiTauPairQuantities,
            genparticles.MMGenDiTauPairQuantities,
            scalefactors.MuonIDIso_SF,
            triggers.MMGenerateSingleMuonTriggerFlags,
        ],
    )
    configuration.add_producers(
        "mt",
        [
            muons.GoodMuons,
            muons.NumberOfGoodMuons,
            muons.VetoMuons,
            muons.ExtraMuonsVeto,
            taus.GoodTaus,
            taus.NumberOfGoodTaus,
            electrons.ExtraElectronsVeto,
            pairselection.MTPairSelection,
            pairselection.GoodMTPairFilter,
            pairselection.LVMu1,
            pairselection.LVTau2,
            pairselection.LVMu1Uncorrected,
            pairselection.LVTau2Uncorrected,
            pairquantities.MTDiTauPairQuantities,
            genparticles.MTGenDiTauPairQuantities,
            scalefactors.MuonIDIso_SF,
            scalefactors.TauID_SF,
            triggers.MTGenerateSingleMuonTriggerFlags,
            triggers.MTGenerateCrossTriggerFlags,
        ],
    )
    configuration.add_producers(
        "et",
        [
            electrons.GoodElectrons,
            taus.GoodTaus,
            taus.NumberOfGoodTaus,
            electrons.NumberOfGoodElectrons,
            electrons.VetoElectrons,
            electrons.ExtraElectronsVeto,
            muons.ExtraMuonsVeto,
            pairselection.ETPairSelection,
            pairselection.GoodETPairFilter,
            pairselection.LVEl1,
            pairselection.LVTau2,
            pairselection.LVEl1Uncorrected,
            pairselection.LVTau2Uncorrected,
            pairquantities.ETDiTauPairQuantities,
            genparticles.ETGenDiTauPairQuantities,
            scalefactors.TauID_SF,
            triggers.ETGenerateSingleElectronTriggerFlags,
            triggers.ETGenerateCrossTriggerFlags,
        ],
    )
    configuration.add_producers(
        "tt",
        [
            taus.GoodTaus,
            taus.NumberOfGoodTaus,
            pairselection.TTPairSelection,
            pairselection.GoodTTPairFilter,
            pairselection.LVTau1,
            pairselection.LVTau2,
            pairselection.LVTau1Uncorrected,
            pairselection.LVTau2Uncorrected,
            pairquantities.TTDiTauPairQuantities,
            genparticles.TTGenDiTauPairQuantities,
            scalefactors.TauID_SF,
            triggers.TTGenerateDoubleTriggerFlags,
        ],
    )
    configuration.add_modification_rule(
        ["et", "mt", "tt"],
        RemoveProducer(producers=scalefactors.TauID_SF, samples="data"),
    )
    configuration.add_modification_rule(
        ["mt", "mm"],
        RemoveProducer(producers=scalefactors.MuonIDIso_SF, samples="data"),
    )
    configuration.add_modification_rule(
        "global",
        RemoveProducer(
            producers=[event.PUweights, event.npartons],
            samples=["data", "emb", "emb_mc"],
        ),
    )
    configuration.add_modification_rule(
        channels,
        AppendProducer(
            producers=[event.GGH_NNLO_Reweighting, event.GGH_WG1_Uncertainties],
            samples="ggh",
        ),
    )
    configuration.add_modification_rule(
        channels,
        AppendProducer(producers=event.QQH_WG1_Uncertainties, samples="qqh"),
    )
    configuration.add_modification_rule(
        channels,
        AppendProducer(producers=event.TopPtReweighting, samples="ttbar"),
    )
    configuration.add_modification_rule(
        channels,
        AppendProducer(producers=event.ZPtMassReweighting, samples="dy"),
    )
    # changes needed for data
    # global scope
    configuration.add_modification_rule(
        "global",
        AppendProducer(
            producers=jets.RenameJetsData, samples=["data", "emb", "emb_mc"]
        ),
    )
    configuration.add_modification_rule(
        "global",
        AppendProducer(producers=event.JSONFilter, samples=["data", "emb"]),
    )
    configuration.add_modification_rule(
        "global",
        AppendProducer(producers=emb.EmbeddingQuantities, samples=["emb", "emb_mc"]),
    )
    configuration.add_modification_rule(
        "global",
        RemoveProducer(
            producers=jets.JetEnergyCorrection, samples=["data", "emb", "emb_mc"]
        ),
    )
    # channel specific
    configuration.add_modification_rule(
        "mt",
        RemoveProducer(
            producers=[genparticles.MTGenDiTauPairQuantities],
            samples=["data"],
        ),
    )
    configuration.add_modification_rule(
        "et",
        RemoveProducer(
            producers=[genparticles.ETGenDiTauPairQuantities],
            samples=["data"],
        ),
    )
    configuration.add_modification_rule(
        "tt",
        RemoveProducer(
            producers=[genparticles.TTGenDiTauPairQuantities],
            samples=["data"],
        ),
    )
    configuration.add_modification_rule(
        "mm",
        RemoveProducer(
            producers=[genparticles.MMGenDiTauPairQuantities],
            samples=["data"],
        ),
    )

    configuration.add_outputs(
        channels,
        [
            q.is_data,
            q.is_emb,
            q.is_tt,
            q.is_dy,
            q.is_wj,
            q.is_ggh,
            q.is_vbf,
            q.is_vv,
            nanoAOD.run,
            q.lumi,
            q.npartons,
            nanoAOD.event,
            q.puweight,
            q.pt_1,
            q.pt_2,
            q.eta_1,
            q.eta_2,
            q.phi_1,
            q.phi_2,
            q.njets,
            q.jpt_1,
            q.jpt_2,
            q.jeta_1,
            q.jeta_2,
            q.jphi_1,
            q.jphi_2,
            q.jtag_value_1,
            q.jtag_value_2,
            q.mjj,
            q.m_vis,
            q.pt_vis,
            q.nbtag,
            q.bpt_1,
            q.bpt_2,
            q.beta_1,
            q.beta_2,
            q.bphi_1,
            q.bphi_2,
            q.btag_value_1,
            q.btag_value_2,
            q.mass_1,
            q.mass_2,
            q.dxy_1,
            q.dxy_2,
            q.dz_1,
            q.dz_2,
            q.q_1,
            q.q_2,
            q.iso_1,
            q.iso_2,
            q.gen_pt_1,
            q.gen_eta_1,
            q.gen_phi_1,
            q.gen_mass_1,
            q.gen_pdgid_1,
            q.gen_pt_2,
            q.gen_eta_2,
            q.gen_phi_2,
            q.gen_mass_2,
            q.gen_pdgid_2,
            q.gen_m_vis,
            q.met,
            q.metphi,
            q.pfmet,
            q.pfmetphi,
            q.met_uncorrected,
            q.metphi_uncorrected,
            q.pfmet_uncorrected,
            q.pfmetphi_uncorrected,
            q.metSumEt,
            q.metcov00,
            q.metcov01,
            q.metcov10,
            q.metcov11,
            q.pzetamissvis,
            q.mTdileptonMET,
            q.mt_1,
            q.mt_2,
            q.pt_tt,
            q.pt_ttjj,
            q.mt_tot,
            q.genbosonmass,
        ],
    )
    configuration.add_outputs(
        "mt",
        [
            q.nmuons,
            q.ntaus,
            scalefactors.Tau_2_VsJetTauID_SF.output_group,
            scalefactors.Tau_2_VsEleTauID_SF.output_group,
            scalefactors.Tau_2_VsMuTauID_SF.output_group,
            pairquantities.VsJetTauIDFlag_2.output_group,
            pairquantities.VsEleTauIDFlag_2.output_group,
            pairquantities.VsMuTauIDFlag_2.output_group,
            triggers.MTGenerateSingleMuonTriggerFlags.output_group,
            triggers.MTGenerateCrossTriggerFlags.output_group,
            q.taujet_pt_2,
            # q.gen_taujet_pt_2,
            q.decaymode_2,
            q.gen_match_2,
            q.muon_veto_flag,
            q.dimuon_veto,
            q.electron_veto_flag,
            q.idWeight_1,
            q.isoWeight_1,
        ],
    )
    configuration.add_outputs(
        "et",
        [
            q.nelectrons,
            q.ntaus,
            scalefactors.Tau_2_VsJetTauID_SF.output_group,
            scalefactors.Tau_2_VsEleTauID_SF.output_group,
            scalefactors.Tau_2_VsMuTauID_SF.output_group,
            pairquantities.VsJetTauIDFlag_2.output_group,
            pairquantities.VsEleTauIDFlag_2.output_group,
            pairquantities.VsMuTauIDFlag_2.output_group,
            triggers.ETGenerateSingleElectronTriggerFlags.output_group,
            triggers.ETGenerateCrossTriggerFlags.output_group,
            q.taujet_pt_2,
            # q.gen_taujet_pt_2,
            q.decaymode_2,
            q.gen_match_2,
            q.muon_veto_flag,
            q.dimuon_veto,
            q.electron_veto_flag,
            # q.idWeight_1,
            # q.isoWeight_1,
        ],
    )
    configuration.add_outputs(
        "tt",
        [
            q.ntaus,
            scalefactors.Tau_1_VsJetTauID_SF.output_group,
            scalefactors.Tau_1_VsEleTauID_SF.output_group,
            scalefactors.Tau_1_VsMuTauID_SF.output_group,
            scalefactors.Tau_2_VsJetTauID_SF.output_group,
            scalefactors.Tau_2_VsEleTauID_SF.output_group,
            scalefactors.Tau_2_VsMuTauID_SF.output_group,
            pairquantities.VsJetTauIDFlag_1.output_group,
            pairquantities.VsEleTauIDFlag_1.output_group,
            pairquantities.VsMuTauIDFlag_1.output_group,
            pairquantities.VsJetTauIDFlag_2.output_group,
            pairquantities.VsEleTauIDFlag_2.output_group,
            pairquantities.VsMuTauIDFlag_2.output_group,
            triggers.TTGenerateDoubleTriggerFlags.output_group,
            q.taujet_pt_1,
            q.taujet_pt_2,
            # q.gen_taujet_pt_2,
            q.decaymode_1,
            q.decaymode_2,
            q.gen_match_1,
            q.gen_match_2,
            # q.muon_veto_flag,
            # q.dimuon_veto,
            # q.electron_veto_flag,
        ],
    )

    configuration.add_outputs(
        "mm",
        [
            q.nmuons,
            triggers.MMGenerateSingleMuonTriggerFlags.output_group,
            # q.idWeight_1,
            # q.isoWeight_1,
            # q.idWeight_2,
            # q.isoWeight_2,
        ],
    )
    if "data" not in sample and "emb" not in sample:
        configuration.add_outputs(
            channels,
            [
                nanoAOD.HTXS_Higgs_pt,
                nanoAOD.HTXS_Higgs_y,
                nanoAOD.HTXS_njets30,
                nanoAOD.HTXS_stage_0,
                nanoAOD.HTXS_stage1_2_cat_pTjet30GeV,
                nanoAOD.HTXS_stage1_2_fine_cat_pTjet30GeV,
            ],
        )

    #########################
    # TES Shifts
    #########################
    # configuration.add_shift(
    #     SystematicShift(
    #         name="tauES_1prong0pizeroDown",
    #         shift_config={"global": {"tau_ES_shift_DM0": 0.998}},
    #         producers={"global": taus.TauPtCorrection},
    #         ignore_producers={"mt": [pairselection.LVMu1, muons.VetoMuons]},
    #     )
    # )
    # configuration.add_shift(
    #     SystematicShift(
    #         name="tauES_1prong0pizeroUp",
    #         shift_config={"global": {"tau_ES_shift_DM0": 1.002}},
    #         producers={"global": taus.TauPtCorrection},
    #         ignore_producers={"mt": [pairselection.LVMu1, muons.VetoMuons]},
    #     )
    # )

    #########################
    # Import triggersetup   #
    #########################
    add_diTauTriggerSetup(configuration)

    configuration.add_shift(
        SystematicShift(
            name="tauES_Down",
            shift_config={"global": {"tau_ES_variation": "down"}},
            producers={"global": taus.TauPtCorrection},
            ignore_producers={
                "mt": [pairselection.LVMu1, muons.VetoMuons],
                "et": [pairselection.LVEl1, electrons.VetoElectrons],
            },
        )
    )
    configuration.add_shift(
        SystematicShift(
            name="tauES_Up",
            shift_config={"global": {"tau_ES_variation": "up"}},
            producers={"global": taus.TauPtCorrection},
            ignore_producers={
                "mt": [pairselection.LVMu1, muons.VetoMuons],
                "et": [pairselection.LVEl1, electrons.VetoElectrons],
            },
        )
    )
    #########################
    # MET Shifts
    #########################
    configuration.add_shift(
        SystematicShiftByQuantity(
            name="metUnclusteredEnUp",
            quantity_change={
                nanoAOD.MET_pt: "PuppiMET_ptUnclusteredUp",
                nanoAOD.MET_phi: "PuppiMET_phiUnclusteredUp",
            },
            scopes=["global"],
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShiftByQuantity(
            name="metUnclusteredEnDown",
            quantity_change={
                nanoAOD.MET_pt: "PuppiMET_ptUnclusteredDown",
                nanoAOD.MET_phi: "PuppiMET_phiUnclusteredDown",
            },
            scopes=["global"],
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    #########################
    # Prefiring Shifts
    #########################
    if era != "2018":
        configuration.add_shift(
            SystematicShiftByQuantity(
                name="prefiringDown",
                quantity_change={
                    nanoAOD.prefireWeight: "L1PreFiringWeight_Dn",
                },
                scopes=["global"],
            )
        )
        configuration.add_shift(
            SystematicShiftByQuantity(
                name="prefiringUp",
                quantity_change={
                    nanoAOD.prefireWeight: "L1PreFiringWeight_Up",
                },
                scopes=["global"],
            )
        )
    #########################
    # MET Recoil Shifts
    #########################
    configuration.add_shift(
        SystematicShift(
            name="metRecoilResponseUp",
            shift_config={
                ("et", "mt", "tt", "em", "ee", "mm"): {
                    "apply_recoil_resolution_systematic": False,
                    "apply_recoil_response_systematic": True,
                    "recoil_systematic_shift_up": True,
                    "recoil_systematic_shift_down": False,
                },
            },
            producers={
                ("et", "mt", "tt", "em", "ee", "mm"): met.ApplyRecoilCorrections
            },
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="metRecoilResponseDown",
            shift_config={
                ("et", "mt", "tt", "em", "ee", "mm"): {
                    "apply_recoil_resolution_systematic": False,
                    "apply_recoil_response_systematic": True,
                    "recoil_systematic_shift_up": False,
                    "recoil_systematic_shift_down": True,
                },
            },
            producers={
                ("et", "mt", "tt", "em", "ee", "mm"): met.ApplyRecoilCorrections
            },
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="metRecoilResolutionUp",
            shift_config={
                ("et", "mt", "tt", "em", "ee", "mm"): {
                    "apply_recoil_resolution_systematic": True,
                    "apply_recoil_response_systematic": False,
                    "recoil_systematic_shift_up": True,
                    "recoil_systematic_shift_down": False,
                },
            },
            producers={
                ("et", "mt", "tt", "em", "ee", "mm"): met.ApplyRecoilCorrections
            },
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="metRecoilResolutionDown",
            shift_config={
                ("et", "mt", "tt", "em", "ee", "mm"): {
                    "apply_recoil_resolution_systematic": True,
                    "apply_recoil_response_systematic": False,
                    "recoil_systematic_shift_up": False,
                    "recoil_systematic_shift_down": True,
                },
            },
            producers={
                ("et", "mt", "tt", "em", "ee", "mm"): met.ApplyRecoilCorrections
            },
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    #########################
    # Jet energy resolution
    #########################
    configuration.add_shift(
        SystematicShift(
            name="jerUncUp",
            shift_config={
                "global": {"JE_reso_shift": 1},
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="jerUncDown",
            shift_config={
                "global": {"JE_reso_shift": -1},
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    #########################
    # Jet energy scale
    #########################
    JEC_sources = '{"SinglePionECAL", "SinglePionHCAL", "AbsoluteMPFBias", "AbsoluteScale", "Fragmentation", "PileUpDataMC", "RelativeFSR", "PileUpPtRef"}'
    configuration.add_shift(
        SystematicShift(
            name="jecUncAbsoluteUp",
            shift_config={
                "global": {
                    "JE_scale_shift": 1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="jecUncAbsoluteDown",
            shift_config={
                "global": {
                    "JE_scale_shift": -1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )

    JEC_sources = '{"AbsoluteStat", "TimePtEta", "RelativeStatFSR"}'
    configuration.add_shift(
        SystematicShift(
            name="jecUncAbsoluteYearUp",
            shift_config={
                "global": {
                    "JE_scale_shift": 1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="jecUncAbsoluteYearDown",
            shift_config={
                "global": {
                    "JE_scale_shift": -1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )

    JEC_sources = '{"FlavorQCD"}'
    configuration.add_shift(
        SystematicShift(
            name="jecUncFlavorQCDUp",
            shift_config={
                "global": {
                    "JE_scale_shift": 1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="jecUncFlavorQCDDown",
            shift_config={
                "global": {
                    "JE_scale_shift": -1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )

    JEC_sources = '{"PileUpPtEC1", "PileUpPtBB", "RelativePtBB"}'
    configuration.add_shift(
        SystematicShift(
            name="jecUncBBEC1Up",
            shift_config={
                "global": {
                    "JE_scale_shift": 1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="jecUncBBEC1Down",
            shift_config={
                "global": {
                    "JE_scale_shift": -1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )

    JEC_sources = '{"RelativeJEREC1", "RelativePtEC1", "RelativeStatEC"}'
    configuration.add_shift(
        SystematicShift(
            name="jecUncBBEC1YearUp",
            shift_config={
                "global": {
                    "JE_scale_shift": 1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="jecUncBBEC1YearDown",
            shift_config={
                "global": {
                    "JE_scale_shift": -1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )

    JEC_sources = '{"RelativePtHF", "PileUpPtHF", "RelativeJERHF"}'
    configuration.add_shift(
        SystematicShift(
            name="jecUncHFUp",
            shift_config={
                "global": {
                    "JE_scale_shift": 1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="jecUncHFDown",
            shift_config={
                "global": {
                    "JE_scale_shift": -1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )

    JEC_sources = '{"RelativeStatHF"}'
    configuration.add_shift(
        SystematicShift(
            name="jecUncHFYearUp",
            shift_config={
                "global": {
                    "JE_scale_shift": 1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="jecUncHFYearDown",
            shift_config={
                "global": {
                    "JE_scale_shift": -1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )

    JEC_sources = '{"PileUpPtEC2"}'
    configuration.add_shift(
        SystematicShift(
            name="jecUncEC2Up",
            shift_config={
                "global": {
                    "JE_scale_shift": 1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="jecUncEC2Down",
            shift_config={
                "global": {
                    "JE_scale_shift": -1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )

    JEC_sources = '{"RelativeJEREC2", "RelativePtEC2"}'
    configuration.add_shift(
        SystematicShift(
            name="jecUncEC2YearUp",
            shift_config={
                "global": {
                    "JE_scale_shift": 1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="jecUncEC2YearDown",
            shift_config={
                "global": {
                    "JE_scale_shift": -1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )

    JEC_sources = '{"RelativeBal"}'
    configuration.add_shift(
        SystematicShift(
            name="jecUncRelativeBalUp",
            shift_config={
                "global": {
                    "JE_scale_shift": 1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="jecUncRelativeBalDown",
            shift_config={
                "global": {
                    "JE_scale_shift": -1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )

    JEC_sources = '{"RelativeSample"}'
    configuration.add_shift(
        SystematicShift(
            name="jecUncRelativeSampleYearUp",
            shift_config={
                "global": {
                    "JE_scale_shift": 1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )
    configuration.add_shift(
        SystematicShift(
            name="jecUncRelativeSampleYearDown",
            shift_config={
                "global": {
                    "JE_scale_shift": -1,
                    "JEC_shift_sources": JEC_sources,
                }
            },
            producers={"global": jets.JetEnergyCorrection},
        ),
        samples=[
            sample
            for sample in available_sample_types
            if sample not in ["data", "emb", "emb_mc"]
        ],
    )

    #########################
    # Finalize and validate the configuration
    #########################
    configuration.optimize()
    configuration.validate()
    configuration.report()
    return configuration.dump_dict()
