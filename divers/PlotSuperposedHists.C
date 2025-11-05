void PlotSuperposedHists()
{
    TFile *file;
    TTree *tsingle;
    TTree *tcoinc;

    file = TFile::Open("/Users/cantacuzene/data/n-ri-22/runs/sorted_runs/84Ga/All.root", "READ");

    tsingle = (TTree*)file->Get("tsingle");
    tcoinc = (TTree*)file->Get("tcoinc");

    TH1I* h1 = new TH1I("Single", "Single", 7000,0,7000);
    TH1I* h2 = new TH1I("Cond1", "Cond1", 7000,0,7000);
    TH1I* h3 = new TH1I("Cond2", "Cond2", 7000,0,7000);

    std::vector<Double_t> *energy1 = 0;
    std::vector<Double_t> *energy2 = 0;
    std::vector<Double_t> *energy3 = 0;
    std::vector<Double_t> *timediff = 0;

    tsingle->SetBranchAddress("Ge_ESingle",&energy1);
    tcoinc->SetBranchAddress("GeBeta_ECond",&energy2);
    tcoinc->SetBranchAddress("GeTetra_ECond",&energy3);
    tcoinc->SetBranchAddress("GeBeta_tDiff",&timediff);

    for(Long64_t i = 0; i < tsingle->GetEntries(); ++i)
    {
        tsingle->GetEntry(i);
    
        for(ULong_t j = 0; j < energy1->size(); ++j)
        {   
            h1->Fill(energy1->at(j));
        }
    }

    for(Long64_t i = 0; i < tcoinc->GetEntries(); ++i)
    {
        tcoinc->GetEntry(i);
    
        for(ULong_t j = 0; j < energy2->size(); ++j)
        {   
            if(timediff->at(j) >= 1.225 && timediff->at(j) <= 1.302)
            {
                h2->Fill(energy2->at(j));
            }
        }
    }

    for(Long64_t i = 0; i < tcoinc->GetEntries(); ++i)
    {
        tcoinc->GetEntry(i);
    
        for(ULong_t j = 0; j < energy3->size(); ++j)
        {   
            h3->Fill(energy3->at(j));
        }
    }

    //Graphics part

    h1->Draw();
    h2->Draw("same");
    h3->Draw("same");

    h1->SetLineColor(kBlack);
    h1->SetLineWidth(4);

    //h2->SetFillColor(kRed);
    h2->SetLineColor(kRed);
    h2->SetLineWidth(1);

    h3->SetLineColor(kBlue);
    h3->SetLineWidth(1);

    h1->GetXaxis()->SetTitle("Energy (keV)");
    h1->GetYaxis()->SetTitle("Counts / keV");

    h1->GetXaxis()->SetTitleSize(0.10);
    h1->GetYaxis()->SetTitleSize(0.10);

    h1->GetXaxis()->SetLabelSize(0.08);
    h1->GetYaxis()->SetLabelSize(0.08);

    h1->GetXaxis()->SetTitleOffset(0.87);
    h1->GetYaxis()->SetTitleOffset(0.40);

    h1->GetXaxis()->SetTickSize(0.07);

    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    TLegend* legend = new TLegend(0.1,0.7,0.3,0.9);

    legend->AddEntry(h1,"Single","l");
    legend->AddEntry(h2,"Beta conditionned","f");
    legend->AddEntry(h3,"Neutron conditionned","f");
    legend->SetBorderSize(0);
    legend->SetTextSize(0.1);

    legend->Draw();

    gPad->SetLeftMargin(0.20);
    gPad->SetBottomMargin(0.25);

    gPad->RedrawAxis();
}