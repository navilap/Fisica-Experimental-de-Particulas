void Tracks_Clusters_macro()
{

  // Open .root file
  TFile *file = TFile::Open("Tracks_Clusters.root");

  // Define tree and print contents
  TTree *tree = (TTree *)file->Get("JetRecoTree");
  tree->Print();

  // Extract variables
  Float_t muav = -1;
  UInt_t npv = -1;
  vector<float> *tracks_pt = 0;
  vector<float> *clusters_pt = 0;
  vector<float> *tracks_eta = 0;
  vector<float> *tracks_phi = 0;
  vector<float> *tracks_m = 0;
  vector<float> *tracks_vtx = 0;
  vector<float> *clusters_eta = 0;
  vector<float> *clusters_phi = 0;
  vector<float> *clusters_m = 0;
  vector<float> *particles_pt = 0;
  vector<float> *particles_eta = 0;
  vector<float> *particles_phi = 0;
  vector<float> *particles_m = 0;
  vector<float> *particles_pdgid = 0;

  tree->SetBranchAddress("mu_average", &muav);
  tree->SetBranchAddress("NPV", &npv);
  tree->SetBranchAddress("Tracks_pt", &tracks_pt);
  tree->SetBranchAddress("Clusters_pt", &clusters_pt);
  tree->SetBranchAddress("Tracks_eta", &tracks_eta);
  tree->SetBranchAddress("Tracks_phi", &tracks_phi);
  tree->SetBranchAddress("Tracks_m", &tracks_m);
  tree->SetBranchAddress("Tracks_vtx", &tracks_vtx);
  tree->SetBranchAddress("Clusters_eta", &clusters_eta);
  tree->SetBranchAddress("Clusters_phi", &clusters_phi);
  tree->SetBranchAddress("Clusters_m", &clusters_m);
  tree->SetBranchAddress("Particles_pt", &particles_pt);
  tree->SetBranchAddress("Particles_eta", &particles_eta);
  tree->SetBranchAddress("Particles_phi", &particles_phi);
  tree->SetBranchAddress("Particles_m", &particles_m);
  tree->SetBranchAddress("Particles_pdgID", &particles_pdgid);

  // Define Canvas
  TCanvas *canvas = new TCanvas("Canvas", "a first way to plot a variable", 800, 600);

  // Histrograms
  TH1F *hist_muav = new TH1F("Mu Average",
                             "Number of Average Interactions per Bunch-Crossing; Mu Average ; Events ",
                             90, 0, 90);

  TH2F *hist_npvvsmuav = new TH2F("NPV vs Mu Average",
                                  "Number of Primary Vertices vs Average Interactions per Bunch-Crossing; NPV; Mu Average; Events",
                                  60, 0, 60,
                                  90, 0, 90);

  TH2F *hist_npvvsntracks = new TH2F("NPV vs nTracks", "Number of Primary Vertices vs Number of Tracks; NPV; Number of Tracks; Events",
                                     50, 0, 50,
                                     100, 0, 1500);

  TH2F *hist_npvvsnclusters = new TH2F("NPV vs nClusters", "Number of Primary Vertices vs Number of Cluster; NPV; Number of Clusters; Events",
                                       40, 0, 40,
                                       100, 0, 1200);

  TH2F *hist_muavvsntracks = new TH2F("Mu Average vs nTracks", "Number of Average Interactions per Bunch-Crossing vs Number of Tracks; Mu Average; Number of Tracks; Events",
                                      80, 0, 80,
                                      100, 0, 1500);

  TH2F *hist_muavvsnclusters = new TH2F("Mu Average vs nClusters", "Number of Average Interactions per Bunch-Crossing vs Number of Clusters; Mu Average; Number of Clusters; Events",
                                        80, 0, 80,
                                        100, 0, 1200);

  TH1F *hist_trackspt = new TH1F("Tracks pt", "Tracks pt; Pt; Events",
                                 100, 400, 5000);

  TH1F *hist_trackseta = new TH1F("Tracks eta", "Tracks eta; Eta; Events",
                                  100, -3, 3);

  TH1F *hist_tracksphi = new TH1F("Tracks phi", "Tracks phi; Phi; Events",
                                  100, -4, 4);

  TH1F *hist_tracksm = new TH1F("Tracks m", "Tracks m; M; Events",
                                100, 139, 140);

  TH1F *hist_tracksvtx = new TH1F("Tracks vtx", "Tracks vtx; vtx; Events",
                                  35, 0, 35);

  TH1F *hist_clusterspt = new TH1F("Clusters pt", "Clusters pt; pt; Events",
                                   100, 0, 6000);

  TH1F *hist_clusterseta = new TH1F("Clusters eta", "Clusters eta; eta; Events",
                                    100, -5, 5);

  TH1F *hist_clustersphi = new TH1F("Clusters phi", "Clusters phi; phi; Events",
                                    100, -4, 4);

  TH1F *hist_clustersm = new TH1F("Clusters m", "Clusters m; m; Events",
                                  100, -0.001, 0.001);

  TH1F *hist_particlespt = new TH1F("Particles pt", "Particles pt; pt; Events",
                                    100, 0, 3000);

  TH1F *hist_particleseta = new TH1F("Particles eta", "Particles eta; eta; Events",
                                     100, -6, 6);

  TH1F *hist_particlesphi = new TH1F("Particles phi", "Particles phi; phi; Events",
                                     100, -4, 4);

  TH1F *hist_particlesm = new TH1F("Particles m", "Particles m; m; Events",
                                   100, -0.1, 0.1);

  TH1F *hist_particlespdgid = new TH1F("Particles pdgID", "Particles pdgID; pdfID; Events",
                                       100, 0, 3500);

  // Fill histograms
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
  {
    std::cout << nentries - i << "\n";
    nbytes = tree->GetEntry(i);

    hist_muav->Fill(muav);
    hist_npvvsmuav->Fill(npv, muav);
    hist_npvvsntracks->Fill(npv, tracks_pt->size());
    hist_npvvsnclusters->Fill(npv, clusters_pt->size());
    hist_muavvsntracks->Fill(muav, tracks_pt->size());
    hist_muavvsnclusters->Fill(muav, clusters_pt->size());
    hist_trackspt->Fill(tracks_pt->size());

    for (int tr = 0; tr < tracks_pt->size(); tr++)
    {
      hist_trackspt->Fill(tracks_pt->at(tr));
    }

    for (int tr = 0; tr < tracks_eta->size(); tr++)
    {
      hist_trackseta->Fill(tracks_eta->at(tr));
    }

    for (int tr = 0; tr < tracks_phi->size(); tr++)
    {
      hist_tracksphi->Fill(tracks_phi->at(tr));
    }

    for (int tr = 0; tr < tracks_m->size(); tr++)
    {
      hist_tracksm->Fill(tracks_m->at(tr));
    }

    for (int tr = 0; tr < tracks_vtx->size(); tr++)
    {
      hist_tracksvtx->Fill(tracks_vtx->at(tr));
    }

    for (int tr = 0; tr < clusters_pt->size(); tr++)
    {
      hist_clusterspt->Fill(clusters_pt->at(tr));
    }

    for (int tr = 0; tr < clusters_eta->size(); tr++)
    {
      hist_clusterseta->Fill(clusters_eta->at(tr));
    }

    for (int tr = 0; tr < clusters_phi->size(); tr++)
    {
      hist_clustersphi->Fill(clusters_phi->at(tr));
    }

    for (int tr = 0; tr < clusters_m->size(); tr++)
    {
      hist_clustersm->Fill(clusters_m->at(tr));
    }

    for (int tr = 0; tr < particles_pt->size(); tr++)
    {
      hist_particlespt->Fill(particles_pt->at(tr));
    }

    for (int tr = 0; tr < particles_eta->size(); tr++)
    {
      hist_particleseta->Fill(particles_eta->at(tr));
    }

    for (int tr = 0; tr < particles_phi->size(); tr++)
    {
      hist_particlesphi->Fill(particles_phi->at(tr));
    }

    for (int tr = 0; tr < particles_m->size(); tr++)
    {
      hist_particlesm->Fill(particles_m->at(tr));
    }

    for (int tr = 0; tr < particles_pdgid->size(); tr++)
    {
      hist_particlespdgid->Fill(particles_pdgid->at(tr));
    }
  }

  // Print histograms
  hist_muav->SetFillColor(3);
  hist_muav->Draw();
  canvas->Print("Mu_Average.pdf");
  canvas->Clear();

  hist_npvvsmuav->Draw("COLZ");
  canvas->Print("NPV_vs_Mu_Average.pdf");
  canvas->Clear();

  hist_npvvsntracks->Draw("COLZ");
  canvas->Print("NPV_vs_nTracks.pdf");
  canvas->Clear();

  hist_npvvsnclusters->Draw("COLZ");
  canvas->Print("NPV_vs_nClusters.pdf");
  canvas->Clear();

  hist_muavvsntracks->Draw("COLZ");
  canvas->Print("Mu_Average_vs_nTracks.pdf");
  canvas->Clear();

  hist_muavvsnclusters->Draw("COLZ");
  canvas->Print("Mu_Average_vs_nClusters.pdf");
  canvas->Clear();

  hist_trackspt->SetFillColor(3);
  hist_trackspt->Draw();
  canvas->Print("Tracks_pt.pdf");
  canvas->Clear();

  hist_trackseta->SetFillColor(3);
  hist_trackseta->Draw();
  canvas->Print("Tracks_eta.pdf");
  canvas->Clear();

  hist_tracksphi->SetFillColor(3);
  hist_tracksphi->Draw();
  canvas->Print("Tracks_phi.pdf");
  canvas->Clear();

  hist_tracksm->SetFillColor(3);
  hist_tracksm->Draw();
  canvas->Print("Tracks_m.pdf");
  canvas->Clear();

  hist_tracksvtx->SetFillColor(3);
  hist_tracksvtx->Draw();
  canvas->Print("Tracks_vtx.pdf");
  canvas->Clear();

  hist_clusterspt->SetFillColor(3);
  hist_clusterspt->Draw();
  canvas->Print("Clusters_pt.pdf");
  canvas->Clear();

  hist_clusterseta->SetFillColor(3);
  hist_clusterseta->Draw();
  canvas->Print("Clusters_eta.pdf");
  canvas->Clear();

  hist_clustersphi->SetFillColor(3);
  hist_clustersphi->Draw();
  canvas->Print("Clusters_phi.pdf");
  canvas->Clear();

  hist_clustersm->SetFillColor(3);
  hist_clustersm->Draw();
  canvas->Print("Clusters_m.pdf");
  canvas->Clear();

  hist_particlespt->SetFillColor(3);
  hist_particlespt->Draw();
  canvas->Print("Particles_pt.pdf");
  canvas->Clear();

  hist_particleseta->SetFillColor(3);
  hist_particleseta->Draw();
  canvas->Print("Particles_eta.pdf");
  canvas->Clear();

  hist_particlesphi->SetFillColor(3);
  hist_particlesphi->Draw();
  canvas->Print("Particles_phi.pdf");
  canvas->Clear();

  hist_particlesm->SetFillColor(3);
  hist_particlesm->Draw();
  canvas->Print("Particles_m.pdf");
  canvas->Clear();

  hist_particlespdgid->SetFillColor(3);
  hist_particlespdgid->Draw();
  canvas->Print("Particles_pdgID.pdf");
  canvas->Clear();
}
