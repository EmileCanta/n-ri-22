#include <TApplication.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TStyle.h>

void systematics()
{

    const int n = 4;
    double x[n]        = {1,2,3,4};
    double y1[n]        = {85, 84, 97.1, 87};
    double ex[n]       = {0,0,0,0}; // erreur sur x
    double ey[n]       = {10, 7, 1.1, 2}; // erreur sur y

    TCanvas *c1 = new TCanvas("c1", "Graph avec erreurs", 800, 600);



    TGraphErrors *gr1 = new TGraphErrors(n, x, y1, ex, ey);
    gr1->SetMarkerStyle(21);
    gr1->SetMarkerColor(kBlue);
    gr1->SetLineColor(kBlue);
    gr1->Draw("AP");

    

    auto fitFunc = new TF1("fitFunc","[0]*TMath::Power(x, [1])",0.,1408.);
    fitFunc->SetLineColor(kRed);
    //gr1->Fit(fitFunc, "R"); // "R" limite le fit à la plage spécifiée (0 à 9)


    c1->Update();
}
