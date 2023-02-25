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
is_embedding = Producer(
    name="is_embedding",
    call="basefunctions::DefineQuantity({df}, {output}, {is_embedding})",
    input=[],
    output=[q.is_embedding],
    scopes=["global"],
)
is_ttbar = Producer(
    name="is_ttbar",
    call="basefunctions::DefineQuantity({df}, {output}, {is_ttbar})",
    input=[],
    output=[q.is_ttbar],
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
        is_ttbar,
        is_dyjets,
        is_wjets,
        is_diboson,
        is_vhmm,
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
DimuonMinMassCut = Producer(
    name="DimuonMinMassCut",
    call='basefunctions::FilterThreshold({df}, {input}, {min_dimuon_mass}, ">=", "No m(mm) < 12 GeV")',
    input=[q.smallest_dimuon_mass],
    output=None,
    scopes=["global","m2m","e2m","eemm","mmmm"],
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
    scopes=["global","e2m","m2m","eemm","mmmm"],
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
    output=[q.dimuon_p4_byPt],
    scopes=["global","e2m","m2m","eemm"],
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
    output=[q.dimuon_p4_Z],
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
    output=[q.dielectron_p4_byPt],
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
    scopes=["global","e2m","m2m","eemm","mmmm"],
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
    scopes=["global","e2m","m2m","eemm"],
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