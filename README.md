# ETT Analyzer 

The purpose of this repository is to create cmssw configuration files to perform ECAL Trigger Team tasks such as emulator development and general data / MC anaysis. This was originally setup to work with the data global tag 113X_dataRun2_relval_v1 in CMSSW_11_3_0_pre1

## Odd Weights Filter 

To run over events with even + odd filters and plot reconstructed ampltiudes, first perform a setup similar to the default:

	cmsrel CMSSW_11_3_0_pre1
	cd CMSSW_11_3_0_pre1/src
	cmsenv
	git cms-init
	git cms-merge-topic CMS-ECAL-Trigger-Group:ecal_double_weights_11_3_X 
	git clone git@github.com:CMS-ECAL-Trigger-Group/ECALDoubleWeights.git -b CMSSW_11_0_2-OddWeightsDev
	scram b -j 10
	cd ECALDoubleWeights/ETTAnalyzer

This command will move your local repository to the ecal_trigger_double_weights_11_3_X branch for odd weights emulator development. 

The odd weights branches of the ETT analyzer and SimCalorimetry repositories are listed above. After obtaining and scramming the relevant repositories, you can run the configuration in the ETTAnalyzer directory and run the even + odd filters on an event. The even filter weights will be obtained from the DB by default, but the Odd filter weights can be set with the local sqlite files, generated thanks to CondTools/Ecal scripts. 

	cmsRun conf_11_3_0_pre1.py  Debug=1 TPmode=0bxxxxxxxxxxxxxxx  TPinfoPrintout=1 maxEvents=10  >log.txt

The TPmode string is setup as an option of the python file but it will be soon moved to a DB tag. 
The available TPmodes are described in these slides https://indico.cern.ch/event/995229/contributions/4189814/attachments/2173034/3669116/21_01_18%20-%20ECAL%20Trigger%20meeting%20-%20Emulator%20configuration.pdf



---------------------------------------

### Old running command
	cd ECALDoubleWeights/ETTAnalyzer
	cmsRun conf_11_0_2.py TPinfoPrintout=1 oddWeightsTxtFile=ExtremeOddWeights.txt >> TPinfo.txt ##-- Run even + odd filters, where odd filter weights are given by "ExtremeOddWeights.txt"
	python preparelog.py ##-- Add header 
	python PlotTPinfo.py --outLoc /eos/user/a/atishelm/www/EcalL1Optimization/Emulator/ ##-- Create pandas dataframe and plot 

This will compute reconstructed amplitudes with "extreme odd weights", which are all set to 1 (64 / 64). This means you would expect to obtain much greater reco A's from the ODD filter in this case.

## Examples

To print out both general debug statements and also TP info, after setup described above simply run:

	cmsRun conf_11_0_2.py Debug=1 TPinfoPrintout=1 

An example command to run with each flag specified is:

	cmsRun conf_11_0_2.py TPinfoPrintout=1 Debug=1 oddWeightsTxtFile=ExtremeOddWeights.txt TPmode=Run2 BarrelOnly=1
