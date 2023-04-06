from ..quantities import output as q
from ..quantities import nanoAOD as nanoAOD
from code_generation.producer import Producer, ProducerGroup

####################
# Set of producers used for get pt, eta, phi, mass from p4
####################

##### for mu1 from Higgs
#####
mu1_fromH_pt = Producer(
    name="mu1_fromH_pt",
    call='quantities::pt({df}, {output}, {input})',
    input=[
      q.muon_leadingp4_H,
    ],
    output=[q.mu1_fromH_pt],
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)
mu1_fromH_eta = Producer(
    name="mu1_fromH_eta",
    call='quantities::eta({df}, {output}, {input})',
    input=[
      q.muon_leadingp4_H,
    ],
    output=[q.mu1_fromH_eta],
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)
mu1_fromH_phi = Producer(
    name="mu1_fromH_phi",
    call='quantities::phi({df}, {output}, {input})',
    input=[
      q.muon_leadingp4_H,
    ],
    output=[q.mu1_fromH_phi],
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)
# mu1_fromH_mass = Producer(
#     name="mu1_fromH_mass",
#     call='quantities::mass({df}, {output}, {input})',
#     input=[
#       q.muon_leadingp4_H,
#     ],
#     output=[q.mu1_fromH_mass],
#     scopes=["e2m","m2m","eemm","mmmm","nnmm"],
# )

##### for mu2 from Higgs
#####
mu2_fromH_pt = Producer(
    name="mu2_fromH_pt",
    call='quantities::pt({df}, {output}, {input})',
    input=[
      q.muon_subleadingp4_H,
    ],
    output=[q.mu2_fromH_pt],
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)
mu2_fromH_eta = Producer(
    name="mu2_fromH_eta",
    call='quantities::eta({df}, {output}, {input})',
    input=[
      q.muon_subleadingp4_H,
    ],
    output=[q.mu2_fromH_eta],
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)
mu2_fromH_phi = Producer(
    name="mu2_fromH_phi",
    call='quantities::phi({df}, {output}, {input})',
    input=[
      q.muon_subleadingp4_H,
    ],
    output=[q.mu2_fromH_phi],
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)
# mu2_fromH_mass = Producer(
#     name="mu2_fromH_mass",
#     call='quantities::mass({df}, {output}, {input})',
#     input=[
#       q.muon_subleadingp4_H,
#     ],
#     output=[q.mu2_fromH_mass],
#     scopes=["e2m","m2m","eemm","mmmm","nnmm"],
# )

##### Higgs 
#####
H_pt = Producer(
    name="H_pt",
    call='quantities::pt({df}, {output}, {input})',
    input=[
      q.dimuon_p4_Higgs,
    ],
    output=[q.H_pt],
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)
H_eta = Producer(
    name="H_eta",
    call='quantities::eta({df}, {output}, {input})',
    input=[
      q.dimuon_p4_Higgs,
    ],
    output=[q.H_eta],
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)
H_phi = Producer(
    name="H_phi",
    call='quantities::phi({df}, {output}, {input})',
    input=[
      q.dimuon_p4_Higgs,
    ],
    output=[q.H_phi],
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)
H_mass = Producer(
    name="H_mass",
    call='quantities::mass({df}, {output}, {input})',
    input=[
      q.dimuon_p4_Higgs,
    ],
    output=[q.H_mass],
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)

##### for met pt and phi
#####
met_pt = Producer(
    name="met_pt",
    call='quantities::pt({df}, {output}, {input})',
    input=[
      q.met_p4,
    ],
    output=[q.met_pt],
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)
met_phi = Producer(
    name="met_phi",
    call='quantities::phi({df}, {output}, {input})',
    input=[
      q.met_p4,
    ],
    output=[q.met_phi],
    scopes=["e2m","m2m","eemm","mmmm","nnmm"],
)

##### for extra lepton
#####
extra_lep_pt = Producer(
    name="extra_lep_pt",
    call='quantities::pt({df}, {output}, {input})',
    input=[
      q.extra_lep_p4,
    ],
    output=[q.extra_lep_pt],
    scopes=["e2m","m2m"],
)
extra_lep_eta = Producer(
    name="extra_lep_eta",
    call='quantities::eta({df}, {output}, {input})',
    input=[
      q.extra_lep_p4,
    ],
    output=[q.extra_lep_eta],
    scopes=["e2m","m2m"],
)
extra_lep_phi = Producer(
    name="extra_lep_phi",
    call='quantities::phi({df}, {output}, {input})',
    input=[
      q.extra_lep_p4,
    ],
    output=[q.extra_lep_phi],
    scopes=["e2m","m2m"],
)
# extra_lep_mass = Producer(
#     name="extra_lep_mass",
#     call='quantities::mass({df}, {output}, {input})',
#     input=[
#       q.extra_lep_p4,
#     ],
#     output=[q.extra_lep_mass],
#     scopes=["e2m","m2m"],
# )

##### for muOS from Higgs
#####
muOS_pt = Producer(
    name="muOS_pt",
    call='quantities::pt({df}, {output}, {input})',
    input=[
      q.mu_p4_OSwithLep,
    ],
    output=[q.muOS_pt],
    scopes=["e2m","m2m"],
)
muOS_eta = Producer(
    name="muOS_eta",
    call='quantities::eta({df}, {output}, {input})',
    input=[
      q.mu_p4_OSwithLep,
    ],
    output=[q.muOS_eta],
    scopes=["e2m","m2m"],
)
muOS_phi = Producer(
    name="muOS_phi",
    call='quantities::phi({df}, {output}, {input})',
    input=[
      q.mu_p4_OSwithLep,
    ],
    output=[q.muOS_phi],
    scopes=["e2m","m2m"],
)
# muOS_mass = Producer(
#     name="muOS_mass",
#     call='quantities::mass({df}, {output}, {input})',
#     input=[
#       q.mu_p4_OSwithLep,
#     ],
#     output=[q.muOS_mass],
#     scopes=["e2m","m2m"],
# )

##### for muSS from Higgs
#####
muSS_pt = Producer(
    name="muSS_pt",
    call='quantities::pt({df}, {output}, {input})',
    input=[
      q.mu_p4_SSwithLep,
    ],
    output=[q.muSS_pt],
    scopes=["e2m","m2m"],
)
muSS_eta = Producer(
    name="muSS_eta",
    call='quantities::eta({df}, {output}, {input})',
    input=[
      q.mu_p4_SSwithLep,
    ],
    output=[q.muSS_eta],
    scopes=["e2m","m2m"],
)
muSS_phi = Producer(
    name="muSS_phi",
    call='quantities::phi({df}, {output}, {input})',
    input=[
      q.mu_p4_SSwithLep,
    ],
    output=[q.muSS_phi],
    scopes=["e2m","m2m"],
)
# muSS_mass = Producer(
#     name="muSS_mass",
#     call='quantities::mass({df}, {output}, {input})',
#     input=[
#       q.mu_p4_SSwithLep,
#     ],
#     output=[q.muSS_mass],
#     scopes=["e2m","m2m"],
# )

##### for lep1 from Z
#####
lep1_fromZ_pt = Producer(
    name="lep1_fromZ_pt",
    call='quantities::pt({df}, {output}, {input})',
    input=[
      q.lepton_leadingp4_Z,
    ],
    output=[q.lep1_fromZ_pt],
    scopes=["eemm","mmmm"],
)
lep1_fromZ_eta = Producer(
    name="lep1_fromZ_eta",
    call='quantities::eta({df}, {output}, {input})',
    input=[
      q.lepton_leadingp4_Z,
    ],
    output=[q.lep1_fromZ_eta],
    scopes=["eemm","mmmm"],
)
lep1_fromZ_phi = Producer(
    name="lep1_fromZ_phi",
    call='quantities::phi({df}, {output}, {input})',
    input=[
      q.lepton_leadingp4_Z,
    ],
    output=[q.lep1_fromZ_phi],
    scopes=["eemm","mmmm"],
)
# lep1_fromZ_mass = Producer(
#     name="lep1_fromZ_mass",
#     call='quantities::mass({df}, {output}, {input})',
#     input=[
#       q.lepton_leadingp4_Z,
#     ],
#     output=[q.lep1_fromZ_mass],
#     scopes=["eemm","mmmm"],
# )

##### for lep2 from Z
#####
lep2_fromZ_pt = Producer(
    name="lep2_fromZ_pt",
    call='quantities::pt({df}, {output}, {input})',
    input=[
      q.lepton_subleadingp4_Z,
    ],
    output=[q.lep2_fromZ_pt],
    scopes=["eemm","mmmm"],
)
lep2_fromZ_eta = Producer(
    name="lep2_fromZ_eta",
    call='quantities::eta({df}, {output}, {input})',
    input=[
      q.lepton_subleadingp4_Z,
    ],
    output=[q.lep2_fromZ_eta],
    scopes=["eemm","mmmm"],
)
lep2_fromZ_phi = Producer(
    name="lep2_fromZ_phi",
    call='quantities::phi({df}, {output}, {input})',
    input=[
      q.lepton_subleadingp4_Z,
    ],
    output=[q.lep2_fromZ_phi],
    scopes=["eemm","mmmm"],
)
# lep2fromZ_mass = Producer(
#     name="lep2fromZ_mass",
#     call='quantities::mass({df}, {output}, {input})',
#     input=[
#       q.lepton_subleadingp4_Z,
#     ],
#     output=[q.lep2fromZ_mass],
#     scopes=["eemm","mmmm"],
# )

##### for Z in 4l category
#####
Z_pt = Producer(
    name="Z_pt",
    call='quantities::pt({df}, {output}, {input})',
    input=[
      q.dilepton_p4_Z,
    ],
    output=[q.Z_pt],
    scopes=["eemm","mmmm"],
)
Z_eta = Producer(
    name="Z_eta",
    call='quantities::eta({df}, {output}, {input})',
    input=[
      q.dilepton_p4_Z,
    ],
    output=[q.Z_eta],
    scopes=["eemm","mmmm"],
)
Z_phi = Producer(
    name="Z_phi",
    call='quantities::phi({df}, {output}, {input})',
    input=[
      q.dilepton_p4_Z,
    ],
    output=[q.Z_phi],
    scopes=["eemm","mmmm"],
)
Z_mass = Producer(
    name="Z_mass",
    call='quantities::mass({df}, {output}, {input})',
    input=[
      q.dilepton_p4_Z,
    ],
    output=[q.Z_mass],
    scopes=["eemm","mmmm"],
)