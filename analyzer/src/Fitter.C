#include "../include/Fitter84Ga.h"

void Fitter(const char* inputFile, Double_t min, Double_t max)
{
	TCanvas* c1 = new TCanvas();
	TCanvas* c2 = new TCanvas();
	
	TFile* rootFile = TFile::Open(inputFile, "READ");
	
	TH1D *hist_beta = (TH1D*)rootFile->Get("AlignedBeta_tSingle");
	TH1D *hist_tetra = (TH1D*)rootFile->Get("AlignedTetra_tSingle");

	TF1 *FitBat_beta = new TF1("Bat_beta", Bat_beta, min, max, 4);
	TF1 *FitBat_tetra = new TF1("Bat_tetra", Bat_tetra, min, max, 4);

	//FitBat_beta->FixParameter(1, 535*0.81);
	//FitBat_beta->FixParameter(2, 0.364*0.81);
	//FitBat_tetra->FixParameter(1, 535*0.364*0.58);
	//FitBat_tetra->FixParameter(1, 535*0.364*0.58);
	//FitBat_tetra->SetParameter(0, 197.721);
	//FitBat_tetra->SetParameter(1, 129.058);
	//FitBat_tetra->SetParameter(2, 0.752108);
	FitBat_tetra->SetParameter(3, 0.0071458472);
	FitBat_beta->SetParameter(3, 0.0071458472);
	
	c1->cd();
	hist_beta->Fit("Bat_beta", "R");

	c2->cd();
	hist_tetra->Fit("Bat_tetra", "R");
	
	/*
	ofstream Para_file_beta;
	Para_file_beta.open("par_beta", ios::app);
	
	ofstream Para_file_tetra;
	Para_file_tetra.open("par_tetra", ios::app);
	
	cout << "Beta parameters:" << ' ';
	
	for (int j = 0; j <= (sizeof(Par_beta)/sizeof(Par_beta[0]))-1; j++)
	{
		cout << Par_beta[j] << ' ';
		
		Para_file_beta << Par_beta[j] << ' ';
	}
	
	Para_file_beta << endl;
	
	cout << endl << "Tetra parameters:" << ' ';
	
	for (int k = 0; k <= (sizeof(Par_tetra)/sizeof(Par_tetra[0]))-1; k++)
	{
		cout << Par_tetra[k] << ' ';
		
		Para_file_tetra << Par_tetra[k] << ' ';
	}
	
	Para_file_tetra << endl;
	
	cout << endl;
		
	Para_file_beta.close();
	Para_file_tetra.close();*/
}
