from ..quantities import output as q
from ..quantities import nanoAOD as nanoAOD
from code_generation.producer import BaseFilter, Producer, ProducerGroup, VectorProducer

####################
# Set of general producers for event quantities
####################

RunLumiEventFilter = VectorProducer(
    name="RunLumiEventFilter",
    call='basefunctions::FilterIntSelection<{RunLumiEventFilter_Quantity_Types}>({df}, "{RunLumiEventFilter_Quantities}", {vec_open}{RunLumiEventFilter_Selections}{vec_close}, "RunLumiEventFilter")',
    input=[],
    output=None,
    scopes=["global"],
    vec_configs=[
        "RunLumiEventFilter_Quantities",
        "RunLumiEventFilter_Quantity_Types",
        "RunLumiEventFilter_Selections",
    ],
)

JSONFilter = BaseFilter(
    name="JSONFilter",
    call='basefunctions::JSONFilter({df}, "{golden_json_file}", {input}, "GoldenJSONFilter")',
    input=[nanoAOD.run, nanoAOD.luminosityBlock],
    scopes=["global"],
)

PrefireWeight = Producer(
    name="PrefireWeight",
    call="basefunctions::rename<Float_t>({df}, {input}, {output})",
    input=[nanoAOD.prefireWeight],
    output=[q.prefireweight],
    scopes=["global"],
)

is_data = Producer(
    name="isData",
    input=[],
    call="basefunctions::DefineQuantity({df}, {output}, {is_data})",
    output=[q.is_data],
    scopes=["global"],
)
is_vhmm = Producer(
    name="is_vhmm",
    call="basefunctions::DefineQuantity({df}, {output}, {is_vhmm})",
    input=[],
    output=[q.is_vhmm],
    scopes=["global"],
)
is_zjjew = Producer(
    name="is_zjjew",
    call="basefunctions::DefineQuantity({df}, {output}, {is_zjjew})",
    input=[],
    output=[q.is_zjjew],
    scopes=["global"],
)
is_triboson = Producer(
    name="is_triboson",
    call="basefunctions::DefineQuantity({df}, {output}, {is_triboson})",
    input=[],
    output=[q.is_triboson],
    scopes=["global"],
)
is_embedding = Producer(
    name="is_embedding",
    call="basefunctions::DefineQuantity({df}, {output}, {is_embedding})",
    input=[],
    output=[q.is_embedding],
    scopes=["global"],
)
is_top = Producer(
    name="is_top",
    call="basefunctions::DefineQuantity({df}, {output}, {is_top})",
    input=[],
    output=[q.is_top],
    scopes=["global"],
)
is_dyjets = Producer(
    name="is_dyjets",
    call="basefunctions::DefineQuantity({df}, {output}, {is_dyjets})",
    input=[],
    output=[q.is_dyjets],
    scopes=["global"],
)
is_wjets = Producer(
    name="is_wjets",
    call="basefunctions::DefineQuantity({df}, {output}, {is_wjets})",
    input=[],
    output=[q.is_wjets],
    scopes=["global"],
)
is_diboson = Producer(
    name="is_diboson",
    call="basefunctions::DefineQuantity({df}, {output}, {is_diboson})",
    input=[],
    output=[q.is_diboson],
    scopes=["global"],
)

SampleFlags = ProducerGroup(
    name="SampleFlags",
    call=None,
    input=None,
    output=None,
    scopes=["global"],
    subproducers=[
        is_data,
        is_embedding,
        is_top,
        is_dyjets,
        is_wjets,
        is_diboson,
        is_vhmm,
        is_zjjew,
        is_triboson,
    ],
)

MetFilter = VectorProducer(
    name="MetFilter",
    call='metfilter::ApplyMetFilter({df}, "{met_filters}", "{met_filters}")',
    input=[],
    output=None,
    scopes=["global"],
    vec_configs=["met_filters"],
)

Lumi = Producer(
    name="Lumi",
    call="basefunctions::rename<UInt_t>({df}, {input}, {output})",
    input=[nanoAOD.luminosityBlock],
    output=[q.lumi],
    scopes=["global"],
)

PUweights = Producer(
    name="PUweights",
    call='reweighting::puweights({df}, {output}, {input}, "{PU_reweighting_file}", "{PU_reweighting_hist}")',
    input=[nanoAOD.Pileup_nTrueInt],
    output=[q.puweight],
    scopes=["global"],
)

VetottHLooseB = Producer(
    name="VetottHLooseB",
    call='basefunctions::FilterThreshold({df}, {input}, {vetottH_max_nbjets_loose}, "<=", "Veto ttH <= 1 bjet loose")',
    input=[q.nbjets_loose],
    output=None,
    scopes=["global"],
)
VetottHMediumB = Producer(
    name="VetottHMediumB",
    call='basefunctions::FilterThreshold({df}, {input}, {vetottH_max_nbjets_medium}, "<=", "Veto ttH <= 0 bjet medium")',
    input=[q.nbjets_medium],
    output=None,
    scopes=["global"],
)

FilterNMuons = Producer(
    name="FilterNMuons",
    call='basefunctions::FilterThreshold({df}, {input}, {vh_m2m_nmuons}, "==", "Number of muons 3")',
    input=[q.nmuons],
    output=None,
    scopes=["m2m"],
)

# write by botao
### e2m
FilterNMuons_e2m = Producer(
    name="FilterNMuons_e2m",
    call='basefunctions::FilterThreshold({df}, {input}, {vh_e2m_nmuons}, "==", "Number of muons 2 in e2m")',
    input=[q.nmuons],
    output=None,
    scopes=["e2m"],
)
FilterNElectrons_e2m = Producer(
    name="FilterNElectrons_e2m",
    call='basefunctions::FilterThreshold({df}, {input}, {vh_e2m_nelectrons}, "==", "Number of electrons 1 in e2m")',
    input=[q.nelectrons],
    output=None,
    scopes=["e2m"],
)
###  2e2m
FilterNMuons_2e2m = Producer(
    name="FilterNMuons_2e2m",
    call='basefunctions::FilterThreshold({df}, {input}, {vh_2e2m_nmuons}, "==", "Number of muons 2 in 2e2m")',
    input=[q.nmuons],
    output=None,
    scopes=["eemm"],
)
FilterNElectrons_2e2m = Producer(
    name="FilterNElectrons_2e2m",
    call='basefunctions::FilterThreshold({df}, {input}, {vh_2e2m_nelectrons}, "==", "Number of electrons 2 in 2e2m")',
    input=[q.nelectrons],
    output=None,
    scopes=["eemm"],
)
FilterNMuons_4m = Producer(
    name="FilterNMuons_4m",
    call='basefunctions::FilterThreshold({df}, {input}, {vh_4m_nmuons}, "==", "Number of muons 4")',
    input=[q.nmuons],
    output=None,
    scopes=["mmmm"],
)
FilterNMuons_nnmm = Producer(
    name="FilterNMuons",
    call='basefunctions::FilterThreshold({df}, {input}, {vh_nnmm_nmuons}, "==", "Number of muons 2")',
    input=[q.nmuons],
    output=None,
    scopes=["nnmm","nnmm_dycontrol"],
)
DimuonMinMassCut = Producer(
    name="DimuonMinMassCut",
    call='basefunctions::FilterThreshold({df}, {input}, {min_dimuon_mass}, ">=", "No m(mm) < 12 GeV")',
    input=[q.smallest_dimuon_mass],
    output=None,
    scopes=["global","m2m","e2m","eemm","mmmm","nnmm","nnmm_dycontrol"],
)
DielectronMinMassCut = Producer(
    name="DielectronMinMassCut",
    call='basefunctions::FilterThreshold({df}, {input}, {min_dielectron_mass}, ">=", "No m(ee) < 12 GeV")',
    input=[q.smallest_dielectron_mass],
    output=None,
    scopes=["global","eemm"],
)
#
Flag_DiMuonFromHiggs = Producer(
    name="Flag_DiMuonFromHiggs",
    call='physicsobject::DiMuonFromHiggs({df}, {output}, {input})',
    input=[q.dimuon_HiggsCand_collection],
    output=[q.Flag_DiMuonFromHiggs],
    scopes=["global","e2m","m2m","eemm","mmmm","nnmm"],
)
### need a collection that di_ele after cut
Flag_DiEleFromZ = Producer(
    name="Flag_DiEleFromZ",
    call='physicsobject::DiEleFromZ({df}, {output}, {input})',
    input=[q.dielectron_ZCand_collection], # in eemm, dielectron_ZCand_collection need to be 2
    output=[q.Flag_DiEleFromZ],
    scopes=["global","eemm"],
)
###
HiggsToDiMuonPair_p4 = Producer(
    name="HiggsToDiMuonPair_p4",
    call='physicsobject::HiggsToDiMuonPairCollection({df}, {output}, {input})',
    input=[nanoAOD.Muon_pt,
           nanoAOD.Muon_eta, 
           nanoAOD.Muon_phi, 
           nanoAOD.Muon_mass,
           q.dimuon_HiggsCand_collection],
    output=[q.dimuon_p4_Higgs],
    scopes=["global","e2m","m2m","eemm","nnmm"],
)
HiggsToDiMuonPair_p4_4m = Producer(
    name="HiggsToDiMuonPair_p4_4m",
    call='physicsobject::HiggsToDiMuonPairCollection({df}, {output}, {input})',
    input=[nanoAOD.Muon_pt,
           nanoAOD.Muon_eta, 
           nanoAOD.Muon_phi, 
           nanoAOD.Muon_mass,
           q.quadmuon_HiggsZCand_collection],
    output=[q.dimuon_p4_Higgs],
    scopes=["mmmm"],
)
ZToDiMuonPair_p4_4m = Producer(
    name="ZToDiMuonPair_p4_4m",
    call='physicsobject::ZToSecondMuonPairCollection({df}, {output}, {input})',
    input=[nanoAOD.Muon_pt,
           nanoAOD.Muon_eta, 
           nanoAOD.Muon_phi, 
           nanoAOD.Muon_mass,
           q.quadmuon_HiggsZCand_collection],
    output=[q.dilepton_p4_Z],
    scopes=["mmmm"],
)
ZToDiElectronPair_p4 = Producer(
    name="ZToDiElectronPair_p4",
    call='physicsobject::ZToDiElectronPairCollection({df}, {output}, {input})',
    input=[nanoAOD.Electron_pt,
           nanoAOD.Electron_eta, 
           nanoAOD.Electron_phi, 
           nanoAOD.Electron_mass,
           q.dielectron_ZCand_collection],
    output=[q.dilepton_p4_Z],
    scopes=["global","e2m","m2m","eemm","mmmm"],
)
DiMuonMassFromZVeto = Producer(
    name="DiMuonMassFromZVeto",
    call='physicsobject::DiMuonFromZVeto({df}, {output}, {input})',
    input=[nanoAOD.Muon_pt,
           nanoAOD.Muon_eta, 
           nanoAOD.Muon_phi, 
           nanoAOD.Muon_mass,
           nanoAOD.Muon_charge,
           q.good_muon_collection],
    output=[q.Flag_dimuon_Zmass_veto], # 1 stands for noZmass, 0 stands for has dimuon from Zmass
    scopes=["global","m2m","eemm","mmmm"],
)
Mask_DiMuonPair = Producer(
    name="Mask_DiMuonPair",
    call='physicsobject::HiggsCandDiMuonPairCollection({df}, {output}, {input})',
    input=[nanoAOD.Muon_pt,
           nanoAOD.Muon_eta, 
           nanoAOD.Muon_phi, 
           nanoAOD.Muon_mass,
           nanoAOD.Muon_charge,
           q.good_muon_collection],
    output=[q.dimuon_HiggsCand_collection], # index about the two selected muons may from Higgs
    scopes=["global","e2m","m2m","eemm","nnmm"],
)
Mask_DiElectronPair = Producer(
    name="Mask_DiElectronPair",
    call='physicsobject::ZCandDiElectronPairCollection({df}, {output}, {input})',
    input=[nanoAOD.Electron_pt,
           nanoAOD.Electron_eta,
           nanoAOD.Electron_phi,
           nanoAOD.Electron_mass,
           nanoAOD.Electron_charge,
           q.base_electron_collection],
    output=[q.dielectron_ZCand_collection], # index about the two selected electrons may from Z boson
    scopes=["eemm"],
)
# output: index about the four muons, first two stand HiggsCand, second two stand ZCand
Mask_QuadMuonPair = Producer(
    name="Mask_QuadMuonPair",
    call='physicsobject::HiggsAndZFourMuonsCollection({df}, {output}, {input})',
    input=[nanoAOD.Muon_pt,
           nanoAOD.Muon_eta, 
           nanoAOD.Muon_phi, 
           nanoAOD.Muon_mass,
           nanoAOD.Muon_charge,
           q.good_muon_collection],
    output=[q.quadmuon_HiggsZCand_collection],
    scopes=["mmmm"],
)
Flag_ZZVeto = Producer(
    name="Flag_ZZVeto",
    call='physicsobject::QuadMuonFromZZVeto({df}, {output}, {input})',
    input=[q.quadmuon_HiggsZCand_collection],
    output=[q.Flag_ZZVeto], # 0 stands two Z Cand
    scopes=["mmmm"],
)
lepton_H_dR = Producer(
    name="lepton_H_dR",
    call='quantities::deltaR({df}, {output}, {input})',
    input=[
      q.extra_lep_p4,
      q.dimuon_p4_Higgs,
    ],
    output=[q.lep_H_dR],
    scopes=["e2m","m2m"],
)
mumuH_dR = Producer(
    name="mumuH_dR",
    call='quantities::deltaR({df}, {output}, {input})',
    input=[
      q.muon_leadingp4_H,
      q.muon_subleadingp4_H,
    ],
    output=[q.mumuH_dR],
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)
### e2m channel 
muSSwithElectronW_p4 = Producer(
    name="muSSwithElectronW_p4",
    call='physicsobject::muSSorOSwithLeptonW_p4({df}, {output}, {input}, 1)',
    input=[
        nanoAOD.Muon_pt,
        nanoAOD.Muon_eta, 
        nanoAOD.Muon_phi, 
        nanoAOD.Muon_mass,
        nanoAOD.Muon_charge,
        nanoAOD.Electron_charge,
        q.dimuon_HiggsCand_collection,
        q.base_electron_collection,
    ],
    output=[q.mu_p4_SSwithLep],
    scopes=["e2m"],
)
muOSwithElectronW_p4 = Producer(
    name="muOSwithElectronW_p4",
    call='physicsobject::muSSorOSwithLeptonW_p4({df}, {output}, {input}, 0)',
    input=[
        nanoAOD.Muon_pt,
        nanoAOD.Muon_eta, 
        nanoAOD.Muon_phi, 
        nanoAOD.Muon_mass,
        nanoAOD.Muon_charge,
        nanoAOD.Electron_charge,
        q.dimuon_HiggsCand_collection,
        q.base_electron_collection,
    ],
    output=[q.mu_p4_OSwithLep],
    scopes=["e2m"],
)
### m2m channel 
muSSwithMuonW_p4 = Producer(
    name="muSSwithMuonW_p4",
    call='physicsobject::muSSorOSwithLeptonW_p4({df}, {output}, {input}, 1)',
    input=[
        nanoAOD.Muon_pt,
        nanoAOD.Muon_eta, 
        nanoAOD.Muon_phi, 
        nanoAOD.Muon_mass,
        nanoAOD.Muon_charge,
        nanoAOD.Muon_charge,
        q.dimuon_HiggsCand_collection,
        q.extra_muon_index,
    ],
    output=[q.mu_p4_SSwithLep],
    scopes=["m2m"],
)
muOSwithMuonW_p4 = Producer(
    name="muOSwithMuonW_p4",
    call='physicsobject::muSSorOSwithLeptonW_p4({df}, {output}, {input}, 0)',
    input=[
        nanoAOD.Muon_pt,
        nanoAOD.Muon_eta, 
        nanoAOD.Muon_phi, 
        nanoAOD.Muon_mass,
        nanoAOD.Muon_charge,
        nanoAOD.Muon_charge,
        q.dimuon_HiggsCand_collection,
        q.extra_muon_index,
    ],
    output=[q.mu_p4_OSwithLep],
    scopes=["m2m"],
)
### dR lepW and muSS
lepton_muSS_dR = Producer(
    name="lepton_muSS_dR",
    call='quantities::deltaR({df}, {output}, {input})',
    input=[
      q.extra_lep_p4,
      q.mu_p4_SSwithLep,
    ],
    output=[q.lep_muSS_dR],
    scopes=["e2m","m2m"],
)
### dR lepW and muOS
lepton_muOS_dR = Producer(
    name="lepton_muOS_dR",
    call='quantities::deltaR({df}, {output}, {input})',
    input=[
      q.extra_lep_p4,
      q.mu_p4_OSwithLep,
    ],
    output=[q.lep_muOS_dR],
    scopes=["e2m","m2m"],
)
#######################
### deta lepW and mumuH
lepton_H_deta = Producer(
    name="lepton_H_deta",
    call='quantities::deltaEta({df}, {output}, {input})',
    input=[
      q.extra_lep_p4,
      q.dimuon_p4_Higgs,
    ],
    output=[q.lep_H_deta],
    scopes=["e2m","m2m"],
)
### deta lepW and muSS
lepton_muSS_deta = Producer(
    name="lepton_muSS_deta",
    call='quantities::deltaEta({df}, {output}, {input})',
    input=[
      q.extra_lep_p4,
      q.mu_p4_SSwithLep,
    ],
    output=[q.lep_muSS_deta],
    scopes=["e2m","m2m"],
)
### deta lepW and muOS
lepton_muOS_deta = Producer(
    name="lepton_muOS_deta",
    call='quantities::deltaEta({df}, {output}, {input})',
    input=[
      q.extra_lep_p4,
      q.mu_p4_OSwithLep,
    ],
    output=[q.lep_muOS_deta],
    scopes=["e2m","m2m"],
)
### dR llZ
leplepZ_dR = Producer(
    name="leplepZ_dR",
    call='quantities::deltaR({df}, {output}, {input})',
    input=[
        q.lepton_leadingp4_Z,
        q.lepton_subleadingp4_Z,
    ],
    output=[q.llZ_dR],
    scopes=["eemm","mmmm"],
)
### deta mumuH and llZ
llZ_mmH_deta = Producer(
    name="llZ_mmH_deta",
    call='quantities::deltaEta({df}, {output}, {input})',
    input=[
      q.dilepton_p4_Z,
      q.dimuon_p4_Higgs,
    ],
    output=[q.Z_H_deta],
    scopes=["eemm","mmmm"],
)
### dphi mumuH and llZ
llZ_mmH_dphi = Producer(
    name="llZ_mmH_dphi",
    call='quantities::deltaPhi({df}, {output}, {input})',
    input=[
      q.dilepton_p4_Z,
      q.dimuon_p4_Higgs,
    ],
    output=[q.Z_H_dphi],
    scopes=["eemm","mmmm"],
)
### dphi met and H
met_mmH_dphi = Producer(
    name="met_mmH_dphi",
    call='quantities::deltaPhi({df}, {output}, {input})',
    input=[
      q.met_p4,
      q.dimuon_p4_Higgs,
    ],
    output=[q.met_H_dphi],
    scopes=["nnmm"],
)
### dphi mu1H and mu2H
mumuH_dphi = Producer(
    name="mumuH_dphi",
    call='quantities::deltaPhi({df}, {output}, {input})',
    input=[
      q.muon_leadingp4_H,
      q.muon_subleadingp4_H,
    ],
    output=[q.mumuH_dphi],
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)
### calc MT(muSS and MHT)
Calc_MT_muSS_MHT = Producer(
    name="Calc_MT_muSS_MHT",
    call="quantities::mT_MHT({df}, {output}, {input})",
    input=[
        q.mu_p4_SSwithLep,
        q.MHT_p4,
    ],
    output=[q.mt_muSSAndMHT],
    scopes=["e2m","m2m"],
)
### calc MT(muOS and MHT)
Calc_MT_muOS_MHT = Producer(
    name="Calc_MT_muOS_MHT",
    call="quantities::mT_MHT({df}, {output}, {input})",
    input=[
        q.mu_p4_OSwithLep,
        q.MHT_p4,
    ],
    output=[q.mt_muOSAndMHT],
    scopes=["e2m","m2m"],
)
### calc MT(lepW and MHT)
Calc_MT_lepton_MHT = Producer(
    name="Calc_MT_lepton_MHT",
    call="quantities::mT_MHT({df}, {output}, {input})",
    input=[
        q.extra_lep_p4,
        q.MHT_p4,
    ],
    output=[q.mt_lepWAndMHT],
    scopes=["e2m","m2m"],
)
### calc dphi(lepW and MHT)
lepW_MHT_dphi = Producer(
    name="lepW_MHT_dphi",
    call='quantities::deltaPhi({df}, {output}, {input})',
    input=[
      q.extra_lep_p4,
      q.MHT_p4,
    ],
    output=[q.lep_MHT_dphi],
    scopes=["e2m","m2m"],
)
### cut flag
FilterFlagDiMuFromH = Producer(
    name="FilterFlagDiMuFromH",
    call='basefunctions::FilterThreshold({df}, {input}, {flag_DiMuonFromHiggs}, "==", "DiMuon From Higgs")',
    input=[q.Flag_DiMuonFromHiggs],
    output=None,
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)
FilterFlagLepChargeSum = Producer(
    name="FilterFlagLepChargeSum",
    call='basefunctions::FilterThreshold({df}, {input}, {flag_LeptonChargeSumVeto}, "==", "LeptonChargeSum")',
    input=[q.Flag_LeptonChargeSumVeto],
    output=None,
    scopes=["e2m","m2m","eemm","mmmm","nnmm","nnmm_dycontrol","nnmm_topcontrol"],
)
FilterFlagEleVeto = Producer(
    name="FilterFlagEleVeto",
    call='basefunctions::FilterThreshold({df}, {input}, {flag_Ele_Veto}, "==", "Electron Veto")',
    input=[q.Flag_Ele_Veto],
    output=None,
    scopes=["m2m","mmmm","nnmm","nnmm_dycontrol"],
)
FilterFlagDiEleZMassVeto = Producer(
    name="FilterFlagDiEleZMassVeto",
    call='basefunctions::FilterThreshold({df}, {input}, {flag_DiEleFromZ}, "==", "DiElectron ZMass Veto")',
    input=[q.Flag_DiEleFromZ],
    output=None,
    scopes=["eemm"],
)
# check dphi
mumuH_MHT_dphi = Producer(
    name="mumuH_MHT_dphi",
    call='quantities::deltaPhi({df}, {output}, {input})',
    input=[
      q.dimuon_p4_Higgs,
      q.MHT_p4,
    ],
    output=[q.mumuH_MHT_dphi],
    scopes=["e2m","m2m","nnmm"],
)
mu1_MHT_dphi = Producer(
    name="mu1_MHT_dphi",
    call='quantities::deltaPhi({df}, {output}, {input})',
    input=[
      q.muon_leadingp4_H,
      q.MHT_p4,
    ],
    output=[q.mu1_MHT_dphi],
    scopes=["e2m","m2m","nnmm"],
)
mu2_MHT_dphi = Producer(
    name="mu2_MHT_dphi",
    call='quantities::deltaPhi({df}, {output}, {input})',
    input=[
      q.muon_subleadingp4_H,
      q.MHT_p4,
    ],
    output=[q.mu2_MHT_dphi],
    scopes=["e2m","m2m","nnmm"],
)
mu1_mu2_dphi = Producer(
    name="mu1_mu2_dphi",
    call='quantities::deltaPhi({df}, {output}, {input})',
    input=[
      q.muon_leadingp4_H,
      q.muon_subleadingp4_H,
    ],
    output=[q.mu1_mu2_dphi],
    scopes=["e2m","m2m","nnmm"],
)
lep_mu1_dphi = Producer(
    name="lep_mu1_dphi",
    call='quantities::deltaPhi({df}, {output}, {input})',
    input=[
      q.extra_lep_p4,
      q.muon_leadingp4_H,
    ],
    output=[q.lep_mu1_dphi],
    scopes=["e2m","m2m"],
)
lep_mu2_dphi = Producer(
    name="lep_mu2_dphi",
    call='quantities::deltaPhi({df}, {output}, {input})',
    input=[
      q.extra_lep_p4,
      q.muon_subleadingp4_H,
    ],
    output=[q.lep_mu2_dphi],
    scopes=["e2m","m2m"],
)
lep_H_dphi = Producer(
    name="lep_H_dphi",
    call='quantities::deltaPhi({df}, {output}, {input})',
    input=[
      q.extra_lep_p4,
      q.dimuon_p4_Higgs,
    ],
    output=[q.lep_H_dphi],
    scopes=["e2m","m2m"],
)
lepW_MHTALL_dphi = Producer(
    name="lepW_MHTALL_dphi",
    call='quantities::deltaPhi({df}, {output}, {input})',
    input=[
      q.extra_lep_p4,
      q.MHTALL_p4,
    ],
    output=[q.lep_MHTALL_dphi],
    scopes=["e2m","m2m"],
)
PassFlagZmassVeto = Producer(
    name="PassFlagZmassVeto",
    call='physicsobject::PassFlag({df}, {output})',
    input=[],
    output=[q.Flag_dimuon_Zmass_veto], # e2m channel using this all pass flag
    scopes=["e2m"],
)
PassFlagEleVeto = Producer(
    name="PassFlagEleVeto",
    call='physicsobject::PassFlag({df}, {output})',
    input=[],
    output=[q.Flag_Ele_Veto], # e2m, eemm channel using this all pass flag
    scopes=["e2m","eemm"],
)
PassFlagZZVeto = Producer(
    name="PassFlagZZVeto",
    call='physicsobject::PassFlag({df}, {output})',
    input=[],
    output=[q.Flag_ZZVeto], # eemm channel using this all pass flag
    scopes=["eemm"],
)
PassFlagDiEleFromZ = Producer(
    name="PassFlagDiEleFromZ",
    call='physicsobject::PassFlag({df}, {output})',
    input=[],
    output=[q.Flag_DiEleFromZ], # mmmm channel using this all pass flag
    scopes=["mmmm"],
)
PassFlagDiMuonHiggs = Producer(
    name="PassFlagDiMuonHiggs",
    call='physicsobject::PassFlag({df}, {output})',
    input=[],
    output=[q.Flag_DiMuonFromHiggs], # mmmm channel using this all pass flag
    scopes=["mmmm"], # already done in ZZ Veto (exist H and Z)
)
PassMinDiEleMass = Producer(
    name="PassMinDiEleMass",
    call='physicsobject::PassDiEleIn4m({df}, {output})',
    input=[],
    output=[q.smallest_dielectron_mass], # mmmm channel using this all pass flag
    scopes=["mmmm"], # already done in ZZ Veto (exist H and Z)
)
# Calculate the cosine helicity angle
Calc_CosThStar_lep_muOS = Producer(
    name="Calc_CosThStar_lep_muOS",
    call="physicsobject::Calc_CosThetaStar({df}, {output}, {input})",
    input=[
      q.extra_lep_p4,
      q.mu_p4_OSwithLep,
    ],
    output=[q.lep_muOS_cosThStar],
    scopes=["e2m","m2m"],
)
Calc_CosThStar_lep_muSS = Producer(
    name="Calc_CosThStar_lep_muSS",
    call="physicsobject::Calc_CosThetaStar({df}, {output}, {input})",
    input=[
      q.extra_lep_p4,
      q.mu_p4_SSwithLep,
    ],
    output=[q.lep_muSS_cosThStar],
    scopes=["e2m","m2m"],
)
Calc_CosThStar_Z_H = Producer(
    name="Calc_CosThStar_Z_H",
    call="physicsobject::Calc_CosThetaStar_ZH({df}, {output}, {input})",
    input=[
      q.dilepton_p4_Z,
      q.dimuon_p4_Higgs,
    ],
    output=[q.Z_H_cosThStar],
    scopes=["eemm","mmmm"],
)
# Cut met pt, return a flag to do filter
Flag_MetCut = Producer(
    name="Flag_MetCut",
    call="physicsobject::MetCut({df}, {output}, {input}, {min_met})",
    input=[
      q.met_p4,
    ],
    output=[q.Flag_MetCut],
    scopes=["nnmm","nnmm_dycontrol","nnmm_topcontrol"],
)
FilterFlagMetCut = Producer(
    name="FilterFlagMetCut",
    call='basefunctions::FilterThreshold({df}, {input}, {flag_MetCut}, "==", "MET >= 50 GeV")',
    input=[q.Flag_MetCut],
    output=None,
    scopes=["nnmm","nnmm_dycontrol","nnmm_topcontrol"],
)