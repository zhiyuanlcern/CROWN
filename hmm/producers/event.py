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
    call='basefunctions::FilterThreshold({df}, {input}, {vh_m2m_nmuons}, ">=", "Number of muons 3")',
    input=[q.nmuons],
    output=None,
    scopes=["m2m"],
)

# write by botao
DileptonMassCut = Producer(
    name="DileptonMassCut",
    call='basefunctions::FilterThreshold({df}, {input}, {min_dilepton_mass}, ">=", "No mll < 12 GeV")',
    input=[q.smallest_dilepton_mass],
    output=None,
    scopes=["global","m2m"],
)
HiggsToDiMuonPair_p4 = Producer(
    name="HiggsToDiMuonPair_p4",
    call='physicsobject::HiggsToDiMuonPairCollection({df}, {output}, {input})',
    input=[nanoAOD.Muon_pt,
           nanoAOD.Muon_eta, 
           nanoAOD.Muon_phi, 
           nanoAOD.Muon_mass,
           q.good_muons_mask,
           q.good_muon_collection],
    output=[q.dimuon_p4_byPt],
    scopes=["global","e2m","m2m","2e2m","4m"],
)
DiMuonMassFromZVeto = Producer(
    name="DiMuonMassFromZVeto",
    call='physicsobject::DiMuonFromZVeto({df}, {output}, {input})',
    input=[nanoAOD.Muon_pt,
           nanoAOD.Muon_eta, 
           nanoAOD.Muon_phi, 
           nanoAOD.Muon_mass,
           q.good_muons_mask,
           q.good_muon_collection],
    output=[q.Flag_dimuon_Zmass_veto], # 1 stands for noZmass, 0 stands for has dimuon from Zmass
    scopes=["global","e2m","m2m","2e2m","4m"],
)
# Mask_DiMuonPair = Producer(
#     name="Mask_DiMuonPair",
#     call='physicsobject::HiggsToMuMu_Cand({df}, {output}, {input})',
#     input=[q.dimuon_p4_byPt],
#     output=[q.HiggsToMuMu_mask],
#     scopes=["global","e2m","m2m","2e2m","4m"],
# )
# HiggsToDiMuonCand = Producer(
#     name="HiggsToDiMuonCand",
#     call='physicsobject::GetFirstElement({df}, {input}, {output})',
#     input=[q.dimuon_p4_byPt],
#     output=[q.dimuon_p4_HiggsCand],
#     scopes=["global","e2m","m2m","2e2m","4m"],
# )