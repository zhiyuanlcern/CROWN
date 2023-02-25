from __future__ import annotations  # needed for type annotations in > python 3.7

from typing import List

from .producers import event as event
from .producers import triggers as triggers
from .producers import genparticles as genparticles
from .producers import muons as muons
from .producers import jets as jets
from .producers import scalefactors as scalefactors
# add by botao
from .producers import lepton as lepton
from .producers import electrons as electrons
# end 
from .quantities import nanoAOD as nanoAOD
from .quantities import output as q
from code_generation.configuration import Configuration
from code_generation.modifiers import EraModifier
from code_generation.rules import RemoveProducer
from code_generation.systematics import SystematicShift


def build_config(
    era: str,
    sample: str,
    scopes: List[str],
    shifts: List[str],
    available_sample_types: List[str],
    available_eras: List[str],
    available_scopes: List[str],
):

    configuration = Configuration(
        era,
        sample,
        scopes,
        shifts,
        available_sample_types,
        available_eras,
        available_scopes,
    )

    configuration.add_config_parameters(
        "global",
        {
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

    # vh add triggers (copying htautau mtau TODO)
    configuration.add_config_parameters(
        ["e2m","m2m","eemm","mmmm"],
        {
            "singlemuon_trigger": EraModifier(
                {
                # vh TODO update pT threshold in trigger matching
                    "2018": [
                        {
                            "flagname": "trg_single_mu24",
                            "hlt_path": "HLT_IsoMu24",
                            "ptcut": 25,
                            "etacut": 2.5,
                            "filterbit": 3,
                            "trigger_particle_id": 13,
                            "max_deltaR_triggermatch": 0.4,
                        },
                        {
                            "flagname": "trg_single_mu27",
                            "hlt_path": "HLT_IsoMu27",
                            "ptcut": 28,
                            "etacut": 2.5,
                            "filterbit": 3,
                            "trigger_particle_id": 13,
                            "max_deltaR_triggermatch": 0.4,
                        },
                    ],
                    "2017": [
                        {
                            "flagname": "trg_single_mu24",
                            "hlt_path": "HLT_IsoMu24",
                            "ptcut": 25,
                            "etacut": 2.5,
                            "filterbit": 3,
                            "trigger_particle_id": 13,
                            "max_deltaR_triggermatch": 0.4,
                        },
                        {
                            "flagname": "trg_single_mu27",
                            "hlt_path": "HLT_IsoMu27",
                            "ptcut": 28,
                            "etacut": 2.5,
                            "filterbit": 3,
                            "trigger_particle_id": 13,
                            "max_deltaR_triggermatch": 0.4,
                        },
                    ],
                    "2016": [
                        {
                            "flagname": "trg_single_mu22",
                            "hlt_path": "HLT_IsoMu22",
                            "ptcut": 23,
                            "etacut": 2.5,
                            "filterbit": 3,
                            "trigger_particle_id": 13,
                            "max_deltaR_triggermatch": 0.4,
                        },
                    ],
                }
            ),
        },
    )

    # muon base selection:
    configuration.add_config_parameters(
        "global",
        {
            "min_muon_pt": 20.0, # vh
            "max_muon_eta": 2.4, # vh
            "max_muon_dxy": 0.05, # vh
            "max_muon_dz": 0.10, # vh
            "max_sip3d" : 8.0, # vh
            #"min_lepmva" : 0.4, # vh TODO
            "min_muon_mvaTTH" : 0.4,
            "muon_id": "Muon_mediumId", # vh cut-based atm https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2#Medium_Muon
            "muon_iso_cut": 0.25, # vh PFIsoLoose dR=0.4 https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2#Particle_Flow_isolation
        },
    )
    # electron base selection:
    configuration.add_config_parameters(
        "global",
        {
            "min_ele_pt": 20.0,
            "max_ele_eta": 2.5,
            "upper_threshold_barrel": 1.444,
            "lower_threshold_endcap": 1.566,
            "max_ele_dxy": 0.05,
            "max_ele_dz": 0.10,
            "ele_id": "Electron_mvaFall17V2noIso_WP90", 
            "ele_conv_veto": "Electron_convVeto",
            "ele_missing_hits": 2,
            # also need max_sip3d
            # "min_lepmva": 0.4,
            "min_electron_mvaTTH" : 0.4,
        }
    )
    # MM scope Muon selection
    configuration.add_config_parameters(
        ["m2m"],
        {
            "muon_index_in_pair": 0,
            "second_muon_index_in_pair": 1,
            "min_muon_pt": 23.0,
            "max_muon_eta": 2.1,
            "muon_iso_cut": 0.15,
        },
    )
    configuration.add_config_parameters(
        ["e2m"],
        {
            "TODO_GoodElectron?": 1,
            "min_muon_pt": 23.0,
            "max_muon_eta": 2.1,
            "muon_iso_cut": 0.15,
        }
    )
    configuration.add_config_parameters(
        ["eemm"],
        {
            "min_muon_pt": 23.0,
            "max_muon_eta": 2.1,
            "muon_iso_cut": 0.15,
        }
    )
    configuration.add_config_parameters(
        ["mmmm"],
        {
            "min_muon_pt": 23.0,
            "max_muon_eta": 2.1,
            "muon_iso_cut": 0.15,
        }
    )
    # Muon scale factors configuration
    configuration.add_config_parameters(
        ["m2m"],
        {
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

    # jet base selection:
    configuration.add_config_parameters(
        "global",
        {
            "min_jet_pt": 25, # vh
            "max_jet_eta": 4.7, # vh
            # vh TODO jet id
            "jet_id": 2,  # default: 2==pass tight ID and fail tightLepVeto
            # vh TODO jet puid
            "jet_puid": EraModifier(
                {
                    "2016preVFP": 1,  # 0==fail, 1==pass(loose), 3==pass(loose,medium), 7==pass(loose,medium,tight)
                    "2016postVFP": 1,  # 0==fail, 1==pass(loose), 3==pass(loose,medium), 7==pass(loose,medium,tight)
                    "2017": 4,  # 0==fail, 4==pass(loose), 6==pass(loose,medium), 7==pass(loose,medium,tight)
                    "2018": 4,  # 0==fail, 4==pass(loose), 6==pass(loose,medium), 7==pass(loose,medium,tight)
                }
            ),
            "jet_puid_max_pt": 50,  # recommended to apply puID only for jets below 50 GeV
            "deltaR_jet_veto": 0.4, # vh jet-muon dR<0.4 overlap removal
            "jet_reapplyJES": False,
            "jet_jes_sources": '{""}',
            "jet_jes_shift": 0,
            "jet_jer_shift": '"nom"',  # or '"up"', '"down"'
            "jet_jec_file": EraModifier(
                {
                    "2016preVFP": '"data/jsonpog-integration/POG/JME/2016preVFP_UL/jet_jerc.json.gz"',
                    "2016postVFP": '"data/jsonpog-integration/POG/JME/2016postVFP_UL/jet_jerc.json.gz"',
                    "2017": '"data/jsonpog-integration/POG/JME/2017_UL/jet_jerc.json.gz"',
                    "2018": '"data/jsonpog-integration/POG/JME/2018_UL/jet_jerc.json.gz"',
                }
            ),
            "jet_jer_tag": EraModifier(
                {
                    "2016preVFP": '"Summer20UL16APV_JRV3_MC"',
                    "2016postVFP": '"Summer20UL16_JRV3_MC"',
                    "2017": '"Summer19UL17_JRV2_MC"',
                    "2018": '"Summer19UL18_JRV2_MC"',
                }
            ),
            "jet_jes_tag_data": '""',
            "jet_jes_tag": EraModifier(
                {
                    "2016preVFP": '"Summer19UL16APV_V7_MC"',
                    "2016postVFP": '"Summer19UL16_V7_MC"',
                    "2017": '"Summer19UL17_V5_MC"',
                    "2018": '"Summer19UL18_V5_MC"',
                }
            ),
            "jet_jec_algo": '"AK4PFchs"',
        },
    )
    # bjet base selection:
    configuration.add_config_parameters(
        "global",
        {
            "min_bjet_pt": 25, # vh
            "max_bjet_eta": EraModifier( # vh TODO
                {
                    "2016": 2.4,
                    "2017": 2.5,
                    "2018": 2.5,
                }
            ),
            "btag_cut_loose": EraModifier(  # loose # vh TODO update this for DeepCSV
                {
                    "2016": 0.3093,
                    "2017": 0.3040,
                    "2018": 0.2783,
                }
            ),
            "btag_cut_medium": EraModifier(  # medium # vh TODO verify this for DeepCSV
                {
                    "2016": 0.3093,
                    "2017": 0.3040,
                    "2018": 0.2783,
                }
            ),
        },
    )

    # veto ttH
    configuration.add_config_parameters(
        "global",
        {
            "vetottH_max_nbjets_loose" : 1,
            "vetottH_max_nbjets_medium" : 0,
        }
    )

    # m2m cuts
    configuration.add_config_parameters(
        "m2m",
        {
            "vh_m2m_nmuons" : 3,
            "min_dimuon_mass" : 12,
            # "dimuon_pair" : 1, # dimuon_pair in [110,150] >=1
        }
    )
    # e2m cuts
    configuration.add_config_parameters(
        "e2m",
        {
            "vh_e2m_nmuons" : 2,
            "vh_e2m_nelectrons" : 1,
            "min_dimuon_mass" : 12,
        }
    )
    configuration.add_config_parameters(
        "eemm",
        {
            "vh_2e2m_nmuons" : 2,
            "vh_2e2m_nelectrons" : 2,
            "min_dimuon_mass" : 12,
            "min_dielectron_mass" : 12,
        }
    )
    configuration.add_config_parameters(
        "mmmm",
        {
            "vh_4m_nmuons" : 4,
            "min_dimuon_mass" : 12,
        }
    )

    ## all scopes misc settings
    configuration.add_config_parameters(
        scopes,
        {
            "pairselection_min_dR": 0.5,
        },
    )

    configuration.add_producers(
        "global",
        [
            event.SampleFlags,
            event.PUweights,
            event.Lumi,
            event.MetFilter,
            muons.BaseMuons, # vh
            # vh muon Rochester corr, FSR recovery, GeoFit? TODO
            # vh muon FSR recovery
            electrons.BaseElectrons,
            jets.JetEnergyCorrection, # vh
            jets.GoodJets, # vh overlap removal with ?base? muons done [need validation]
            jets.GoodBJetsLoose, # vh TODO update btag
            jets.GoodBJetsMedium, # vh TODO update btag
            jets.NumberOfLooseB, # vh count loose bjets for ttH veto
            jets.NumberOfMediumB, # vh count medium bjets for ttH veto
            event.VetottHLooseB, # vh veto ttH no more than 1 loose bjet
            event.VetottHMediumB, # vh veto ttH no more than 1 medium bjet
        ],
    )
    configuration.add_producers(
        "m2m",
        [
            muons.GoodMuons, # vh tighter selections on muons
            muons.NumberOfGoodMuons,
            event.FilterNMuons, # vh ==3 muons
            muons.MuonCollection, # collect ordered by pt
            # write by botao
            lepton.CalcSmallestDiMuonMass,  # SFOS, m2m only has m
            event.DimuonMinMassCut,
            ###
            event.Mask_DiMuonPair, # dimuonHiggs index
            event.Flag_DiMuonFromHiggs,
            event.HiggsToDiMuonPair_p4, # select the dimuon pairs in [110,150] and order by pt
            ###
            event.DiMuonMassFromZVeto,  # has dimuon from Z return mask equal to 0, otherwise return 1
            lepton.LeptonChargeSumVeto,
            ###
            electrons.NumberOfBaseElectrons,
            electrons.Ele_Veto,
            # end
            muons.Mu1_H, # vh
            muons.Mu2_H, # vh
            ### extra muon in m2m
            lepton.Mu1_W_m2m_index, # extra muon index
            lepton.Mu1_W_m2m, # extra muon p4 (From W)
            ###
            #muons.LVMu3, # vh 
            #scalefactors.MuonIDIso_SF, # TODO 3 muon SF
            muons.LVMu1,
            muons.LVMu2,
            muons.LVMu3,
            triggers.GenerateSingleMuonTriggerFlags, # vh check trigger matching TODO
            # vh the trigger-matched muon should have pT > 29 (26) for 2017 (2016,18)
        ],
    )
    configuration.add_producers(
        "e2m",
        [
            muons.GoodMuons, # missing good muons selection in NOTE
            muons.NumberOfGoodMuons,
            event.FilterNMuons_e2m, # nmuons == 2
            muons.MuonCollection, # collect ordered by pt
            ###
            electrons.NumberOfBaseElectrons,
            event.FilterNElectrons_e2m, # nelectrons == 1
            electrons.ElectronCollection, # collect ordered by pt
            ###
            lepton.CalcSmallestDiMuonMass,  # SFOS, e2m only has 2m
            event.DimuonMinMassCut,
            ###
            event.Mask_DiMuonPair,
            event.Flag_DiMuonFromHiggs,
            event.HiggsToDiMuonPair_p4, # select the first dimuon pairs in [110,150] that ordered by pt
            ###
            lepton.LeptonChargeSumVeto_elemu, # only in e2m and 2e2m channel
            ###
            muons.Mu1_H,
            muons.Mu2_H,
            lepton.Ele1_W_e2m,
            #electrons.LVEle1,
        ],
    )
    configuration.add_producers(
        "eemm",
        [
            muons.GoodMuons, # missing good muons selection in NOTE
            muons.NumberOfGoodMuons,
            event.FilterNMuons_2e2m,
            muons.MuonCollection, # collect ordered by pt
            ###
            electrons.NumberOfBaseElectrons,
            event.FilterNElectrons_2e2m,
            electrons.ElectronCollection, # collect ordered by pt (2 electrons)
            ###
            lepton.CalcSmallestDiMuonMass,  # both dimuon and diele
            lepton.CalcSmallestDiElectronMass,
            event.DimuonMinMassCut,
            event.DielectronMinMassCut,
            ###
            event.Mask_DiMuonPair,
            event.Flag_DiMuonFromHiggs,
            event.HiggsToDiMuonPair_p4, # select the first dimuon pairs in [110,150] that ordered by pt
            ###
            event.Mask_DiElectronPair,
            event.Flag_DiEleFromZ,  ### need ZCand m(ee) in [70,110]
            event.ZToDiElectronPair_p4,
            ###
            lepton.LeptonChargeSumVeto_elemu, # only in e2m and 2e2m channel
            ###
            muons.Mu1_H,
            muons.Mu2_H,
            electrons.LVEle1,
            electrons.LVEle2,
        ],
    )
    configuration.add_producers(
        "mmmm",
        [
            muons.GoodMuons,
            muons.NumberOfGoodMuons,
            event.FilterNMuons_4m, # vh == 4 muons
            muons.MuonCollection,
            ###
            lepton.CalcSmallestDiMuonMass,
            event.DimuonMinMassCut,
            ###
            ### need make dimuon pair from Higgs and pair from Z
            event.Mask_QuadMuonPair,
            event.Flag_ZZVeto,
            # Higgs p4
            event.HiggsToDiMuonPair_p4_4m,
            event.ZToDiMuonPair_p4_4m,
            # Z p4
            ###
            lepton.LeptonChargeSumVeto,
            electrons.Ele_Veto,
            muons.Mu1_H_4m,
            muons.Mu2_H_4m,
            muons.Mu1_Z_4m,
            muons.Mu2_Z_4m,
        ],
    )

    configuration.add_outputs(
        "m2m",
        [
            q.is_data,
            q.is_embedding,
            q.is_ttbar,
            q.is_dyjets,
            q.is_wjets,
            q.is_diboson,
            q.is_vhmm,
            nanoAOD.run,
            q.lumi,
            nanoAOD.event,
            q.puweight,
            q.muon_leadingp4_H,
            q.muon_subleadingp4_H,
            #q.muon_p4_3,
            # extra lepton p4
            q.extra_lep_p4,
            #
            q.nmuons,
            q.nelectrons,
            ###
            q.smallest_dimuon_mass,
            q.dimuon_p4_byPt,
            q.Flag_dimuon_Zmass_veto,
            q.Flag_LeptonChargeSumVeto,
            q.Flag_Ele_Veto,
            q.Flag_DiMuonFromHiggs,
        ],
    )
    configuration.add_outputs(
        "e2m",
        [
            q.is_data,
            q.is_embedding,
            q.is_ttbar,
            q.is_dyjets,
            q.is_wjets,
            q.is_diboson,
            q.is_vhmm,
            nanoAOD.run,
            q.lumi,
            nanoAOD.event,
            q.puweight,
            q.nmuons,
            #q.muon_p4_1,
            #q.muon_p4_2,
            q.muon_leadingp4_H,
            q.muon_subleadingp4_H,
            q.nelectrons,
            q.extra_lep_p4,
            #q.electron_p4_1,
            q.smallest_dimuon_mass,
            q.Flag_LeptonChargeSumVeto,
            q.dimuon_p4_byPt,
            q.Flag_DiMuonFromHiggs,
        ],
    )
    configuration.add_outputs(
        "eemm",
        [
            q.is_data,
            q.is_embedding,
            q.is_ttbar,
            q.is_dyjets,
            q.is_wjets,
            q.is_diboson,
            q.is_vhmm,
            nanoAOD.run,
            q.lumi,
            nanoAOD.event,
            q.puweight,
            q.nmuons,
            q.muon_leadingp4_H,
            q.muon_subleadingp4_H,
            #q.muon_p4_1,
            #q.muon_p4_2,
            q.nelectrons,
            q.electron_p4_1,
            q.electron_p4_2,
            q.smallest_dimuon_mass,
            q.smallest_dielectron_mass,
            q.Flag_LeptonChargeSumVeto,
            q.dimuon_p4_byPt,
            q.dielectron_p4_byPt,
            q.Flag_DiMuonFromHiggs,
            q.Flag_DiEleFromZ,
        ],
    )
    configuration.add_outputs(
        "mmmm",
        [
            q.is_data,
            q.is_embedding,
            q.is_ttbar,
            q.is_dyjets,
            q.is_wjets,
            q.is_diboson,
            q.is_vhmm,
            nanoAOD.run,
            q.lumi,
            nanoAOD.event,
            q.puweight,
            q.nmuons,
            #q.muon_p4_1,
            #q.muon_p4_2,
            #q.nelectrons,
            #q.electron_p4_1,
            #q.electron_p4_2,
            q.smallest_dimuon_mass,
            #q.smallest_dielectron_mass,
            q.Flag_LeptonChargeSumVeto,
            q.dimuon_p4_Higgs,
            q.dimuon_p4_Z,
            q.Flag_ZZVeto,
            q.Flag_Ele_Veto,
            q.muon_leadingp4_H,
            q.muon_subleadingp4_H,
            q.muon_leadingp4_Z,
            q.muon_subleadingp4_Z,
        ],
    )

    configuration.add_modification_rule(
        "global",
        RemoveProducer(
            producers=[event.PUweights],
            samples=["data"],
        ),
    )
    configuration.add_modification_rule(
        "m2m",
        RemoveProducer(
            producers=[
                genparticles.MMGenDiTauPairQuantities,
                scalefactors.MuonIDIso_SF,
            ],
            samples=["data"],
        ),
    )

    configuration.add_shift(
        SystematicShift(
            name="MuonIDUp",
            shift_config={"m2m": {"muon_sf_varation": "systup"}},
            producers={
                "m2m": [
                    scalefactors.Muon_1_ID_SF,
                    scalefactors.Muon_2_ID_SF,
                ]
            },
        )
    )
    configuration.add_shift(
        SystematicShift(
            name="MuonIDDown",
            shift_config={"m2m": {"muon_sf_varation": "systdown"}},
            producers={
                "m2m": [
                    scalefactors.Muon_1_ID_SF,
                    scalefactors.Muon_2_ID_SF,
                ]
            },
        )
    )

    #########################
    # Finalize and validate the configuration
    #########################
    configuration.optimize()
    configuration.validate()
    configuration.report()
    return configuration.expanded_configuration()
