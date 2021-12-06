void Jets_macro()
{

  // Open .root file
  TFile *file = TFile::Open("Tracks_Clusters.root");

  // Define tree and print contents
  TTree *tree = (TTree *)file->Get("JetRecoTree");
  tree->Print();

  // Extract variables
  float evtw = -1;
  vector<float> *reco_R4_pt = 0;
  vector<float> *truth_R4_pt = 0;

  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("RecoJets_R4_pt", &reco_R4_pt);
  tree->SetBranchAddress("TruthJets_R4_pt", &truth_R4_pt);

  // Canvas
  TCanvas *canvas = new TCanvas("Canvas", "", 800, 600);

  // Define histograms
  TH1F *hist_leadreco_pt_evtw = new TH1F("Lead Reco-jet", "Leading jet pT; pT(GeV);Events", 50, 10, 200);
  TH1F *hist_leadtruth_pt_evtw = new TH1F("Lead Truth-jet", "Leading jet pT; pT(GeV);Events", 50, 10, 200);
  TH1F *hist_leadreco_pt = new TH1F("Lead Reco-jet", "Leading jet pT; pT(GeV);Events", 50, 10, 300);
  TH1F *hist_leadtruth_pt = new TH1F("Lead Truth-jet", "Leading jet pT; pT(GeV);Events", 50, 10, 300);

  // Fill histograms
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
  {
    std::cout << nentries - i << "\n";
    nbytes = tree->GetEntry(i);

    if (reco_R4_pt->size() > 0)
    {
      hist_leadreco_pt_evtw->Fill(reco_R4_pt->at(0) / 1000., evtw);
      hist_leadreco_pt->Fill(reco_R4_pt->at(0) / 1000.);
    }

    if (truth_R4_pt->size() > 0)
    {
      hist_leadtruth_pt_evtw->Fill(truth_R4_pt->at(0) / 1000., evtw);
      hist_leadtruth_pt->Fill(truth_R4_pt->at(0) / 1000.);
    }
  }

  std::cout << "Done!" << std::endl;

  // Print histograms
  hist_leadtruth_pt_evtw->SetMarkerStyle(20);
  hist_leadtruth_pt_evtw->SetMarkerColor(1);
  hist_leadtruth_pt_evtw->Draw("");
  hist_leadreco_pt_evtw->SetMarkerStyle(20);
  hist_leadreco_pt_evtw->SetMarkerColor(2);
  hist_leadreco_pt_evtw->Draw("same");
  canvas->SetLogy();
  canvas->Print("Jets_R4_evtw.pdf");
  canvas->Clear();

  hist_leadtruth_pt->SetLineColor(1);
  hist_leadtruth_pt->Draw("");
  hist_leadtruth_pt->SetLineColor(2);
  hist_leadreco_pt->Draw("same");
  canvas->SetLogy();
  canvas->Print("Jets_R4.pdf");
  canvas->Clear();
}
