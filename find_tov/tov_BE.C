/*
Rappel sur les TOV. L'acquisition est interrogée toutes les ms et si elle est 
occupée le contenu du TOV est incrémenté de 1, ceci pour chaque voie, le contenu
du TOV est transmis toutes les 512ms. 

     Construction du spectre de temps correspondant à une voie donnee
     les données sont a entrer dans un fichier de données, on lancera le programme 
     dans root par :
              .L tov.C+       //compilation prealable pour que l'executionsoit rapide
              tov()           // on demande alors d'entrer le nom du fichier de donnees 

     le fichier de données (dans l'exemple tov.don) se presente de la maniere suivante :
              run7-tov.root             // nom du fichier root dans lequel on ecrira le spectre
              40 4000                   // temps maximal en s (durée d'un coden), nombre de canaux du spectre (ici maximum 40000) 
              /mnt/Dossiers/LINUX/RUN7.dat             // nom du fichier narval a analyser
              2                                       // nombre de cartes dans le chassis VXI
              3                                      // position de la premiere carte (n° du slot)
              4                                     // position de la deuxieme carte (n° du slot)
              4 0                                  // n° de slot et n° de voie (0 à 5) du detecteur choisi
              temps-mort-sp_100ms                  // nom du spectre temps mort




*/

#include <iostream>
#include <iomanip> 
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "TStyle.h"
#include "TH1F.h"
#include "TH2I.h"
#include "TF1.h"
#include "TFormula.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TRandom3.h"

using namespace std ;
unsigned short endian_swap(unsigned short x)
{
    x = (x>>8) |
        ((x&0xff)<<8);
return(x);
} 
void tov_BE()
{clock_t debut,fin;
        debut = clock();
char fichroot[110];char narval[110];
//char bidim[110];
char nomspe[110]; float tempsmax;int ncy;
// nom du fichier de donnees a lire
char fichdonnees[110];
cout << " nom du fichier a lire contenant le nom du fichier narval, le nom du fichier root, du bidim etc...:\n";
//cin >> fichdonnees;
//ifstream fichin (fichdonnees, ios::in);
ifstream fichin ("input.txt", ios::in);
if (!fichin) {cout << "lecture de "<< fichdonnees << " impossible \n";
               exit(1);}
TRandom3 r;
fichin >> fichroot;
// creation du fichier root dans lequel on sauvera les histogrammes
TFile * f = new TFile(fichroot,"UPDATE");
//fichin >> bidim;
fichin >> tempsmax  >> ncy ;
float tempsparcl;float tm;
tempsparcl=tempsmax/ncy;

fichin >> narval;
short int nbrecartes; short int carte[12]; short int macarte;short int mavoie;
fichin >> nbrecartes;
for (int ic=0; ic<nbrecartes; ic++) {fichin >>carte[ic];} 
fichin >> macarte >> mavoie;
fichin >> nomspe;

int cont_tov_sp[40000]={0};int nb_tov_sp[40000]={0};
int cont_tov[40000]={0};int nb_tov[40000]={0};
int icl2=0;

ifstream entree (narval, ios::in);
if (!entree) {cout << "lecture de "<< narval << "impossible \n";
               exit(1);}



short int val;// int n=1;
short int nbremots;unsigned short int w[8];unsigned short int w2[8];
short int nbremots2;
int nevents =0;

// type d'evts :
short int groupe =0;
//short int carte[2]={3,4};
short int chassis =0;
short int service[2]={0,1};
short int marquage =0;
short int voie[6]= {0,1,2,3,4,5};

// identificateurs
// detecteurs :
int det[12];int mondet;
int i=0;
for (int j=0;j<nbrecartes;j++)
{for (int k=0;k<6;k++)
{det[i]= (groupe << 12)+ (carte[j] << 8) + (chassis << 6)+ (service[0]<<5)+(marquage<<4)+voie[k];
cout << " det["<<i+1<<"] = "<<det[i]<<"\n";
i++;
}}
//cout <<"\n";
// coden :
 i=0; int coden[2];
for (int j=0;j<nbrecartes;j++)
{coden[i]= (groupe << 12)+ (carte[j] << 8) + (chassis << 6)+ (service[1]<<5)+(marquage<<4)+6;
cout << " coden["<<i+1<<"] = "<<coden[i]<<"\n";
i++;
}
//cout <<"\n";

// Tov
i=0; int tov[12];
for (int j=0;j<nbrecartes;j++)
{for (int k=0;k<6;k++)
{tov[i]= (groupe << 12)+ (carte[j] << 8) + (chassis << 6)+ (service[1]<<5)+(marquage<<4)+voie[k];
cout << " Tov["<<i+1<<"] = "<<tov[i]<<"\n";
i++;
}}
//cout <<"\n";

int cptrerr=0;int cptrtov=0;

val=0;
while (val != -1) {
entree.read ((char *) &val,sizeof(short int));
} 

int montov=0;int moncoden=0;

mondet= (groupe << 12)+ (macarte << 8) + (chassis << 6)+ (service[0]<<5)+(marquage<<4)+mavoie;
montov= (groupe << 12)+ (macarte << 8) + (chassis << 6)+ (service[1]<<5)+(marquage<<4)+mavoie;
moncoden= (groupe << 12)+ (macarte << 8) + (chassis << 6)+ (service[1]<<5)+(marquage<<4)+6;
cout <<"mondet = "<<mondet<<"\n";
cout <<"montov = "<<montov<<"\n";
cout <<"moncoden = "<<moncoden<<"\n";
// lecture du fichier
      // recherche du premier evenement
while (entree){
//cout << val<<"\n";
entree.read ((char *) &nbremots,sizeof(short int));
nbremots2=endian_swap(nbremots);
//cout << nbremots2 << "\n";
for (int i=0 ;i<nbremots2-2; i++) {entree.read ((char *) & w[i],sizeof(short int));
w2[i]=endian_swap(w[i]);}
//cout << w2[0] << "\n";
 if (w2[0]==moncoden) {icl2=0;}
if (w2[0]==montov) {cptrtov++;   // cout << w2[3] << "\n";  
                        cont_tov[icl2]=cont_tov[icl2]+w2[3];
                                     nb_tov[icl2]=nb_tov[icl2]+1;
                                          icl2++;
   }
 
nevents++;
entree.read ((char *) &val,sizeof(short int));
while (val != -1) {cptrerr++;
entree.read ((char *) &val,sizeof(short int));
if (!entree) break;
}
//if (nevents > 2000000) break; //test avec 2E6 evts 

}

entree.close();  
int icl3=0;
TH1F * spetm = new TH1F(nomspe,nomspe,ncy,0,ncy-1);

if (tempsparcl<=0.512) {
           for(int isp=0;isp<ncy;isp++) {
               if (isp*tempsparcl <= (icl3+1)*0.512) {nb_tov_sp[isp]=nb_tov[icl3];cont_tov_sp[isp]=cont_tov[icl3];
                                                         tm = cont_tov_sp[isp]/(512.*nb_tov_sp[isp]);
                                    spetm->Fill(isp,tm);}
                else {  icl3++;nb_tov_sp[isp]=nb_tov[icl3];cont_tov_sp[isp]=cont_tov[icl3];
                                                         tm = cont_tov_sp[isp]/(512.*nb_tov_sp[isp]);
                                    spetm->Fill(isp,tm);
                      }                                    
                             }}
else{ 
          for(int isp=0;isp<ncy;isp++) {
               while ((isp+1)*tempsparcl>(icl3+1)*0.512) { nb_tov_sp[isp]=nb_tov_sp[isp]+nb_tov[icl3];
                                                        cont_tov_sp[isp]=cont_tov_sp[isp]+cont_tov[icl3];icl3++;}  
           tm = cont_tov_sp[isp]/(512.*nb_tov_sp[isp]);
            spetm->Fill(isp,tm);
    }}
 
cout << " evts lus = " << nevents <<"\n";

TCanvas * c2=new TCanvas("c2","c2",0,0,600,400);
c2->cd();
spetm->Draw("hist");
f->Write();

       fin = clock();
        cout << "\n";
        cout<<"L'execution a dure : "<<(fin - debut)*1E-6 <<" secondes\n";
}
