from ..quantities import output as q
from code_generation.producer import Producer, ProducerGroup
from code_generation.producer import ExtendedVectorProducer


############################
# Muon ID, ISO SF
# The readout is done via correctionlib
############################

Muon_1_ID_SF_RooWorkspace = Producer(
    name="MuonID_SF_RooWorkspace",
    call='scalefactor::muon::id_rooworkspace({df}, {input}, {output}, "{muon_sf_workspace}", "{muon_sf_id_name}", "{muon_sf_id_args}")',
    input=[q.pt_1, q.eta_1],
    output=[q.id_wgt_mu_1],
    scopes=["e2m","m2m", "eemm","mmmm"],
)
Muon_1_Iso_SF_RooWorkspace = Producer(
    name="MuonIso_SF_RooWorkspace",
    call='scalefactor::muon::iso_rooworkspace({df}, {input}, {output}, "{muon_sf_workspace}", "{muon_sf_iso_name}", "{muon_sf_iso_args}")',
    input=[q.pt_1, q.eta_1, q.iso_1],
    output=[q.iso_wgt_mu_1],
    scopes=["e2m","m2m", "eemm","mmmm"],
)
Muon_1_ID_SF = Producer(
    name="MuonID_SF",
    call='scalefactor::muon::id({df}, {input}, "{muon_sf_year_id}", "{muon_sf_varation}", {output}, "{muon_sf_file}", "{muon_id_sf_name}")',
    input=[q.pt_1, q.eta_1],
    output=[q.id_wgt_mu_1],
    scopes=["e2m","m2m", "eemm","mmmm"],
)
Muon_1_Iso_SF = Producer(
    name="MuonIso_SF",
    call='scalefactor::muon::iso({df}, {input}, "{muon_sf_year_id}", "{muon_sf_varation}", {output}, "{muon_sf_file}", "{muon_iso_sf_name}")',
    input=[q.pt_1, q.eta_1],
    output=[q.iso_wgt_mu_1],
    scopes=["e2m","m2m", "eemm","mmmm"],
)
Muon_2_ID_SF_RooWorkspace = Producer(
    name="MuonID_SF_RooWorkspace",
    call='scalefactor::muon::id_rooworkspace({df}, {input}, {output}, "{muon_sf_workspace}", "{muon_sf_id_name}", "{muon_sf_id_args}")',
    input=[q.pt_2, q.eta_2],
    output=[q.id_wgt_mu_2],
    scopes=["e2m","m2m", "eemm","mmmm"],
)
Muon_2_Iso_SF_RooWorkspace = Producer(
    name="MuonIso_SF_RooWorkspace",
    call='scalefactor::muon::iso_rooworkspace({df}, {input}, {output}, "{muon_sf_workspace}", "{muon_sf_iso_name}", "{muon_sf_iso_args}")',
    input=[q.pt_2, q.eta_2, q.iso_2],
    output=[q.iso_wgt_mu_2],
    scopes=["e2m","m2m", "eemm","mmmm"],
)
Muon_2_ID_SF = Producer(
    name="MuonID_SF",
    call='scalefactor::muon::id({df}, {input}, "{muon_sf_year_id}", "{muon_sf_varation}", {output}, "{muon_sf_file}", "{muon_id_sf_name}")',
    input=[q.pt_2, q.eta_2],
    output=[q.id_wgt_mu_2],
    scopes=["e2m","m2m", "eemm","mmmm"],
)
Muon_2_Iso_SF = Producer(
    name="MuonIso_SF",
    call='scalefactor::muon::iso({df}, {input}, "{muon_sf_year_id}", "{muon_sf_varation}", {output}, "{muon_sf_file}", "{muon_iso_sf_name}")',
    input=[q.pt_2, q.eta_2],
    output=[q.iso_wgt_mu_2],
    scopes=["e2m","m2m", "eemm","mmmm"],
)

Muon_1_ID_SF_vhmm = Producer(
    name="Muon_1_ID_SF_vhmm",
    call='scalefactor::muon::id_vhmm({df}, {input}, "{muon_sf_year_id}", "{muon_sf_varation}", {output}, "{muon_sf_file}", "{muon_id_sf_name}")',
    input=[q.muon_leadingp4_H],
    output=[q.id_wgt_mu_1],
    scopes=["e2m","m2m", "eemm","mmmm","nnmm"],
)
Muon_2_ID_SF_vhmm = Producer(
    name="Muon_2_ID_SF_vhmm",
    call='scalefactor::muon::id_vhmm({df}, {input}, "{muon_sf_year_id}", "{muon_sf_varation}", {output}, "{muon_sf_file}", "{muon_id_sf_name}")',
    input=[q.muon_subleadingp4_H],
    output=[q.id_wgt_mu_2],
    scopes=["e2m","m2m", "eemm","mmmm","nnmm"],
)
Muon_3_ID_SF_vhmm_m2m = Producer(
    name="Muon_3_ID_SF_vhmm_m2m",
    call='scalefactor::muon::id_vhmm({df}, {input}, "{muon_sf_year_id}", "{muon_sf_varation}", {output}, "{muon_sf_file}", "{muon_id_sf_name}")',
    input=[q.extra_lep_p4],
    output=[q.id_wgt_mu_3],
    scopes=["m2m"],
)
Muon_3_ID_SF_vhmm_mmmm = Producer(
    name="Muon_3_ID_SF_vhmm_mmmm",
    call='scalefactor::muon::id_vhmm({df}, {input}, "{muon_sf_year_id}", "{muon_sf_varation}", {output}, "{muon_sf_file}", "{muon_id_sf_name}")',
    input=[q.lepton_leadingp4_Z],
    output=[q.id_wgt_mu_3],
    scopes=["mmmm"],
)
Muon_4_ID_SF_vhmm_mmmm = Producer(
    name="Muon_4_ID_SF_vhmm_mmmm",
    call='scalefactor::muon::id_vhmm({df}, {input}, "{muon_sf_year_id}", "{muon_sf_varation}", {output}, "{muon_sf_file}", "{muon_id_sf_name}")',
    input=[q.lepton_subleadingp4_Z],
    output=[q.id_wgt_mu_4],
    scopes=["mmmm"],
)
Muon_1_Iso_SF_vhmm = Producer(
    name="Muon_1_Iso_SF_vhmm",
    call='scalefactor::muon::iso_vhmm({df}, {input}, "{muon_sf_year_id}", "{muon_sf_varation}", {output}, "{muon_sf_file}", "{muon_iso_sf_name}")',
    input=[q.muon_leadingp4_H],
    output=[q.iso_wgt_mu_1],
    scopes=["e2m","m2m", "eemm","mmmm","nnmm"],
)
Muon_2_Iso_SF_vhmm = Producer(
    name="Muon_2_Iso_SF_vhmm",
    call='scalefactor::muon::iso_vhmm({df}, {input}, "{muon_sf_year_id}", "{muon_sf_varation}", {output}, "{muon_sf_file}", "{muon_iso_sf_name}")',
    input=[q.muon_subleadingp4_H],
    output=[q.iso_wgt_mu_2],
    scopes=["e2m","m2m", "eemm","mmmm","nnmm"],
)
Muon_3_Iso_SF_vhmm_m2m = Producer(
    name="Muon_3_Iso_SF_vhmm_m2m",
    call='scalefactor::muon::iso_vhmm({df}, {input}, "{muon_sf_year_id}", "{muon_sf_varation}", {output}, "{muon_sf_file}", "{muon_iso_sf_name}")',
    input=[q.extra_lep_p4],
    output=[q.iso_wgt_mu_3],
    scopes=["m2m"],
)
Muon_3_Iso_SF_vhmm_mmmm = Producer(
    name="Muon_3_Iso_SF_vhmm_mmmm",
    call='scalefactor::muon::iso_vhmm({df}, {input}, "{muon_sf_year_id}", "{muon_sf_varation}", {output}, "{muon_sf_file}", "{muon_iso_sf_name}")',
    input=[q.lepton_leadingp4_Z],
    output=[q.iso_wgt_mu_3],
    scopes=["mmmm"],
)
Muon_4_Iso_SF_vhmm_mmmm = Producer(
    name="Muon_4_Iso_SF_vhmm_mmmm",
    call='scalefactor::muon::iso_vhmm({df}, {input}, "{muon_sf_year_id}", "{muon_sf_varation}", {output}, "{muon_sf_file}", "{muon_iso_sf_name}")',
    input=[q.lepton_subleadingp4_Z],
    output=[q.iso_wgt_mu_4],
    scopes=["mmmm"],
)
MuonIDIso_SF = ProducerGroup(
    name="MuonIDIso_SF",
    call=None,
    input=None,
    output=None,
    scopes=["e2m","m2m", "eemm","mmmm","nnmm"],
    subproducers={
        "e2m": [
            Muon_1_ID_SF_vhmm,
            Muon_1_Iso_SF_vhmm,
            Muon_2_ID_SF_vhmm,
            Muon_2_Iso_SF_vhmm,
        ],
        "m2m": [
            Muon_1_ID_SF_vhmm,
            Muon_1_Iso_SF_vhmm,
            Muon_2_ID_SF_vhmm,
            Muon_2_Iso_SF_vhmm,
            Muon_3_ID_SF_vhmm_m2m,
            Muon_3_Iso_SF_vhmm_m2m,
        ],
        "eemm": [
            Muon_1_ID_SF_vhmm,
            Muon_1_Iso_SF_vhmm,
            Muon_2_ID_SF_vhmm,
            Muon_2_Iso_SF_vhmm,
        ],
        # 4m TODO
        "mmmm": [
            Muon_1_ID_SF_vhmm,
            Muon_1_Iso_SF_vhmm,
            Muon_2_ID_SF_vhmm,
            Muon_2_Iso_SF_vhmm,
            Muon_3_ID_SF_vhmm_mmmm,
            Muon_3_Iso_SF_vhmm_mmmm,
            Muon_4_ID_SF_vhmm_mmmm,
            Muon_4_Iso_SF_vhmm_mmmm,
        ],
        "nnmm": [
            Muon_1_ID_SF_vhmm,
            Muon_1_Iso_SF_vhmm,
            Muon_2_ID_SF_vhmm,
            Muon_2_Iso_SF_vhmm,
        ],
    },
)
MuonIDIso_SF_RooWorkspace = ProducerGroup(
    name="MuonIDIso_SF_RooWorkspace",
    call=None,
    input=None,
    output=None,
    scopes=["e2m","m2m", "eemm","mmmm"],
    subproducers={
        "e2m": [
            Muon_1_ID_SF_RooWorkspace,
            Muon_1_Iso_SF_RooWorkspace,
            Muon_2_ID_SF_RooWorkspace,
            Muon_2_Iso_SF_RooWorkspace,
        ],
        "m2m": [
            Muon_1_ID_SF_RooWorkspace,
            Muon_1_Iso_SF_RooWorkspace,
            Muon_2_ID_SF_RooWorkspace,
            Muon_2_Iso_SF_RooWorkspace,
        ],
        "eemm": [
            Muon_1_ID_SF_RooWorkspace,
            Muon_1_Iso_SF_RooWorkspace,
            Muon_2_ID_SF_RooWorkspace,
            Muon_2_Iso_SF_RooWorkspace,
        ],
        # 4m TODO
        "mmmm": [
            Muon_1_ID_SF_RooWorkspace,
            Muon_1_Iso_SF_RooWorkspace,
            Muon_2_ID_SF_RooWorkspace,
            Muon_2_Iso_SF_RooWorkspace,
        ],
    },
)
