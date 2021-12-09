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
  vector<float> *reco_R10_pt = 0;
  vector<float> *truth_R10_pt = 0;
  vector<float> *reco_R10_Trimmed_pt = 0;
  vector<float> *truth_R10_Trimmed_pt = 0;
  UInt_t npv = -1;

  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("RecoJets_R4_pt", &reco_R4_pt);
  tree->SetBranchAddress("TruthJets_R4_pt", &truth_R4_pt);
  tree->SetBranchAddress("RecoJets_R10_pt", &reco_R10_pt);
  tree->SetBranchAddress("TruthJets_R10_pt", &truth_R10_pt);
  tree->SetBranchAddress("RecoJets_R10_Trimmed_pt", &reco_R10_Trimmed_pt);
  tree->SetBranchAddress("TruthJets_R10_Trimmed_pt", &truth_R10_Trimmed_pt);
  tree->SetBranchAddress("NPV", &npv);

  // Canvas
  TCanvas *canvas = new TCanvas("Canvas", "", 800, 600);

  // Define histograms
  TH1F *hist_leadreco_R4_pt_evtw = new TH1F("Lead Reco-jet", "Leading jet pT; pT(GeV);Events", 50, 10, 200);
  TH1F *hist_leadtruth_R4_pt_evtw = new TH1F("Lead Truth-jet", "Leading jet pT; pT(GeV);Events", 50, 10, 200);
  TH1F *hist_leadreco_R4_pt = new TH1F("Lead Reco-jet", "Leading jet pT; pT(GeV);Events", 50, 10, 300);
  TH1F *hist_leadtruth_R4_pt = new TH1F("Lead Truth-jet", "Leading jet pT; pT(GeV);Events", 50, 10, 300);

  TH1F *hist_leadreco_R10_pt_evtw = new TH1F("Lead Reco-jet", "Leading jet pT; pT(GeV);Events", 50, 80, 500);
  TH1F *hist_leadtruth_R10_pt_evtw = new TH1F("Lead Truth-jet", "Leading jet pT; pT(GeV);Events", 50, 80, 500);
  TH1F *hist_leadreco_R10_pt = new TH1F("Lead Reco-jet", "Leading jet pT; pT(GeV);Events", 50, 80, 500);
  TH1F *hist_leadtruth_R10_pt = new TH1F("Lead Truth-jet", "Leading jet pT; pT(GeV);Events", 50, 80, 500);

  TH1F *hist_leadreco_R10_Trimmed_pt_evtw = new TH1F("Lead Reco-jet", "Leading jet pT; pT(GeV);Events", 50, 10, 500);
  TH1F *hist_leadtruth_R10_Trimmed_pt_evtw = new TH1F("Lead Truth-jet", "Leading jet pT; pT(GeV);Events", 50, 10, 500);
  TH1F *hist_leadreco_R10_Trimmed_pt = new TH1F("Lead Reco-jet", "Leading jet pT; pT(GeV);Events", 50, 10, 500);
  TH1F *hist_leadtruth_R10_Trimmed_pt = new TH1F("Lead Truth-jet", "Leading jet pT; pT(GeV);Events", 50, 10, 500);

  TH2F *hist_reco_jet_R4_pt_npv = new TH2F("Reco-jet pT vs. NPV", ";NPV; jet pT", 50, 1, 50, 20, 0, 200);
  TProfile *prof_reco_jet_R4_pt_npv = new TProfile("Profile Reco-jet pT vs. NPV", ";NPV; jet pT", 50, 1, 50, 0, 200);
  TH2F *hist_truth_jet_R4_pt_npv = new TH2F("Truth-jet pT vs. NPV", ";NPV; jet pT", 40, 1, 40, 20, 0, 200);
  TProfile *prof_truth_jet_R4_pt_npv = new TProfile("Profile Truth-jet pT vs. NPV", ";NPV; jet pT", 40, 1, 40, 0, 200);

  // Fill histograms
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
  {
    std::cout << nentries - i << "\n";
    nbytes = tree->GetEntry(i);

    if (reco_R4_pt->size() > 0)
    {
      hist_leadreco_R4_pt_evtw->Fill(reco_R4_pt->at(0) / 1000., evtw);
      hist_leadreco_R4_pt->Fill(reco_R4_pt->at(0) / 1000.);
    }

    if (truth_R4_pt->size() > 0)
    {
      hist_leadtruth_R4_pt_evtw->Fill(truth_R4_pt->at(0) / 1000., evtw);
      hist_leadtruth_R4_pt->Fill(truth_R4_pt->at(0) / 1000.);
    }

    if (reco_R10_pt->size() > 0)
    {
      hist_leadreco_R10_pt_evtw->Fill(reco_R10_pt->at(0) / 1000., evtw);
      hist_leadreco_R10_pt->Fill(reco_R10_pt->at(0) / 1000.);
    }

    if (truth_R10_pt->size() > 0)
    {
      hist_leadtruth_R10_pt_evtw->Fill(truth_R10_pt->at(0) / 1000., evtw);
      hist_leadtruth_R10_pt->Fill(truth_R10_pt->at(0) / 1000.);
    }

    if (reco_R10_Trimmed_pt->size() > 0)
    {
      hist_leadreco_R10_Trimmed_pt_evtw->Fill(reco_R10_Trimmed_pt->at(0) / 1000., evtw);
      hist_leadreco_R10_Trimmed_pt->Fill(reco_R10_Trimmed_pt->at(0) / 1000.);
    }

    if (truth_R10_Trimmed_pt->size() > 0)
    {
      hist_leadtruth_R10_Trimmed_pt_evtw->Fill(truth_R10_Trimmed_pt->at(0) / 1000., evtw);
      hist_leadtruth_R10_Trimmed_pt->Fill(truth_R10_Trimmed_pt->at(0) / 1000.);
    }

    if (reco_R4_pt->size() != 0 && reco_R4_pt->at(0) > 20000.)
    {
      for (int j = 0; j < reco_R4_pt->size(); j++)
      {
        hist_reco_jet_R4_pt_npv->Fill(reco_R4_pt->at(j) / 1000., npv, evtw);
        prof_reco_jet_R4_pt_npv->Fill(reco_R4_pt->at(j) / 1000., npv, evtw);
      }
    }

    if (truth_R4_pt->size() != 0 && truth_R4_pt->at(0) > 20000.)
    {
      for (int j = 0; j < truth_R4_pt->size(); j++)
      {
        hist_truth_jet_R4_pt_npv->Fill(truth_R4_pt->at(j) / 1000., npv, evtw);
        prof_truth_jet_R4_pt_npv->Fill(truth_R4_pt->at(j) / 1000., npv, evtw);
      }
    }
  }

  std::cout << "Done!" << std::endl;

  // Print histograms
  /*hist_leadtruth_R4_pt_evtw->SetMarkerStyle(20);
  hist_leadtruth_R4_pt_evtw->SetMarkerColor(1);
  hist_leadtruth_R4_pt_evtw->Draw("");
  hist_leadreco_R4_pt_evtw->SetMarkerStyle(20);
  hist_leadreco_R4_pt_evtw->SetMarkerColor(2);
  hist_leadreco_R4_pt_evtw->Draw("same");
  canvas->SetLogy();
  canvas->Print("Jets_R4_evtw.pdf");
  canvas->Clear();

  hist_leadtruth_R4_pt->SetLineColor(1);
  hist_leadtruth_R4_pt->Draw("");
  hist_leadreco_R4_pt->SetLineColor(2);
  hist_leadreco_R4_pt->Draw("same");
  canvas->SetLogy();
  canvas->Print("Jets_R4.pdf");
  canvas->Clear();

  hist_leadtruth_R10_pt_evtw->SetMarkerStyle(20);
  hist_leadtruth_R10_pt_evtw->SetMarkerColor(1);
  hist_leadtruth_R10_pt_evtw->Draw("");
  hist_leadreco_R10_pt_evtw->SetMarkerStyle(20);
  hist_leadreco_R10_pt_evtw->SetMarkerColor(2);
  hist_leadreco_R10_pt_evtw->Draw("same");
  canvas->SetLogy();
  canvas->Print("Jets_R10_evtw.pdf");
  canvas->Clear();

  hist_leadtruth_R10_pt->SetLineColor(1);
  hist_leadtruth_R10_pt->Draw("");
  hist_leadreco_R10_pt->SetLineColor(2);
  hist_leadreco_R10_pt->Draw("same");
  canvas->SetLogy();
  canvas->Print("Jets_R10.pdf");
  canvas->Clear();

  hist_leadtruth_R10_Trimmed_pt_evtw->SetMarkerStyle(20);
  hist_leadtruth_R10_Trimmed_pt_evtw->SetMarkerColor(1);
  hist_leadtruth_R10_Trimmed_pt_evtw->Draw("");
  hist_leadreco_R10_Trimmed_pt_evtw->SetMarkerStyle(20);
  hist_leadreco_R10_Trimmed_pt_evtw->SetMarkerColor(2);
  hist_leadreco_R10_Trimmed_pt_evtw->Draw("same");
  canvas->SetLogy();
  canvas->Print("Jets_R10_Trimmed_evtw.pdf");
  canvas->Clear();

  hist_leadtruth_R10_Trimmed_pt->SetLineColor(1);
  hist_leadtruth_R10_Trimmed_pt->Draw("");
  hist_leadreco_R10_Trimmed_pt->SetLineColor(2);
  hist_leadreco_R10_Trimmed_pt->Draw("same");
  canvas->SetLogy();
  canvas->Print("Jets_R10_Trimmed.pdf");
  canvas->Clear();


  hist_reco_jet_R4_pt_npv->Draw("colz");
  canvas->Print("Hist_Reco_Jets_R4_pt_npv.pdf");
  canvas->Clear();
  prof_reco_jet_R4_pt_npv->Draw("");
  canvas->Print("Prof_Reco_Jets_R4_pt_npv.pdf");
  canvas->Clear();

  hist_truth_jet_R4_pt_npv->Draw("colz");
  canvas->Print("Hist_Truth_Jets_R4_pt_npv.pdf");
  canvas->Clear();
  prof_truth_jet_R4_pt_npv->Draw("");
  canvas->Print("Prof_Truth_Jets_R4_pt_npv.pdf");
  canvas->Clear();*/
}