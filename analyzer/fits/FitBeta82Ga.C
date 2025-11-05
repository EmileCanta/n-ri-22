#include "../include/Fitter82Ga.h"

Double_t Bateman_tot(Double_t *x, Double_t *par)
{
	
	if(x[0] < t0)
    {
      	return (135.689);
    }
    
  	if(x[0] >= t0 && x[0] < tc+t0)
    {	
      	return (135.689)
		+(-exp(-x[0]*l1)*(exp(t0*l1)-exp(x[0]*l1))*1274.84)
		+((-exp(-x[0]*l1-x[0]*l2)*(-1+0.706489)*(exp(x[0]*l1+t0*l2)*l1-exp(x[0]*l1+x[0]*l2)*l1-exp(t0*l1+x[0]*l2)*l2+exp(x[0]*l1+x[0]*l2)*l2)*1274.84)/(-l1+l2))
		+((exp(-x[0]*l1-x[0]*l3)*(0.706489)*(exp(x[0]*l1+t0*l3)*l1-exp(x[0]*l1+x[0]*l3)*l1-exp(t0*l1+x[0]*l3)*l3+exp(x[0]*l1+x[0]*l3)*l3)*1274.84)/(-l1+l3));
    }
    
  	if(x[0] >= tc+t0 && x[0] <= ta)
    {
     	return (135.689)
		+(-exp(-x[0]*l1)*(exp(t0*l1)-exp((t0+tc)*l1))*1274.84)
		+((-exp(-x[0]*l1-x[0]*l2)*(-1+0.706489)*(-exp(x[0]*l1+t0*l2)*l1+exp(x[0]*l1+(t0+tc)*l2)*l1+exp(t0*l1+x[0]*l2)*l2-exp((t0+tc)*l1+x[0]*l2)*l2)*1274.84)/(l1-l2))
		+((exp(-x[0]*l1-x[0]*l3)*(0.706489)*(-exp(x[0]*l1+t0*l3)*l1+exp(x[0]*l1+(t0+tc)*l3)*l1+exp(t0*l1+x[0]*l3)*l3-exp((t0+tc)*l1+x[0]*l3)*l3)*1274.84)/(l1-l3));
    }
    
  	if(x[0] > ta)
    {
    	return 0;
    }
    
    return 0;
}

Double_t bgd(Double_t *x, Double_t *par)
{
	
	if(0 < x[0] && x[0] < ta)
    {
      	return (135.689);
    }
    
    return 0;

}


Double_t Bateman_A1(Double_t *x, Double_t *par)
{  
	if(x[0] < t0)
    {
      	return 0;
    }
    
  	if(x[0] >= t0 && x[0] < tc+t0)
    {	
      	return (-exp(-x[0]*l1)*(exp(t0*l1)-exp(x[0]*l1))*1274.84);
    }
    
  	if(x[0] >= tc+t0 && x[0] <= ta)
    {
     	return (-exp(-x[0]*l1)*(exp(t0*l1)-exp((t0+tc)*l1))*1274.84);
    }
    
  	if(x[0] > ta)
    {
    	return 0;
    }
    
    return 0;
}


Double_t Bateman_A2(Double_t *x, Double_t *par)
{		
	if(x[0] < t0)
    {
      	return 0;
    }
    
  	if(x[0] >= t0 && x[0] < tc+t0)
    {	
      	return ((-exp(-x[0]*l1-x[0]*l2)*(-1+0.706489)*(exp(x[0]*l1+t0*l2)*l1-exp(x[0]*l1+x[0]*l2)*l1-exp(t0*l1+x[0]*l2)*l2+exp(x[0]*l1+x[0]*l2)*l2)*1274.84)/(-l1+l2));
    }
    
  	if(x[0] >= tc+t0 && x[0] <= ta)
    {	
     	return ((-exp(-x[0]*l1-x[0]*l2)*(-1+0.706489)*(-exp(x[0]*l1+t0*l2)*l1+exp(x[0]*l1+(t0+tc)*l2)*l1+exp(t0*l1+x[0]*l2)*l2-exp((t0+tc)*l1+x[0]*l2)*l2)*1274.84)/(l1-l2));
    }
    
  	if(x[0] > ta)
    {
    	return 0;
    }
    
    return 0;
}

Double_t Bateman_A3(Double_t *x, Double_t *par)
{		
	if(x[0] < t0)
    {
      	return 0;
    }
    
  	if(x[0] >= t0 && x[0] < tc+t0)
    {	
      	return ((exp(-x[0]*l1-x[0]*l3)*(0.706489)*(exp(x[0]*l1+t0*l3)*l1-exp(x[0]*l1+x[0]*l3)*l1-exp(t0*l1+x[0]*l3)*l3+exp(x[0]*l1+x[0]*l3)*l3)*1274.84)/(-l1+l3));
    }
    
  	if(x[0] >= tc+t0 && x[0] <= ta)
    {	
     	return ((exp(-x[0]*l1-x[0]*l3)*(0.706489)*(-exp(x[0]*l1+t0*l3)*l1+exp(x[0]*l1+(t0+tc)*l3)*l1+exp(t0*l1+x[0]*l3)*l3-exp((t0+tc)*l1+x[0]*l3)*l3)*1274.84)/(l1-l3));
    }
    
  	if(x[0] > ta)
    {
    	return 0;
    }
    
    return 0;
}

void FitBeta82Ga()
{
	TCanvas *c1 = new TCanvas();
	
	TFile *input = new TFile("/Users/cantacuzene/data/n-ri-22/runs/sorted_runs/82Ga/RUN121.root");
	
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0001);
	
	TH1D *hist_beta = (TH1D*)input->Get("AlignedBeta_tSingle");
  	
  	TF1 *FitBatemanTot = new TF1("Bateman_tot", Bateman_tot, 0.0e3, 6.5e3);
  	TF1 *FitBgd = new TF1("bgd", bgd, 0.0e3, 6.5e3);
  	TF1 *FitA1 = new TF1("Bateman_A1", Bateman_A1, 0.0e3, 6.5e3);
  	TF1 *FitA2 = new TF1("Bateman_A2", Bateman_A2, 0.0e3, 6.5e3);
	TF1 *FitA3 = new TF1("Bateman_A3", Bateman_A3, 0.0e3, 6.5e3);

  	hist_beta->Draw();

	FitBatemanTot->SetLineColor(kOrange);
  	FitBatemanTot->Draw("SAME");
  	
  	FitBgd->SetLineColor(kGreen);
  	FitBgd->Draw("SAME");

  	FitA1->SetLineColor(kCyan);
  	FitA1->Draw("SAME");
  	
  	FitA2->SetLineColor(kBlack);
  	FitA2->Draw("SAME");

	FitA3->SetLineColor(kRed);
  	FitA3->Draw("SAME");
  	
  	TLegend *legend = new TLegend(0.1,0.7,0.3,0.9);
    legend->AddEntry(hist_beta,"Beta activity","lpe");
    legend->AddEntry(FitBatemanTot,"Bateman fit","l");
    legend->AddEntry(FitBgd,"Background","l");
    legend->AddEntry(FitA1,"Galium 82","l");
    legend->AddEntry(FitA2,"Germanium 82","l");
	legend->AddEntry(FitA3,"Germanium 81","l");
    legend->Draw();

    hist_beta->SetLineColor(kRed);
    hist_beta->SetLineWidth(4);

	FitBatemanTot->SetLineWidth(6);
	FitBgd->SetLineWidth(6);
	FitA1->SetLineWidth(6);
	FitA2->SetLineWidth(6);
	FitA3->SetLineWidth(6);

    hist_beta->GetXaxis()->SetTitle("Cycle time (ms)");
    hist_beta->GetYaxis()->SetTitle("Counts / ms");

    hist_beta->GetXaxis()->SetTitleSize(0.07);
    hist_beta->GetYaxis()->SetTitleSize(0.07);

    hist_beta->GetXaxis()->SetLabelSize(0.07);
    hist_beta->GetYaxis()->SetLabelSize(0.07);

    /*h1->GetXaxis()->SetTitleOffset(0.87);
    h1->GetYaxis()->SetTitleOffset(0.40);*/

    hist_beta->GetXaxis()->SetTickSize(0.07);

    gStyle->SetOptTitle(0);

    legend->SetBorderSize(0);

    gPad->SetLeftMargin(0.20);
    gPad->SetBottomMargin(0.25);
    
    gPad->RedrawAxis();

	Double_t IntA1 = FitA1->Integral(0.0e3, 6.5e3);
  	Double_t IntBgd = FitBgd->Integral(0.0e3, 6.5e3);
	Double_t IntA2 = FitA2->Integral(0.0e3, 6.5e3);
	Double_t IntA3 = FitA3->Integral(0.0e3, 6.5e3);

	cout << "IntegralBgd:" << IntBgd << endl;
	
  	cout << "IntegralA1:" << IntA1 << endl;
	cout << "IntegralA2:" << IntA2 << endl;
	cout << "IntegralA3:" << IntA3 << endl;
}
