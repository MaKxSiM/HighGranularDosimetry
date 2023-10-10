{

  gROOT->Reset();
  //gStyle->SetOptStat(0);
  //gStyle->SetOptTitle(0);
  gStyle->SetOptFit(0);
  gStyle->SetLabelFont(42);
  gStyle->SetTitleFont(42);

  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetPadRightMargin(0.17);
  gStyle->SetPadTopMargin(0.1);//!!
  gStyle->SetPadBottomMargin(0.12);//!!

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  //gPad->SetLogy();
  TGaxis::SetMaxDigits(3);

  double TextSizeScale = 1.0;


  gStyle->SetLineStyleString(16,"24 12 12 12");
  gStyle->SetLineStyleString(11,"34 34");


  struct GraphAttr {
  	int colour;
  	int marker;
  	float width;
  	float size;
  	char  ModelName[100];
  	char option[20];
  };


  GraphAttr ModelAttr[] = {
  	{ 4, 21, 2.0, 1.2, "protons", "" },
  	{ 3, 33, 2.0, 1.5, "neutrons", "same" },
  	{ 2, 34, 2.0, 1.5, "electrons", "same" },
  	{ 45, 29, 2.0, 1.6, "photons", "same" },
    { 5, 29, 2.0, 1.6, "alpha", "same" },
  };

  vector<int> PIDofInterest;
  PIDofInterest.push_back(2212);   //proton
  PIDofInterest.push_back(2112);   //neutron
  PIDofInterest.push_back(11);     //electron
  PIDofInterest.push_back(22);     //gamma
  PIDofInterest.push_back(1000020040);  //alpha



//======================= 87 MeV ========================================
  TFile *f1 = new TFile("~/Programs/Geant4/WorkTest/MedPhysG11.1_v1/HighGranularity/MedPhys_pBi-build/output_Cell1mm_p_87_5kevt.root");
  //TFile *f1 = new TFile("~/Programs/Geant4/WorkTest/MedPhysG11.1_v1/HighGranularity/MedPhys_pBi-build/output_Cell1mm_gamma_6MV_v2_200kevt.root");
  //TFile *f1 = new TFile("~/Programs/Geant4/WorkTest/MedPhysG11.1_v1/HighGranularity/MedPhys_pBi-build/output_Cell1mm_gamma_150kev_20kevt.root");

  //TFile *f1 = new TFile("~/Programs/Geant4/WorkTest/MedPhysG11.1_v1/HighGranularity/MedPhys_pBi-build/output.root");

//==============================================================================



//===================== 2D energy depostion ====================================
TH2F *hBeamSpot1 = new TH2F("EnergyDeposition1","Dose, Depth: 0 - 10 [mm]", 60,-30,30, 60,-30,30);
TH2F *hBeamSpot2 = new TH2F("EnergyDeposition2","Dose, Depth: 10 - 20 [mm]", 60,-30,30, 60,-30,30);
TH2F *hBeamSpot3 = new TH2F("EnergyDeposition3","Dose, Depth: 20 - 30 [mm]", 60,-30,30, 60,-30,30);
TH2F *hBeamSpot4 = new TH2F("EnergyDeposition4","Dose, Depth: 30 - 40 [mm]", 60,-30,30, 60,-30,30);
TH2F *hBeamSpot5 = new TH2F("EnergyDeposition5","Dose, Depth: 40 - 50 [mm]", 60,-30,30, 60,-30,30);
TH2F *hBeamSpot6 = new TH2F("EnergyDeposition6","Dose, Depth: 50 - 60 [mm]", 60,-30,30, 60,-30,30);
TH2F *hBeamSpot7 = new TH2F("EnergyDeposition7","Dose, Depth: 60 - 70 [mm]", 60,-30,30, 60,-30,30);
TH2F *hBeamSpot8 = new TH2F("EnergyDeposition8","Dose, Depth: 70 - 80 [mm]", 60,-30,30, 60,-30,30);


//==============================================================================

TTree *t1 = (TTree*)f1->Get("Dose_in_volume_N");
double Dose, Energy;
double X, Y, Z;
char ParticleName[100];
t1->SetBranchAddress("X",&X);
t1->SetBranchAddress("Y",&Y);
t1->SetBranchAddress("Z",&Z);
t1->SetBranchAddress("dose",&Dose);
t1->SetBranchAddress("Edep_MeV",&Energy);


double  scaleDose = 6.24151e+24 * 1.6e-19 * 1.6e-19; // for  1st proton sample with 2000 events
//double  scaleDose = 1; // for  the fixed EventActions.cc

int nentries1 = (int)t1->GetEntries();
for (int i=0; i<nentries1; i++) {
//for (int i=0; i<10000; i++) {
  t1 -> GetEntry(i);
  if(Z>0 && Z<10)hBeamSpot1 ->Fill(X,Y, Dose*scaleDose);
//  if(Z>10 && Z<=20)hBeamSpot2 ->Fill(X,Y, Dose*1.6e-13);
  if(Z>20 && Z<30)hBeamSpot3 ->Fill(X,Y, Dose*scaleDose);
//  if(Z>30 && Z<=40)hBeamSpot4 ->Fill(X,Y, Dose*1.6e-13);
//  if(Z>40 && Z<=50)hBeamSpot5 ->Fill(X,Y, Dose*1.6e-13);
  if(Z>50 && Z<60)hBeamSpot6 ->Fill(X,Y, Dose*scaleDose);
  if(Z>60 && Z<70)hBeamSpot7 ->Fill(X,Y, Dose*scaleDose);
  if(Z>70 && Z<80)hBeamSpot8 ->Fill(X,Y, Dose*scaleDose);
}



double TileSize = 0.055;
double N_protons =5000;
//double N_protons =200000;

hBeamSpot1->Scale(1 / N_protons);
hBeamSpot2->Scale(1 / N_protons);
hBeamSpot3->Scale(1 / N_protons);
hBeamSpot4->Scale(1 / N_protons);
hBeamSpot5->Scale(1 / N_protons);
hBeamSpot6->Scale(1 / N_protons);
hBeamSpot7->Scale(1 / N_protons);

//double N_protons =500000.01;

//double N_protons =10000.01;

/*
int RebinFactor = 5;// 2 by defualt
hDensityProfile4->Scale(1 / N_protons / RebinFactor);
*/


//getinng maximun for first histrgram and makins some offset by multiplying by 1.2
/*
double max_y_plot[4];
max_y_plot[0] = 1.2*std::max(hDensityProfile1->GetMaximum (), hDensityProfile1_2->GetMaximum ());
max_y_plot[1] = 1.2*std::max(hDensityProfile2->GetMaximum (), hDensityProfile2_2->GetMaximum ());
max_y_plot[2] = 1.2*std::max(hDensityProfile3->GetMaximum (), hDensityProfile3_2->GetMaximum ());
max_y_plot[3] = 1.2*std::max(hDensityProfile4->GetMaximum (), hDensityProfile4_2->GetMaximum ());
cout<< max_y_plot[0] <<"   "<<max_y_plot[1] <<"   "<<max_y_plot[2]<<"   "<<max_y_plot[3]<<endl;
*/

double Zrange_max = 45e-9;//proton 87 MeV
//double Zrange_max = 20e-12;

TCanvas* c3 = new TCanvas("c3", "Produced particle", 1600, 360);
c3->Divide(4,1, 0.01, 0.01);
c3->cd(1);
//hDensityProfile3->GetYaxis()->SetRangeUser(0,  max_y_plot[2]);
hBeamSpot1->GetXaxis()->SetTitle("x [mm]");
hBeamSpot1->GetYaxis()->SetTitle("y [mm]");
hBeamSpot1->GetZaxis()->SetTitle("Dose, Gy / beam particle");
hBeamSpot1->GetZaxis()->SetRangeUser(0,  Zrange_max);
hBeamSpot1->GetXaxis()->SetTitleSize(TileSize);
hBeamSpot1->GetYaxis()->SetTitleSize(TileSize);
hBeamSpot1->GetZaxis()->SetTitleSize(TileSize);
hBeamSpot1->GetYaxis()->SetTitleOffset(1.1);
hBeamSpot1->GetZaxis()->SetTitleOffset(0.8);
hBeamSpot1->GetXaxis()->SetLabelSize(0.9*TileSize);
hBeamSpot1->GetYaxis()->SetLabelSize(0.9*TileSize);
hBeamSpot1->GetYaxis()->CenterTitle();
hBeamSpot1->Draw("colz");


c3->cd(2);
hBeamSpot3->GetXaxis()->SetTitle("x [mm]");
hBeamSpot3->GetYaxis()->SetTitle("y [mm]");
hBeamSpot3->GetZaxis()->SetTitle("Dose, Gy / beam particle");
hBeamSpot3->GetZaxis()->SetRangeUser(0,  Zrange_max);
hBeamSpot3->GetXaxis()->SetTitleSize(TileSize);
hBeamSpot3->GetYaxis()->SetTitleSize(TileSize);
hBeamSpot3->GetZaxis()->SetTitleSize(TileSize);
hBeamSpot3->GetYaxis()->SetTitleOffset(1.1);
hBeamSpot3->GetXaxis()->SetLabelSize(0.9*TileSize);
hBeamSpot3->GetYaxis()->SetLabelSize(0.9*TileSize);
hBeamSpot3->GetYaxis()->CenterTitle();
hBeamSpot3->Draw("colz");

c3->cd(3);
hBeamSpot6->GetXaxis()->SetTitle("x [mm]");
hBeamSpot6->GetYaxis()->SetTitle("y [mm]");
hBeamSpot6->GetZaxis()->SetTitle("Dose, Gy / beam particle");
hBeamSpot6->GetZaxis()->SetRangeUser(0,  Zrange_max);
hBeamSpot6->GetXaxis()->SetTitleSize(TileSize);
hBeamSpot6->GetYaxis()->SetTitleSize(TileSize);
hBeamSpot6->GetZaxis()->SetTitleSize(TileSize);
hBeamSpot6->GetYaxis()->SetTitleOffset(1.1);
hBeamSpot6->GetXaxis()->SetLabelSize(0.9*TileSize);
hBeamSpot6->GetYaxis()->SetLabelSize(0.9*TileSize);
hBeamSpot6->GetYaxis()->CenterTitle();
hBeamSpot6->Draw("colz");

c3->cd(4);
hBeamSpot7->GetXaxis()->SetTitle("x [mm]");
hBeamSpot7->GetYaxis()->SetTitle("y [mm]");
hBeamSpot7->GetZaxis()->SetTitle("Dose, Gy / beam particle");
hBeamSpot7->GetZaxis()->SetRangeUser(0,  Zrange_max);
hBeamSpot7->GetXaxis()->SetTitleSize(TileSize);
hBeamSpot7->GetYaxis()->SetTitleSize(TileSize);
hBeamSpot7->GetZaxis()->SetTitleSize(TileSize);
hBeamSpot7->GetYaxis()->SetTitleOffset(1.1);
hBeamSpot7->GetXaxis()->SetLabelSize(0.9*TileSize);
hBeamSpot7->GetYaxis()->SetLabelSize(0.9*TileSize);
hBeamSpot7->GetYaxis()->CenterTitle();
hBeamSpot7->Draw("colz");

/*
c3->cd(5);
hBeamSpot8->GetXaxis()->SetTitle("x [mm]");
hBeamSpot8->GetYaxis()->SetTitle("y [mm]");
hBeamSpot8->GetZaxis()->SetTitle("Dose, Gy / beam particle");
hBeamSpot8->GetZaxis()->SetRangeUser(0,  Zrange_max);
hBeamSpot8->GetXaxis()->SetTitleSize(TileSize);
hBeamSpot8->GetYaxis()->SetTitleSize(TileSize);
hBeamSpot8->GetZaxis()->SetTitleSize(TileSize);
hBeamSpot8->GetYaxis()->SetTitleOffset(1.1);
hBeamSpot8->GetXaxis()->SetLabelSize(0.9*TileSize);
hBeamSpot8->GetYaxis()->SetLabelSize(0.9*TileSize);
hBeamSpot8->GetYaxis()->CenterTitle();
hBeamSpot8->Draw("colz");
*/


}
