#include "TFile.h"
#include "TGraph.h"
#include "fstream"

void PlotData()
{   
    TGraph* graph = new TGraph();

    fstream data;

    data.open("data.dat", ios::in);

    const Int_t n = 10;

    Double_t eff[n] = {2.51, 1.67, 1.45, 1.15, 1.21, 0.77, 0.64, 0.66, 0.62, 0.494};
    Double_t inceff[n] = {0.01, 0.02, 0.01, 0.03, 0.03, 0.01, 0.02, 0.01, 0.01, 0.007};
    Double_t nrj[n] = {121.7817, 244.6975, 344.2785, 411.1163, 443.965, 778.904, 867.378, 964.079, 1112.074, 1408.006};
    Double_t incnrj[n] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    auto gr = new TGraphErrors(n,nrj,eff,incnrj,inceff);

    double energy;
    double weight;

    /*while(1)
    {
        data >> energy >> weight;
        graph->AddPoint(energy,weight);
        if(data.eof()) break;
    }*/

    gr->Draw("ALP");

    auto fa = new TF1("fa","exp([0])*(TMath::Power(x, [1]))",0,1400);
    gr->Fit("fa");
}