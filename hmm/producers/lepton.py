from ..quantities import output as q
from ..quantities import nanoAOD as nanoAOD
from code_generation.producer import Producer, ProducerGroup
# write by botao

####################
# Set of producers used for select the smallest mass of di-lepton
####################

# dilepton mass > 12 GeV need SFOS
CalcSmallestDiMuonMass = Producer(
    name="CalcSmallestDiMuonMass",
    call='physicsobject::M_dileptonMass({df}, {output}, {input})',
    input=[nanoAOD.Muon_pt,
           nanoAOD.Muon_eta, 
           nanoAOD.Muon_phi, 
           nanoAOD.Muon_mass,
           nanoAOD.Muon_charge,
           q.good_muon_collection],
    output=[q.smallest_dimuon_mass],
    scopes=["global","m2m","e2m","eemm","mmmm"],
)
CalcSmallestDiElectronMass = Producer(
    name="CalcSmallestDiElectronMass",
    call='physicsobject::M_dileptonMass({df}, {output}, {input})',
    input=[nanoAOD.Electron_pt,
           nanoAOD.Electron_eta, 
           nanoAOD.Electron_phi, 
           nanoAOD.Electron_mass,
           nanoAOD.Electron_charge,
           q.base_electron_collection],
    output=[q.smallest_dielectron_mass],
    scopes=["global","eemm"],
)
LeptonChargeSumVeto = Producer(
    name="LeptonChargeSumVeto",
    call='physicsobject::LeptonChargeSum({df}, {output}, {input})',
    input=[nanoAOD.Muon_charge,  # only in m2m and 4m can input only muon charge
           q.good_muon_collection],
    output=[q.Flag_LeptonChargeSumVeto],   # 1 stands pm1, 2 stands 0, 0 stands others
    scopes=["global","m2m","mmmm"],
)
LeptonChargeSumVeto_elemu = Producer(
    name="LeptonChargeSumVeto_elemu",
    call='physicsobject::LeptonChargeSumEleMu({df}, {output}, {input})',
    input=[nanoAOD.Muon_charge,  # only in e2m and 2e2m can input only muon charge
           nanoAOD.Electron_charge,
           q.good_muon_collection,
           q.base_electron_collection],
    output=[q.Flag_LeptonChargeSumVeto],   # 1 stands pm1, 2 stands 0, 0 stands others
    scopes=["global","e2m","eemm"],
)