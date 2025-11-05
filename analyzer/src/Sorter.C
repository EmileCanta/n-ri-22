#include "../include/Sorter.h"
 
Sorter::Sorter(const char* InputFileName, const char* OutputFileName, Double_t collection_time, Double_t acquisition_time, Double_t background_time)                        
{
    cout << "Starting Sorter" << endl;
    
    gROOT->ProcessLine("#include <vector>");

    coll_time = collection_time;
    acqu_time = acquisition_time;
    bgd_time = background_time;

    Load_rawdata(InputFileName);

    SetTreesAndBranches(OutputFileName);

    FillSingleBranches();
    
    output_tree_single->Write();

    //FillNeutronCoincs(200e6,200e6);

    //FillBetaCoincs(50e6,100e6);

    Tester1(200e6);

    Tester2(10e6);

    output_tree_coinc->Write();

    data_file->Close();
}

//******************************************************************************
//******************************************************************************

Sorter::~Sorter()
{
    ;
}

//******************************************************************************
//******************************************************************************

Double_t Sorter::Ge_alignement(UInt_t channel)
{   
    Double_t channel_d = (Double_t)channel;
    Double_t channel_aligned = 0.;
    Double_t ch = (channel_d + gRandom->Uniform(1.0) - 0.5);
    //channel_aligned = ch * 0.6264 + 96.469; Calibration runs production
    channel_aligned = ch * 0.17701043557 + 26.646713014; /*Calibration runs manip*/
    return channel_aligned;
}

//******************************************************************************
//******************************************************************************

UChar_t Sorter::GetStatus(Double_t time)
{
    UChar_t status = -10;
    if(time / 1e6 > bgd_time && time / 1e6 <= bgd_time + coll_time) status = 1; //Collection
    else if(time / 1e6 > bgd_time + coll_time) status = 1; //Acquisition
    return status;
}

//******************************************************************************
//******************************************************************************

void Sorter::ResetVar()
{
    fTetra_Id = 0;
    fTetra_Time = 0.;

    fBeta_Id = 0;
    fBeta_Time = 0.;

    fGe_E = 0.;
    fGe_Id = 0;
    fGe_Time = 0.;

    fCoding = 0;
    fStatus = -10;
}

//******************************************************************************
//******************************************************************************

void Sorter::ClearVectors()
{   
        //Single

    //Time
    fTetra_tSingle.clear();
    fBeta_tSingle.clear();
    fGe_tSingle.clear();

    //Energy
    fGe_ESingle.clear();

    //Cycles
    fTetra_Cycle.clear();
    fBeta_Cycle.clear();
    fGe_Cycle.clear();
    
    //Tetra cell groups and rings
    fTetra_CellGroups.clear();
    fTetra_Rings.clear();

        //Coincidences

    //Ge-Beta
    fGeBeta_ECond.clear();
    fGeBeta_tCond.clear();
    fGeBeta_tDiff.clear();
    fGeBeta_Index.clear();

    //Ge-Tetra
    fGeTetra_ECond.clear();
    fGeTetra_tCond.clear();
    fGeTetra_tDiff.clear();
    fGeTetra_Index.clear();
        
    //Beta-Tetra
    fBetaTetra_tCond.clear();
    fBetaTetra_tDiff.clear();

    //Tetra-Tetra
    fTetraTetra_tCond.clear();
    fTetraTetra_tDiff.clear();
    fNeutCount.clear();

    double_events_check.clear();
}

//******************************************************************************
//******************************************************************************

void Sorter::SetVar(UChar_t det)
{   
    if(det >= 1 && det <= 12)
    {
        fTetra_Id = det;
        fTetra_Time = raw_time;
        fCoding = raw_coding;
        fStatus = GetStatus(raw_time);
    }

    if(det == 14)
    { 
        fBeta_Id = det;
        fBeta_Time = raw_time;
        fCoding = raw_coding;
        fStatus = GetStatus(raw_time);
    }
        
    if(det == 15)
    {   
        fGe_E = raw_energy;
        fGe_Id = det;
        fGe_Time = raw_time;
        fCoding = raw_coding;
        fStatus = GetStatus(raw_time);
    }
}

//******************************************************************************
//******************************************************************************

void Sorter::Load_rawdata (const char* InputFileName)
{
	cout << "Loading Narval Tree" << endl;
	
	data_file = TFile::Open(InputFileName);

    raw_data_tree = (TTree*)data_file->Get("Narval_tree");
	
	raw_data_tree->SetBranchAddress("Energy", &raw_energy);
    raw_data_tree->SetBranchAddress("Time", &raw_time);
    raw_data_tree->SetBranchAddress("Coding", &raw_coding);
    raw_data_tree->SetBranchAddress("Det_nbr", &raw_det_nbr);

    fEntries = raw_data_tree->GetEntries();
    
    std::cout << "Entries to be sorted : " << fEntries << std::endl;
}

//******************************************************************************
//******************************************************************************

void Sorter::SetTreesAndBranches(const char* OutputFileName)
{
    std::cout << "Initialization of output TTree" << std::endl;

    std::cout << "Creating branches" << std::endl;
    
    output_file = new TFile(OutputFileName, "recreate");
    
    output_tree_single = new TTree("tsingle", "Tree with singles");
    output_tree_coinc = new TTree("tcoinc", "Tree with coincidences");
      
        //Single
    
    //Time
    output_tree_single->Branch("Tetra_tSingle", &fTetra_tSingle);
    output_tree_single->Branch("Ge_tSingle", &fGe_tSingle);
    output_tree_single->Branch("Beta_tSingle", &fBeta_tSingle);

    //Energy
    output_tree_single->Branch("Ge_ESingle", &fGe_ESingle);

    //Cycles
    output_tree_single->Branch("Tetra_Cycle", &fTetra_Cycle);    
    output_tree_single->Branch("Ge_Cycle", &fGe_Cycle);
    output_tree_single->Branch("Beta_Cycle", &fBeta_Cycle);

    //Tetra cells and rings
    output_tree_single->Branch("Tetra_Rings", &fTetra_Rings);
    output_tree_single->Branch("Tetra_CellGroups", &fTetra_CellGroups);
    
        //Coincidences

    //Ge-Beta
    output_tree_coinc->Branch("GeBeta_ECond", &fGeBeta_ECond);
    output_tree_coinc->Branch("GeBeta_tCond", &fGeBeta_tCond);
    output_tree_coinc->Branch("GeBeta_tDiff", &fGeBeta_tDiff);
    output_tree_coinc->Branch("GeBeta_Index", &fGeBeta_Index);
    
    //Ge-Tetra
    output_tree_coinc->Branch("GeTetra_ECond", &fGeTetra_ECond);
    output_tree_coinc->Branch("GeTetra_tCond", &fGeTetra_tCond);
    output_tree_coinc->Branch("GeTetra_tDiff", &fGeTetra_tDiff);
    output_tree_coinc->Branch("GeTetra_Index", &fGeTetra_Index);

    //Beta-Tetra
    output_tree_coinc->Branch("BetaTetra_tCond", &fBetaTetra_tCond);
    output_tree_coinc->Branch("BetaTetra_tDiff", &fBetaTetra_tDiff);

    //Tetra-Tetra
    output_tree_coinc->Branch("TetraTetra_tCond", &fTetraTetra_tCond);
    output_tree_coinc->Branch("TetraTetra_tDiff", &fTetraTetra_tDiff);
    output_tree_coinc->Branch("NeutCount", &fNeutCount);
}

//******************************************************************************
//******************************************************************************

void Sorter::FillSingleBranches()
{   
    std::cout << "Filling single data" << std::endl;

    Double_t last_time = 0.;
    UInt_t fCycle = 1;

    ResetVar();
    
    for(fEntry = 0; fEntry < fEntries; fEntry++)
	{
        raw_data_tree->GetEntry(fEntry);

        if(fEntry == 0)
        {
            last_time = raw_time;
            fCycle = 1;
	    }

        ClearVectors();

        if(raw_det_nbr >= 1 && raw_det_nbr <= 12)
        {
            fTetra_tSingle.push_back(raw_time / 1.e9); //millisecond
            fTetra_Cycle.push_back(fCycle);
            
            for(UInt_t i = 1; i <= 13; i++)
            {
                if(raw_det_nbr == i)
                {
                    fTetra_CellGroups.push_back(i);
                }
            }

            if(raw_det_nbr >= 1 && raw_det_nbr <= 2)
            {
                fTetra_Rings.push_back(1);
            }

            if(raw_det_nbr >= 3 && raw_det_nbr <= 5)
            {
                fTetra_Rings.push_back(2);
            }

            if(raw_det_nbr >= 6 && raw_det_nbr <= 8)
            {
                fTetra_Rings.push_back(3);
            }

            if(raw_det_nbr >= 9 && raw_det_nbr <= 12)
            {
                fTetra_Rings.push_back(4);
            }

            if(raw_det_nbr == 13)
            {
                fTetra_Rings.push_back(0);
            }
        }

        if(raw_det_nbr == 14)
        {
            fBeta_tSingle.push_back(raw_time / 1.e9); //millisecond
            fBeta_Cycle.push_back(fCycle);
        }

        if(raw_det_nbr == 15)
        {
            fGe_ESingle.push_back(Ge_alignement(raw_energy));
            fGe_tSingle.push_back(raw_time / 1.e9); //millisecond
            fGe_Cycle.push_back(fCycle);
        }

        if(raw_time - last_time < 0) fCycle++;
        
        last_time = raw_time;

        output_tree_single->Fill();

        std::cout << std::setprecision(3) << std::setw(5) << (100.*fEntry/fEntries) << " %\r";
    }
}

//******************************************************************************
//******************************************************************************

void Sorter::FillBetaCoincs(Double_t coincbackw, Double_t coincforw)
{
    std::cout << "Filling beta coincidences" << std::endl;
    
    lastevent = 0;

    ResetVar();

	for(fEntry = 0; fEntry < fEntries; fEntry++)
	{
        raw_data_tree->GetEntry(fEntry);

        ClearVectors();
        
        SetVar(raw_det_nbr);
        
        eventafter = 0;
        eventbefore = 0;

        neutcount = 0;

        if(fEntry < lastevent) continue;
        
        while(TMath::Abs(raw_time - fBeta_Time) < coincbackw)
        {

            raw_data_tree->GetEntry(fEntry - eventbefore++);

            if(fEntry - eventbefore < 0) break;
            if(fCoding != raw_coding) break;
            if(fStatus != GetStatus(raw_time)) break;
            
            if(TMath::Abs(raw_time - fBeta_Time) > coincbackw) continue;
            if(TMath::Abs(raw_time - fBeta_Time) < coincbackw)
            {   
                if(std::find(double_events_check.begin(), double_events_check.end(), (fEntry - eventbefore)) != double_events_check.end()) continue;

                if(raw_det_nbr == 15)
                {
                    fGeBeta_ECond.push_back(Ge_alignement(raw_energy));
                    fGeBeta_tDiff.push_back((raw_time - fBeta_Time) / 1.e6);
                    fGeBeta_tCond.push_back(raw_time / 1.e9);
                }
            }
	    }

        double_events_check.clear();

        raw_data_tree->GetEntry(fEntry);

        while(TMath::Abs(raw_time -fBeta_Time) < coincforw)
        {
            raw_data_tree->GetEntry(fEntry + eventafter++);

            if(fEntry + eventafter > fEntries) break;

            if(TMath::Abs(raw_time - fBeta_Time) > coincforw) continue;
            if(TMath::Abs(raw_time - fBeta_Time) < coincforw)
            {
                if(raw_det_nbr == 15)
                {
                    fGeBeta_ECond.push_back(Ge_alignement(raw_energy));
                    fGeBeta_tDiff.push_back((raw_time - fBeta_Time) / 1.e6);
                    fGeBeta_tCond.push_back(raw_time / 1.e9);
                }

                double_events_check.push_back(fEntry + eventafter);
            }   
        }

        lastevent = fEntry + eventafter;
	    
	    output_tree_coinc->Fill();

        std::cout << std::setprecision(3) << std::setw(5) << (100.*fEntry/fEntries) << " %\r";
    }
}

//******************************************************************************
//******************************************************************************

void Sorter::FillNeutronCoincs(Double_t coincback, Double_t coincfront)
{
    std::cout << "Filling neutron coincidences" << std::endl;

    lastevent = 0;

    ResetVar();

	for(fEntry = 0; fEntry < fEntries; fEntry++)
	{
        raw_data_tree->GetEntry(fEntry);

        ClearVectors();
        
        SetVar(raw_det_nbr);
        
        eventafter = 0;
        eventbefore = 0;

        neutcount = 0;

        if(fEntry < lastevent) continue;

        while(TMath::Abs(raw_time - fTetra_Time) < coincback)
        {

            raw_data_tree->GetEntry(fEntry - eventbefore++);

            if(fEntry - eventbefore < 0) break;
            if(fCoding != raw_coding) break;
            if(fStatus != GetStatus(raw_time)) break;
            
            if(TMath::Abs(raw_time - fTetra_Time) > coincback) continue;
            if(TMath::Abs(raw_time - fTetra_Time) < coincback)
            {   
                if(std::find(double_events_check.begin(), double_events_check.end(), (fEntry - eventbefore)) != double_events_check.end()) continue;

                if(raw_det_nbr >= 1 && raw_det_nbr <= 12)
                {
                    if(TMath::Abs(raw_time - fTetra_Time != 0)) 
                    {
                        fTetraTetra_tDiff.push_back((raw_time - fTetra_Time) / 1.e6);
                        fTetraTetra_tCond.push_back(raw_time / 1.e9);

                        neutcount++;
                    }
                }

                if(raw_det_nbr == 15)
                {
                    fGeTetra_ECond.push_back(Ge_alignement(raw_energy));
                    fGeTetra_tDiff.push_back((raw_time - fTetra_Time) / 1.e6);
                    fGeTetra_tCond.push_back(raw_time / 1.e9);
                }

                if(raw_det_nbr == 14)
                {
                    fBetaTetra_tCond.push_back(raw_time  / 1.e9);
                    fBetaTetra_tDiff.push_back((raw_time - fTetra_Time) / 1.e6);
                }
            }
	    }

        double_events_check.clear();

        raw_data_tree->GetEntry(fEntry);
        
        while(TMath::Abs(raw_time - fTetra_Time) < coincfront)
        {
            raw_data_tree->GetEntry(fEntry + eventafter++);

            if(fEntry + eventafter > fEntries) break;

            if(TMath::Abs(raw_time - fTetra_Time) > coincfront) continue;
            if(TMath::Abs(raw_time - fTetra_Time) < coincfront)
            {
                if(raw_det_nbr >= 1 && raw_det_nbr <= 12)
                {
                    if(TMath::Abs(raw_time - fTetra_Time != 0)) 
                    {
                        fTetraTetra_tDiff.push_back((raw_time - fTetra_Time) / 1.e6);
                        fTetraTetra_tCond.push_back(raw_time / 1.e9);

                        neutcount++;
                    }
                }

                if(raw_det_nbr == 15)
                {
                    fGeTetra_ECond.push_back(Ge_alignement(raw_energy));
                    fGeTetra_tDiff.push_back((raw_time - fTetra_Time) / 1.e6);
                    fGeTetra_tCond.push_back(raw_time / 1.e9);
                }

                if(raw_det_nbr == 14)
                {
                    fBetaTetra_tCond.push_back(raw_time  / 1.e9);
                    fBetaTetra_tDiff.push_back((raw_time - fTetra_Time) / 1.e6);
                }

                double_events_check.push_back(fEntry + eventafter);
            }   
        }

        lastevent = fEntry + eventafter;

        fNeutCount.push_back(neutcount);

        output_tree_coinc->Fill();

        std::cout << std::setprecision(3) << std::setw(5) << (100.*fEntry/fEntries) << " %\r";
    }
}

//******************************************************************************
//******************************************************************************

void Sorter::Tester1(Double_t coincwindow)
{
    std::cout << "Sorting neutron-gamma coinc data" << std::endl;
    
    lastevent = 0;

    ResetVar();

	for(fEntry = fEntries; fEntry > 0; fEntry--)
	{
        raw_data_tree->GetEntry(fEntry);

        ClearVectors();
        
        SetVar(raw_det_nbr);
        
        eventafter = 0;

        if(fTetra_Id >= 1 && fTetra_Id <= 12)
        {   
            if(fEntry > lastevent) continue;

            while(TMath::Abs(raw_time - fTetra_Time) < coincwindow)
            {
	      		if(raw_det_nbr >= 1 && raw_det_nbr <= 12) break;

                raw_data_tree->GetEntry(fEntry - eventafter++);

                if(fEntry - eventafter < 0) break;
                if(fCoding != raw_coding) break;
                if(fStatus != GetStatus(raw_time)) break;
                
                if(TMath::Abs(raw_time - fTetra_Time) > coincwindow) continue;
                if(TMath::Abs(raw_time - fTetra_Time) < coincwindow)
                {   
                    if(raw_det_nbr == 15)
                    {   
                        fGeTetra_tDiff.push_back(TMath::Abs(raw_time - fTetra_Time) / 1e6); //microsecondes
				        fGeTetra_ECond.push_back(Ge_alignement(raw_energy));
				        fGeTetra_tCond.push_back(raw_time / 1.e9); //milisecondes;
                        fGeTetra_Index.push_back(fEntry - (eventafter-1));
                    }
                 }
            }
	    }
	    
	    lastevent = fEntry - eventafter;
	    
	    output_tree_coinc->Fill();

        std::cout << std::setprecision(3) << std::setw(5) << (100.*(fEntries - fEntry)/fEntries) << " %\r";
    }
}

//******************************************************************************
//******************************************************************************

void Sorter::Tester2(Double_t coincwindow)
{
    std::cout << "Sorting beta-gamma coinc data" << std::endl;
    
    lastevent = 0;

    ResetVar();

	for(fEntry = 0; fEntry < fEntries; fEntry++)
	{
        raw_data_tree->GetEntry(fEntry);

        ClearVectors();
        
        SetVar(raw_det_nbr);
        
        eventafter = 0;

        if(fBeta_Id == 14)
        {   
            if(fEntry < lastevent) continue;
            
            while(TMath::Abs(raw_time - fBeta_Time) < coincwindow)
            {
	      		if(raw_det_nbr == 14) break;

                raw_data_tree->GetEntry(fEntry + eventafter++);

                if(fEntry + eventafter > fEntries) break;
                if(fCoding != raw_coding) break;
                if(fStatus != GetStatus(raw_time)) break;
                
                if(TMath::Abs(raw_time - fBeta_Time) > coincwindow) continue;
                if(TMath::Abs(raw_time - fBeta_Time) < coincwindow)
                {   
                    if(raw_det_nbr == 15)
                    {   

                        fGeBeta_tDiff.push_back(TMath::Abs(raw_time - fBeta_Time) / 1.e6); //microsecondes
                        fGeBeta_ECond.push_back(Ge_alignement(raw_energy));
                        fGeBeta_tCond.push_back(raw_time / 1.e9); //milisecondes;
                        fGeBeta_Index.push_back(fEntry + (eventafter-1));

                    }
                 }
            }
	    }
	    
	    lastevent = fEntry + eventafter;
	    
	    output_tree_coinc->Fill();

        std::cout << std::setprecision(3) << std::setw(5) << (100.*fEntry/fEntries) << " %\r";
    }
}