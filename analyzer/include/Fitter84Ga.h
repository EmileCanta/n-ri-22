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

//84Ga

Double_t t0 = 0.3e3;
Double_t tc = 2.0e3;
Double_t td = 1.0e3;
Double_t ta = tc+td+t0;

Double_t l1 = 0.0071458472; //84Ga
Double_t l2 = 7.358250324e-4; //84Ge
Double_t l3 = 3.746741517e-4; //83Ge
Double_t l4 = 1.724246718e-4; //84As

Double_t pn2 = 0.102;

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
		+(-exp(-x_2[0]*par_2[3])*(exp(t0*par_2[3])-exp(x_2[0]*par_2[3]))*par_2[1])
		+((-exp(-x_2[0]*par_2[3]-x_2[0]*l2)*(-1+par_2[2])*(exp(x_2[0]*par_2[3]+t0*l2)*par_2[3]-exp(x_2[0]*par_2[3]+x_2[0]*l2)*par_2[3]-exp(t0*par_2[3]+x_2[0]*l2)*l2+exp(x_2[0]*par_2[3]+x_2[0]*l2)*l2)*par_2[1])/(-par_2[3]+l2));
    }
    
  	if(x_2[0] >= tc+t0 && x_2[0] <= ta)
    {
     	return (par_2[0])
		+(-exp(-x_2[0]*par_2[3])*(exp(t0*par_2[3])-exp((t0+tc)*par_2[3]))*par_2[1])
		+((-exp(-x_2[0]*par_2[3]-x_2[0]*l2)*(-1+par_2[2])*(-exp(x_2[0]*par_2[3]+t0*l2)*par_2[3]+exp(x_2[0]*par_2[3]+(t0+tc)*l2)*par_2[3]+exp(t0*par_2[3]+x_2[0]*l2)*l2-exp((t0+tc)*par_2[3]+x_2[0]*l2)*l2)*par_2[1])/(par_2[3]-l2));
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
		+(-exp(-x_1[0]*par_1[3])*(exp(t0*par_1[3])-exp(x_1[0]*par_1[3]))*par_1[1])
		+((-exp(-x_1[0]*par_1[3]-x_1[0]*l2)*(-1+par_1[2])*(exp(x_1[0]*par_1[3]+t0*l2)*par_1[3]-exp(x_1[0]*par_1[3]+x_1[0]*l2)*par_1[3]-exp(t0*par_1[3]+x_1[0]*l2)*l2+exp(x_1[0]*par_1[3]+x_1[0]*l2)*l2)*par_1[1])/(-par_1[3]+l2))
		+((exp(-x_1[0]*par_1[3]-x_1[0]*l3)*(par_1[2])*(exp(x_1[0]*par_1[3]+t0*l3)*par_1[3]-exp(x_1[0]*par_1[3]+x_1[0]*l3)*par_1[3]-exp(t0*par_1[3]+x_1[0]*l3)*l3+exp(x_1[0]*par_1[3]+x_1[0]*l3)*l3)*par_1[1])/(-par_1[3]+l3))
		+(1/((par_1[3]-l2)*(par_1[3]-l4)*(l2-l4)))*exp(-x_1[0]*(par_1[3]+l2+l4))*(-1+par_1[2])*(-1+pn2)*(-exp(x_1[0]*(par_1[3]+l2)+t0*l4)*par_1[3]*(par_1[3]-l2)*l2+exp(x_1[0]*(par_1[3]+l2+l4))*(par_1[3]-l2)*(par_1[3]-l4)*(l2-l4)+exp(t0*l2+x_1[0]*(par_1[3]+l4))*par_1[3]*(par_1[3]-l4)*l4-exp(t0*par_1[3]+x_1[0]*(l2+l4))*l2*(l2-l4)*l4)*par_1[1];
    }
    
  	if(x_1[0] >= tc+t0 && x_1[0] <= ta)
    {
     	return (par_1[0])
		+(-exp(-x_1[0]*par_1[3])*(exp(t0*par_1[3])-exp((t0+tc)*par_1[3]))*par_1[1])
		+((-exp(-x_1[0]*par_1[3]-x_1[0]*l2)*(-1+par_1[2])*(-exp(x_1[0]*par_1[3]+t0*l2)*par_1[3]+exp(x_1[0]*par_1[3]+(t0+tc)*l2)*par_1[3]+exp(t0*par_1[3]+x_1[0]*l2)*l2-exp((t0+tc)*par_1[3]+x_1[0]*l2)*l2)*par_1[1])/(par_1[3]-l2))
		+((exp(-x_1[0]*par_1[3]-x_1[0]*l3)*(par_1[2])*(-exp(x_1[0]*par_1[3]+t0*l3)*par_1[3]+exp(x_1[0]*par_1[3]+(t0+tc)*l3)*par_1[3]+exp(t0*par_1[3]+x_1[0]*l3)*l3-exp((t0+tc)*par_1[3]+x_1[0]*l3)*l3)*par_1[1])/(par_1[3]-l3))
		+((exp(-x_1[0]*(par_1[3]+l2+l4))*(-1+par_1[2])*(-1+pn2)*(-exp(x_1[0]*(par_1[3]+l2)+t0*l4)*par_1[3]*(par_1[3]-l2)*l2+exp(x_1[0]*(par_1[3]+l2)+(t0+tc)*l4)*par_1[3]*(par_1[3]-l2)*l2+exp(t0*l2+x_1[0]*(par_1[3]+l4))*par_1[3]*(par_1[3]-l4)*l4-exp((t0+tc)*l2+x_1[0]*(par_1[3]+l4))*par_1[3]*(par_1[3]-l4)*l4-exp(t0*par_1[3]+x_1[0]*(l2+l4))*l2*(l2-l4)*l4+exp((t0+tc)*par_1[3]+x_1[0]*(l2+l4))*l2*(l2-l4)*l4)*par_1[1])/((par_1[3]-l2)*(par_1[3]-l4)*(l2-l4)));
    }
    
  	if(x_1[0] > ta)
    {
    	return 0;
    }
    
    return 0;
}