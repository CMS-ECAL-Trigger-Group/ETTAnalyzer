## To convert CMSSW errors into warning, which are safe do following: 
export USER_CXXFLAGS="-Wno-delete-non-virtual-dtor -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=sign-compare -Wno-error=reorder"


#####  At the moment this setup Worked with data GT: 110X_dataRun2_v12, taken from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideL1TStage2Instructions#Environment_Setup_with_Integrati


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