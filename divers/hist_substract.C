void hist_substract()
{

    TFile *file1;
    TTree *tsingle1;

    TFile *file2;
    TTree *tsingle2;

    file1 = TFile::Open("~/phd/data/n-ri-22/runs/sorted_runs/84Ga/All.root", "READ");
    //file2 = TFile::Open("/Users/cantacuzene/data/n-ri-22/runs/sorted_runs/82Ga/RUN121.root", "READ");

    tsingle1 = (TTree*)file1->Get("tsingle");
    //tsingle2 = (TTree*)file2->Get("tsingle");

    TH1I* h1 = new TH1I("h1", "h1", 12,1,13);
    TH1I* h2 = new TH1I("h2", "h2", 12,1,13);
    TH1I* h3 = new TH1I("h3", "h3", 12,1,13);
    TH1I* h4 = new TH1I("h4", "h4", 12,1,13);

    std::vector<Double_t> *rings1 = 0;
    std::vector<Double_t> *rings2 = 0;
    std::vector<Double_t> *time1 = 0;
    std::vector<Double_t> *time2 = 0;
    //std::vector<Double_t> *diff = 0;

    tsingle1->SetBranchAddress("Tetra_Rings",&rings1);
    tsingle1->SetBranchAddress("Tetra_Rings",&rings2);
    tsingle1->SetBranchAddress("Tetra_tSingle",&time1);
    tsingle1->SetBranchAddress("Tetra_tSingle",&time2);
    //tsingle->SetBranchAddress("TwoNeutronsGamma_tDiff",&diff);

    for(Long64_t i = 0; i < tsingle1->GetEntries(); ++i)
    {
        tsingle1->GetEntry(i);
    
        //for(ULong_t j = 0; j < rings1->size(); ++j)
        //{   
            //if(diff->at(j) <= 40)
            //{
                //if(time1->at(j) >= 700 && time1->at(j) <= 1000)
                //{
                    //h1->Fill(rings1->at(j));
                //}

                //if(time1->at(j) >= 300 && time1->at(j) <= 2300)
                //{
                    //h1->Fill(rings1->at(j));
                //}
            //}
        //}
        
        

        for(ULong_t j = 0; j < rings2->size(); ++j)
        { 
            if(time2->at(j) >= 300 && time2->at(j) <= 600)
            {
                h3->Fill(rings2->at(j));
                h1->Fill(rings2->at(j));
            }

            if(time2->at(j) >= 0 && time2->at(j) <= 300)
            {
                h4->Fill(rings2->at(j));
            }
        }
    }

    /*for(Long64_t i = 0; i < tsingle2->GetEntries(); ++i)
    {
        tsingle2->GetEntry(i);
    
        for(ULong_t j = 0; j < rings2->size(); ++j)
        {   
            //if(diff->at(j) <= 40)
            //{
                //if(time1->at(j) >= 700 && time1->at(j) <= 1000)
                //{
                    //h1->Fill(rings1->at(j));
                //}

                if(time2->at(j) >= 0 && time2->at(j) <= 500)
                {
                    h2->Fill(rings2->at(j));
                }
            //}
        }
        
        

        for(ULong_t j = 0; j < rings2->size(); ++j)
        { 
            if(time2->at(j) >= 700 && time2->at(j) <= 1000)
            {
                h3->Fill(rings2->at(j));
            }

            if(time2->at(j) >= 0 && time2->at(j) <= 300)
            {
                h4->Fill(rings2->at(j));
            }
        }
    }*/

    //h1->Add(h2,-1);
    h3->Add(h4,-1);

    h1->Draw();
    h3->Draw("same");
    h4->Draw("same");

    h1->SetLineColor(kBlack);
    h3->SetLineColor(kBlue);
    h4->SetLineColor(kRed);

    h1->SetLineWidth(7);
    h3->SetLineWidth(7);
    h4->SetLineWidth(7);

    //h1->GetYaxis()->SetRangeUser(0,100000);
}