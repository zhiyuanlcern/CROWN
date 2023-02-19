from ..quantities import output as q
from ..quantities import nanoAOD as nanoAOD
from code_generation.producer import Producer, ProducerGroup

####################
# Set of producers used for loosest selection of electrons
####################

ElectronPtCut = Producer(
    name="ElectronPtCut",
    call="physicsobject::CutPt({df}, {input}, {output}, {min_ele_pt})",
    input=[nanoAOD.Electron_pt],
    output=[],
    scopes=["global"],
)
ElectronECalGapVeto = Producer(
    name="ElectronECalGapVeto",
    call="physicsobject::ECalGapVeto({df}, {input}, {output}, {max_ele_eta}, 0, {upper_threshold_barrel}, {lower_threshold_endcap})",
    input=[nanoAOD.Electron_eta],
    output=[],
    scopes=["global"],
)
ElectronDxyCut = Producer(
    name="ElectronDxyCut",
    call="physicsobject::CutDxy({df}, {input}, {output}, {max_ele_dxy})",
    input=[nanoAOD.Electron_dxy],
    output=[],
    scopes=["global"],
)
ElectronDzCut = Producer(
    name="ElectronDzCut",
    call="physicsobject::CutDz({df}, {input}, {output}, {max_ele_dz})",
    input=[nanoAOD.Electron_dz],
    output=[],
    scopes=["global"],
)
ElectronIDCut = Producer(
    name="ElectronIDCut",
    call='physicsobject::electron::CutID({df}, {output}, "{ele_id}")',
    input=[],
    output=[],
    scopes=["global"],
)
ElectronSIP3DCut = Producer(
    name="MuonSIP3DCut",
    call="physicsobject::CutVarMax({df}, {input}, {output}, {max_sip3d})",
    input=[nanoAOD.Electron_sip3d],
    output=[],
    scopes=["global"],
)
BaseElectrons = ProducerGroup(
    name="BaseElectrons",
    call="physicsobject::CombineMasks({df}, {output}, {input})",
    input=[],
    output=[q.base_electrons_mask],
    scopes=["global"],
    subproducers=[
        ElectronPtCut,
        ElectronECalGapVeto,
        ElectronDxyCut,
        ElectronDzCut,
        ElectronIDCut,
        ElectronSIP3DCut,
    ],
)
Ele_Veto = Producer(
    name="Ele_Veto",
    call="physicsobject::Ele_Veto({df}, {output}, {input})",
    input=[q.base_electrons_mask],
    output=[q.Flag_Ele_Veto],
    scopes=["global","m2m","4m"],
)