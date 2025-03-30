void del_path1()
{
    int basesize=0;
    for(auto it=Path.at(0).begin(); it!=Path.at(0).end(); )
    {
        it++;
        int a=(*it)+1;
        it++;
        if(it == Path.at(0).end()) break;
        else if(a !=(*it)) basesize++;
    }
    for(auto it=Path.begin(); it!=Path.end(); )
    {
        int path_st_size=0;
        for(auto itr=(*it).begin(); itr!=(*it).end(); )
        {
            itr++;
            int a=(*itr)+1;
            itr++;
            if(itr == (*it).end()) break;
            else if(a !=(*itr)) path_st_size++;
        }
        if(path_st_size<basesize) Path.erase(it);
        else it++;
    }
}



void del_path2(vector<vector<int>> Path_junction, vector<vector<int>> &Path)
{
    int n=Path_junction.size();
    vector<int> del_path_index;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(Path_junction[i].size()>=Path_junction[j].size()) continue;
            else
            {
                int k=0;
                for(k=0;k<Path_junction[j].size();k++)
                {
                    if(Path_junction[i].at(0)!=Path_junction[j].at(k)) k++;
                    else break;
                }
                if(Path_junction[i].size()+k>Path_junction[j].size()) continue;
                else
                {
                    bool clude=true;
                    for(int l=0;l<Path_junction[i].size();l++)
                    {
                        if(Path_junction[i].at(l)!=Path_junction[j].at(k+l)) 
                        {
                            clude=false;
                            break;
                        }
                    }
                    if(clude) 
                    {
                        del_path_index.push_back(i);
                        break;
                    }
                    else continue;
                }
            }
        }
    }
    int i=0;
    for(auto itr=Path.begin(); itr!=Path.end();)
    {
        if(find(del_path_index.begin(),del_path_index.end(),i)!=del_path_index.end()) 
        {
            Path.erase(itr);
            i++;
        }
        else 
        {
            i++;
            itr++;
        }
    }
}

bool del_path3(vector<edge> &pathset)
{
    int start=pathset.at(0).from;
    int l=pathset.size()-1;
    int end =pathset.at(l).to;
    int in_flow=0,out_flow=0;
    for(auto itr=edgeset_copy.begin();itr!=edgeset_copy.end();itr++)
    {
        if((*itr).to == start)
        {
            in_flow += (*itr).w;
        }
        if((*itr).from == end)
        {
            out_flow += (*itr).w;
        }
    }
    if((in_flow >=2 || out_flow >=2) && t.w < 20) return 0;
    else return 1;
}