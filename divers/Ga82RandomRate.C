#include "Ga82RandomRate.h"

Double_t the_function(Double_t *x, Double_t *par)
{
	
	if(x[0] < t0)
    {
      	return 20*((Bgd_rate* N_cycles)+(pow((4.29395/N_cycles), 2)*theta*exp(-theta*(4.29395/N_cycles)))*N_cycles);
    }
    
  	if(x[0] >= t0 && x[0] < tc+t0)
    {	
      	return 
        20*((Bgd_rate*N_cycles)
		+((pow((4.29395+(-exp(-x[0]*l1)*(exp(t0*l1)-exp(x[0]*l1))*213.752))/N_cycles, 2))*theta*exp(-theta*((4.29395+(-exp(-x[0]*l1)*(exp(t0*l1)-exp(x[0]*l1))*213.752))/N_cycles)))*N_cycles);
    }
    
  	if(x[0] >= tc+t0 && x[0] <= ta)
    {
     	return 
        20*((Bgd_rate*N_cycles)
		+((pow((4.29395+(-exp(-x[0]*l1)*(exp(t0*l1)-exp((t0+tc)*l1))*213.752))/N_cycles, 2))*theta*exp(-theta*((4.29395+(-exp(-x[0]*l1)*(exp(t0*l1)-exp((t0+tc)*l1))*213.752))/N_cycles)))*N_cycles);
    }
    
  	if(x[0] > ta)
    {
    	return 0;
    }
    
    return 0;
}

void Ga82RandomRate()
{
	TCanvas *c1 = new TCanvas();
	
	TFile *input = new TFile("/Users/cantacuzene/data/n-ri-22/runs/sorted_runs/82Ga/a.root");
	
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0001);
	
	TH1D *hist_2n = (TH1D*)input->Get("h");
  	//TH1D *hist_single = (TH1D*)input->Get("AlignedTetra_tSingle");

  	TF1 *f1 = new TF1("the_function", the_function, 0.0e3, 6.5e3);
  	
	//hist_single->Draw();
  	hist_2n->Draw("sameshist");

  	f1->Draw("same");
  	
  	TLegend *legend = new TLegend(0.65,0.65,0.80,0.85);
	legend->SetTextFont(72);
    legend->SetTextSize(0.02);
	//legend->AddEntry(hist_single,"Single data","lpe");
    legend->AddEntry(hist_2n,"2n data","lpe");
    legend->AddEntry(f1,"Calculated random rate","l");
    legend->Draw();  	
}