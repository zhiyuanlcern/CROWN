from ..quantities import output as q
from ..quantities import nanoAOD as nanoAOD
from code_generation.producer import Producer, ProducerGroup
# write by botao

####################
# Set of producers used for select the smallest mass of di-lepton
####################

CalcSmallestDileptonMass = Producer(
    name="CalcSmallestDileptonMass",
    call='physicsobject::M_dileptonMass({df}, {output}, {input})',
    input=[nanoAOD.Muon_pt,
           nanoAOD.Muon_eta, 
           nanoAOD.Muon_phi, 
           nanoAOD.Muon_mass,
           nanoAOD.Muon_charge,
           q.good_muon_collection],
    output=[q.smallest_dilepton_mass],
    scopes=["global","m2m"],
)
LeptonChargeSumVeto = Producer(
    name="LeptonChargeSumVeto",
    call='physicsobject::LeptonChargeSum({df}, {output}, {input})',
    input=[nanoAOD.Muon_charge,
           q.good_muon_collection],
    output=[q.Flag_LeptonChargeSumVeto],   # 1 stands passed, 0 stands failed
    scopes=["global","e2m","m2m","2e2m","4m"],
)