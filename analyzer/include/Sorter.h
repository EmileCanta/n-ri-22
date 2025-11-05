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

using namespace std;

class Sorter{
  
	private:

	TFile *data_file;
	TFile *output_file;

	TTree *raw_data_tree;
	TTree *output_tree_single;
	TTree *output_tree_coinc;

	UInt_t raw_energy;
	Double_t raw_time;
	UChar_t raw_det_nbr;
	UInt_t raw_coding;

	Long64_t fEntries;
	Long64_t fEntry;

	UInt_t lastevent;
	UInt_t neutcount;
	UInt_t eventafter;
	UInt_t eventbefore;

	int neut_id;
	int lastneutron;

	Double_t fGe_E;
	UChar_t fGe_Id;
	Double_t fGe_Time;

	UChar_t fBeta_Id;
	Double_t fBeta_Time;

	UChar_t fTetra_Id;
	Double_t fTetra_Time;

		//Single

	//Time
	std::vector<Double_t> fGe_tSingle;
	std::vector<Double_t> fBeta_tSingle;
	std::vector<Double_t> fTetra_tSingle;

	//Energy
	std::vector<Double_t> fGe_ESingle;

	//Cycles
	std::vector<UInt_t> fTetra_Cycle;
	std::vector<UInt_t> fBeta_Cycle;
	std::vector<UInt_t> fGe_Cycle;

	//Tetra cells and rings
	std::vector<UInt_t> fTetra_Rings;
	std::vector<UInt_t> fTetra_CellGroups;

		//Coincidences

	std::vector<Long64_t> double_events_check;

	//Ge-Beta
	std::vector<Double_t> fGeBeta_ECond;
	std::vector<Double_t> fGeBeta_tCond;
	std::vector<Double_t> fGeBeta_tDiff;
	std::vector<Long64_t> fGeBeta_Index;

	//Ge-Tetra
	std::vector<Double_t> fGeTetra_ECond;
	std::vector<Double_t> fGeTetra_tCond;
	std::vector<Double_t> fGeTetra_tDiff;
	std::vector<Long64_t> fGeTetra_Index;

	//Beta-Tetra
	std::vector<Double_t> fBetaTetra_tCond;
	std::vector<Double_t> fBetaTetra_tDiff;

	//Tetra-Tetra
	std::vector<Double_t> fTetraTetra_tDiff;
	std::vector<Double_t> fTetraTetra_tCond;
	std::vector<UInt_t> fNeutCount;

	protected:

	UInt_t fCoding;
	UChar_t fStatus;
	Double_t coll_time;
	Double_t acqu_time;
	Double_t bgd_time;

	public:

	Sorter(const char*, const char*, Double_t, Double_t, Double_t);
	virtual ~Sorter();

	void Load_rawdata(const char*);

	protected:

	virtual void SetTreesAndBranches(const char*);
	virtual void FillSingleBranches();
	virtual void FillNeutronCoincs(Double_t, Double_t);
	virtual void FillBetaCoincs(Double_t, Double_t);
	virtual Double_t Ge_alignement(UInt_t);
	virtual void ResetVar();
	virtual void ClearVectors();
	virtual void SetVar(UChar_t);
	virtual UChar_t GetStatus(Double_t time);

	virtual void Tester1(Double_t);
	virtual void Tester2(Double_t);
};
