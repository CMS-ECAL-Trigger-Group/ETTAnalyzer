"""
16 August 2021
Abraham Tishelman-Charny 

The purpose of this CMSSW configuration file is to run over CMSSW data files, with or without the ETTAnalyzer run on top. 
"""

##-- Imports 
import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras
import os 
from ConfigParams import options 

##-- Define cms process 
process = cms.Process("ETTAnalyzer",eras.Run2_2017)
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("SimCalorimetry.EcalTrigPrimProducers.ecalTriggerPrimitiveDigis_readDBOffline_cff") ##-- Configuration for module which produces an EcalTrigPrimDigiCollection
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
                               
##-- Global Tag 
process.GlobalTag.globaltag = options.UserGlobalTag
# process.GlobalTag.globaltag = '113X_dataRun2_relval_v1'
# process.GlobalTag.globaltag = '113X_dataRun3_HLT_v3' ##-- July 2021 CRUZET 

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('EventFilter.L1TRawToDigi.gtStage2Digis_cfi')

process.GlobalTag.toGet = cms.VPSet(
    cms.PSet(record = cms.string("EcalTPGLinearizationConstRcd"),
         ),
    cms.PSet(record = cms.string("EcalTPGPedestalsRcd"), 
         )
)

##-- If overriding odd weights' records over global tag 
if(options.OverrideWeights):
    print("Setting double weights records to user input values")
    process.load("CondCore.CondDB.CondDB_cfi")
    # input database (in this case the local sqlite file)

    process.EcalOnTheFlyTPGconf = cms.ESSource("PoolDBESSource",
        DumpStat=cms.untracked.bool(True),
        toGet = cms.VPSet(cms.PSet(
                                record = cms.string('EcalTPGOddWeightIdMapRcd'),
                                tag = cms.string("EcalTPGOddWeightIdMap_test"),
                                connect = cms.string('sqlite_file:%s'%(options.OddWeightsSqliteFile))
                            ),
                        cms.PSet(
                                record = cms.string('EcalTPGOddWeightGroupRcd'),
                                tag = cms.string("EcalTPGOddWeightGroup_test"),
                                connect = cms.string('sqlite_file:EcalTPGOddWeightGroup.db')
                            ),
                        cms.PSet(
                                record = cms.string('EcalTPGTPModeRcd'),
                                tag = cms.string(options.TPModeTag),
                                connect = cms.string('sqlite_file:%s'%(options.TPModeSqliteFile))
                            )
        ),
    )

# ECAL Unpacker
process.load("EventFilter.EcalRawToDigi.EcalUnpackerMapping_cfi")
process.load("EventFilter.EcalRawToDigi.EcalUnpackerData_cfi")
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff') ##--  --> RawToDigi_cff --> Loads ecalTriggerPrimitiveDigis_cfi.py 
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('L1Trigger.Configuration.L1TReco_cff')
process.load('Configuration.EventContent.EventContent_cff')

process.raw2digi_step = cms.Path(process.RawToDigi)
process.endjob_step = cms.EndPath(process.endOfProcess)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step)

from L1Trigger.Configuration.customiseReEmul import L1TReEmulFromRAW

#call to customisation function L1TReEmulFromRAW imported from L1Trigger.Configuration.customiseReEmul
#process = L1TReEmulFromRAW(process)
from EventFilter.L1TRawToDigi.caloStage2Digis_cfi import caloStage2Digis
process.rawCaloStage2Digis = caloStage2Digis.clone()
process.rawCaloStage2Digis.InputLabel = cms.InputTag('rawDataCollector')

##-- Create ECAL TP digis module 
process.ecalTriggerPrimitiveDigis = cms.EDProducer("EcalTrigPrimProducer",
   InstanceEB = cms.string('ebDigis'),
   InstanceEE = cms.string('eeDigis'),
   Label = cms.string('ecalDigis'),
   BarrelOnly = cms.bool(True),
   Famos = cms.bool(False),
   TcpOutput = cms.bool(False),
   Debug = cms.bool(options.Debug), ##-- Lots of printout 
   binOfMaximum = cms.int32(6), ## optional from release 200 on, from 1-10
   TPinfoPrintout = cms.bool(options.TPinfoPrintout),
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.userMaxEvents) )
#process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( options.Printerval ) ##-- Printout run, lumi, event info
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 99999999 ) ##-- Printout run, lumi, event info

files = []

##-- If a file is passed as a flag, run over it 
if(options.inFile != ""):
    print("inFile flag value found:")
    print(options.inFile)
    files.append(options.inFile)

##-- If not file is passed, process a default files from 2018 Zerobias data 
else:
    files = ["/store/data/Run2018C/ZeroBias/RAW/v1/000/320/063/00000/62F3929A-F08D-E811-8133-FA163E19E543.root"]

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                                files
                            )
                        )

##-- If running ETT Analyzer
if(options.RunETTAnalyzer):

    print("[conf_11_3_0.py] - Running ETT Analyzer")

    ##-- Create EDAnalyzer 
    process.tuplizer = cms.EDAnalyzer('ETTAnalyzer', ##-- Name ultimately comes from plugins/ETTAnalyzer.cc final lines with plugin name definition 
                                    ugtProducer = cms.InputTag("gtStage2Digis"),
                                    savePreFireInfo = cms.bool(False), 
                                    TPEmulatorCollection =  cms.InputTag("ecalTriggerPrimitiveDigis",""), ##-- Different name for full readout?
                                    # TPEmulatorCollection =  cms.InputTag("ecalTriggerPrimitiveDigis","ecalTriggerPrimitiveDigis"), ##-- Different name for full readout?
                                    useAlgoDecision = cms.untracked.string("initial"),
                                    firstBXInTrainAlgo = cms.untracked.string("L1_FirstCollisionInTrain"),
                                    lastBXInTrainAlgo = cms.untracked.string("L1_LastCollisionInTrain"),
                                    isoBXAlgo = cms.untracked.string("L1_IsolatedBunch"),
                                    TPCollection = cms.InputTag("ecalDigis","EcalTriggerPrimitives"), 
                                    ## for data 
                                    stage2CaloLayer2EGammaProducer = cms.InputTag("gtStage2Digis","EGamma"),
                                    ## for mc 
                                    #stage2CaloLayer2EGammaProducer = cms.InputTag("hltGtStage2Digis","EGamma"),
                                    
                                    ## For rechits 
                                    EcalRecHitCollectionEB = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
                                    EcalRecHitCollectionEE = cms.InputTag("ecalRecHit","EcalRecHitsEE"),                                                                        
                                    
                                    ## for data on Raw
                                    EBdigis      = cms.InputTag("ecalDigis","ebDigis"),
                                    EEdigis      = cms.InputTag("ecalDigis","eeDigis"),
                                    
                                    ## for data on DIGIS : make sure why is this diff, w.r.t. RAW
                                    #EBdigis      = cms.InputTag("selectDigi","selectedEcalEBDigiCollection"),
                                    #EEdigis      = cms.InputTag("selectDigi","selectedEcalEEDigiCollection"),
                                    
                                    ## for mc
                                    #EBdigis      = cms.InputTag("simEcalDigis","ebDigis"),
                                    #EEdigis      = cms.InputTag("simEcalDigis","eeDigis"),
                                    genparticles = cms.InputTag("genParticles")
                                )

    ## Load appropriate processes for Rec Hits 
    process.load("Configuration/StandardSequences/Reconstruction_cff")

    if(options.RecoMethod == "Multifit"):
        print("Offline energy reconstruction to be performed with Multifit")
        ## Multifit 
        import RecoLocalCalo.EcalRecProducers.ecalMultiFitUncalibRecHit_cfi
        process.ecalUncalibHit =  RecoLocalCalo.EcalRecProducers.ecalMultiFitUncalibRecHit_cfi.ecalMultiFitUncalibRecHit.clone()
        process.ecalUncalibHit.algoPSet.activeBXs =cms.vint32(-5,-4,-3,-2,-1,0,1,2,3,4)
        process.ecalUncalibHit.algoPSet.useLumiInfoRunHeader = cms.bool (False )

    elif(options.RecoMethod == "weights"):
        print("Offline energy reconstruction to be performed with offline weights")
        ## Offline weights 
        import RecoLocalCalo.EcalRecProducers.ecalGlobalUncalibRecHit_cfi
        process.ecalUncalibHit = RecoLocalCalo.EcalRecProducers.ecalGlobalUncalibRecHit_cfi.ecalGlobalUncalibRecHit.clone()

    else:
        raise Exception("Unknown reconstruction method: %s"%(options.RecoMethod))

    process.load("RecoLocalCalo.EcalRecProducers.ecalRecHit_cfi")
    process.load("Geometry.CaloEventSetup.CaloTopology_cfi")
    process.load("RecoLocalCalo.EcalRecProducers.ecalDetIdToBeRecovered_cfi")
    process.ecalRecHit.EBuncalibRecHitCollection = 'ecalUncalibHit:EcalUncalibRecHitsEB'
    process.ecalRecHit.EEuncalibRecHitCollection = 'ecalUncalibHit:EcalUncalibRecHitsEE'

    ##-- Used for output root files 
    process.TFileService = cms.Service("TFileService",
                                    fileName = cms.string("ETTAnalyzer_output.root")
                                    )

    ##-- Define Path Which includes necessary modules for ETTAnalyzer 
    process.p = cms.Path(
                         process.gtDigis*
                         process.RawToDigi*
                         process.L1Reco*
                         process.gtStage2Digis*
                         process.ecalTriggerPrimitiveDigis*
                         process.ecalUncalibHit*
                         process.ecalDetIdToBeRecovered*
                         process.ecalRecHit*
                         process.tuplizer
                    )

##-- If not running ETT Analyzer
else: 

    ##-- Define Path Without ETTAnalyzer modules 
    process.p = cms.Path(
                        process.L1Reco*
                        process.gtStage2Digis*
                        process.ecalTriggerPrimitiveDigis
                    )

##-- In either case, append process path to process schedule 
process.schedule.append(process.p)
