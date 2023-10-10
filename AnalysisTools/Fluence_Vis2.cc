{

  gROOT->Reset();
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetOptFit(0);
  gStyle->SetLabelFont(42);
  gStyle->SetLabelFont(42);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleFont(42);

  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadTopMargin(0.1);//!!
  gStyle->SetPadBottomMargin(0.12);//!!

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  //gPad->SetLogy();
  //TGaxis::SetMaxDigits(3);
  double TextSizeScale = 1.0;

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
  };

  vector<int> PIDofInterest;
  PIDofInterest.push_back(2212);   //proton
  PIDofInterest.push_back(2112);   //neutron
  PIDofInterest.push_back(11);     //electron
  PIDofInterest.push_back(22);     //gamma

   TFile *f = new TFile("/home/martin/geant4/MedPhysics/MedPhys_pBi_build/output.root");
   TTree *t1 = (TTree*)f->Get("Fluences");
   double X, Y, Zsurf, Energy;
   int particle_id;
   int Event;

   t1->SetBranchAddress("X",&X);
   t1->SetBranchAddress("Y",&Y);
   t1->SetBranchAddress("Zsurf",&Zsurf);
   t1->SetBranchAddress("Energy",&Energy);
   t1->SetBranchAddress("particle_id",&particle_id);
   //t1->SetBranchAddress("Event",&Event);

   TH1F *hFluence_Ref   = new TH1F("hFluence[0]  ","Fluence (z)",400,0,400);
   TH1F *hFluence[4];
   for(int i=0; i<4; i++) hFluence[i] = (TH1F*) hFluence_Ref->Clone();

   int nentries = (int)t1->GetEntries();
   for (int i=0; i<nentries; i++) {
     t1 -> GetEntry(i);
     for(int pid_it=0; pid_it<4;pid_it++){
       if(particle_id == PIDofInterest[pid_it])hFluence[pid_it] -> Fill(Zsurf);
     }
   }

//====================  Making plots   =========================================

c1 = new TCanvas("c1", "c1", 960, 720);

hFluence[0]->GetYaxis()->SetTickLength(0.02);
hFluence[0]->GetYaxis()->SetNdivisions(505);
hFluence[0]->GetXaxis()->CenterTitle();
hFluence[0]->GetYaxis()->CenterTitle();
hFluence[0]->GetXaxis()->SetTitle("Distance, mm");
hFluence[0]->GetYaxis()->SetTitle("Fluence, N_{particle}/slice");
//hFluence[0] ->GetXaxis()->SetRangeUser(x1, x2);
hFluence[0] ->GetYaxis()->SetTitleSize(0.045*TextSizeScale);
hFluence[0]->GetYaxis()->SetTitleOffset(1.2);
hFluence[0]->GetXaxis()->SetTitleSize(0.045*TextSizeScale);
hFluence[0]->GetXaxis()->SetTitleOffset(1.0);
hFluence[0]->GetYaxis()->SetLabelSize(0.04*TextSizeScale);
hFluence[0]->GetXaxis()->SetLabelSize(0.04*TextSizeScale);
hFluence[0]->GetYaxis()->SetLabelFont(42);
hFluence[0]->GetYaxis()->SetTitleFont(42);
hFluence[0]->GetXaxis()->SetTitleFont(42);

for(int pid_it=0; pid_it<4;pid_it++){
  hFluence[pid_it]->SetLineWidth(ModelAttr[pid_it].width);
  hFluence[pid_it]->SetLineColor(ModelAttr[pid_it].colour);
  hFluence[pid_it]->SetMarkerStyle(ModelAttr[pid_it].marker);
  hFluence[pid_it]->SetMarkerColor(ModelAttr[pid_it].colour);
  hFluence[pid_it]->SetMarkerSize(ModelAttr[pid_it].size);
  hFluence[pid_it]->Draw(ModelAttr[pid_it].option);
}


TLegend* legend = new TLegend(0.75, 0.67, 0.9, 0.87);//
legend->SetTextSize(0.036);
legend->SetTextFont(42);
legend->SetHeader("Particle fluences","C");
for(int pid_it=0; pid_it<4;pid_it++) legend->AddEntry(hFluence[pid_it], ModelAttr[pid_it].ModelName, "l");
legend->SetFillColor(kWhite);
legend->SetLineColor(kWhite);
legend->Draw();

}
