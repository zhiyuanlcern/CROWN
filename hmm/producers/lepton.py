from ..quantities import output as q
from ..quantities import nanoAOD as nanoAOD
from code_generation.producer import Producer, ProducerGroup
# write by botao

####################
# Set of producers used for select the smallest mass of di-lepton
####################

CalcSmallestDileptonMass = Producer(
    name="CalcSmallestDileptonMass",
    call="physicsobject::M_dileptonMass({df}, {output}, {input})",
    input=[nanoAOD.Muon_pt,
           nanoAOD.Muon_eta, 
           nanoAOD.Muon_phi, 
           nanoAOD.Muon_mass,
           q.good_muons_mask],
    output=[q.smallest_dilepton_mass],
    scopes=["global","m2m"],
)