

//string to char
void stc_e(string str, int count)
{
    if (count == 0)
    {
        int r = atoi(str.c_str());  
        e.from=r;
    }
    else if (count == 2)
    {
        int r = atoi(str.c_str());  
        e.to=r;
    }
    else if (count == 4){
        int r = atoi(str.c_str());  
        e.w=r;
    }
}

void stc_n(string str, int count)
{
    if (count == 0)
    {
        t.chain=str;
    }
    else if (count == 1)
    {
        t.chr=str;
    }
    else if (count == 2)
    {
        int r = atoi(str.c_str());  
        v.start=r;
    }
    else if (count == 3)
    {
        int r = atoi(str.c_str());  
        v.end=r;
    }
    else if (count == 4)
    {
        float r = atof(str.c_str());  
        v.w=r;
    }
    else if (count == 6)
    {
    int r = atoi(str.c_str());  
    v.index=r;
    }
}


//graph information:edges, nodes,pairs -> vector

void info(ifstream& fin, string temp)
{
    if(temp.find("#") != string::npos) cout << "error" <<endl;
    else
    {
        if(temp !="Edges")   cout<< "error" <<endl;
        else
        {
            while(getline(fin,temp))
            {
                if(temp != "Nodes")
                {
                    istringstream istr(temp);
                    string str;
                    int count = 0;							 
                    while (istr >> str)
                    {                   
                        stc_e(str,count);
                        e.p_i=0;
                        e.num=0;
                        count++;
                    }
                    if(!edgeset.empty())
                    {
                        if (e.from != edgeset.back().from | e.to != edgeset.back().to)
                        {
                            edgeset.push_back(e);
                        }
                        else edgeset.back().w += e.w;
                    }
                    else edgeset.push_back(e);
                }
                else
                {
                    while(getline(fin,temp))
                    {
                        if( temp != "Pair")
                        {
                            istringstream istr(temp);
                            string str;
                            int count = 0;							 
                            while (istr >> str)                      
                            {
                                stc_n(str,count);
                                count++;
                            }
                            nodeset.push_back(v);
                        }
                        else
                        {
                            while(getline(fin,temp) && temp.find("#") == string::npos)
                            {
                                istringstream istr(temp);
                                string str;
                                bool m=1;
                                while(istr>>str)
                                {
                                    if(str != ":")
                                    {
                                        if(m)
                                        {
                                            int r = atoi(str.c_str());
                                            p.eds.push_back(r);
                                        }
                                        else 
                                        {
                                            int r = atoi(str.c_str());
                                            p.w=r;
                                        }
                                    }
                                    else m=0;
                                }
                                pairset.push_back(p);
                                p.eds.clear();
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
}
