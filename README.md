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

## Examples

Example commands to run:

	cmsRun conf_11_0_2.py 
	cmsRun conf_11_0_2.py debug=1 ##-- For extra debug statements 
