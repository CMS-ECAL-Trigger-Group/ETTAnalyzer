# ETT Analyzer

The purpose of the ETT (ECAL Trigger Team) Analyzer is to process RAW CMS data files for ETT studies and re-emulation. Studies include the evaluation of double weights configurations with 2018 data and 2021 CMS commissioning data, and the studying of ECAL TP pre-firing. 

Current CMSSW version compatibility: CMSSW_12_1_0_pre3

## Setup

To setup the repository in CMSSW_12_1_0_pre3:

	export SCRAM_ARCH=slc7_amd64_gcc900 
	cmsrel CMSSW_12_1_0_pre3
	cd CMSSW_12_1_0_pre3/src
	cmsenv
	git cms-init
	
Then one should clone the repository either via HTTPS protocol:

	git clone https://github.com/CMS-ECAL-Trigger-Group/ETTAnalyzer.git
	
or SSH protocol:
	
	git clone git@github.com:CMS-ECAL-Trigger-Group/ETTAnalyzer.git
	
And proceed to build:
	
	cd ETTAnalyzer/ETTAnalyzer
	scram b -j  


## Examples

Some running examples can be found in the [Examples README](Examples.md)
