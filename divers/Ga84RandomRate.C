#include "Ga84RandomRate.h"

Double_t the_function(Double_t *x, Double_t *par)
{
	
	if(x[0] < t0)
    {
      	return 4*(((Bgd_rate* N_cycles)+(pow((197.721/N_cycles), 2)*theta*exp(-theta*(197.721/N_cycles)))*N_cycles));
		
    }
    
  	if(x[0] >= t0 && x[0] < tc+t0)
    {	
      	return 
		4*(((Bgd_rate* N_cycles)
		+(pow(((
			(197.721)
			+(-exp(-x[0]*l1)*(exp(t0*l1)-exp(x[0]*l1))*129.058)
			+((-exp(-x[0]*l1-x[0]*l2)*(-1+0.752108)*(exp(x[0]*l1+t0*l2)*l1-exp(x[0]*l1+x[0]*l2)*l1-exp(t0*l1+x[0]*l2)*l2+exp(x[0]*l1+x[0]*l2)*l2)*129.058)/(-l1+l2)))
			/N_cycles),2)*theta*exp(-theta*((197.721)
											+(-exp(-x[0]*l1)*(exp(t0*l1)-exp(x[0]*l1))*129.058)
											+((-exp(-x[0]*l1-x[0]*l2)*(-1+0.752108)*(exp(x[0]*l1+t0*l2)*l1-exp(x[0]*l1+x[0]*l2)*l1-exp(t0*l1+x[0]*l2)*l2+exp(x[0]*l1+x[0]*l2)*l2)*129.058)/(-l1+l2)))
											/N_cycles))*N_cycles));
    }
    
  	if(x[0] >= tc+t0 && x[0] <= ta)
    {
     	return
		4*(((Bgd_rate* N_cycles)
		+(pow(((
			(197.721)
			+(-exp(-x[0]*l1)*(exp(t0*l1)-exp((t0+tc)*l1))*129.058)
			+((-exp(-x[0]*l1-x[0]*l2)*(-1+0.752108)*(-exp(x[0]*l1+t0*l2)*l1+exp(x[0]*l1+(t0+tc)*l2)*l1+exp(t0*l1+x[0]*l2)*l2-exp((t0+tc)*l1+x[0]*l2)*l2)*129.058)/(l1-l2)))
			/N_cycles),2)*theta*exp(-theta*((197.721)
											+(-exp(-x[0]*l1)*(exp(t0*l1)-exp((t0+tc)*l1))*129.058)
											+((-exp(-x[0]*l1-x[0]*l2)*(-1+0.752108)*(-exp(x[0]*l1+t0*l2)*l1+exp(x[0]*l1+(t0+tc)*l2)*l1+exp(t0*l1+x[0]*l2)*l2-exp((t0+tc)*l1+x[0]*l2)*l2)*129.058)/(l1-l2)))
											/N_cycles))*N_cycles));
    }
    
  	if(x[0] > ta)
    {
    	return 0;
    }
    
    return 0;
}

Double_t the_other_function(Double_t *x_2, Double_t *par_2)
{
	
	if(x_2[0] < t0)
    {
      	return 4*7.28583;
		
    }
    
  	if(x_2[0] >= t0 && x_2[0] < tc+t0)
    {	
      	return 4*((7.28583)
		+(-exp(-x_2[0]*l1)*(exp(t0*l1)-exp(x_2[0]*l1))*3.15308));
    }
    
  	if(x_2[0] >= tc+t0 && x_2[0] <= ta)
    {
     	return 4*((7.28583)
		+(-exp(-x_2[0]*l1)*(exp(t0*l1)-exp((t0+tc)*l1))*3.15308));
    }
    
  	if(x_2[0] > ta)
    {
    	return 0;
    }
    
    return 0;
}

void Ga84RandomRate()
{
	TCanvas *c1 = new TCanvas();
	
	TFile *input = new TFile("/Users/cantacuzene/data/n-ri-22/runs/sorted_runs/84Ga/AllBut97.root");
	
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0001);
	
	TH1D *hist_neutron = (TH1D*)input->Get("Aligned2n_tCond");
  	
  	TF1 *f1 = new TF1("the_function", the_function, 0.0e3, 3.3e3);
	TF1 *f2 = new TF1("the_other_function", the_other_function, 0.0e3, 3.3e3);
  	
  	hist_neutron->Draw();

	f1->SetLineColor(kOrange);
  	f1->Draw("SAME");

	f2->SetLineColor(kCyan);
  	f2->Draw("SAME");
  	
  	TLegend *legend = new TLegend(0.65,0.65,0.80,0.85);
    legend->SetTextSize(0.05);
    legend->AddEntry(hist_neutron,"Two neutron events","lpe");
    legend->AddEntry(f1,"Calculated random rate","l");
	legend->AddEntry(f2,"Galium 84","l");
    legend->Draw();

	hist_neutron->SetLineColor(kGreen+1);
    hist_neutron->SetLineWidth(4);

	f1->SetLineWidth(6);
	f2->SetLineWidth(6);

    hist_neutron->GetXaxis()->SetTitle("Cycle time (ms)");
    hist_neutron->GetYaxis()->SetTitle("Counts / 4 ms");

    hist_neutron->GetXaxis()->SetTitleSize(0.07);
    hist_neutron->GetYaxis()->SetTitleSize(0.07);

    hist_neutron->GetXaxis()->SetLabelSize(0.07);
    hist_neutron->GetYaxis()->SetLabelSize(0.07);

    hist_neutron->GetXaxis()->SetTickSize(0.07);

    gStyle->SetOptTitle(0);

    legend->SetBorderSize(0);

    gPad->SetLeftMargin(0.20);
    gPad->SetBottomMargin(0.25);
    
    gPad->RedrawAxis();

	cout << "Total minus fake:" << (f2->Integral(0.e3,3.3e3))-(f1->Integral(0.e3,3.3e3)) << endl; 	
}