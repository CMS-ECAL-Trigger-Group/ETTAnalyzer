# ETTAnalyzer Examples 

The purpose of this file is to keep track of examples for running ETTAnalyzer.

## 2018 Beam Splash re-emulation 

```
cmsRun conf_12_1_0_pre3.py Debug=0 TPModeSqliteFile=TPModes/EcalTPG_TPMode_Run3_zeroing.db \
TPModeTag=EcalTPG_TPMode_Run3_zeroing TPinfoPrintout=0 userMaxEvents=50 OddWeightsSqliteFile=weights/ZeroCandidateSet.db BarrelOnly=1 \
RunETTAnalyzer=1 inFile="file:/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2018BeamSplashes/RAW/Splashes2018_highECALReadout_run313133.root" \
OverrideWeights=1 UserGlobalTag=113X_dataRun2_relval_v1 RecoMethod=weights
```
