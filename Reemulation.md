# Re-emulation 

The purpose of this readme is to provide instructions for re-emulating CMS data using custom ECAL L1 configurations (TPModes) and different sets of ODD weights (the second set of double
weights). This type of study is useful as it describes the expected performance at ECAL and CMS if we had been running with a given TPMode and set of ODD weights previously, and
therefore gives us an idea of what performance we may expect when running with such configurations in the future. 

## 2021 Pilot Beam data 

In this example, we will go over the steps necessary to re-emulate the 2021 pilot beam data taken at CMS. First make sure to run the [ETTAnalyzer Setup](https://github.com/CMS-ECAL-Trigger-Group/ETTAnalyzer#setup) 
steps from the main README. 

One can run on a single file with:

```
cmsRun conf_12_1_0_pre3.py Debug=0 TPModeSqliteFile=TPModes/output/EcalTPG_TPMode_Run3_zeroing.db   TPModeTag=EcalTPG_TPMode_Run3_zeroing TPinfoPrintout=0 userMaxEvents=1 \
OddWeightsSqliteFile=weights/output/MinDelta_2p5Prime_OddWeights.db  OddWeightsGroupSqliteFile="weights/output/OneEBOneEEset_adding2021Strips.db"  BarrelOnly=1 RunETTAnalyzer=1 \
inFile="file:/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2021StableBeams/Run_346446/f811cb68-7ac4-4148-abbc-3a76d95881d2.root" OverrideWeights=1 \
UserGlobalTag=120X_dataRun3_HLT_v3 RecoMethod=weights
```

6 cases to look at: (WP X PF X RECO) --> 2 working points, with or without ODD peak finder, with weights or multifit offline reco. 
