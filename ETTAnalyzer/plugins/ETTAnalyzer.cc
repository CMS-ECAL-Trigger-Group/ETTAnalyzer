/* To do: 


For the extra variables, I think the rechit severity level is an important one.  Here you need to add some extra commands to the python to run the rechit producer, and add an extra part to the analyser to find  the rechits corresponding to each tower and check the rechit severity level
https://gitlab.cern.ch/ECALPFG/EcalTPGAnalysis/-/blob/tpganalysis2018/TriggerAnalysis/plugins/EcalTPGAnalyzer.cc#L935

The other thing we will probably need is a way of extracting the digis for specific towers. In TPGAnalysis, this takes the form of a separate tree with one entry per channel. Maybe we can come up with a better and more compact structure, i.e. for each tower we have an array with a set of 25x10 numbers  (25 crystals and 10 samples per crystal). The issue here might be that the ntuple will become large. Perhaps it could be a configurable option, or something that just dumps a text file of the digis, since we might only want to do it for a few selected events

Add verbosity and debug statement in this piece of code to understand the steps and whats going on.. 
https://cmssdt.cern.ch/lxr/source/SimCalorimetry/EcalTrigPrimAlgos/src/
*/

// -*- C++ -*-v_
//
// Package:    ECALDoubleWeights/ETTAnalyzer
// Class:      ETTAnalyzer
//
/**\class ETTAnalyzer ETTAnalyzer.cc ECALDoubleWeights/ETTAnalyzer/plugins/ETTAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Raman Khurana
//         Created:  Wed, 1 November 2020 08:53:01 GMT
//
//

// system include files
#include <memory>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>
#include <string>
#include <TH2F.h> 
#include <TTree.h>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


#include "DataFormats/EcalDigi/interface/EcalTriggerPrimitiveDigi.h"
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "DataFormats/EcalRecHit/interface/EcalUncalibratedRecHit.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h"
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgoRcd.h"

#include "DataFormats/DetId/interface/DetId.h"

#include "Geometry/CaloTopology/interface/EcalTrigTowerConstituentsMap.h"

#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "Geometry/EcalMapping/interface/EcalElectronicsMapping.h"
#include "Geometry/EcalMapping/interface/EcalMappingRcd.h"


#include "DataFormats/L1Trigger/interface/Muon.h"
#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "DataFormats/L1Trigger/interface/Jet.h"
#include "DataFormats/L1Trigger/interface/EtSum.h"
#include "DataFormats/L1Trigger/interface/Tau.h"

#include "DataFormats/L1Trigger/interface/BXVector.h"
#include "L1Trigger/L1TGlobal/interface/L1TGlobalUtil.h"


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
 #include "FWCore/Utilities/interface/InputTag.h"
 #include "DataFormats/TrackReco/interface/Track.h"
 #include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "Geometry/CaloTopology/interface/EcalTrigTowerConstituentsMap.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"

class towerEner {
public:
  float eRec_ ;
  int crystNb_ ;
  int tpgEmul_[5] ;
  int tpgEmulFlag_[5] ;
  int tpgEmulsFGVB_[5] ;
  int tpgADC_;
  int iphi_, ieta_, nbXtal_, spike_ ;
  int twrADC, sFGVB, sevlv_, ttFlag_;
  int TCCid_, TowerInTCC_, strip_;
  int time_;
  towerEner()
    : eRec_(0),  crystNb_(0), tpgADC_(0),
      iphi_(-999), ieta_(-999), nbXtal_(0), spike_(0), twrADC(0), sFGVB(-999), sevlv_(-999) , ttFlag_(0), TCCid_(0), TowerInTCC_(0), strip_(0), time_(-999)
  {
    for (int i=0 ; i<5 ; i ++) {
      tpgEmul_[i] = 0 ;
      tpgEmulFlag_[i]=0;
      tpgEmulsFGVB_[i]=0;
    }
  }
};



class ETTAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {


public:
  explicit ETTAnalyzer(const edm::ParameterSet&);
  
  ~ETTAnalyzer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  void beginRun(edm::Run const& iEvent, edm::EventSetup const&);

  //virtual void beginRun(const edm::Run&, const edm::EventSetup&) override;
  
  edm::ESHandle<EcalTrigTowerConstituentsMap> eTTmap_;
  edm::EDGetTokenT<GlobalAlgBlkBxCollection> l1tStage2uGtProducer_; // input tag for L1 uGT DAQ readout record
  edm::EDGetTokenT<l1t::EGammaBxCollection> stage2CaloLayer2EGammaToken_;
  edm::EDGetTokenT<EcalTrigPrimDigiCollection> tpEmulatorCollection_ ;
  edm::EDGetTokenT<EcalTrigPrimDigiCollection> tpCollection_ ;
  edm::EDGetTokenT<EBDigiCollection> EBdigistoken_ ;
  edm::EDGetTokenT<EEDigiCollection> EEdigistoken_ ;
  
  edm::EDGetTokenT<EcalRecHitCollection> EcalRecHitCollectionEB1_  ;
  edm::EDGetTokenT<EcalRecHitCollection> EcalRecHitCollectionEE1_  ;

  const CaloSubdetectorGeometry * theEndcapGeometry_ ;
  const CaloSubdetectorGeometry * theBarrelGeometry_ ;


  std::string monitorDir_;
  
  // To get the algo bits corresponding to algo names
  std::shared_ptr<l1t::L1TGlobalUtil> gtUtil_;
  std::vector<double> egammaPtCuts_;


  
  // not all of the following are needed, clean later on 
  // For the timing histograms
  int algoBitFirstBxInTrain_;
  int algoBitLastBxInTrain_;
  int algoBitIsoBx_;
  const std::string algoNameFirstBxInTrain_;
  const std::string algoNameLastBxInTrain_;
  const std::string algoNameIsoBx_;
  //const unsigned int bxrange_; //this is the out bx range

  unsigned int useAlgoDecision_;
  edm::Service<TFileService> fs;
  int myevt;
  const EcalElectronicsMapping* theMapping_;
  // variables for branches 
  uint runNb ;
  ULong64_t evtNb ;
  uint bxNb ;
  //uint bxGT ;
  ULong64_t orbitNb ;
  uint lumiBlock ;
  double timeStamp ;
  
  uint nbOfActiveTriggers ;
  int activeTriggers[160] ;
  int activeTriggersBX[160] ;  // all triggers from gt even disabled                                                                                                                                      

  uint nbOfActiveTechTriggers ;
  int activeTechTriggers[64] ;
  
  // variables for pulse shape
  uint ndataframe;
  uint nADC;
  int index_df[8064];
  int index_ts[8064];
  int count_ADC[8064];
  int gain_id[8064];
  int tower_eta[8064];
  int tower_phi[8064];
  int xtal_ix[8064];
  int xtal_iy[8064];
  
  
  
  uint nbOfTowers ; //max 4032 EB+EE                                                                                                                                                                      
  int ieta[4032] ;
  int iphi[4032] ;
  int nbOfXtals[4032] ;
  int rawTPData[4032] ;
  int rawTPEmul1[4032] ;
  int rawTPEmul2[4032] ;
  int rawTPEmul3[4032] ;
  int rawTPEmul4[4032] ;
  int rawTPEmul5[4032] ;
  int rawTPEmulttFlag1[4032] ;
  int rawTPEmulttFlag2[4032] ;
  int rawTPEmulttFlag3[4032] ;
  int rawTPEmulttFlag4[4032] ;
  int rawTPEmulttFlag5[4032] ;
  int rawTPEmulsFGVB1[4032] ;
  int rawTPEmulsFGVB2[4032] ;
  int rawTPEmulsFGVB3[4032] ;
  int rawTPEmulsFGVB4[4032] ;
  int rawTPEmulsFGVB5[4032] ;
  float eRec[4032] ;
  int crystNb[4032];
  int sevlv[4032];
  int time[4032];
  int spike[4032] ;
  int twrADC[4032];
  int sFGVB[4032];
  int twrEmulMaxADC[4032];
  int twrEmul3ADC[4032];
  
  int ttFlag[4032];
  int TCCid[4032];
  int TowerInTCC[4032] ;
  int strip[4032];

  Int_t v_nonisocounterm2     ;
  Int_t v_nonisocounterm1     ;
  Int_t v_nonisocounterzero   ;
  Int_t v_nonisocounterp1     ;
  Int_t v_nonisocounterp2     ;

  Int_t v_isocounterm2     ;
  Int_t v_isocounterm1     ;
  Int_t v_isocounterzero   ;
  Int_t v_isocounterp1     ;
  Int_t v_isocounterp2     ;


  Int_t L1preIsoIetam2[10];
  Int_t L1preIsoIetam1[10];
  Int_t L1preIsoIetazero[10];
  Int_t L1preIsoIetap1[10];
  Int_t L1preIsoIetap2[10];

  Int_t L1preNonisoIetam2[10];
  Int_t L1preNonisoIetam1[10];
  Int_t L1preNonisoIetazero[10];
  Int_t L1preNonisoIetap1[10];
  Int_t L1preNonisoIetap2[10];

  Int_t L1preIsoIphim2[10];
  Int_t L1preIsoIphim1[10];
  Int_t L1preIsoIphizero[10];
  Int_t L1preIsoIphip1[10];
  Int_t L1preIsoIphip2[10];

  Int_t L1preNonisoIphim2[10];
  Int_t L1preNonisoIphim1[10];
  Int_t L1preNonisoIphizero[10];
  Int_t L1preNonisoIphip1[10];
  Int_t L1preNonisoIphip2[10];

  Int_t L1preIsoEnergym2[10];
  Int_t L1preIsoEnergym1[10];
  Int_t L1preIsoEnergyzero[10];
  Int_t L1preIsoEnergyp1[10];
  Int_t L1preIsoEnergyp2[10];
  
  Float_t L1preIsoPtm2[10];
  Float_t L1preIsoPtm1[10];
  Float_t L1preIsoPtzero[10];
  Float_t L1preIsoPtp1[10];
  Float_t L1preIsoPtp2[10];

  Int_t L1preNonisoEnergym2[10];
  Int_t L1preNonisoEnergym1[10];
  Int_t L1preNonisoEnergyzero[10];
  Int_t L1preNonisoEnergyp1[10];
  Int_t L1preNonisoEnergyp2[10];

  Float_t L1preNonisoPtm2[10];
  Float_t L1preNonisoPtm1[10];
  Float_t L1preNonisoPtzero[10];
  Float_t L1preNonisoPtp1[10];
  Float_t L1preNonisoPtp2[10];

  // Define histograms 
  TH2F* ibx_vs_ieta_Iso;
  TH2F* ibx_vs_ieta_NonIso;
  TTree *ETTAnalyzerTree;

  
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

ETTAnalyzer::ETTAnalyzer(const edm::ParameterSet& ps)
  :

  l1tStage2uGtProducer_(consumes<GlobalAlgBlkBxCollection>(ps.getParameter<edm::InputTag>("ugtProducer"))),
  stage2CaloLayer2EGammaToken_(consumes<l1t::EGammaBxCollection>(ps.getParameter<edm::InputTag>("stage2CaloLayer2EGammaProducer"))),
  tpEmulatorCollection_(consumes<EcalTrigPrimDigiCollection>(ps.getParameter<edm::InputTag>("TPEmulatorCollection"))),
  tpCollection_(consumes<EcalTrigPrimDigiCollection>(ps.getParameter<edm::InputTag>("TPCollection"))),
  EBdigistoken_(consumes<EBDigiCollection>(ps.getParameter<edm::InputTag>("EBdigis") )  ),
  EEdigistoken_(consumes<EEDigiCollection>(ps.getParameter<edm::InputTag>("EEdigis") )  ),    
  gtUtil_(new l1t::L1TGlobalUtil(ps, consumesCollector(), *this, ps.getParameter<edm::InputTag>("ugtProducer"), ps.getParameter<edm::InputTag>("ugtProducer"))),
  
  algoBitFirstBxInTrain_(-1),
  algoBitLastBxInTrain_(-1),  
  algoBitIsoBx_(-1),
  algoNameFirstBxInTrain_(ps.getUntrackedParameter<std::string>("firstBXInTrainAlgo","")),
  algoNameLastBxInTrain_(ps.getUntrackedParameter<std::string>("lastBXInTrainAlgo","")),
  algoNameIsoBx_(ps.getUntrackedParameter<std::string>("isoBXAlgo",""))
  
  /*
  l1tStage2uGtProducer_(consumes<GlobalAlgBlkBxCollection>(ps.getParameter<edm::InputTag>("ugtProducer"))),
  stage2CaloLayer2EGammaToken_(consumes<l1t::EGammaBxCollection>(ps.getParameter<edm::InputTag>("stage2CaloLayer2EGammaProducer"))),
  tpEmulatorCollection_(consumes<EcalTrigPrimDigiCollection>(ps.getParameter<edm::InputTag>("TPEmulatorCollection"))),
  tpCollection_(consumes<EcalTrigPrimDigiCollection>(ps.getParameter<edm::InputTag>("TPCollection"))),
  EBdigistoken_(consumes<EBDigiCollection>(ps.getParameter<edm::InputTag>("EBdigis") )  ),
  EEdigistoken_(consumes<EEDigiCollection>(ps.getParameter<edm::InputTag>("EEdigis") )  )
  */

{
  EcalRecHitCollectionEB1_ = consumes<EcalRecHitCollection>( ps.getParameter<edm::InputTag>("EcalRecHitCollectionEB") );
  EcalRecHitCollectionEE1_ = consumes<EcalRecHitCollection>( ps.getParameter<edm::InputTag>("EcalRecHitCollectionEE") );


  
  
  useAlgoDecision_ = 0;
  /*
  if (ps.getUntrackedParameter<std::string>("useAlgoDecision").find("final") == 0) {
    useAlgoDecision_ = 2;
  } else if (ps.getUntrackedParameter<std::string>("useAlgoDecision").find("intermediate") == 0) {
    useAlgoDecision_ = 1;
  } else {
    useAlgoDecision_ = 0;
  }
  */
  egammaPtCuts_.clear();
  egammaPtCuts_.push_back(10.0);
  //egammaPtCuts_.push_back(20.0);
  //egammaPtCuts_.push_back(30.0);

  
  //ibx_vs_ieta_Iso = new TH2F("ibx_vs_ieta_Iso","ibx_vs_ieta_Iso", 5, -2.5, 2.5, 70, -70, 70);
  //ibx_vs_ieta_NonIso = new TH2F("ibx_vs_ieta_NonIso","ibx_vs_ieta_NonIso", 5, -2.5, 2.5, 70, -70, 70);
  ETTAnalyzerTree = fs->make<TTree>("ETTAnalyzerTree","A ROOT tree to save information to understand prefiring");

  ibx_vs_ieta_Iso = fs->make<TH2F>("ibx_vs_ieta_Iso","ibx_vs_ieta_Iso", 5, -2.5, 2.5, 70, -70, 70);
  ibx_vs_ieta_NonIso = fs->make<TH2F>("ibx_vs_ieta_NonIso","ibx_vs_ieta_NonIso", 5, -2.5, 2.5, 70, -70, 70);


  ETTAnalyzerTree->Branch("runNb", &runNb ,"runNb/i");
  ETTAnalyzerTree->Branch("evtNb", &evtNb ,"evtNb/L");
  ETTAnalyzerTree->Branch("bxNb", &bxNb ,"bxNb/i");
  //ETTAnalyzerTree->Branch("b_bxGT", &bxGT ,"b_bxGT/i");
  ETTAnalyzerTree->Branch("orbitNb", &orbitNb ,"orbitNb/L");
  ETTAnalyzerTree->Branch("lumiBlock", &lumiBlock ,"lumiBlock/i");
  ETTAnalyzerTree->Branch("timeStamp", &timeStamp ,"timeStamp/i");
  
  // ADC counts for 10 samples when there is some significant energy deposit. 
  ETTAnalyzerTree->Branch("ndataframe", &ndataframe ,"ndataframe/i");
  ETTAnalyzerTree->Branch("nADC", &nADC ,"nADC/i");
  ETTAnalyzerTree->Branch("index_df", index_df,"index_df[nADC]/I");
  ETTAnalyzerTree->Branch("index_ts", index_ts,"index_ts[nADC]/I");
  ETTAnalyzerTree->Branch("count_ADC", count_ADC,"count_ADC[nADC]/I");
  ETTAnalyzerTree->Branch("gain_id", gain_id,"gain_id[nADC]/I");

  ETTAnalyzerTree->Branch("tower_eta",tower_eta ,"tower_eta[nADC]/I");
  ETTAnalyzerTree->Branch("tower_phi",tower_phi ,"tower_phi[nADC]/I");
  ETTAnalyzerTree->Branch("xtal_ix", xtal_ix,"xtal_ix[nADC]/I");
  ETTAnalyzerTree->Branch("xtal_iy", xtal_iy,"xtal_iy[nADC]/I");
  
  ETTAnalyzerTree->Branch("nbOfTowers",&nbOfTowers, "nbOfTowers/i");
  ETTAnalyzerTree->Branch("ieta", ieta ,"ieta[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("iphi", iphi ,"iphi[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("nbOfXtals", nbOfXtals ,"nbOfXtals[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPData", rawTPData ,"rawTPData[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmul1", rawTPEmul1  ,"rawTPEmul1[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmul2", rawTPEmul2 ,"rawTPEmul2[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmul3", rawTPEmul3 ,"rawTPEmul3[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmul4", rawTPEmul4 ,"rawTPEmul4[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmul5", rawTPEmul5 ,"rawTPEmul5[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmulttFlag1", rawTPEmulttFlag1 ,"rawTPEmulttFlag1[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmulttFlag2", rawTPEmulttFlag2 ,"rawTPEmulttFlag2[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmulttFlag3", rawTPEmulttFlag3 ,"rawTPEmulttFlag3[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmulttFlag4", rawTPEmulttFlag4 ,"rawTPEmulttFlag4[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmulttFlag5", rawTPEmulttFlag5 ,"rawTPEmulttFlag5[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmulsFGVB1", rawTPEmulsFGVB1 ,"rawTPEmulsFGVB1[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmulsFGVB2", rawTPEmulsFGVB2 ,"rawTPEmulsFGVB2[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmulsFGVB3", rawTPEmulsFGVB3 ,"rawTPEmulsFGVB3[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmulsFGVB4", rawTPEmulsFGVB4 ,"rawTPEmulsFGVB4[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmulsFGVB5", rawTPEmulsFGVB5 ,"rawTPEmulsFGVB5[nbOfTowers]/I");

  // Want to save all Rec Hits (all XTALS)
  


  // ETTAnalyzerTree->Branch("eRec", eRec ,"eRec[nbOfTowers][25]/I"); // Max of 25 xtals per TT 
  ETTAnalyzerTree->Branch("crystNb", crystNb ,"crystNb[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("sevlv", sevlv ,"sevlv[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("time", time ,"time[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("spike", spike ,"spike[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("twrADC", twrADC ,"twrADC[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("sFGVB", sFGVB ,"sFGVB[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("ttFlag", ttFlag ,"ttFlag[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("TCCid", TCCid ,"TCCid[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("TowerInTCC", TowerInTCC ,"TowerInTCC[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("strip", strip ,"strip[nbOfTowers]/I");
  
  ETTAnalyzerTree->Branch("twrEmulMaxADC", twrEmulMaxADC ,"twrEmulMaxADC[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("twrEmul3ADC", twrEmul3ADC ,"twrEmul3ADC[nbOfTowers]/I");
  
  //counters 
  ETTAnalyzerTree->Branch("nonisocounterm2", &v_nonisocounterm2, "nonisocounterm2/I");
  ETTAnalyzerTree->Branch("nonisocounterm1", &v_nonisocounterm1, "nonisocounterm1/I");
  ETTAnalyzerTree->Branch("nonisocounterzero", &v_nonisocounterzero, "nonisocounterzero/I");
  ETTAnalyzerTree->Branch("nonisocounterp1", &v_nonisocounterp1, "nonisocounterp1/I");
  ETTAnalyzerTree->Branch("nonisocounterp2", &v_nonisocounterp2, "nonisocounterp2/I");

  ETTAnalyzerTree->Branch("isocounterm2", &v_isocounterm2, "isocounterm2/I");
  ETTAnalyzerTree->Branch("isocounterm1", &v_isocounterm1, "isocounterm1/I");
  ETTAnalyzerTree->Branch("isocounterzero", &v_isocounterzero, "isocounterzero/I");
  ETTAnalyzerTree->Branch("isocounterp1", &v_isocounterp1, "isocounterp1/I");
  ETTAnalyzerTree->Branch("isocounterp2", &v_isocounterp2, "isocounterp2/I");
  
  // isolated 
  ETTAnalyzerTree->Branch("L1preIsoIetam2", L1preIsoIetam2 , "L1preIsoIetam2[isocounterm2]/I");
  ETTAnalyzerTree->Branch("L1preIsoIetam1", L1preIsoIetam1 , "L1preIsoIetam1[isocounterm1]/I");
  ETTAnalyzerTree->Branch("L1preIsoIetazero", L1preIsoIetazero , "L1preIsoIetazero[isocounterzero]/I");
  ETTAnalyzerTree->Branch("L1preIsoIetap1", L1preIsoIetap1 , "L1preIsoIetap1[isocounterp1]/I");
  ETTAnalyzerTree->Branch("L1preIsoIetap2", L1preIsoIetap2 , "L1preIsoIetap2[isocounterp2]/I");


  ETTAnalyzerTree->Branch("L1preIsoIphim2", L1preIsoIphim2 , "L1preIsoIphim2[isocounterm2]/I");
  ETTAnalyzerTree->Branch("L1preIsoIphim1", L1preIsoIphim1 , "L1preIsoIphim1[isocounterm1]/I");
  ETTAnalyzerTree->Branch("L1preIsoIphizero", L1preIsoIphizero , "L1preIsoIphizero[isocounterzero]/I");
  ETTAnalyzerTree->Branch("L1preIsoIphip1", L1preIsoIphip1 , "L1preIsoIphip1[isocounterp1]/I");
  ETTAnalyzerTree->Branch("L1preIsoIphip2", L1preIsoIphip2 , "L1preIsoIphip2[isocounterp2]/I");

  ETTAnalyzerTree->Branch("L1preIsoEnergym2", L1preIsoEnergym2 , "L1preIsoEnergym2[isocounterm2]/I");
  ETTAnalyzerTree->Branch("L1preIsoEnergym1", L1preIsoEnergym1 , "L1preIsoEnergym1[isocounterm1]/I");
  ETTAnalyzerTree->Branch("L1preIsoEnergyzero", L1preIsoEnergyzero , "L1preIsoEnergyzero[isocounterzero]/I");
  ETTAnalyzerTree->Branch("L1preIsoEnergyp1", L1preIsoEnergyp1 , "L1preIsoEnergyp1[isocounterp1]/I");
  ETTAnalyzerTree->Branch("L1preIsoEnergyp2", L1preIsoEnergyp2 , "L1preIsoEnergyp2[isocounterp2]/I");

  ETTAnalyzerTree->Branch("L1preIsoPtm2", L1preIsoPtm2 , "L1preIsoPtm2[isocounterm2]/F");
  ETTAnalyzerTree->Branch("L1preIsoPtm1", L1preIsoPtm1 , "L1preIsoPtm1[isocounterm1]/F");
  ETTAnalyzerTree->Branch("L1preIsoPtzero", L1preIsoPtzero , "L1preIsoPtzero[isocounterzero]/F");
  ETTAnalyzerTree->Branch("L1preIsoPtp1", L1preIsoPtp1 , "L1preIsoPtp1[isocounterp1]/F");
  ETTAnalyzerTree->Branch("L1preIsoPtp2", L1preIsoPtp2 , "L1preIsoPtp2[isocounterp2]/F");


  // non isolated 
  ETTAnalyzerTree->Branch("L1preNonisoIetam2", L1preNonisoIetam2 , "L1preNonisoIetam2[nonisocounterm2]/I");
  ETTAnalyzerTree->Branch("L1preNonisoIetam1", L1preNonisoIetam1 , "L1preNonisoIetam1[nonisocounterm1]/I");
  ETTAnalyzerTree->Branch("L1preNonisoIetazero", L1preNonisoIetazero , "L1preNonisoIetazero[nonisocounterzero]/I");
  ETTAnalyzerTree->Branch("L1preNonisoIetap1", L1preNonisoIetap1 , "L1preNonisoIetap1[nonisocounterp1]/I");
  ETTAnalyzerTree->Branch("L1preNonisoIetap2", L1preNonisoIetap2 , "L1preNonisoIetap2[nonisocounterp2]/I");

  ETTAnalyzerTree->Branch("L1preNonisoIphim2", L1preNonisoIphim2 , "L1preNonisoIphim2[nonisocounterm2]/I");
  ETTAnalyzerTree->Branch("L1preNonisoIphim1", L1preNonisoIphim1 , "L1preNonisoIphim1[nonisocounterm1]/I");
  ETTAnalyzerTree->Branch("L1preNonisoIphizero", L1preNonisoIphizero , "L1preNonisoIphizero[nonisocounterzero]/I");
  ETTAnalyzerTree->Branch("L1preNonisoIphip1", L1preNonisoIphip1 , "L1preNonisoIphip1[nonisocounterp1]/I");
  ETTAnalyzerTree->Branch("L1preNonisoIphip2", L1preNonisoIphip2 , "L1preNonisoIphip2[nonisocounterp2]/I");


  ETTAnalyzerTree->Branch("L1preNonisoEnergym2", L1preNonisoEnergym2 , "L1preNonisoEnergym2[nonisocounterm2]/I");
  ETTAnalyzerTree->Branch("L1preNonisoEnergym1", L1preNonisoEnergym1 , "L1preNonisoEnergym1[nonisocounterm2]/I");
  ETTAnalyzerTree->Branch("L1preNonisoEnergyzero", L1preNonisoEnergyzero , "L1preNonisoEnergyzero[nonisocounterzero]/I");
  ETTAnalyzerTree->Branch("L1preNonisoEnergyp1", L1preNonisoEnergyp1 , "L1preNonisoEnergyp1[nonisocounterp1]/I");
  ETTAnalyzerTree->Branch("L1preNonisoEnergyp2", L1preNonisoEnergyp2 , "L1preNonisoEnergyp2[nonisocounterp2]/I");

  ETTAnalyzerTree->Branch("L1preNonisoPtm2", L1preNonisoPtm2 , "L1preNonisoPtm2[nonisocounterm2]/F");
  ETTAnalyzerTree->Branch("L1preNonisoPtm1", L1preNonisoPtm1 , "L1preNonisoPtm1[nonisocounterm2]/F");
  ETTAnalyzerTree->Branch("L1preNonisoPtzero", L1preNonisoPtzero , "L1preNonisoPtzero[nonisocounterzero]/F");
  ETTAnalyzerTree->Branch("L1preNonisoPtp1", L1preNonisoPtp1 , "L1preNonisoPtp1[nonisocounterp1]/F");
  ETTAnalyzerTree->Branch("L1preNonisoPtp2", L1preNonisoPtp2 , "L1preNonisoPtp2[nonisocounterp2]/F");
  
  

  //ETTAnalyzerTree->Branch("b_",  ,"b_[nbOfTowers]/I");
}


ETTAnalyzer::~ETTAnalyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
ETTAnalyzer::analyze(const edm::Event& e, const edm::EventSetup& c)
{
   using namespace edm;
   myevt++;

   ESHandle< EcalElectronicsMapping > ecalmapping;
   c.get< EcalMappingRcd >().get(ecalmapping);
   theMapping_ = ecalmapping.product();
   
   
   
   for (int i=0; i<4032;i++){
     count_ADC[i] = -999;
     gain_id[i] = -999;
     index_df[i] = -999;
     index_ts[i] = -999;
     tower_eta[i] = -999;
     tower_phi[i] = -999;
     xtal_ix[i] = -999;
     xtal_iy[i] = -999;
   }
   for (int i=0; i<10; i++){
     L1preIsoIetam2[i] = -999;
     L1preIsoIetam1[i] = -999;
     L1preIsoIetazero[i] = -999;
     L1preIsoIetap1[i] = -999;
     L1preIsoIetap2[i] = -999;
     
     L1preNonisoIetam2[i] = -999;
     L1preNonisoIetam1[i] = -999;
     L1preNonisoIetazero[i] = -999;
     L1preNonisoIetap1[i] = -999;
     L1preNonisoIetap2[i] = -999;
     
     L1preIsoIphim2[i] = -999;
     L1preIsoIphim1[i] = -999;
     L1preIsoIphizero[i] = -999;
     L1preIsoIphip1[i] = -999;
     L1preIsoIphip2[i] = -999;
     
     L1preNonisoIphim2[i] = -999;
     L1preNonisoIphim1[i] = -999;
     L1preNonisoIphizero[i] = -999;
     L1preNonisoIphip1[i] = -999;
     L1preNonisoIphip2[i] = -999;
     
     L1preIsoEnergym2[i] = -999;
     L1preIsoEnergym1[i] = -999;
     L1preIsoEnergyzero[i] = -999;
     L1preIsoEnergyp1[i] = -999;
     L1preIsoEnergyp2[i] = -999;

     L1preNonisoEnergym2[i] = -999;
     L1preNonisoEnergym1[i] = -999;
     L1preNonisoEnergyzero[i] = -999;
     L1preNonisoEnergyp1[i] = -999;
     L1preNonisoEnergyp2[i] = -999;

   
     L1preIsoPtm2[i] = -999;
     L1preIsoPtm1[i] = -999;
     L1preIsoPtzero[i] = -999;
     L1preIsoPtp1[i] = -999;
     L1preIsoPtp2[i] = -999;

     L1preNonisoPtm2[i] = -999;
     L1preNonisoPtm1[i] = -999;
     L1preNonisoPtzero[i] = -999;
     L1preNonisoPtp1[i] = -999;
     L1preNonisoPtp2[i] = -999;

   }
   v_nonisocounterm2     = 0 ;
   v_nonisocounterm1     = 0 ;
   v_nonisocounterzero   = 0 ;
   v_nonisocounterp1     = 0 ;
   v_nonisocounterp2     = 0 ;
   
   v_isocounterm2     = 0 ;
   v_isocounterm1     = 0 ;
   v_isocounterzero   = 0 ;
   v_isocounterp1     = 0 ;
   v_isocounterp2     = 0 ;


   
   
   // ------------------------------*----------------*-------------**********--------------------------------------------------------------------------------------------
   // ------------------------------*--------------*-*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------*----------------*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------*----------------*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------*----------------*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------*----------------*------------------*------------------------------------------------------------------------------------------------
   // ------------------------------**********------***-----------------*------------------------------------------------------------------------------------------------

   
   
   // Open uGT readout record
   edm::Handle<GlobalAlgBlkBxCollection> uGtAlgs;
   e.getByToken(l1tStage2uGtProducer_, uGtAlgs);
   

   
   // EGamma Collection
   edm::Handle<l1t::EGammaBxCollection> EGammaBxCollection;
   e.getByToken(stage2CaloLayer2EGammaToken_, EGammaBxCollection);

   
     
   
   // Find out in which BX the first collision in train, isolated bunch, and last collision in train have fired.
   // In case of pre firing it will be in BX 1 or BX 2 and this will determine the BX shift that
   // will be applied to the timing histogram later.
   int bxShiftFirst = -999;
   int bxShiftIso = -999;
   int bxShiftLast = -999;
   for (int bx = uGtAlgs->getFirstBX(); bx <= uGtAlgs->getLastBX(); ++bx) {
     for (GlobalAlgBlkBxCollection::const_iterator itr = uGtAlgs->begin(bx); itr != uGtAlgs->end(bx); ++itr) {
       // first bunch in train
       if (algoBitFirstBxInTrain_ != -1) {
	 bool bit = false;
	 switch (useAlgoDecision_) {
	 case 0:
	   bit = itr->getAlgoDecisionInitial(algoBitFirstBxInTrain_);
	   break;
	 case 1:
	   bit = itr->getAlgoDecisionInterm(algoBitFirstBxInTrain_);
	   break;
	 case 2:
	   bit = itr->getAlgoDecisionFinal(algoBitFirstBxInTrain_);
	   break;
	 }
	 if (bit) {
	   bxShiftFirst = bx;
	 }
       }
       // last bunch in train
       if(algoBitLastBxInTrain_ != -1) {
	 bool bit = false;
	 switch (useAlgoDecision_) {
	 case 0:
	   bit = itr->getAlgoDecisionInitial(algoBitLastBxInTrain_);
	   break;
	 case 1:
	   bit = itr->getAlgoDecisionInterm(algoBitLastBxInTrain_);
	   break;
	 case 2:
	   bit = itr->getAlgoDecisionFinal(algoBitLastBxInTrain_);
	   break;
	 }
	 if (bit) {
	   ;//bxShiftLast = bx;
	 }
       }
       // isolated bunch
       if (algoBitIsoBx_ != -1) {
	 bool bit = false;
	 switch (useAlgoDecision_) {
	 case 0:
	   bit = itr->getAlgoDecisionInitial(algoBitIsoBx_);
	   break;
	 case 1:
	   bit = itr->getAlgoDecisionInterm(algoBitIsoBx_);
	   break;
	 case 2:
	   bit = itr->getAlgoDecisionFinal(algoBitIsoBx_);
	   break;
	 }
	 if (bit) {
	   ;//bxShiftIso = bx;
	 }
       }
     }
   }
   
   
   
   //std::cout<<" bxShiftFirst = " << bxShiftFirst<< " "<<bxShiftIso<< " "<<bxShiftLast<<std::endl;
   
   // the following shifting is needed for following reason: 
   // we want to use only those events which comes as a result of the begining of the bunch train, each bunch train can have crossings multiple times. 
   // if the egamma triggering happended one bx before the begining of bunch train i.e. egamma trigger pre-fired then we need to correct for this effect. 
   // The data is written only once, for all the five bunch crossings. if the egamma trigger was prefired then (-1 bx) then everything needs to be translated. 
   
   
   
   int nonisocounterm2    = 0 ;
   int nonisocounterm1    = 0 ;
   int nonisocounterzero  = 0 ;
   int nonisocounterp1    = 0 ;
   int nonisocounterp2    = 0 ;

   int isocounterm2    = 0 ;
   int isocounterm1    = 0 ;
   int isocounterzero  = 0 ;
   int isocounterp1    = 0 ;
   int isocounterp2    = 0 ;
   
   
   

   
   for (int itBX = std::max(EGammaBxCollection->getFirstBX(), EGammaBxCollection->getFirstBX() + bxShiftFirst); itBX <= std::min(EGammaBxCollection->getLastBX(), EGammaBxCollection->getLastBX() + bxShiftFirst); ++itBX) {
     std::cout<<"inside itBx" <<std::endl;
     

     //int index = itBX - bxShiftFirst - uGtAlgs->getFirstBX();
     for (l1t::EGammaBxCollection::const_iterator egamma = EGammaBxCollection->begin(itBX); egamma != EGammaBxCollection->end(itBX); ++egamma) {
       std::cout<<"inside egamma" <<std::endl;
       
       
       for (size_t i = 0; i < egammaPtCuts_.size(); ++i) {
	 std::cout<<" for pt cut "<<egammaPtCuts_[i]<<"  "<<egamma->pt() << std::endl;
	 if (egamma->pt() >= egammaPtCuts_.at(i)) {
	   //if (index >= 0 and index < (int)egamma_eta_phi_firstbunch.size()) {
	   //denominator_egamma_firstbunch.at(i)->Fill(egamma->eta(), egamma->phi());
	   //egamma_eta_phi_firstbunch.at(i).at(index)->Fill(egamma->eta(), egamma->phi());
	   //}
	   
	   int bxNumberActual = itBX - bxShiftFirst;
	  	   
	   
	   std::cout<<" all candidates egamma->pt, egamma->hwPt, egamma->energy, egamma->hwEta, egamma->hwPhi ="<<egamma->pt()<<" "<<egamma->hwPt()<<"  "<<egamma->energy()<<"  "<<egamma->hwEta()<<"  "<<egamma->hwPhi()<<std::endl;
	   
	   if ((bool)egamma->hwIso()) {
	     std::cout<<" isolated bx, eta, counter "<<itBX - bxShiftFirst<<"  "<< egamma->hwEta()<<"  "<<isocounterp2<<std::endl;
	     ibx_vs_ieta_Iso->Fill(itBX - bxShiftFirst, egamma->hwEta() );

	     // see the description of variables at the twiki 
	     //https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideL1TCaloFormats 
	     
	     if (bxNumberActual == -2){ 
	       L1preIsoIetam2[isocounterm2] = egamma->hwEta();
	       L1preIsoIphim2[isocounterm2] = egamma->hwPhi();
	       L1preIsoPtm2[isocounterm2] = egamma->pt();
	       L1preIsoEnergym2[isocounterm2] = egamma->energy();
	       isocounterm2++;
	     }
	     if (bxNumberActual == -1){ 
	       L1preIsoIetam1[isocounterm1] = egamma->hwEta();
	       L1preIsoIphim1[isocounterm1] = egamma->hwPhi();
	       L1preIsoPtm1[isocounterm1]   = egamma->pt();
	       L1preIsoEnergym1[isocounterm1] = egamma->energy();
	       isocounterm1++;
	     }
	     if (bxNumberActual ==  0){ 
	       L1preIsoIetazero[isocounterzero] = egamma->hwEta();
	       L1preIsoIphizero[isocounterzero] = egamma->hwPhi();
	       L1preIsoPtzero[isocounterzero]   = egamma->pt();
	       L1preIsoEnergyzero[isocounterzero] = egamma->energy();
	       isocounterzero++;
	     }
	     if (bxNumberActual ==  1){ 
	       L1preIsoIetap1[isocounterp1] = egamma->hwEta();
	       L1preIsoIphip1[isocounterp1] = egamma->hwPhi();
	       L1preIsoEnergyp1[isocounterp1] = egamma->energy();
	       isocounterp1++;
	     }
	     if (bxNumberActual ==  2){
	       L1preIsoIetap2[isocounterp2] = egamma->hwEta();
	       L1preIsoIphip2[isocounterp2] = egamma->hwPhi();
	       L1preIsoPtp2[isocounterp2]   = egamma->pt();
	       L1preIsoEnergyp2[isocounterp2] = egamma->energy();
	       isocounterp2++;
	     }
	   }// end of  if ((bool)egamma->hwIso()) {
	 

	   // ----------------------------------------------------------
	   // -------- non-isolated branches starts from here. ---------
	   // ----------------------------------------------------------
	   ibx_vs_ieta_NonIso->Fill(itBX - bxShiftFirst, egamma->hwEta());

	   std::cout<<" eta and hweta "<<egamma->hwEta() <<" "<<egamma->eta() <<std::endl;
	   
	   // non-isolated 
	   if (bxNumberActual == -2){ 
	     L1preNonisoIetam2[nonisocounterm2] = egamma->hwEta();
     	     L1preNonisoIphim2[nonisocounterm2] = egamma->hwPhi();
	     L1preNonisoPtm2[nonisocounterm2]   = egamma->pt();
	     L1preNonisoEnergym2[nonisocounterm2] = egamma->energy();
	     nonisocounterm2++;
	   }
	   if (bxNumberActual == -1){ 
	     L1preNonisoIetam1[nonisocounterm1] = egamma->hwEta();
	     L1preNonisoIphim1[nonisocounterm1] = egamma->hwPhi();
	     L1preNonisoPtm1[nonisocounterm1]   = egamma->pt();
	     L1preNonisoEnergym1[nonisocounterm1] = egamma->energy();
	     nonisocounterm1++;
	   }
	   if (bxNumberActual ==  0){ 
	     L1preNonisoIetazero[nonisocounterzero] = egamma->hwEta();
	     L1preNonisoIphizero[nonisocounterzero] = egamma->hwPhi();
	     L1preNonisoPtzero[nonisocounterzero]   = egamma->pt();
	     L1preNonisoEnergyzero[nonisocounterzero] = egamma->energy();
	       nonisocounterzero++;
	   }
	   if (bxNumberActual ==  1){ 
	     L1preNonisoIetap1[nonisocounterp1] = egamma->hwEta();
	     L1preNonisoIphip1[nonisocounterp1] = egamma->hwPhi();
	     L1preNonisoPtp1[nonisocounterp1]   = egamma->pt();
	     L1preNonisoEnergyp1[nonisocounterp1] = egamma->energy();
	     nonisocounterp1++;
	   }
	   if (bxNumberActual ==  2){
	     L1preNonisoIetap2[nonisocounterp2] = egamma->hwEta();
	     L1preNonisoIphip2[nonisocounterp2] = egamma->hwPhi();
	     L1preNonisoPtp2[nonisocounterp2]   = egamma->pt();
	     L1preNonisoEnergyp2[nonisocounterp2] = egamma->energy();
	     nonisocounterp2++;
	   }

	   // fill all counters 
	   
	   v_nonisocounterm2  = nonisocounterm2    ;    
	   v_nonisocounterm1  = nonisocounterm1    ; 
	   v_nonisocounterzero  = nonisocounterzero; 
	   v_nonisocounterp1  = nonisocounterp1    ; 
	   v_nonisocounterp2  = nonisocounterp2    ; 

	   v_isocounterm2     = isocounterm2       ;
	   v_isocounterm1     = isocounterm1       ;
	   v_isocounterzero   = isocounterzero     ;
	   v_isocounterp1     = isocounterp1       ;
	   v_isocounterp2     = isocounterp2       ;

	   
	   	   
	 }
       }
     }
   }
   
   
   // for the last bunch crossing 
   /*


   for (int itBX = std::max(EGammaBxCollection->getFirstBX(), EGammaBxCollection->getFirstBX() + bxShiftLast); itBX <= std::min(EGammaBxCollection->getLastBX(), EGammaBxCollection->getLastBX() + bxShiftLast); ++itBX) {
     std::cout<<"inside itBx" <<std::endl;
     auto correctedBx = itBX - bxShiftLast;
     for (l1t::EGammaBxCollection::const_iterator egamma = EGammaBxCollection->begin(itBX); egamma != EGammaBxCollection->end(itBX); ++egamma) {
       std::cout<<"inside egamma" <<std::endl;
       for (size_t i = 0; i < egammaPtCuts_.size(); ++i) {
	 if (egamma->pt() >= egammaPtCuts_.at(i)) {
	   //if (correctedBx >= 0 and correctedBx < (int)egamma_eta_phi_lastbunch.size()) {
	     //denominator_egamma_lastbunch.at(i)->Fill(egamma->eta(), egamma->phi());
	     //egamma_eta_phi_lastbunch.at(i).at(correctedBx)->Fill(egamma->eta(), egamma->phi());
	   //}
	   if ((bool)egamma->hwIso()) {
	     std::cout<<" isolated "<<correctedBx<<"  "<< egamma->hwEta()<<std::endl;
	     //egamma_iso_bx_ieta_lastbunch.at(i)->Fill(correctedBx, egamma->hwEta());
	   }
	   //egamma_noniso_bx_ieta_lastbunch.at(i)->Fill(correctedBx, egamma->hwEta());
	   std::cout<<" non-isolated "<<correctedBx<<"  "<< egamma->hwEta()<<std::endl;
	   
	 }
       }
     }
   }

   */


   
   // ------------------------------------------**********----------***-------------------------------------------------------------------------
   // -----------------------------------------------*--------------*--***----------------------------------------------------------------------
   // -----------------------------------------------*--------------*----**---------------------------------------------------------------------
   // -----------------------------------------------*--------------*--***----------------------------------------------------------------------
   // -----------------------------------------------*--------------***-------------------------------------------------------------------------
   // -----------------------------------------------*--------------*---------------------------------------------------------------------------
   // -----------------------------------------------*--------------*---------------------------------------------------------------------------

   // ---------------------------------
   // event information 
   // ---------------------------------
   runNb = e.id().run() ;
   evtNb = e.id().event() ;
   bxNb = e.bunchCrossing() ;
   orbitNb = e.orbitNumber() ;
   lumiBlock = e.luminosityBlock();
   
   float startTime_ = 1461466500; //                                                                                                                                                                               
   unsigned int  timeStampLow = ( 0xFFFFFFFF & e.time().value() );
   unsigned int  timeStampHigh = ( e.time().value() >> 32 );

   double rawEventTime = ( double)(timeStampHigh)+((double )(timeStampLow)/1000000.);
   double eventTime = rawEventTime - startTime_; //Notice the subtraction of the "starttime"
   
   timeStamp =  eventTime;

   
   
   // -------------------------------
   //  TT information 
   // -------------------------------
   
   edm::Handle<EcalTrigPrimDigiCollection> tp; // Different from TP info in the trigger path? Is TP info from the trigger path saved at all? 
   e.getByToken(tpCollection_,tp);
   //std::cout<<"TP collection size="<<tp.product()->size()<<std::endl ;
   
   map<EcalTrigTowerDetId, towerEner>::iterator itTT ;
   map<EcalTrigTowerDetId, towerEner> mapTower ;

   
   edm::Handle<EEDigiCollection>  EEdigis;
   e.getByToken(EEdigistoken_,EEdigis);
   if(not e.getByToken(EEdigistoken_,EEdigis)){
     std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: EEdigistoken_ "<<std::endl;
     exit(0);
   }

   int j=0;
   int countNadc=0;
   c.get<IdealGeometryRecord>().get(eTTmap_);

   
   for ( EEDigiCollection::const_iterator hitItr = EEdigis->begin(); hitItr != EEdigis->end(); ++hitItr ) {
     EEDataFrame df(*hitItr);
     const EEDetId & id = df.id();
     const EcalTrigTowerDetId towid = (*eTTmap_).towerOf(id);
     
     // testing 
     const EcalTriggerElectronicsId elId = theMapping_->getTriggerElectronicsId(df.id());
     uint32_t stripid = elId.rawId() & 0xfffffff8;  // from Pascal
     //std::cout<<" strip id : "<<stripid<<std::endl;

     


     
     for(int i=0; i<10;++i){
       //std::cout<<" tower (eta, phi): ("<<towid.ieta() << ", "<<towid.iphi()<<")"
       //     <<" xtal (ix, iy): ("<<id.ix() <<", "<<id.iy()<<")"
       //     <<" ADC for EEDataFrame: "<<j << "  sample number "<<i<<"  "<<df.sample(i).adc()<<std::endl;
     
     tower_eta[countNadc] = towid.ieta();
     tower_phi[countNadc] = towid.iphi();
     xtal_ix[countNadc] = id.ix();
     xtal_iy[countNadc] = id.iy();
     
     index_df[countNadc] = j;
     index_ts[countNadc] = i;
     count_ADC[countNadc] = df.sample(i).adc();
     gain_id[countNadc]    = df.sample(i).gainId();
       
     countNadc++;
     
     }
     j++;
     
   }
   
   ndataframe = j;
   nADC       = countNadc;
   
   
   // pulseshape setup ends here 


   for (unsigned int i=0;i<tp.product()->size();i++) {
     EcalTriggerPrimitiveDigi d = (*(tp.product()))[i];
     const EcalTrigTowerDetId TPtowid= d.id();
     towerEner tE ;
     
     // suggested by David 
     // follow from https://github.com/cms-ecal-L1TriggerTeam/CMS-ECAL_TPGAnalysis/blob/master/TriggerAnalysis/plugins/EcalTPGAnalyzer.cc#L845
     tE.TCCid_= theMapping_->TCCid(TPtowid);                                                                                                                                                           
     tE.TowerInTCC_ = theMapping_->iTT(TPtowid);                                                                                                                                                       
     //const EcalTriggerElectronicsId elId = theMapping_->getTriggerElectronicsId(id) ;                                                                                                            
     //tE.strip_ = 0;//elId.pseudoStripId() ;                                                                                                                                                            
     
     tE.iphi_ = TPtowid.iphi() ;
     tE.ieta_ = TPtowid.ieta() ;
     tE.ttFlag_ = d[0].ttFlag();
     tE.tpgADC_ = (d[0].raw()&0xfff) ;
     tE.twrADC = (d[0].raw()&0xff) ;
     tE.sFGVB = (d[0].sFGVB());
     //if ((d[0].raw()&0xfff)>0 ) {std::cout<<" EcalTrigTowerDetId :: filling "<<TPtowid<<" twradc: "<<(d[0].raw()&0xff)<<std::endl;}
     mapTower[TPtowid] = tE ;
   }


   // -------------------------------
   //  emulator information 
   // -------------------------------
   edm::Handle<EcalTrigPrimDigiCollection> tpEmul ;
   e.getByToken(tpEmulatorCollection_, tpEmul);
   
   
   for (unsigned int i=0;i<tpEmul.product()->size();i++) {
     EcalTriggerPrimitiveDigi d = (*(tpEmul.product()))[i];
     const EcalTrigTowerDetId TPtowid= d.id();
     itTT = mapTower.find(TPtowid) ;
     if (itTT != mapTower.end())
       for (int j=0 ; j<5 ; j++) {
        (itTT->second).tpgEmul_[j] = (d[j].raw()&0xfff) ;
        (itTT->second).tpgEmulFlag_[j] = d[j].ttFlag();
        (itTT->second).tpgEmulsFGVB_[j] = d[j].sFGVB();
       }
   }

   


   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // ----------------REC HITS -------------------------------------------------------------------------------------------------------------------------------------------------------
   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   ESHandle<CaloGeometry> theGeometry;
   ESHandle<CaloSubdetectorGeometry> theEndcapGeometry_handle, theBarrelGeometry_handle;
    
   c.get<CaloGeometryRecord>().get( theGeometry );
   c.get<EcalEndcapGeometryRecord>().get("EcalEndcap",theEndcapGeometry_handle);
   c.get<EcalBarrelGeometryRecord>().get("EcalBarrel",theBarrelGeometry_handle);
    
   c.get<IdealGeometryRecord>().get(eTTmap_);
   theEndcapGeometry_ = &(*theEndcapGeometry_handle);
   theBarrelGeometry_ = &(*theBarrelGeometry_handle);

   edm::ESHandle<EcalSeverityLevelAlgo> sevlv1;
   c.get<EcalSeverityLevelAlgoRcd>().get(sevlv1);



   // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideEcalRecoLocalReco#Mapping_into_severity_levels
   
   edm::Handle<EcalRecHitCollection> rechitsEB; 
   e.getByToken(EcalRecHitCollectionEB1_,rechitsEB); 
  //  float maxRecHitEnergy = 0. ;
  //  int irechit=0;
   int sevlvl_tmp = -999; 
   double theta = -999; 
   double recHitEnergy = -999; 
  //  if (rechitsEB.product()->size()!=0) {

  //    // For each EB Rec Hit
  //    for ( EcalRecHitCollection::const_iterator rechitItr = rechitsEB->begin(); rechitItr != rechitsEB->end(); ++rechitItr ) {   
  //      recHitEnergy = rechitItr->energy(); 
              
  //     //  EBDetId id = rechitItr->id(); 
  //     //  sevlvl_tmp =  (sevlv1->severityLevel(id, *rechitsEB));
  //     //  (itTT->second).time_ = rechitItr->time();
  //     //  (itTT->second).sevlv_ = sevlvl_tmp; 
       
  //     //  const EcalTrigTowerDetId towid = id.tower();
  //     //  irechit++;
  //     //  itTT = mapTower.find(towid) ;
  //      //  (itTT->second).eRec_ = rechitItr->energy();

  //      // Associate highest energy crystal rechit in tower to tower 
  //     //  if (itTT != mapTower.end()) {
  //         //if((itTT->second).tpgADC_){	 std::cout<<" EcalTrigTowerDetId :: Rechit matched "<<towid<<" sevlev: "<<sevlv1->severityLevel(id, *rechitsEB)<<" ene:"<<(itTT->second).twrADC<<std::endl; }
          
  //         // theta = theBarrelGeometry_->getGeometry(id)->getPosition().theta() ;
  //         // (itTT->second).eRec_ += rechitItr->energy()*sin(theta) ;

  //         // int sevlvl_tmp =  (sevlv1->severityLevel(id, *rechitsEB)) ;
 
  //         //  maxRecHitEnergy = rechitItr->energy();
  //         // (itTT->second).sevlv_ = sevlvl_tmp; 	
  //         //  (itTT->second).twrADC_ = (itTT->second).twrADC;

  //         //  if ( rechitItr->energy() > maxRecHitEnergy && ((itTT->second).twrADC>32) ){
  //         //   //  maxRecHitEnergy = rechitItr->energy();
  //         //    (itTT->second).sevlv_ = sevlvl_tmp; 	
  //         //    (itTT->second).time_ = rechitItr->time();
  //         //   //  (itTT->second).eRec_ = rechitItr->energy();
  //         //  }

	//         // (itTT->second).crystNb_++; // Xtal loop? 
  //     //  }

  //    }
  //  }


   /*
   std::cout<<" inside the code "<<std::endl;
   edm::Handle<EcalRecHitCollection> rechitsEE; 
   e.getByToken(EcalRecHitCollectionEB1_,rechitsEE); 
   std::cout << " rechitsEE size " << rechitsEE.product()->size() << std::endl;
   if (rechitsEE.product()->size()!=0) {
     for ( EcalRecHitCollection::const_iterator rechitItr = rechitsEE->begin(); rechitItr != rechitsEE->end(); ++rechitItr ) {   
       EEDetId id = rechitItr->id(); 
       const EcalTrigTowerDetId towid = id.tower();
       
       itTT = mapTower.find(towid) ;

       
       if (itTT != mapTower.end()) {
	        
	 //double theta = theBarrelGeometry_->getGeometry(id)->getPosition().theta() ;
	 //(itTT->second).eRec_ += rechitItr->energy()*sin(theta) ;
	 //if (maxRecHitEnergy < rechitItr->energy()*sin(theta) && rechitItr->energy()*sin(theta) > 1. ){
	 (itTT->second).sevlv_ = sevlv1->severityLevel(id, *rechitsEE); 	
	 (itTT->second).time_ = rechitItr->time();
	   //}
	 (itTT->second).crystNb_++;
       }
     }
   }
   */



   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
   // -----------write tree----------------------------------------------------------------------------------------------------------------------------------------------------------- 
   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 

   // Save all rec hits (?)

  //  double recHitEnergy_ = -999; 
  //  int iRecHit = 0; 
  //  if (rechitsEB.product()->size()!=0) {

  //    // For each EB Rec Hit
  //    for ( EcalRecHitCollection::const_iterator rechitItr = rechitsEB->begin(); rechitItr != rechitsEB->end(); ++rechitItr ) {   
  //      recHitEnergy_ = rechitItr->energy(); 
  //      recHitEnergy[iRecHit] = recHitEnergy_;
  //      iRecHit ++; 
  //    }
  //  }

   int towerNb = 0 ;
   for (itTT = mapTower.begin() ; itTT != mapTower.end() ; ++itTT) {

     // select only non zero towers                                                                                                                                                                      
    //  bool fill(true) ;
    //  bool nonZeroEmul(false) ;
    //  for (int i=0 ; i<5 ; i++) if (((itTT->second).tpgEmul_[i]&0xff) > 0) nonZeroEmul = true ;
    //  if ( true && ((itTT->second).tpgADC_&0xff) <= 0 && (!nonZeroEmul) ) fill = false ;

    //  if (fill) {
    //    if (false) std::cout<<"ieta="<<(itTT->second).ieta_<<" iphi "<<(itTT->second).iphi_<<" tp="<<((itTT->second).tpgADC_&0xff)<<" tpEmul=" ;
    //    if (false) for (int i=0 ; i<5 ; i++) std::cout<<((itTT->second).tpgEmul_[i]&0xff)<<" " ;
    //    // nxtal info is not copied from the tpganalyzer 
    //    //std::cout<<" nbXtal="<<(itTT->second).nbXtal_ ;
    //    if (false) std::cout<<std::endl ;
    //  }

    //  std::cout<<"ieta="<<(itTT->second).ieta_<<" iphi "<<(itTT->second).iphi_<<" tp="<<((itTT->second).tpgADC_&0xff)<<" tpEmul=" ;
    //  std::cout<<"ieta="<<(itTT->second).ieta_<<" iphi "<<(itTT->second).iphi_<<" tp="<<((itTT->second).tpgADC_&0xff)<<" tpEmul=" ;
    //  if((itTT->second).twrADC != 0){
    //   std::cout << "towerNb:" << towerNb << std::endl;
    //   std::cout << "(itTT->second).twrADC: " << (itTT->second).twrADC << std::endl;
    //  }

    //  if((itTT->second).tpgADC_ != 0){
    //   std::cout << "towerNb:" << towerNb << std::endl;
    //   std::cout << "(itTT->second).tpgADC_: " << (itTT->second).tpgADC_ << std::endl;
    //  }     

    //  if((itTT->second).tpgEmul_[0] != 0){
    //    std::cout << "(itTT->second).tpgEmul_[0]: " << (itTT->second).tpgEmul_[0] << std::endl;
    //  }


     ieta[towerNb] = (itTT->second).ieta_ ;
     iphi[towerNb] = (itTT->second).iphi_ ;
     nbOfXtals[towerNb] = (itTT->second).nbXtal_ ;
     rawTPData[towerNb] = (itTT->second).tpgADC_ ;
     rawTPEmul1[towerNb] = (itTT->second).tpgEmul_[0] ;
     rawTPEmul2[towerNb] = (itTT->second).tpgEmul_[1] ;
     rawTPEmul3[towerNb] = (itTT->second).tpgEmul_[2] ;
     rawTPEmul4[towerNb] = (itTT->second).tpgEmul_[3] ;
     rawTPEmul5[towerNb] = (itTT->second).tpgEmul_[4] ;
     
     // Et values for emulated TP with index 2 (BX = 0?)
     twrEmul3ADC[towerNb] = ((itTT->second).tpgEmul_[2]&0xff) ;
     
     rawTPEmulttFlag1[towerNb] = (itTT->second).tpgEmulFlag_[0] ;
     rawTPEmulttFlag2[towerNb] = (itTT->second).tpgEmulFlag_[1] ;
     rawTPEmulttFlag3[towerNb] = (itTT->second).tpgEmulFlag_[2] ;
     rawTPEmulttFlag4[towerNb] = (itTT->second).tpgEmulFlag_[3] ;
     rawTPEmulttFlag5[towerNb] = (itTT->second).tpgEmulFlag_[4] ;
     rawTPEmulsFGVB1[towerNb] = (itTT->second).tpgEmulsFGVB_[0] ;
     rawTPEmulsFGVB2[towerNb] = (itTT->second).tpgEmulsFGVB_[1] ;
     rawTPEmulsFGVB3[towerNb] = (itTT->second).tpgEmulsFGVB_[2] ;
     rawTPEmulsFGVB4[towerNb] = (itTT->second).tpgEmulsFGVB_[3] ;
     rawTPEmulsFGVB5[towerNb] = (itTT->second).tpgEmulsFGVB_[4] ;
     crystNb[towerNb] = (itTT->second).crystNb_ ;

    //  for(int ixtal = 0; ixtal < 25; ixtal++){
    //    eRec[towerNb][ixtal] = (itTT->second).eRec_ ;
    //  }

    //  eRec[towerNb] = (itTT->second).eRec_ ;
     sevlv[towerNb] = (itTT->second).sevlv_ ; 
     time[towerNb] = (itTT->second).time_ ; 
     ttFlag[towerNb] = (itTT->second).ttFlag_ ;
     spike[towerNb] = (itTT->second).spike_ ;
     twrADC[towerNb] =  (itTT->second).twrADC;
     sFGVB[towerNb] =  (itTT->second).sFGVB;
    
     TCCid[towerNb] = (itTT->second).TCCid_;
     TowerInTCC[towerNb] = (itTT->second).TowerInTCC_;
     unsigned int maxEmul = 0 ;
     for (int i=0 ; i<5 ; i++) if (((itTT->second).tpgEmul_[i]&0xff) > maxEmul) maxEmul = ((itTT->second).tpgEmul_[i]&0xff) ;
     //for the emulated TP with max ADC of the 5
     twrEmulMaxADC[towerNb] = maxEmul;
     towerNb++ ;
     
     
   }

   nbOfTowers = towerNb ;
   
   ETTAnalyzerTree->Fill();
   
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void
ETTAnalyzer::beginJob()
{
  myevt = 0;
}

void ETTAnalyzer::beginRun(const edm::Run& r, const edm::EventSetup& c) {
  myevt = 0;
  
  // this should be moved to begin run 
  // but where is begin run 
  // begin job does not have the event setup infp 
  // Get the trigger menu information
  gtUtil_->retrieveL1Setup(c);
  
  // Get the algo bits needed for the timing histograms
  if (!gtUtil_->getAlgBitFromName(algoNameFirstBxInTrain_, algoBitFirstBxInTrain_)) {
    edm::LogWarning("L1TObjectsTiming") << "Algo \"" << algoNameFirstBxInTrain_ << "\" not found in the trigger menu " << gtUtil_->gtTriggerMenuName() << ". Could not retrieve algo bit number.";
  }
  
  if (!gtUtil_->getAlgBitFromName(algoNameLastBxInTrain_, algoBitLastBxInTrain_)) {
    edm::LogWarning("L1TObjectsTiming") << "Algo \"" << algoNameLastBxInTrain_ << "\" not found in the trigger menu " << gtUtil_->gtTriggerMenuName() << ". Could not retrieve algo bit number.";
  }
  
  if (!gtUtil_->getAlgBitFromName(algoNameIsoBx_, algoBitIsoBx_)) {
    edm::LogWarning("L1TObjectsTiming") << "Algo \"" << algoNameIsoBx_ << "\" not found in the trigger menu " << gtUtil_->gtTriggerMenuName() << ". Could not retrieve algo bit number.";
  }
  
  
}



// ------------ method called once each job just after ending the event loop  ------------
void
ETTAnalyzer::endJob()
{

  ibx_vs_ieta_Iso->Write();
  ibx_vs_ieta_NonIso->Write();
  
  ETTAnalyzerTree->Write();
  
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ETTAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  desc.addUntracked<std::string>("useAlgoDecision", "initial")->setComment("Which algo decision should be checked [initial, intermediate, final].");
  desc.addUntracked<std::vector<double>>("egammaPtCuts", {20., 10., 30.})->setComment("List if min egamman pT vaules");

    
  
  descriptions.addDefault(desc);
  
  
  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ETTAnalyzer);

