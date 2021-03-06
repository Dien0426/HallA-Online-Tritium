R__LOAD_LIBRARY(../../../libraries/TriFadcRasteredBeam/libTriFadcRasteredBeam.so)

Int_t get_rastersize(TString codafname,TString runNo, Int_t firsteve, Int_t lasteve, TString rootfname)
{

  // 
  //
  //  Steering script to extract the BPM information out of 
  //  the first few events from a rawdata file
  //  replacement for raster++
  //
  // original by Bodo Reitz, June 2004
  // modified and maintained by Bob Michaels, 2006
  // 
  // 
  // modified for Root 6 and FADC beam line by Tong Su,2017
  // 
  
  
  TString* ca_title = new TString("Raster Size (");
  ca_title->Append(codafname);
  ca_title->Append(")");


  TCanvas* c1 = new TCanvas("c1",ca_title->Data(),900,600);

  c1->Divide(3,2);

  TLatex *t = new TLatex();
  t->SetTextFont(32);
  t->SetTextColor(1);
  t->SetTextSize(0.015);
  t->SetTextAlign(12);
  t->DrawLatex(0.01,0.335,ca_title->Data());


  TCanvas* fc1 = new TCanvas("fc1",ca_title->Data(),900,600);

  fc1->Divide(3,2);

  TLatex *ft = new TLatex();
  ft->SetTextFont(32);
  ft->SetTextColor(1);
  ft->SetTextSize(0.015);
  ft->SetTextAlign(12);
  ft->DrawLatex(0.01,0.335,ca_title->Data());






  // Set up the event layout for the output file
  
  THaEvent* event = new THaEvent;
 
  // Set up the analyzer - we use the standard one,
  // but this could be an experiment-specific one as well.
  THaAnalyzer* analyzer = THaAnalyzer::GetInstance();
  if( analyzer ) {
    analyzer->Close();
  } else {
    analyzer = new THaAnalyzer;
  }

  cout << "Loading spot's private libBeam ..."<<endl;

 // THaApparatus* BEAM1 = new THaUnRasteredBeam("Lurb","Unraster Beamline");
  THaApparatus* FbusLrb = new THaRasteredBeam("FbusLrb","Raster Beamline"); 
  FbusLrb->AddDetector( new THaRaster("Raster2","Downstream raster") );
  FbusLrb->AddDetector( new THaBPM("BPMA","bpmA for raster beam"));
  FbusLrb->AddDetector( new THaBPM("BPMB","bpmB for raster beam"));
  THaApparatus* Lrb = new TriFadcRasteredBeam("Lrb","Raster Beamline for FADC ");


  gHaApps->Add( FbusLrb );
  gHaApps->Add(Lrb);

  analyzer->SetEvent( event );
  analyzer->SetOutFile( rootfname );

  analyzer->SetCompressionLevel(1);
  analyzer->SetOdefFile("output_rastersize.def");
  analyzer->SetCutFile("cuts_rastersize.def");


  THaRun* run = new THaRun( codafname );
    
  run->SetFirstEvent( firsteve );
  run->SetLastEvent( lasteve );
    
  analyzer->Process(*run);
  
  delete run;

  gStyle->SetOptStat(1);
  gStyle->SetStatH(0.3);
  gStyle->SetStatW(0.3);
  gStyle->SetTitleH(0.10);
  gStyle->SetTitleW(0.5);
  gStyle->SetLabelSize(0.06,"x");
  gStyle->SetLabelSize(0.06,"y");
  gROOT->ForceStyle();


 TFile *TritiumSpot = TFile::Open("rastersize.root");
if ( TritiumSpot->IsOpen() ) printf("File opened successfully\n");

 TH1F *bpma_x; TritiumSpot->GetObject("bpma_x", bpma_x);
 TH1F *bpma_y; TritiumSpot->GetObject("bpma_y", bpma_y);
 TH1F *bpmb_x; TritiumSpot->GetObject("bpmb_x", bpmb_x);
 TH1F *bpmb_y; TritiumSpot->GetObject("bpmb_y", bpmb_y);
 TH2F *bpma_xy; TritiumSpot->GetObject("bpma_xy", bpma_xy);
 TH2F *bpmb_xy; TritiumSpot->GetObject("bpmb_xy", bpmb_xy);
 TH2F *beam_xy; TritiumSpot->GetObject("beam_xy", beam_xy);
 TH2F *rastxy1; TritiumSpot->GetObject("rastxy1", rastxy1);
 TH2F *rastxy2; TritiumSpot->GetObject("rastxy2", rastxy2);
 TH2F *rastx1x2; TritiumSpot->GetObject("rastx1x2", rastx1x2);
 TH2F *rasty1y2; TritiumSpot->GetObject("rasty1y2", rasty1y2);
 TH2F *rastx1y2; TritiumSpot->GetObject("rastx1y2", rastx1y2);
 TH2F *rastx2y1; TritiumSpot->GetObject("rastx2y1", rastx2y1);
  
 TH1F *beam_x; TritiumSpot->GetObject("beam_x", beam_x);
 TH1F *beam_y; TritiumSpot->GetObject("beam_y", beam_y);



TH1F *bpmaraw1; TritiumSpot->GetObject("bpmaraw1", bpmaraw1);
TH1F *bpmaraw2; TritiumSpot->GetObject("bpmaraw2", bpmaraw2);
TH1F *bpmaraw3; TritiumSpot->GetObject("bpmaraw3", bpmaraw3);
TH1F *bpmaraw4; TritiumSpot->GetObject("bpmaraw4", bpmaraw4);
TH1F *bpmbraw1; TritiumSpot->GetObject("bpmbraw1", bpmbraw1);
TH1F *bpmbraw2; TritiumSpot->GetObject("bpmbraw2", bpmbraw2);
TH1F *bpmbraw3; TritiumSpot->GetObject("bpmbraw3", bpmbraw3);
TH1F *bpmbraw4; TritiumSpot->GetObject("bpmbraw4", bpmbraw4);
TH1F *bpmaraws; TritiumSpot->GetObject("bpmaraws", bpmaraws);
TH1F *bpmbraws; TritiumSpot->GetObject("bpmbraws", bpmbraws);

TH1F *URastX; TritiumSpot->GetObject("URastX", URastX);
TH1F *URastY; TritiumSpot->GetObject("URastY", URastY);
TH1F *DRastX; TritiumSpot->GetObject("DRastX", DRastX);
TH1F *DRastY; TritiumSpot->GetObject("DRastY", DRastY);

TH2F *urastraw_bpma_x; TritiumSpot->GetObject("urastraw_bpma_x", urastraw_bpma_x);
TH2F *urastraw_bpma_y; TritiumSpot->GetObject("urastraw_bpma_y", urastraw_bpma_y);
TH2F *urastraw_bpmb_x; TritiumSpot->GetObject("urastraw_bpmb_x", urastraw_bpmb_x);
TH2F *urastraw_bpmb_y; TritiumSpot->GetObject("urastraw_bpmb_y", urastraw_bpmb_y);

TH2F *urastraw_y_bpma_x; TritiumSpot->GetObject("urastraw_y_bpma_x", urastraw_y_bpma_x);
TH2F *urastraw_x_bpma_y; TritiumSpot->GetObject("urastraw_x_bpma_y", urastraw_x_bpma_y);
TH2F *urastraw_y_bpmb_x; TritiumSpot->GetObject("urastraw_y_bpmb_x", urastraw_y_bpmb_x);
TH2F *urastraw_x_bpmb_y; TritiumSpot->GetObject("urastraw_x_bpmb_y", urastraw_x_bpmb_y);

TH2F *drastraw_bpma_x; TritiumSpot->GetObject("drastraw_bpma_x", drastraw_bpma_x);
TH2F *drastraw_bpma_y; TritiumSpot->GetObject("drastraw_bpma_y", drastraw_bpma_y);
TH2F *drastraw_bpmb_x; TritiumSpot->GetObject("drastraw_bpmb_x", drastraw_bpmb_x);
TH2F *drastraw_bpmb_y; TritiumSpot->GetObject("drastraw_bpmb_y", drastraw_bpmb_y);

TH2F *drastraw_y_bpma_x; TritiumSpot->GetObject("drastraw_y_bpma_x", drastraw_y_bpma_x);
TH2F *drastraw_x_bpma_y; TritiumSpot->GetObject("drastraw_x_bpma_y", drastraw_x_bpma_y);
TH2F *drastraw_y_bpmb_x; TritiumSpot->GetObject("drastraw_y_bpmb_x", drastraw_y_bpmb_x);
TH2F *drastraw_x_bpmb_y; TritiumSpot->GetObject("drastraw_x_bpmb_y", drastraw_x_bpmb_y);
// BELOW IS FOR FADC FADC FADC --THREE TIMES FOR EVERYTHING IMPORTANT

 TH1F *fbpma_x; TritiumSpot->GetObject("fbpma_x", fbpma_x);
 TH1F *fbpma_y; TritiumSpot->GetObject("fbpma_y", fbpma_y);
 TH1F *fbpmb_x; TritiumSpot->GetObject("fbpmb_x", fbpmb_x);
 TH1F *fbpmb_y; TritiumSpot->GetObject("fbpmb_y", fbpmb_y);
 TH2F *fbpma_xy; TritiumSpot->GetObject("fbpma_xy", fbpma_xy);
 TH2F *fbpmb_xy; TritiumSpot->GetObject("fbpmb_xy", fbpmb_xy);
 TH2F *fbeam_xy; TritiumSpot->GetObject("fbeam_xy", fbeam_xy);
 TH2F *frastxy1; TritiumSpot->GetObject("frastxy1", frastxy1);
 TH2F *frastxy2; TritiumSpot->GetObject("frastxy2", frastxy2);
 TH2F *frastx1x2; TritiumSpot->GetObject("frastx1x2", frastx1x2);
 TH2F *frasty1y2; TritiumSpot->GetObject("frasty1y2", frasty1y2);
 TH2F *frastx1y2; TritiumSpot->GetObject("frastx1y2", frastx1y2);
 TH2F *frastx2y1; TritiumSpot->GetObject("frastx2y1", frastx2y1);
  
 TH1F *fbeam_x; TritiumSpot->GetObject("fbeam_x", fbeam_x);
 TH1F *fbeam_y; TritiumSpot->GetObject("fbeam_y", fbeam_y);



TH1F *fbpmaraw1; TritiumSpot->GetObject("fbpmaraw1", fbpmaraw1);
TH1F *fbpmaraw2; TritiumSpot->GetObject("fbpmaraw2", fbpmaraw2);
TH1F *fbpmaraw3; TritiumSpot->GetObject("fbpmaraw3", fbpmaraw3);
TH1F *fbpmaraw4; TritiumSpot->GetObject("fbpmaraw4", fbpmaraw4);
TH1F *fbpmbraw1; TritiumSpot->GetObject("fbpmbraw1", fbpmbraw1);
TH1F *fbpmbraw2; TritiumSpot->GetObject("fbpmbraw2", fbpmbraw2);
TH1F *fbpmbraw3; TritiumSpot->GetObject("fbpmbraw3", fbpmbraw3);
TH1F *fbpmbraw4; TritiumSpot->GetObject("fbpmbraw4", fbpmbraw4);
TH1F *fbpmaraws; TritiumSpot->GetObject("fbpmaraws", fbpmaraws);
TH1F *fbpmbraws; TritiumSpot->GetObject("fbpmbraws", fbpmbraws);

TH1F *fURastX; TritiumSpot->GetObject("fURastX", fURastX);
TH1F *fURastY; TritiumSpot->GetObject("fURastY", fURastY);
TH1F *fDRastX; TritiumSpot->GetObject("fDRastX", fDRastX);
TH1F *fDRastY; TritiumSpot->GetObject("fDRastY", fDRastY);

TH2F *furastraw_bpma_x; TritiumSpot->GetObject("furastraw_bpma_x", furastraw_bpma_x);
TH2F *furastraw_bpma_y; TritiumSpot->GetObject("furastraw_bpma_y", furastraw_bpma_y);
TH2F *furastraw_bpmb_x; TritiumSpot->GetObject("furastraw_bpmb_x", furastraw_bpmb_x);
TH2F *furastraw_bpmb_y; TritiumSpot->GetObject("furastraw_bpmb_y", furastraw_bpmb_y);

TH2F *furastraw_y_bpma_x; TritiumSpot->GetObject("furastraw_y_bpma_x", furastraw_y_bpma_x);
TH2F *furastraw_x_bpma_y; TritiumSpot->GetObject("furastraw_x_bpma_y", furastraw_x_bpma_y);
TH2F *furastraw_y_bpmb_x; TritiumSpot->GetObject("furastraw_y_bpmb_x", furastraw_y_bpmb_x);
TH2F *furastraw_x_bpmb_y; TritiumSpot->GetObject("furastraw_x_bpmb_y", furastraw_x_bpmb_y);

TH2F *fdrastraw_bpma_x; TritiumSpot->GetObject("fdrastraw_bpma_x", fdrastraw_bpma_x);
TH2F *fdrastraw_bpma_y; TritiumSpot->GetObject("fdrastraw_bpma_y", fdrastraw_bpma_y);
TH2F *fdrastraw_bpmb_x; TritiumSpot->GetObject("fdrastraw_bpmb_x", fdrastraw_bpmb_x);
TH2F *fdrastraw_bpmb_y; TritiumSpot->GetObject("fdrastraw_bpmb_y", fdrastraw_bpmb_y);

TH2F *fdrastraw_y_bpma_x; TritiumSpot->GetObject("fdrastraw_y_bpma_x", fdrastraw_y_bpma_x);
TH2F *fdrastraw_x_bpma_y; TritiumSpot->GetObject("fdrastraw_x_bpma_y", fdrastraw_x_bpma_y);
TH2F *fdrastraw_y_bpmb_x; TritiumSpot->GetObject("fdrastraw_y_bpmb_x", fdrastraw_y_bpmb_x);
TH2F *fdrastraw_x_bpmb_y; TritiumSpot->GetObject("fdrastraw_x_bpmb_y", fdrastraw_x_bpmb_y);




  bpma_x->GetXaxis()->SetLabelSize(0.075);
  bpma_x->GetYaxis()->SetLabelSize(0.075);
  bpma_y->GetXaxis()->SetLabelSize(0.075);
  bpma_y->GetYaxis()->SetLabelSize(0.075);
  bpma_xy->GetXaxis()->SetLabelSize(0.075);
  bpma_xy->GetYaxis()->SetLabelSize(0.075);
  bpmb_x->GetXaxis()->SetLabelSize(0.075);
  bpmb_x->GetYaxis()->SetLabelSize(0.075);

  bpmb_y->GetXaxis()->SetLabelSize(0.075);
  bpmb_y->GetYaxis()->SetLabelSize(0.075);
  bpmb_xy->GetXaxis()->SetLabelSize(0.075);
  bpmb_xy->GetYaxis()->SetLabelSize(0.075);
  beam_x->GetXaxis()->SetLabelSize(0.075);
  beam_x->GetYaxis()->SetLabelSize(0.075);
  beam_y->GetXaxis()->SetLabelSize(0.075);
  beam_y->GetYaxis()->SetLabelSize(0.075);
  beam_xy->GetXaxis()->SetLabelSize(0.075);
  beam_xy->GetYaxis()->SetLabelSize(0.075);


  fbpma_x->GetXaxis()->SetLabelSize(0.075);
  fbpma_x->GetYaxis()->SetLabelSize(0.075);
  fbpma_y->GetXaxis()->SetLabelSize(0.075);
  fbpma_y->GetYaxis()->SetLabelSize(0.075);
  fbpma_xy->GetXaxis()->SetLabelSize(0.075);
  fbpma_xy->GetYaxis()->SetLabelSize(0.075);
  fbpmb_x->GetXaxis()->SetLabelSize(0.075);
  fbpmb_x->GetYaxis()->SetLabelSize(0.075);

  fbpmb_y->GetXaxis()->SetLabelSize(0.075);
  fbpmb_y->GetYaxis()->SetLabelSize(0.075);
  fbpmb_xy->GetXaxis()->SetLabelSize(0.075);
  fbpmb_xy->GetYaxis()->SetLabelSize(0.075);
  fbeam_x->GetXaxis()->SetLabelSize(0.075);
  fbeam_x->GetYaxis()->SetLabelSize(0.075);
  fbeam_y->GetXaxis()->SetLabelSize(0.075);
  fbeam_y->GetYaxis()->SetLabelSize(0.075);
  fbeam_xy->GetXaxis()->SetLabelSize(0.075);
  fbeam_xy->GetYaxis()->SetLabelSize(0.075);




  c1->cd(1);
  bpma_xy->Draw("colz");
  gPad->SetGridx();  
  gPad->SetGridy();
  c1->cd(4);
  bpmb_xy->Draw("colz");
  gPad->SetGridx();
  gPad->SetGridy();
 
  c1->cd(2);
  bpma_x->Draw();
  c1->cd(5);
  bpmb_x->Draw();
 
  c1->cd(3);
  bpma_y->Draw();
  c1->cd(6);
  bpmb_y->Draw();


  TCanvas* c2 =  new TCanvas("c2","Upstream Raster Plots",1200,600);
  c2->Divide(3,1);
  c2->cd(1);
  // Added to fix axes, show raster x-y in full window
  TH2F *haxis = new TH2F("haxis","Fast Raster 1 X vs.Y",20,0,8000,20,0,8000);
  haxis->Draw();
  rastxy1->Draw("same colz");
  gStyle->SetOptStat(1);
  c2->cd(2);
  URastX->Draw();
  c2->cd(3);
  URastY->Draw();

  TCanvas* c2A =  new TCanvas("c2A","Downstream Raster Plots",1200,600);
  c2A->Divide(3,1);
  c2A->cd(1);
  // Added to fix axes, show raster x-y in full window
  TH2F *haxis2 = new TH2F("haxis","Fast Raster 2 X vs.Y",20,0,8000,20,0,8000);
  haxis2->Draw();
  rastxy2->Draw("same colz");
  gStyle->SetOptStat(1);
  c2A->cd(2);
  DRastX->Draw();
  c2A->cd(3);
  DRastY->Draw();

 
  TCanvas* c2B =  new TCanvas("c2B","check",900,600);
  //  gStyle->SetOptStat(0);
  c2B->Divide(2,1);
  c2B->cd(1);
  rastx1x2->Draw("same colz");
  gStyle->SetOptStat(1);
  c2B->cd(2);
  rasty1y2->Draw("same colz");

  
  TCanvas* c3 =  new TCanvas("c3","BPM Antenna Plots",900,600);
  //  gStyle->SetOptStat(0);
  c3->Divide(4,2);

  c3->cd(1);
  bpmaraw1->Draw();
  c3->cd(2);
  bpmaraw2->Draw();
  c3->cd(3);
  bpmaraw3->Draw();
  c3->cd(4);
  bpmaraw4->Draw(); 
  c3->cd(5);
  bpmbraw1->Draw();
  c3->cd(6);
  bpmbraw2->Draw();
  c3->cd(7);
  bpmbraw3->Draw();
  c3->cd(8);
  bpmbraw4->Draw(); 

  TCanvas* c4 =  new TCanvas("c4","Raster vs BPM Plots",1600,800);
  //  gStyle->SetOptStat(0);
  c4->Divide(4,2);

  c4->cd(1);
  urastraw_bpma_x->Draw("col");
  c4->cd(2);
  urastraw_bpma_y->Draw("col");
  c4->cd(3);
  urastraw_bpmb_x->Draw("col");
  c4->cd(4);
  urastraw_bpmb_y->Draw("col");
  c4->cd(5);
  drastraw_bpma_x->Draw("col");
  c4->cd(6);
  drastraw_bpma_y->Draw("col");
  c4->cd(7);
  drastraw_bpmb_x->Draw("col");
  c4->cd(8);
  drastraw_bpmb_y->Draw("col");

  TCanvas* c5 =  new TCanvas("c5","Beam Positions (A,B,Target)",1200,1200);
  c5->Divide(3,3);

  c5->cd(1);
  bpma_xy->Draw("col");
  c5->cd(2);
  bpma_x->Draw();
  c5->cd(3);
  bpma_y->Draw();
  c5->cd(4);
  bpmb_xy->Draw("col");
  c5->cd(5);
  bpmb_x->Draw();
  c5->cd(6);
  bpmb_y->Draw();
  c5->cd(7);
  beam_xy->Draw("col");
  c5->cd(8);
  beam_x->Draw();
  c5->cd(9);
  beam_y->Draw();

//// BELOW IS FOR FADC FADC FADC --THREE TIMES FOR EVERYTHING IMPORTANT////
  fc1->cd(1);
  fbpma_xy->Draw("colz");
  gPad->SetGridx();  
  gPad->SetGridy();
  fc1->cd(4);
  fbpmb_xy->Draw("colz");
  gPad->SetGridx();
  gPad->SetGridy();
 
  fc1->cd(2);
  fbpma_x->Draw();
  fc1->cd(5);
  fbpmb_x->Draw();
 
  fc1->cd(3);
  fbpma_y->Draw();
  fc1->cd(6);
  fbpmb_y->Draw();


  TCanvas* fc2 =  new TCanvas("fc2","Upstream Raster Plots for FADC ",1200,600);
  fc2->Divide(3,1);
  fc2->cd(1);
  // Added to fix axes, show raster x-y in full window
  TH2F *fhaxis = new TH2F("fhaxis","FADC Fast Raster 1 X vs.Y",20,0,8000,20,0,8000);
  fhaxis->Draw();
  frastxy1->Draw("same colz");
  gStyle->SetOptStat(1);
  fc2->cd(2);
  fURastX->Draw();
  fc2->cd(3);
  fURastY->Draw();

  TCanvas* fc2A =  new TCanvas("fc2A","FADC Downstream Raster Plots",1200,600);
  fc2A->Divide(3,1);
  fc2A->cd(1);
  // Added to fix axes, show raster x-y in full window
  TH2F *fhaxis2 = new TH2F("fhaxis","FADC Fast Raster 2 X vs.Y",20,0,8000,20,0,8000);
  fhaxis2->Draw();
  frastxy2->Draw("same colz");
  gStyle->SetOptStat(1);
  fc2A->cd(2);
  fDRastX->Draw();
  fc2A->cd(3);
  fDRastY->Draw();

 
  TCanvas* fc2B =  new TCanvas("fc2B","fadc check",900,600);
  //  gStyle->SetOptStat(0);
  fc2B->Divide(2,1);
  fc2B->cd(1);
  frastx1x2->Draw("same colz");
  gStyle->SetOptStat(1);
  fc2B->cd(2);
  frasty1y2->Draw("same colz");

  
  TCanvas* fc3 =  new TCanvas("fc3","FADC BPM Antenna Plots",900,600);
  //  gStyle->SetOptStat(0);
  fc3->Divide(4,2);

  fc3->cd(1);
  fbpmaraw1->Draw();
  fc3->cd(2);
  fbpmaraw2->Draw();
  fc3->cd(3);
  fbpmaraw3->Draw();
  fc3->cd(4);
  fbpmaraw4->Draw(); 
  fc3->cd(5);
  fbpmbraw1->Draw();
  fc3->cd(6);
  fbpmbraw2->Draw();
  fc3->cd(7);
  fbpmbraw3->Draw();
  fc3->cd(8);
  fbpmbraw4->Draw(); 

  TCanvas* fc4 =  new TCanvas("c4","FADC Raster vs BPM Plots",1600,800);
  //  gStyle->SetOptStat(0);
  fc4->Divide(4,2);

  fc4->cd(1);
  furastraw_bpma_x->Draw("col");
  fc4->cd(2);
  furastraw_bpma_y->Draw("col");
  fc4->cd(3);
  furastraw_bpmb_x->Draw("col");
  fc4->cd(4);
  furastraw_bpmb_y->Draw("col");
  fc4->cd(5);
  fdrastraw_bpma_x->Draw("col");
  fc4->cd(6);
  fdrastraw_bpma_y->Draw("col");
  fc4->cd(7);
  fdrastraw_bpmb_x->Draw("col");
  fc4->cd(8);
  fdrastraw_bpmb_y->Draw("col");

  TCanvas* fc5 =  new TCanvas("fc5","FADC Beam Positions (A,B,Target)",1200,1200);
  fc5->Divide(3,3);

  fc5->cd(1);
  fbpma_xy->Draw("col");
  fc5->cd(2);
  fbpma_x->Draw();
  fc5->cd(3);
  fbpma_y->Draw();
  fc5->cd(4);
  fbpmb_xy->Draw("col");
  fc5->cd(5);
  fbpmb_x->Draw();
  fc5->cd(6);
  fbpmb_y->Draw();
  fc5->cd(7);
  fbeam_xy->Draw("col");
  fc5->cd(8);
  fbeam_x->Draw();
  fc5->cd(9);
  fbeam_y->Draw();









  cout<<"++++++++++++++++++++++++++++++++"<<endl;
  cout<<"*****Beam Check For TRITIUM*****"<<endl;
  cout<<"++++++++++++++++++++++++++++++++"<<endl;


  cout<<"CODA-file:   "<<codafname<<endl;
  cout<<"first event: "<<firsteve<<endl;
  cout<<"last event:  "<<lasteve<<endl;
  cout<<"++++++++++++++++++++++++++++++++"<<endl;
  cout<<""<<endl;
  cout<<"type .q when you are done"<<endl;
  

   TString name1=Form("Tritium_");
   name1.Append(runNo);
   name1.Append(".pdf[");
 
   TString name2=Form("Tritium_");
   name2.Append(runNo);
   name2.Append(".pdf");
   
   TString name3=Form("Tritium_");
   name3.Append(runNo);
   name3.Append(".pdf]");
 
    //TString name4=Form("Fadc_Tritium_");
  // name1.Append(runNo);
  // name1.Append(".pdf[");

   // TString name5=Form("Fadc_Tritium_");
   //name2.Append(runNo);
   //name2.Append(".pdf");

  // TString name6=Form("Fadc_Tritium_");
  // name3.Append(runNo);
  // name3.Append(".pdf]");



   c1->Print(name1);
   c1->Print(name2);
   c2A->Print(name2);
   c2B->Print(name2);
   c3->Print(name2);
   //c4->Print(name2);
   c5->Print(name2); 
   //c5->Print(name3);


   fc1->SaveAs(name2);
   //fc1->SaveAs(name5);
   fc2A->SaveAs(name2);
   fc2B->SaveAs(name2);
   fc3->SaveAs(name2);
   //fc4->SaveAs(name5);
   fc5->SaveAs(name2);
   fc5->SaveAs(name3);
  // fc5->SaveAs(name6);
  return 1;


}


