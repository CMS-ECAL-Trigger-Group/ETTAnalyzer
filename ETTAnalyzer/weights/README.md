# FENIX weight encoding and SQLite File creation 

The purpose of this directory is to produce the FENIX integer encoded versions of decimal weights, and produce SQLite files in order to overwrite ODD weights that would be picked up from the DB. This 
is useful for re-emulating with a custom set of ODD weights that were not necessarily used at the time of data taking, and in particular for which a class which may 
not exist. 

## Weight encoding 

If one has decimal weights they would like to convert to integers (encoded version of weights to be read by the FENIX), one can use the python module `weights_encoder.py`. One can run a hardcoded example with the following:

```
cd ETTAnalyzer/ETTAnalyzer/weights
cmsenv
python3 weights_encoder.py
```

This will take a set of ODD amplitude weights output from the [Numerical Optimization](https://github.com/CMS-ECAL-Trigger-Group/DoubleWeightsOptimization) which have been converted to intervals of 1/64 (FENIX decimal precision), and will return the encoded integer values to be passed to the FENIX and used for re-emulation with a custom ODD weights set. 

## SQLite file creation 

In order to create weights and weight groups as SQLite files to overwrite the DB when running the ETTAnalyzer, one can use the following CMSSW configuration files:

```
updateTPGOddWeightGroup.py
updateTPGOddWeightIdMap.py
```

### Creating a TPGOddWeightIdMap (weight values to be used by stips)

To create a map from weight ID to encoded weight values, one should input a text file with one row per weight group into `updateTPGOddWeightIdMap.py`, which should output an SQLite file. An example usage would be using the text file `input/MinDelta_2p5_OddWeights.txt`:

```
cd ETTAnalyzer/ETTAnalyzer/weights
cmsRun updateTPGOddWeightIdMap.py input=input/MinDelta_2p5_OddWeights.txt output=output/test.db
```

If this works properly, you should have an output SQLite file `output/test.db`. The following are some miscellanous commands that can be used for inpsecting this SQLite file with `sqlite3` (available currently on lxplus):

```
sqlite3 
.open output/MinDelta_2p5_OddWeights.db
SELECT * FROM 'IOV';
SELECT * FROM 'PAYLOAD';
SELECT * FROM 'TAG';
SELECT * FROM 'TAG_LOG';
```
