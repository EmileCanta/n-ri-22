void ComputeRatios()
{
    TFile* file = TFile::Open("/Users/cantacuzene/data/n-ri-22/runs/sorted_runs/Efficiency/152euEt252cf_SansGe.root", "READ");

    TH1D* hist = (TH1D*)file->Get("Tetra_Rings");

    cout << "R2/R1: " << (hist->GetBinContent(5))/(hist->GetBinContent(3)) << endl;
    cout << "R3/R1: " << (hist->GetBinContent(7))/(hist->GetBinContent(3)) << endl;
    cout << "R4/R1: " << (hist->GetBinContent(9))/(hist->GetBinContent(3)) << endl;
    cout << "R3/R2: " << (hist->GetBinContent(7))/(hist->GetBinContent(5)) << endl;
    cout << "R4/R2: " << (hist->GetBinContent(9))/(hist->GetBinContent(5)) << endl;
    cout << "R4/R3: " << (hist->GetBinContent(9))/(hist->GetBinContent(7)) << endl;
}