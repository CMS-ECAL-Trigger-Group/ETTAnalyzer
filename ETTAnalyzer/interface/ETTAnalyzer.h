#ifndef ETTANALYZER_H_
#define ETTANALYZER_H_

//------------------------------------------------------------------------//
// 21 June 2021                                                           //
//                                                                        //
// Raman Khurana                                                          //
// Abraham Tishelman-Charny                                               //
//                                                                        //
// The purpose of this plugin is to save trigger primitive and Level 1    //
// information from CMS data and MC AODs. This header file defines the    //
// ETTAnalyzer class.                                                     //
//------------------------------------------------------------------------//

// system include files
#include <memory>
#include <vector>
#include <array>
#include <algorithm>
#include <string>
#include <TH2F.h> 
#include <TTree.h>
#include <TDirectory.h>
#include <TROOT.h>
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
  float maxRecHitEnergy_; 
  towerEner()
    : eRec_(0),  crystNb_(0), tpgADC_(0),
      iphi_(-999), ieta_(-999), nbXtal_(0), spike_(0), twrADC(0), sFGVB(-999), sevlv_(-999) , ttFlag_(0), TCCid_(0), TowerInTCC_(0), strip_(0), time_(-999), maxRecHitEnergy_(-999)
  {
    // for (int i=0 ; i<5 ; i ++) { //-- 5 BX window 
      for (int i=2 ; i<3 ; i++) { //-- In time BX only
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
  bool savePreFireInfo_;
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
  // int myevt;
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
  // uint ndataframe;
  uint nADC;
  int index_df[8064];
  int index_ts[8064];
  int count_ADC[8064];
  int gain_id[8064];
  int tower_eta[8064];
  int tower_phi[8064];
  // int xtal_ix[8064];
  // int xtal_iy[8064];
  int xtal_ieta[8064];
  int xtal_iphi[8064];  
  
  uint nbOfTowers ; //max 4032 EB+EE            

  // Save per TT                                                                                                                                                           
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
  float maxRecHitEnergy[4032]; 
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
  // TH2F* ibx_vs_ieta_Iso;
  // TH2F* ibx_vs_ieta_NonIso;
  TTree *ETTAnalyzerTree;
  
};


ETTAnalyzer::ETTAnalyzer(const edm::ParameterSet& ps)
  :

  l1tStage2uGtProducer_(consumes<GlobalAlgBlkBxCollection>(ps.getParameter<edm::InputTag>("ugtProducer"))),
  savePreFireInfo_(ps.getParameter<bool>("savePreFireInfo")),
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

{
  EcalRecHitCollectionEB1_ = consumes<EcalRecHitCollection>( ps.getParameter<edm::InputTag>("EcalRecHitCollectionEB") );
  EcalRecHitCollectionEE1_ = consumes<EcalRecHitCollection>( ps.getParameter<edm::InputTag>("EcalRecHitCollectionEE") );
  
  useAlgoDecision_ = 0;
  egammaPtCuts_.clear();
  //egammaPtCuts_.push_back(10.0);
  //egammaPtCuts_.push_back(20.0);
  //egammaPtCuts_.push_back(30.0);
  
  //ibx_vs_ieta_Iso = new TH2F("ibx_vs_ieta_Iso","ibx_vs_ieta_Iso", 5, -2.5, 2.5, 70, -70, 70);
  //ibx_vs_ieta_NonIso = new TH2F("ibx_vs_ieta_NonIso","ibx_vs_ieta_NonIso", 5, -2.5, 2.5, 70, -70, 70);
  ETTAnalyzerTree = fs->make<TTree>("ETTAnalyzerTree","ECAL trigger primitive and rec hit information");

  // ibx_vs_ieta_Iso = fs->make<TH2F>("ibx_vs_ieta_Iso","ibx_vs_ieta_Iso", 5, -2.5, 2.5, 70, -70, 70);
  // ibx_vs_ieta_NonIso = fs->make<TH2F>("ibx_vs_ieta_NonIso","ibx_vs_ieta_NonIso", 5, -2.5, 2.5, 70, -70, 70);

  ETTAnalyzerTree->Branch("runNb", &runNb ,"runNb/i");
  ETTAnalyzerTree->Branch("evtNb", &evtNb ,"evtNb/L");
  ETTAnalyzerTree->Branch("bxNb", &bxNb ,"bxNb/i");
  //ETTAnalyzerTree->Branch("b_bxGT", &bxGT ,"b_bxGT/i");
  ETTAnalyzerTree->Branch("orbitNb", &orbitNb ,"orbitNb/L");
  ETTAnalyzerTree->Branch("lumiBlock", &lumiBlock ,"lumiBlock/i");
  ETTAnalyzerTree->Branch("timeStamp", &timeStamp ,"timeStamp/i");
  
  // ADC counts for 10 samples when there is some significant energy deposit. 
  // ETTAnalyzerTree->Branch("ndataframe", &ndataframe ,"ndataframe/i");
  ETTAnalyzerTree->Branch("nADC", &nADC ,"nADC/i");
  ETTAnalyzerTree->Branch("index_df", index_df,"index_df[nADC]/I");
  ETTAnalyzerTree->Branch("index_ts", index_ts,"index_ts[nADC]/I");
  ETTAnalyzerTree->Branch("count_ADC", count_ADC,"count_ADC[nADC]/I");
  ETTAnalyzerTree->Branch("gain_id", gain_id,"gain_id[nADC]/I");

  ETTAnalyzerTree->Branch("tower_eta",tower_eta ,"tower_eta[nADC]/I");
  ETTAnalyzerTree->Branch("tower_phi",tower_phi ,"tower_phi[nADC]/I");
  ETTAnalyzerTree->Branch("xtal_ieta", xtal_ieta,"xtal_ieta[nADC]/I");
  ETTAnalyzerTree->Branch("xtal_iphi", xtal_iphi,"xtal_iphi[nADC]/I");
  
  ETTAnalyzerTree->Branch("nbOfTowers",&nbOfTowers, "nbOfTowers/i");

  //-- Save information in groups of number of towers 
  ETTAnalyzerTree->Branch("ieta", ieta ,"ieta[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("iphi", iphi ,"iphi[nbOfTowers]/I");
  // ETTAnalyzerTree->Branch("nbOfXtals", nbOfXtals ,"nbOfXtals[nbOfTowers]/I");
  // ETTAnalyzerTree->Branch("rawTPData", rawTPData ,"rawTPData[nbOfTowers]/I");
  // ETTAnalyzerTree->Branch("rawTPEmul1", rawTPEmul1 ,"rawTPEmul1[nbOfTowers]/I");
  // ETTAnalyzerTree->Branch("rawTPEmul2", rawTPEmul2 ,"rawTPEmul2[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmul3", rawTPEmul3 ,"rawTPEmul3[nbOfTowers]/I");
  // ETTAnalyzerTree->Branch("rawTPEmul4", rawTPEmul4 ,"rawTPEmul4[nbOfTowers]/I");
  // ETTAnalyzerTree->Branch("rawTPEmul5", rawTPEmul5 ,"rawTPEmul5[nbOfTowers]/I");
  // ETTAnalyzerTree->Branch("rawTPEmulttFlag1", rawTPEmulttFlag1 ,"rawTPEmulttFlag1[nbOfTowers]/I");
  // ETTAnalyzerTree->Branch("rawTPEmulttFlag2", rawTPEmulttFlag2 ,"rawTPEmulttFlag2[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmulttFlag3", rawTPEmulttFlag3 ,"rawTPEmulttFlag3[nbOfTowers]/I");
  // ETTAnalyzerTree->Branch("rawTPEmulttFlag4", rawTPEmulttFlag4 ,"rawTPEmulttFlag4[nbOfTowers]/I");
  // ETTAnalyzerTree->Branch("rawTPEmulttFlag5", rawTPEmulttFlag5 ,"rawTPEmulttFlag5[nbOfTowers]/I");
  // ETTAnalyzerTree->Branch("rawTPEmulsFGVB1", rawTPEmulsFGVB1 ,"rawTPEmulsFGVB1[nbOfTowers]/I");
  // ETTAnalyzerTree->Branch("rawTPEmulsFGVB2", rawTPEmulsFGVB2 ,"rawTPEmulsFGVB2[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("rawTPEmulsFGVB3", rawTPEmulsFGVB3 ,"rawTPEmulsFGVB3[nbOfTowers]/I");
  // ETTAnalyzerTree->Branch("rawTPEmulsFGVB4", rawTPEmulsFGVB4 ,"rawTPEmulsFGVB4[nbOfTowers]/I");
  // ETTAnalyzerTree->Branch("rawTPEmulsFGVB5", rawTPEmulsFGVB5 ,"rawTPEmulsFGVB5[nbOfTowers]/I");

  // ETTAnalyzerTree->Branch("eRec", eRec ,"eRec[nbOfTowers][25]/I"); // Max of 25 xtals per TT 
  ETTAnalyzerTree->Branch("crystNb", crystNb ,"crystNb[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("maxRecHitEnergy", maxRecHitEnergy ,"maxRecHitEnergy[nbOfTowers]/F");
  ETTAnalyzerTree->Branch("sevlv", sevlv ,"sevlv[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("time", time ,"time[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("spike", spike ,"spike[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("twrADC", twrADC ,"twrADC[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("sFGVB", sFGVB ,"sFGVB[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("ttFlag", ttFlag ,"ttFlag[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("TCCid", TCCid ,"TCCid[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("TowerInTCC", TowerInTCC ,"TowerInTCC[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("strip", strip ,"strip[nbOfTowers]/I");
  
  // ETTAnalyzerTree->Branch("twrEmulMaxADC", twrEmulMaxADC ,"twrEmulMaxADC[nbOfTowers]/I");
  ETTAnalyzerTree->Branch("twrEmul3ADC", twrEmul3ADC ,"twrEmul3ADC[nbOfTowers]/I");

  if(savePreFireInfo_){

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

  }

  //ETTAnalyzerTree->Branch("b_",  ,"b_/I");
}


ETTAnalyzer::~ETTAnalyzer()
{

   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}

#endif 