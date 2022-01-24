#include <iostream>
#include <string>
#include <stdio.h>

void DataMC()
{
    // ROOT File
    TFile *file = TFile::Open("ttbar_8TeV.root");

    // Tree and print
    TTree *tree = (TTree *)file->Get("mini");
    tree->Print();

    // Variables
    Bool_t e_trig;
    Bool_t mu_trig;
    Bool_t good_vtx;
    UInt_t lep_n;
    UInt_t jet_n;
    Float_t MET;
    Float_t MET_phi;

    Float_t scalef_pileup;
    Float_t scalef_e;
    Float_t scalef_mu;
    Float_t scalef_btag;
    Float_t scalef_trigger;
    Float_t scalef_jvfsf;
    Float_t scalef_zvertex;

    Float_t lep_pt[10];
    Float_t lep_eta[10];
    Float_t lep_phi[10];
    Float_t lep_E[10];
    Int_t lep_type[10];
    Float_t lep_ptcone30[10];
    Float_t lep_etcone20[10];

    Float_t jet_pt[10];
    Float_t jet_eta[10];
    Float_t jet_jvf[10];
    Float_t jet_mv1[10];

    tree->SetBranchAddress("trigE", &e_trig);
    tree->SetBranchAddress("trigM", &mu_trig);
    tree->SetBranchAddress("hasGoodVertex", &good_vtx);
    tree->SetBranchAddress("lep_n", &lep_n);
    tree->SetBranchAddress("jet_n", &jet_n);
    tree->SetBranchAddress("met_et", &MET);
    tree->SetBranchAddress("met_phi", &MET_phi);

    tree->SetBranchAddress("scaleFactor_PILEUP", &scalef_pileup);
    tree->SetBranchAddress("scaleFactor_ELE", &scalef_e);
    tree->SetBranchAddress("scaleFactor_MUON", &scalef_mu);
    tree->SetBranchAddress("scaleFactor_BTAG", &scalef_btag);
    tree->SetBranchAddress("scaleFactor_TRIGGER", &scalef_trigger);
    tree->SetBranchAddress("scaleFactor_JVFSF", &scalef_jvfsf);
    tree->SetBranchAddress("scaleFactor_ZVERTEX", &scalef_zvertex);

    tree->SetBranchAddress("lep_pt", &lep_pt);
    tree->SetBranchAddress("lep_eta", &lep_eta);
    tree->SetBranchAddress("lep_phi", &lep_phi);
    tree->SetBranchAddress("lep_E", &lep_E);
    tree->SetBranchAddress("lep_type", &lep_type);
    tree->SetBranchAddress("lep_ptcone30", &lep_ptcone30);
    tree->SetBranchAddress("lep_etcone20", &lep_etcone20);

    tree->SetBranchAddress("jet_pt", &jet_pt);
    tree->SetBranchAddress("jet_eta", &jet_eta);
    tree->SetBranchAddress("jet_jvf", &jet_jvf);
    tree->SetBranchAddress("jet_MV1", &jet_mv1);

    // Canvas
    TCanvas *canvas = new TCanvas("Canvas", "", 800, 600);

    // Histograms
    TH1F *cutflow = new TH1F("Cutflow", "Cutflow; Cut; Events", 10, 0, 10);

    TH1F *hist_lepton_pt = new TH1F(
        "Lepton pT", "Lepton pT; pT (GeV); Events",
        50, 0, 1000);

    TH1F *hist_lepton_pt_cone30 = new TH1F(
        "Track isolation", "Track isolation; lep_ptcone30/lep_pt; Events",
        50, 0, 0.2);

    TH1F *hist_lepton_et_cone20 = new TH1F(
        "Calorimeter isolation",
        "Calorimeter isolation; lep_etcone30/lep_pt; Events",
        50, 0, 0.2);

    TH1F *hist_lepton_eta = new TH1F(
        "Leptons eta", "Lepton eta; eta; Events",
        50, -5, 5);

    TH1F *hist_njets = new TH1F(
        "Number of jets", "n-jets; Number of Jet; Events",
        10, 0, 10);

    TH1F *hist_jets_pt = new TH1F(
        "Jets pT", "Jet pT; pT (GeV); Events",
        50, 0, 1000);

    TH1F *hist_jets_eta = new TH1F(
        "Jets eta", "Jet eta; eta; Events",
        50, -5, 5);

    TH1F *hist_jets_JVF = new TH1F(
        "Jets JVF", "Jet JVF; JVF; Events",
        50, 0, 1);

    TH1F *hist_jets_MV1 = new TH1F(
        "Jets MV1", "Jet MV1; MV1; Events",
        50, 0.5, 1);

    TH1F *hist_nbjets = new TH1F(
        "Number of b-jets", "n-bjets; Number of b-Jets; Events",
        50, 0, 6);

    TH1F *hist_MET = new TH1F(
        "MET", "MET; MET (GeV); Events",
        50, 0, 200);

    TH1F *hist_mTW = new TH1F(
        "mTW", "mTW; mTW (GeV); Events",
        50, 0, 200);

    int nentries, nbytes, i;
    nentries = (Int_t)tree->GetEntries();

    int cut1 = 0;
    int cut2 = 0;
    int cut3 = 0;
    int cut4 = 0;
    int cut5 = 0;
    int cut6 = 0;
    int cut7 = 0;
    int cut8 = 0;

    for (i = 0; i < nentries; i++)
    {
        nbytes = tree->GetEntry(i);
        std::cout << nentries - i << "\n";

        // MC scaling
        Float_t MC_events = 49761200.21;
        Float_t filter = 0.072212854;
        Float_t xsec = 137.29749; // 1/(pbarn)

        // MC luminisity
        Float_t L_MC = MC_events * filter / xsec;

        Float_t MC_weight = 1000 / L_MC;

        Float_t scalef = scalef_pileup * scalef_e * scalef_mu * scalef_btag * scalef_trigger * scalef_jvfsf * scalef_zvertex;

        Float_t event_weight = scalef * MC_weight;

        // First cut: Good vertex
        if (!good_vtx)
            continue;
        cut1++;
        cutflow->Fill(1, event_weight);

        // Second cut: Trigger
        if (!e_trig && !mu_trig)
            continue;
        cut2++;
        cutflow->Fill(2, event_weight);

        // Preselection of good leptons
        int n_mu = 0;
        int n_el = 0;
        int n_lep = 0;
        int g_lep = 0;

        // Loop over leptons
        for (unsigned int j = 0; j < lep_n; j++)
        {

            if (lep_pt[j] < 25000.0)
                continue;
            hist_lepton_pt->Fill(lep_pt[j] / 1000, event_weight);

            if (lep_ptcone30[j] / lep_pt[j] > 0.15)
                continue;
            hist_lepton_pt_cone30->Fill(lep_ptcone30[j] / lep_pt[j], event_weight);

            if (lep_etcone20[j] / lep_pt[j] > 0.15)
                continue;
            hist_lepton_et_cone20->Fill(lep_etcone20[j] / lep_pt[j], event_weight);

            if (lep_type[j] == 13 && TMath::Abs(lep_eta[j]) < 2.5)
            {
                n_mu++;
                g_lep = j;
                hist_lepton_eta->Fill(lep_eta[j], event_weight);
            }

            if (lep_type[j] == 11 && TMath::Abs(lep_eta[j]) < 2.47)
            {
                if (TMath::Abs(lep_eta[j]) < 1.37 || TMath::Abs(lep_eta[j]) > 1.52)
                {
                    n_el++;
                    g_lep = j;
                    hist_lepton_eta->Fill(lep_eta[j], event_weight);
                }
            }
            n_lep++;
        }

        // Third cut: One good Lepton
        if (n_lep != 1)
            continue;
        cutflow->Fill(3, event_weight);
        cut3++;

        int n_jets = 0;
        int n_bjets = 0;

        // Number of jets distribution
        hist_njets->Fill(jet_n, event_weight);

        // Fourth cut: At least 4 jets
        if (jet_n < 4)
            continue;
        cutflow->Fill(4, event_weight);
        cut4++;

        for (unsigned int j = 0; j < jet_n; j++)
        {
            // To complete: apply jet cuts to find the good jets
            if (jet_pt[j] < 25000.)
                continue;
            hist_jets_pt->Fill(jet_pt[j] / 1000, event_weight);

            // Eta cut
            if (jet_eta[j] > 2.5)
                continue;
            hist_jets_eta->Fill(jet_eta[j], event_weight);

            // JVF cleaning
            if (jet_pt[j] < 50000. && TMath::Abs(jet_eta[j]) < 2.4)
            {
                if (jet_jvf[j] < 0.5)
                    continue;
            }
            hist_jets_JVF->Fill(jet_jvf[j], event_weight);

            n_jets++;

            // cut on 0.7892 MV1 and count the number of b-jets
            if (jet_mv1[j] < 0.7892)
                continue;

            n_bjets++;
            hist_jets_MV1->Fill(jet_mv1[j], event_weight);
        }

        // Fifth cut: At least 4 good jets
        if (n_jets < 4)
            continue;
        cutflow->Fill(5, event_weight);
        cut5++;

        // Sixth cut: at least one b-jet
        if (n_bjets < 2)
            continue;
        cutflow->Fill(6, event_weight);
        cut6++;
        hist_nbjets->Fill(n_bjets, event_weight);

        // Seventh cut: MET > 30 GeV
        if (MET < 30000.)
            continue;
        cutflow->Fill(7, event_weight);
        cut7++;
        hist_MET->Fill(MET / 1000, event_weight);

        // TLorentzVector definitions
        TLorentzVector Lepton = TLorentzVector();
        Lepton.SetPtEtaPhiE(
            lep_pt[g_lep],
            lep_eta[g_lep],
            lep_phi[g_lep],
            lep_E[g_lep]);

        TLorentzVector MeT = TLorentzVector();
        MeT.SetPtEtaPhiE(
            MET,
            0,
            MET_phi,
            MET);

        // Calculation of the mTW using TLorentz vectors
        float mTW = sqrt(2 * Lepton.Pt() * MeT.Et() * (1 - cos(Lepton.DeltaPhi(MeT))));

        // Eight cut: mTW > 30 GeV
        if (mTW < 30000.)
            continue;
        cutflow->Fill(8, event_weight);
        cut8++;
        hist_mTW->Fill(mTW / 1000, event_weight);
    }

    std::cout << "Done!" << std::endl;
    std::cout << "All events:" << nentries << std::endl;
    std::cout << "Cut1:" << cut1 << std::endl;
    std::cout << "Cut2:" << cut2 << std::endl;
    std::cout << "Cut3:" << cut3 << std::endl;
    std::cout << "Cut4:" << cut4 << std::endl;
    std::cout << "Cut5:" << cut5 << std::endl;
    std::cout << "Cut6:" << cut6 << std::endl;
    std::cout << "Cut7:" << cut7 << std::endl;
    std::cout << "Cut8:" << cut8 << std::endl;

    canvas->SetLogy();
    cutflow->SetMarkerStyle(22);
    cutflow->SetMarkerColor(kGreen);
    cutflow->Draw("");
    canvas->Print("cutflow_mc.pdf");
    canvas->Clear();

    hist_lepton_pt->SetMarkerStyle(22);
    hist_lepton_pt->SetMarkerColor(kGreen);
    hist_lepton_pt->Draw();
    canvas->Print("hist_lepton_pt_mc.pdf");
    canvas->Clear();

    hist_lepton_pt_cone30->SetMarkerStyle(22);
    hist_lepton_pt_cone30->SetMarkerColor(kGreen);
    hist_lepton_pt_cone30->Draw();
    canvas->Print("hist_lepton_pt_cone30_mc.pdf");
    canvas->Clear();

    hist_lepton_et_cone20->SetMarkerStyle(22);
    hist_lepton_et_cone20->SetMarkerColor(kGreen);
    hist_lepton_et_cone20->Draw();
    canvas->Print("hist_lepton_et_cone20_mc.pdf");
    canvas->Clear();

    hist_lepton_eta->SetMarkerStyle(22);
    hist_lepton_eta->SetMarkerColor(kGreen);
    hist_lepton_eta->Draw();
    canvas->Print("hist_lepton_eta_mc.pdf");
    canvas->Clear();

    hist_njets->SetMarkerStyle(22);
    hist_njets->SetMarkerColor(kGreen);
    hist_njets->Draw();
    canvas->Print("hist_njets_mc.pdf");
    canvas->Clear();

    hist_jets_pt->SetMarkerStyle(22);
    hist_jets_pt->SetMarkerColor(kGreen);
    hist_jets_pt->Draw();
    canvas->Print("hist_jets_pt_mc.pdf");
    canvas->Clear();

    hist_jets_eta->SetMarkerStyle(22);
    hist_jets_eta->SetMarkerColor(kGreen);
    hist_jets_eta->Draw();
    canvas->Print("hist_jets_eta_mc.pdf");
    canvas->Clear();

    hist_jets_JVF->SetMarkerStyle(22);
    hist_jets_JVF->SetMarkerColor(kGreen);
    hist_jets_JVF->Draw();
    canvas->Print("hist_jet_JVF_mc.pdf");
    canvas->Clear();

    hist_jets_MV1->SetMarkerStyle(22);
    hist_jets_MV1->SetMarkerColor(kGreen);
    hist_jets_MV1->Draw();
    canvas->Print("hist_jet_MV1_mc.pdf");
    canvas->Clear();

    hist_nbjets->SetMarkerStyle(22);
    hist_nbjets->SetMarkerColor(kGreen);
    hist_nbjets->Draw();
    canvas->Print("hist_nbjets_mc.pdf");
    canvas->Clear();

    canvas->SetLogy(false);
    hist_MET->SetMarkerStyle(22);
    hist_MET->SetMarkerColor(kGreen);
    hist_MET->Draw();
    canvas->Print("hist_MET_mc.pdf");
    canvas->Clear();

    hist_mTW->SetMarkerStyle(22);
    hist_mTW->SetMarkerColor(kGreen);
    hist_mTW->Draw();
    canvas->Print("hist_mTW_mc.pdf");
    canvas->Clear();
}