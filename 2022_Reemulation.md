# 2022 Data reemulation

On 3 June 2022, during a low intensity 900 GeV collisions run (Run 352912 [[Link to OMS]](https://cmsoms.cern.ch/cms/runs/report?cms_run=352912&cms_run_sequence=GLOBAL-RUN)),
ECAL ran in full readout mode with double weights in tagging mode with the delta min = 2.5 GeV working point. The files were copied to `/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2022StableBeams/Run_352912/`. One 
can run the ETTAnalyzer over 100 events of one file as a test with the following command:

```
cmsRun ETTAnalyzer_cfg_12_3_0.py BarrelOnly=1 RunETTAnalyzer=1 \ 
inFile="file:/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2022StableBeams/Run_352912/dfe92cc8-cdaa-4ce2-a7a5-53c9e5078f50.root" \
OverrideWeights=0 RecoMethod=weights UserGlobalTag=123X_dataRun3_HLT_v7 era=Run3 userMaxEvents=100
```

