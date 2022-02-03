# FENIX weight encoding and SQLite creation 

The purpose of this directory is to produce the FENIX integer encoded versions of decimal weights, and produce SQLite files in order to overwrite ODD weights that would be picked up from the DB. This 
is useful for re-emulating with a custom set of ODD weights that were not necessarily used at the time of data taking, and in particular for which a class which may 
not exist. 

## Weight encoding 

If one has decimal weights they would like to convert to integers (encoded version of weights to be read by the FENIX), one can use the python module `weights_encoder.py`. 

## SQLite creation 

In order to create weights and weight groups as SQLite files to overwrite the DB, one can use the following CMSSW configuration files:

```
updateTPGOddWeightGroup.py
updateTPGOddWeightIdMap.py
```
