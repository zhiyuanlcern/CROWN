import os
import subprocess
from concurrent.futures import ThreadPoolExecutor
import ROOT

# Function to execute command in parallel
def execute_command(command, input_root, mass_value, config_command):
    output_file = f"{command}_et.root"
    
    file_exists = os.path.isfile(output_file)
    ntuple_present = False
    
    if file_exists:
        try:
            root_file = ROOT.TFile.Open(output_file)
            if root_file and not root_file.IsZombie():
                ntuple = root_file.Get("ntuple")
                if ntuple and ntuple.InheritsFrom("TTree"):
                    ntuple_present = True
            root_file.Close()
        except Exception as e:
            print(f"Error checking file {output_file}: {e}")

    if not file_exists or not ntuple_present:
        if not file_exists:
            print(f"start running for file: {command}.root")
        elif not ntuple_present:
            print(f"found incomplete file: {command}.root")
        if os.path.isfile(f'{input_root}/Mass_{mass_value}/'):
            exec_command = f"{config_command} {command}.root {input_root}/Mass_{mass_value}/*root > {command}.txt 2>&1 &" ## leyan input directory 
        else:
            exec_command = f"{config_command} {command}.root {input_root}/*_M-{mass_value}_2HDM*/*root > {command}.txt 2>&1 &" ## Jordan input directory 
        print(exec_command)
        subprocess.run(exec_command, shell=True)

if __name__ == "__main__":
    # Define the mass values and commands
    # mass_values = [60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,160,180,200,250,300,350,400,450,500,600,700,800,900,1000,1100,1200,1400,1600,1800,2000,2300,2600,2900,3200,3500]
    # commands_preEE = [f"bbHto2Tau_M-{m}_2HDM-II_TuneCP5_13p6TeV_powheg-pythia8_Run3Summer22NanoAODv12" for m in mass_values]
    # commands_postEE = [f"bbHto2Tau_M-{m}_2HDM-II_TuneCP5_13p6TeV_powheg-pythia8_Run3Summer22EENanoAODv12" for m in mass_values]

    # # Define the common parts of the commands
    # config_command_pre = "./config_vbf_htautau_2022EE"
    # config_command_post = "./config_vbf_htautau_2022postEE"
    # input_root_pre = "/data/pku/home/LeyanLee13/Htautau/syst/bbH_Rerun/2022preEE"
    # input_root_post = "/data/pku/home/LeyanLee13/Htautau/syst/bbH_Rerun/2022postEE"

    # # Execute commands in parallel
    # with ThreadPoolExecutor() as executor:
    #     for i in range(len(commands_preEE)):
    #         if i < len(mass_values):
    #             executor.submit(execute_command, commands_preEE[i], input_root_pre, mass_values[i], config_command_pre)
        
    #     for i in range(len(commands_postEE)):
    #         if i < len(mass_values):
    #             executor.submit(execute_command, commands_postEE[i], input_root_post, mass_values[i], config_command_post)

    mass_values = [60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,160,180,200,250,300,350,400,450,500,600,700,800,900,1000,1100,1200,1400,1600,1800,2000,2300,2600,2900,3200,3500]
    commands_preEE = [f"GluGluHto2Tau_M-{m}_2HDM-II_TuneCP5_13p6TeV_powheg-pythia8_Run3Summer22NanoAODv12" for m in mass_values]
    commands_postEE = [f"GluGluHto2Tau_M-{m}_2HDM-II_TuneCP5_13p6TeV_powheg-pythia8_Run3Summer22EENanoAODv12" for m in mass_values]

    # Define the common parts of the commands
    config_command_pre = "./config_ggh_htautau_2HDM_2022EE"
    config_command_post = "./config_ggh_htautau_2HDM_2022postEE"
    input_root_pre = "/data/bond/zhiyuanl/2022_samples/ggH_NanoAOD/2022EE"
    input_root_post = "/data/bond/zhiyuanl/2022_samples/ggH_NanoAOD/2022postEE"
    # Execute commands in parallel
    with ThreadPoolExecutor() as executor:
        for i in range(len(commands_preEE)):
            if i < len(mass_values):
                executor.submit(execute_command, commands_preEE[i], input_root_pre, mass_values[i], config_command_pre)
        
        for i in range(len(commands_postEE)):
            if i < len(mass_values):
                executor.submit(execute_command, commands_postEE[i], input_root_post, mass_values[i], config_command_post)

