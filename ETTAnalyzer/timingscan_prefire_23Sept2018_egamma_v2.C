void timingscan (char const *era, int thresh) {

  // Macro to plot L1 EGamma object pre-firing and post-firing probabilities
  // customised for ECAL timing scan data
  // Author: D. Petyt


  // uses 13 ECAL timing scan points from -6ns to +6ns
  
  Float_t timeoffset[13]={-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6};
  Float_t timeoffseterr[13]={0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};

  
  // input histograms, extracted from DQM root files

  // char era[10]="sep2018";
  
  char txt[80];

  sprintf(txt,"./l1tHistograms_%s.root",era);

  
  TFile fin(txt,"READ");

  
  TH2F **fhistfront;
  fhistfront=new TH2F*[13];
  TH2F **fhistback;
  fhistback=new TH2F*[13];

  
  // vectors to hold event counts and pre/post-firing probabilities

  Float_t eg_eb_bxm1[13];
  Float_t eg_eb_bx0[13];
  Float_t eg_eb_bxp1[13];
 
  Float_t eg_eb_pre[13];
  Float_t eg_eb_preerr[13];
  
  Float_t eg_eb_post[13];
  Float_t eg_eb_posterr[13];


  Float_t eg_ee_bxm1[13];
  Float_t eg_ee_bx0[13];
  Float_t eg_ee_bxp1[13];
 
  Float_t eg_ee_pre[13];
  Float_t eg_ee_preerr[13];
  
  Float_t eg_ee_post[13];
  Float_t eg_ee_posterr[13];


  

  // select Egamma ET threshold

  // int thresh=30;
  
  char pt[80];
    
  sprintf(pt,"%dp0",thresh);
  
  
  char pm[2];


  // Read Egamma L1T object relative BX vs ieta histograms for all 13 time scan points
  
  for (Int_t i=0;i<13;i++) {

    // event counters
    
    float eecountm1=0;
    float ebcountm1=0;
    float eecount0=0;
    float ebcount0=0;
    
    cout << i << endl;

    Int_t tm=int(timeoffset[i]);
  
    // first extract "first bunch in train" histos
  
    if (tm<0) sprintf(pm,"m");
    if (tm>0) sprintf(pm,"p");

    tm=abs(tm);
    
    if (i!=6)  sprintf(txt,"egamma_noniso_bx_ieta_firstbunch_ptmin%s_delay_%s%i",pt,pm,tm);
    else  sprintf(txt,"egamma_noniso_bx_ieta_firstbunch_ptmin%s_delay_%i",pt,tm);
    cout<< txt<< endl;

    fhistfront[i]=(TH2F*)fin.Get(txt);

    cout << "read ok" << endl;
    // count numbers of entries in BX-1 and BX 0:
    //   ieta bins 01-18 -> EE-
    //   ieta bins 19-52 -> EB
    //   ieta bins 53-69 -> EE+

    // pre-firing
    for (Int_t j=1;j<19;j++) eecountm1+=fhistfront[i]->GetBinContent(2,j);
    for (Int_t j=19;j<53;j++)  ebcountm1+=fhistfront[i]->GetBinContent(2,j);
    for (Int_t j=53;j<70;j++) eecountm1+=fhistfront[i]->GetBinContent(2,j);
    
    // in-time
    for (Int_t j=1;j<19;j++) eecount0+=fhistfront[i]->GetBinContent(3,j);
    for (Int_t j=19;j<53;j++) ebcount0+=fhistfront[i]->GetBinContent(3,j);
    for (Int_t j=53;j<70;j++) eecount0+=fhistfront[i]->GetBinContent(3,j);

    
    // compute ratios of BX-1 to BX0 for EB and EE separately
    
    Float_t num=ebcountm1;
    Float_t denom=ebcountm1+ebcount0;
    
    Float_t rat=0;
    Float_t error=0;

    
    if (num>0) {
      rat=num/denom;
      error=sqrt((rat*(1-rat))/denom);
    }
    else {
      rat=1e-4;
      error=sqrt(((1./denom)*(1.-1./denom))/denom);
    }
    eg_eb_pre[i]=rat;
    eg_eb_preerr[i]=error;


    num=eecountm1;
    denom=eecountm1+eecount0;

    rat=0;
    error=0;

    if (num>0) {
      rat=num/denom;
      error=sqrt((rat*(1-rat))/denom);
    }
    else {
      rat=1e-4;
      error=sqrt(((1./denom)*(1.-1./denom))/denom);
    }   

    cout << num << " " << denom << " " << rat << " " << error << endl;

    eg_ee_pre[i]=rat;
    eg_ee_preerr[i]=error;
 

    
  }

    cout << "here" << endl;

  // do the same for the last bunch in train histograms
  
  for (Int_t i=0;i<13;i++) {

    Int_t tm=int(timeoffset[i]);
  
    // first extract "first bunch in train" histos
  
    if (tm<0) sprintf(pm,"m");
    if (tm>0) sprintf(pm,"p");

    tm=abs(tm);

        
    if (i!=6)  sprintf(txt,"egamma_noniso_bx_ieta_lastbunch_ptmin%s_delay_%s%i",pt,pm,tm);
    else  sprintf(txt,"egamma_noniso_bx_ieta_lastbunch_ptmin%s_delay_%i",pt,tm);

    cout << txt << endl;
    fhistback[i]=(TH2F*)fin.Get(txt);


 
    float eecountp1=0;
    float ebcountp1=0;
    float eecount0=0;
    float ebcount0=0;
    
    for (Int_t j=1;j<19;j++) eecountp1+=fhistback[i]->GetBinContent(4,j);
    for (Int_t j=19;j<53;j++) ebcountp1+=fhistback[i]->GetBinContent(4,j);
    for (Int_t j=53;j<70;j++) eecountp1+=fhistback[i]->GetBinContent(4,j);
    

    for (Int_t j=1;j<19;j++) eecount0+=fhistback[i]->GetBinContent(3,j);
    for (Int_t j=19;j<53;j++) ebcount0+=fhistback[i]->GetBinContent(3,j);
    for (Int_t j=53;j<70;j++) eecount0+=fhistback[i]->GetBinContent(3,j);
    
    
    Float_t num=ebcountp1;
    Float_t denom=ebcountp1+ebcount0;

    Float_t rat=0;
    Float_t error=0;

    if (num>0) {
      rat=num/denom;
      error=sqrt((rat*(1-rat))/denom);
    }
    else {
      rat=1e-4;
      error=sqrt(((1./denom)*(1.-1./denom))/denom);
    }
    
    eg_eb_post[i]=rat;
    eg_eb_posterr[i]=error;
       
    num=eecountp1;
    denom=eecountp1+eecount0;

    rat=0;
    error=0;

    if (num>0) {
      rat=num/denom;
      error=sqrt((rat*(1-rat))/denom);
    }
    else {
      rat=1e-4;
      error=sqrt(((1./denom)*(1.-1./denom))/denom);
    }
    
    eg_ee_post[i]=rat;
    eg_ee_posterr[i]=error;

    
  }
  

  // create TGraphs for EB/EE,  pre/post -iring

  TGraphErrors *eg_eb_prefire=new TGraphErrors(13,timeoffset,eg_eb_pre,timeoffseterr,eg_eb_preerr);

  TGraphErrors *eg_eb_postfire=new TGraphErrors(13,timeoffset,eg_eb_post,timeoffseterr,eg_eb_posterr);

  TGraphErrors *eg_ee_prefire=new TGraphErrors(13,timeoffset,eg_ee_pre,timeoffseterr,eg_ee_preerr);

  TGraphErrors *eg_ee_postfire=new TGraphErrors(13,timeoffset,eg_ee_post,timeoffseterr,eg_ee_posterr);



  // EB plots
  
  TCanvas c1("c1","c1",10,10,800,700);
  c1.SetLogy(1);

  TH1F *frame=new TH1F("frame","",10,-8,8);
  frame->SetMaximum(1.0);
  frame->SetMinimum(1e-4);

  frame->SetXTitle("Time offset [ns]");
  frame->SetYTitle("Probability");
  
  frame->Draw();
  eg_eb_prefire->Draw("mlep");

  eg_eb_postfire->SetMarkerColor(801);
  eg_eb_postfire->SetLineColor(801);
  
  
  eg_eb_postfire->Draw("mlep");
  eg_eb_prefire->Draw("mlep");

  TLegend leg1(0.35,0.73,0.7,0.81);
  leg1.SetBorderSize(0);
  leg1.AddEntry(eg_eb_prefire,"Pre-firing","mlep");
  leg1.AddEntry(eg_eb_postfire,"Post-firing","mlep");
  leg1.Draw();

  TLatex l1;
  l1.SetNDC();
  l1.SetTextSize(0.06);
  l1.SetTextAlign(26);

  sprintf(txt,"EG candidates, E_{T}>%d GeV",thresh);
  l1.DrawLatex(0.5,0.91,txt);

  l1.DrawLatex(0.2,0.78,"EB");
  TLine lin1(-8,0.02,8,0.02);
  lin1.SetLineStyle(2);
  lin1.SetLineColor(921);
  lin1.Draw();

  l1.SetTextSize(0.025);
  l1.SetTextColor(921);
  l1.DrawLatex(0.76,0.52,"2% PRE-FIRING");
  l1.SetTextColor(1);

  sprintf(txt,"./plots/%s/prefiring_scan_%s_eb_egamma%d.png",era,era,thresh);
  c1.SaveAs(txt);

   

  // EE plots

  TCanvas c2("c2","c2",20,20,800,700);
  c2.SetLogy(1);

  
  frame->Draw();
  eg_ee_prefire->Draw("mlep");

  eg_ee_postfire->SetMarkerColor(801);
  eg_ee_postfire->SetLineColor(801);
  
  
  eg_ee_postfire->Draw("mlep");
  eg_ee_prefire->Draw("mlep");
 

  leg1.Draw();

  l1.SetNDC();
  l1.SetTextSize(0.06);
  l1.SetTextAlign(26);
   sprintf(txt,"EG candidates, E_{T}>%d GeV",thresh);
  l1.DrawLatex(0.5,0.91,txt);

  l1.DrawLatex(0.2,0.78,"EE");

  lin1.Draw();

  l1.SetTextSize(0.025);
  l1.SetTextColor(921);
  l1.DrawLatex(0.76,0.52,"2% PRE-FIRING");

  sprintf(txt,"./plots/%s/prefiring_scan_%s_ee_egamma%d.png",era,era,thresh);
  c2.SaveAs(txt);
  
    
   
 
}
