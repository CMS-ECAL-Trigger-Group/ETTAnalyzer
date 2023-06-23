
# Scan file Analysis

To run a full analysis of the scans:

- Retrieve the name of the files for the analysis:
    - Modify the runs and lumisections in Scan_files/FindScanFiles.py (and possibly the path to the files on DAS)
    - Run :

```
python FindScanFiles.py
```

This command will compute .txt files for each time delay.

- Run the Crab job:
    - Check the following parameters in the CrabConfig file:
        - inDir
        - config.Data.outLFNDirBase
        - config.Site.whitelist
        - config.Site.storageSite

    - Run :

```
submit_crab.sh
```


- Once the jobs are done, retrieve the output with the script (once again be careful to the paths):

```
./crab_get_scan_output.sh
```

It will merge the files and delete them afterwards.

- Run the following macros (check the paths):

```
root DQM_extract.C
```

```
.L timingscan_prefire_23Sept2018_egamma_v2.C
timingscan(era, threshold)
```

## Run single file analysis

To run a single file analysis, you can use:

```
cmsRun ETTAnalyzer_cfg_12_3_0.py RunETTAnalyzer=1 inFile="/store/data/Run2023B/SpecialHLTPhysics0/RAW/v1/000/366/713/00000/06692d3f-c7be-4b14-8bb1-26214175f348.root" OverrideWeights=0 RecoMethod=weights UserGlobalTag=123X_dataRun3_HLT_v7 era=Run3 
```

If you want to limit the number of events (for debug for example), you can add the parameter:

```
userMaxEvents=1000
```
