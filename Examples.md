# ETTAnalyzer Examples 

The purpose of this file is to keep track of examples for running ETTAnalyzer.

## 2021 Beam Splash analysis 

To check global tag from a file:

```
edmProvDump /eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2021BeamSplashes/skimSplashEvents2021_run_346050.root | grep "globaltag"
```

Run ETTAnalyzer over 2021 beam splash skim file:

```
cmsRun conf_12_1_0_pre3.py Debug=0 TPModeSqliteFile=TPModes/EcalTPG_TPMode_tagging.db \
TPModeTag=EcalTPG_TPMode_tagging TPinfoPrintout=0 userMaxEvents=50 OddWeightsSqliteFile=weights/ZeroCandidateSet.db BarrelOnly=1 \
RunETTAnalyzer=1 inFile="file:/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2021BeamSplashes/skimSplashEvents2021_run_346050.root" \
OverrideWeights=1 UserGlobalTag=120X_dataRun3_HLT_v3 RecoMethod=weights
```

## 2018 Beam Splash re-emulation 

Run 2 mode:

```
cmsRun conf_12_1_0_pre3.py Debug=0 TPModeSqliteFile=TPModes/EcalTPG_TPMode_Run2_default.db \
TPModeTag=EcalTPG_TPMode_Run2_default TPinfoPrintout=0 userMaxEvents=50 OddWeightsSqliteFile=weights/ZeroCandidateSet.db BarrelOnly=1 \
RunETTAnalyzer=1 inFile="file:/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2018BeamSplashes/RAW/Splashes2018_highECALReadout_run313133.root" \
OverrideWeights=1 UserGlobalTag=113X_dataRun2_relval_v1 RecoMethod=weights
```

Tagging mode with sensible ODD weights:

```
cmsRun conf_12_1_0_pre3.py Debug=0 TPModeSqliteFile=TPModes/EcalTPG_TPMode_tagging.db \
TPModeTag=EcalTPG_TPMode_tagging TPinfoPrintout=0 userMaxEvents=50 OddWeightsSqliteFile=weights/ZeroCandidateSet.db BarrelOnly=1 \
RunETTAnalyzer=1 inFile="file:/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2018BeamSplashes/RAW/Splashes2018_highECALReadout_run313133.root" \
OverrideWeights=1 UserGlobalTag=113X_dataRun2_relval_v1 RecoMethod=weights
```
