#!/bin/bash
pathadd() {
    if [[ ":$PATH:" != *":$1:"* ]]; then
        PATH="${PATH:+"$PATH:"}$1"
        export PATH
    fi
}
# get the directory of the script
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]:-$0}")" &>/dev/null && pwd 2>/dev/null)"
# distro=$(lsb_release -i | cut -f2)
# os_version=$(lsb_release -r | cut -f2)
echo "Setting up CROWN for $distro Version $os_version"
# check if the distro is centos

PRETTY_NAME=$(grep "^PRETTY_NAME" /etc/os-release | cut -d= -f2 | tr -d '"')

if [[ "$PRETTY_NAME" == *"Linux 9"* ]]; then
    echo "This system is running Linux 9"
    source /cvmfs/sft.cern.ch/lcg/views/LCG_104/x86_64-el9-gcc11-opt/setup.sh

elif [[ "$PRETTY_NAME" == *"Linux 7"* ]]; then
    echo "This is CentOS Linux 7"
    source /cvmfs/sft.cern.ch/lcg/views/LCG_104/x86_64-centos7-gcc11-opt/setup.sh
    # Add commands specific to CentOS Linux 7 here
else
    echo "Unsupported OS: $PRETTY_NAME"
    # Add commands for unsupported OS or default actions here
    source /cvmfs/sft.cern.ch/lcg/views/LCG_104/x86_64-el9-gcc11-opt/setup.sh
fi

pathadd "${HOME}/.local/bin/"
# set the cmake generator to Ninja
# export CMAKE_GENERATOR="Ninja"
export CMAKE_GENERATOR="Unix Makefiles"
# set the compiler optimization for cling to O2, this
# will result in about 20% faster JIT for the snapshot generation
export EXTRA_CLING_ARGS='-O2'

# clone a given analysis if an argument is given
if [ -z "$1" ]; then
    echo "No configuration clone"
else
    if [[ "$1" == "tau" && ! -d "${SCRIPT_DIR}/analysis_configurations/tau" ]]; then
        echo "Cloning analysis tau into ${SCRIPT_DIR}/analysis_configurations/tau"

        git clone git@github.com:zhiyuanlcern/TauAnalysis-CROWN.git ${SCRIPT_DIR}/analysis_configurations/tau

    elif [[ "$1" == "earlyrun3" && ! -d "${SCRIPT_DIR}/analysis_configurations/earlyrun3" ]]; then
        echo "Cloning analysis earlyrun3 into ${SCRIPT_DIR}/analysis_configurations/earlyrun3"
        git clone https://github.com/khaosmos93/CROWN-config-earlyRun3.git "${SCRIPT_DIR}/analysis_configurations/earlyrun3"
    elif [[ "$1" == "whtautau" && ! -d "${SCRIPT_DIR}/analysis_configurations/whtautau" ]]; then
        echo "Cloning analysis whtautau into ${SCRIPT_DIR}/analysis_configurations/whtautau"

        git clone git@github.com:KIT-CMS/WHTauTauAnalysis-CROWN.git "${SCRIPT_DIR}/analysis_configurations/whtautau"
    elif [[ "$1" == "s" && ! -d "${SCRIPT_DIR}/analysis_configurations/s" ]]; then

        echo "Cloning analysis s-channel into ${SCRIPT_DIR}/analysis_configurations/s"
        git clone git@github.com:nfaltermann/CROWNs.git "${SCRIPT_DIR}/analysis_configurations/s"
    fi
fi
