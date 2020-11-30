#####  At the moment this setup Worked with data GT: 110X_dataRun2_v12 in CMSSW_11_0_2, taken from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideL1TStage2Instructions#Environment_Setup_with_Integrati


```
cmsrel CMSSW_11_0_2 
cd CMSSW_11_0_2/src
cmsenv 
git clone git@github.com:CMS-ECAL-Trigger-Group/ECALDoubleWeights.git
cd ECALDoubleWeights
git checkout CMSSW_11_0_2
cd ETTAnalyzer/
scramv1 b -j 10 
cmsRun conf_11_0_2.py ## test it on the .root file already added to the config file. 
```

If the above setup works fine, it means you have the analyzer working. In order to print the debug
 statements (newly added, don't switch on the default swicth from emulator if you need the columnar output). 

Install the ```SimCalorimetry``` package in the ```CMSSW/src``` area. 
```
git clone git@github.com:CMS-ECAL-Trigger-Group/SimCalorimetry.git ## by default it takes the main branch which works fine in CMSSW_11_0_2 branch of ```ECALDoubleWeights```
## all the cout statements are already added but it still need to make it configurable. So they will always appear for a few more days untill it is made configurable
## no need to change anything in this package for debug statements [unless you need something extra]. 
scramv1 b -j 10
cd ECALDoubleWeights/ETTAnalyzer
cmsRun conf_11_0_2.py  >& log
## clean up the log file and attach the run lumi event as new columns 
python preparelog.py
## the output name is hardcoded: amplifier_filter_log.txt
## The new text file can be analyzed using the python file 
python readlog.py ## a few exmaples given already. 
## The screen print can directed to a .csv or .txt file if needed. 

```

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