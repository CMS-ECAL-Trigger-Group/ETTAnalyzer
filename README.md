# ETT Analyzer 

The purpose of this repository is to create cmssw configuration files to perform ECAL Trigger Team tasks such as emulator development and general data / MC anaysis. This was originally setup to work with the data global tag 110X_dataRun2_v12 in CMSSW_11_0_2, taken from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideL1TStage2Instructions#Environment_Setup_with_Integrati

## Odd Weights Filter 

To run over events with even + odd filters and plot reconstructed ampltiudes, first perform a setup similar to the default:

	cmsrel CMSSW_11_0_2 
	cd CMSSW_11_0_2/src
	cmsenv 
	git clone git@github.com:CMS-ECAL-Trigger-Group/ECALDoubleWeights.git -b CMSSW_11_0_2-OddWeightsDev
	git clone git@github.com:CMS-ECAL-Trigger-Group/SimCalorimetry.git -b Odd-Weights-Filter-Dev
	scram b -j 
	cd ECALDoubleWeights/ETTAnalyzer

The odd weights branches of the ETT analyzer and SimCalorimetry repositories are listed above. After obtaining and scramming the relevant repositories, you can run the configuration in the ETTAnalyzer directory and run the even + odd filters on an event. The even filter weights will be obtained from the DB by default, but the Odd filter weights can be set with an input text file, passed with the flag "oddWeightsTxtFile". In this example, the file ExtremeOddWeights.txt will be used which contains "64" for all five odd weights. This is read by SimCalorimetry as "1" for all five:

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
