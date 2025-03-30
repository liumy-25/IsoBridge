void outgtf(int i,int j)
{
    // open gtf file
    ofstream fout;
    fout.open("flow.gtf",ios::app);
    if (!fout)
    {
        cout << "File open error !" << endl;
    }
    string t1=to_string(*(Path.at(j-1).begin()));
    string t2=to_string(Path.at(j-1).back());
    fout << t.chr << "\t" << "flow" << "\t" << "transcript" << "\t" << \
    t1 <<"\t" << t2 << "\t" << "1000" << "\t" <<t.chain << "\t" << " ."  \
    << "\t"<< "gene_id" << " " <<"\""<< i <<"\""<<";"<<" "<<"transcript_id" << " " \
    <<"\""<< i<<"."<<j <<"\""<<";"<<endl;
    auto s4=Path.at(j-1).begin();
    int k=1;
    while (k<=Path.at(j-1).size() && s4 != Path.at(j-1).end())
    {
        fout << t.chr <<"\t" << "flow" << "\t" << "exon" << "\t" <<(*s4) << "\t" ;
        s4++;
        fout << (*s4)<< "\t" << "1000" << "\t" << t.chain << "\t" << " ." <<"\t"<< \
        "gene_id" << "\t" <<"\""<< i <<"\""<<";"<< " " <<"transcript_id" << " " <<"\""\
        << i<<"."<< j <<"\""<< ";" <<" "<<"exon_num" << " " <<"\""<< k<<"\""<<";" <<endl;
        s4++;
        k++;
    }
    //clear used exon and weight
    pathset.clear();
    exonset.clear();
    fout.close();

}

