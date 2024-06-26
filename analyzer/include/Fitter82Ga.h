#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

#include <root/RtypesCore.h>
#include <root/TFile.h>
#include <root/TTree.h>
#include <root/TROOT.h>
#include <root/TH1.h>
#include <root/TH2.h>
#include <root/TRandom.h>
#include <root/TF1.h>
#include <root/TCanvas.h>

using namespace std;

//82Ga

Double_t t0 = 0.5e3;
Double_t tc = 3.0e3;
Double_t td = 3.0e3;
Double_t ta = tc+td+t0;

Double_t l1 = 0.0011552453;
Double_t l2 = 1.732867951e-4;
Double_t l3 = 9.120357639e-5;

//par0 is Bgd
//par1 is Phi
//par2 is Pn

Double_t Bat_tetra(Double_t *x_2, Double_t *par_2)
{	
    
	if(x_2[0] <= t0)
    {
      	return (par_2[0]);
    }
    
  	if(x_2[0] >= t0 && x_2[0] <= tc+t0)
    {  	
      	return (par_2[0])
		+(-exp(-x_2[0]*l1)*(exp(t0*l1)-exp(x_2[0]*l1))*par_2[1]);
    }
    
  	if(x_2[0] >= tc+t0 && x_2[0] <= ta)
    {
     	return (par_2[0])
		+(-exp(-x_2[0]*l1)*(exp(t0*l1)-exp((t0+tc)*l1))*par_2[1]);
    }
    
  	if(x_2[0] > ta)
    {
    	return 0;
    }
    
    return 0;
}

Double_t Bat_beta(Double_t *x_1, Double_t *par_1)
{
	
	if(x_1[0] <= t0)
    {
      	return (par_1[0]);
    }
    
  	if(x_1[0] >= t0 && x_1[0] <= tc+t0)
    {	
      	return (par_1[0])
		+(-exp(-x_1[0]*l1)*(exp(t0*l1)-exp(x_1[0]*l1))*par_1[1])
		+((-exp(-x_1[0]*l1-x_1[0]*l2)*(-1+par_1[2])*(exp(x_1[0]*l1+t0*l2)*l1-exp(x_1[0]*l1+x_1[0]*l2)*l1-exp(t0*l1+x_1[0]*l2)*l2+exp(x_1[0]*l1+x_1[0]*l2)*l2)*par_1[1])/(-l1+l2))
		+((exp(-x_1[0]*l1-x_1[0]*l3)*(par_1[2])*(exp(x_1[0]*l1+t0*l3)*l1-exp(x_1[0]*l1+x_1[0]*l3)*l1-exp(t0*l1+x_1[0]*l3)*l3+exp(x_1[0]*l1+x_1[0]*l3)*l3)*par_1[1])/(-l1+l3));
    }
    
  	if(x_1[0] >= tc+t0 && x_1[0] <= ta)
    {
     	return (par_1[0])
		+(-exp(-x_1[0]*l1)*(exp(t0*l1)-exp((t0+tc)*l1))*par_1[1])
		+((-exp(-x_1[0]*l1-x_1[0]*l2)*(-1+par_1[2])*(-exp(x_1[0]*l1+t0*l2)*l1+exp(x_1[0]*l1+(t0+tc)*l2)*l1+exp(t0*l1+x_1[0]*l2)*l2-exp((t0+tc)*l1+x_1[0]*l2)*l2)*par_1[1])/(l1-l2))
		+((exp(-x_1[0]*l1-x_1[0]*l3)*(par_1[2])*(-exp(x_1[0]*l1+t0*l3)*l1+exp(x_1[0]*l1+(t0+tc)*l3)*l1+exp(t0*l1+x_1[0]*l3)*l3-exp((t0+tc)*l1+x_1[0]*l3)*l3)*par_1[1])/(l1-l3));
    }
    
  	if(x_1[0] > ta)
    {
    	return 0;
    }
    
    return 0;
}