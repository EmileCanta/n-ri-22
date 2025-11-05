void PlotOneHist()
{
    TFile *file;
    TTree *tsingle;
    TTree *tcoinc;

    file = TFile::Open("/Users/cantacuzene/data/n-ri-22/runs/sorted_runs/84Ga/All.root", "READ");

    tcoinc = (TTree*)file->Get("tcoinc");

    TH1I* h1 = new TH1I("Hist", "Hist", 7000,0,7000);

    std::vector<Double_t> *var1 = 0;
    std::vector<Double_t> *var2 = 0;

    tcoinc->SetBranchAddress("GeBeta_ECond",&var1);
    tcoinc->SetBranchAddress("GeBeta_tDiff",&var2);

    for(Long64_t i = 0; i < tcoinc->GetEntries(); ++i)
    {
        tcoinc->GetEntry(i);
    
        for(ULong_t j = 0; j < var1->size(); ++j)
        {   
            if(var2->at(j) >= 1.225 && var2->at(j) <= 1.302)
            {
                h1->Fill(var1->at(j));
            }
        }
    }

    //Graphics part

    h1->Draw();

    h1->SetLineColor(kRed);
    h1->SetLineWidth(4);

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

    legend->AddEntry(h1,"Beta conditionned","l");
    legend->SetBorderSize(0);
    legend->SetTextSize(0.1);

    legend->Draw();

    gPad->SetLeftMargin(0.20);
    gPad->SetBottomMargin(0.25);
    
    gPad->SetLeftMargin(0.20);
    gPad->SetBottomMargin(0.25);

    gPad->RedrawAxis();
}