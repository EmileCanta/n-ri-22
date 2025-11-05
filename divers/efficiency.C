#include <TApplication.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TStyle.h>

void efficiency()
{

    const int n = 5;
    double x[n]        = {121.8, 244.7, 661.6, 1173.23, 1332.5};
    double y1[n]        = {0.0891, 0.0604, 0.0393, 0.0231, 0.0219};
    double ex[n]       = {0,0,0,0,0}; // erreur sur x
    double ey[n]       = {0.00891, 0.00604, 0.007, 0.00231, 0.00219}; // erreur sur y

    TCanvas *c1 = new TCanvas("c1", "Graph avec erreurs", 800, 600);



    TGraphErrors *gr1 = new TGraphErrors(n, x, y1, ex, ey);
    gr1->SetMarkerStyle(21);
    gr1->SetMarkerColor(kBlue);
    gr1->SetLineColor(kBlue);
    gr1->Draw("AP");

    

    auto fitFunc = new TF1("fitFunc","[0]*TMath::Power(x, [1])",0.,1408.);
    fitFunc->SetLineColor(kRed);
    gr1->Fit(fitFunc, "R"); // "R" limite le fit à la plage spécifiée (0 à 9)


    c1->Update();
}
