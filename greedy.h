void greedy(vector<edge> edgeset)
{
    edge max_weight_edge;
    int i=0,j=0;
    max_weight_edge=edgeset[0];
    //search for the edge with maximum weight
    for(auto itr=edgeset.begin(); itr != edgeset.end(); )
    {
        itr++;
        i++;
        if(itr != edgeset.end()) 
        {
            if(max_weight_edge.w < (*itr).w) 
            {
                max_weight_edge=*itr;
                j=i;
            }
        }
    }
    pathset.push_back(max_weight_edge);
    edge temp=edgeset[j];
    t.w=max_weight_edge.w/2;
    temp.w=0;
    int index,index_copy=j;
    //greedy_left
    while(max_weight_edge.from != 0)
    {
        for(int l=index_copy-1;l>=0;)
        {
            if(edgeset[l].to==max_weight_edge.from)
            {
                if(temp.w<=edgeset[l].w) 
                {
                    temp=edgeset[l];
                    index=l;
                }
                l--;
                if(l<0) break;
            }
            else l--;
        }
        if(temp.w==0) break;
        else
        {
            pathset.insert(pathset.begin(),temp);
            t.w=(t.w>(temp.w/2))? temp.w/2:t.w;
            max_weight_edge=temp;
            temp.w=0;
            index_copy=index;
        }
    }
    int n=edgeset.size();
    max_weight_edge=edgeset[j];
    temp=edgeset[j];
    temp.w=0;
    //greedy_right
    for(int k=1;j+k<n;)
    {
        if(edgeset[j+k].from==max_weight_edge.to)
        {
            temp=(temp.w>=edgeset[j+k].w)?temp:edgeset[j+k];
            if(j+k==n-1)
            {
                pathset.push_back(temp);
                t.w=(t.w>(temp.w/2))? temp.w/2:t.w;
            }
            k++;
        }
        else if(edgeset[j+k].from<max_weight_edge.to) 
        {
            k++;
        }
        else
        {
            if(temp.w==0) break;
            else
            {
                pathset.push_back(temp);
                t.w=(t.w>(temp.w/2))? temp.w/2:t.w;
                max_weight_edge=temp;
                temp.w=0;
            }
        }
    }
}

//delete the edge in edgeset which weight is less than threshold
void del_edge(vector<edge> pathedge)
{
    vector<edge>::iterator s3 = pathedge.begin();
    while (s3 != pathedge.end())
    {
        vector<edge>::iterator itr = edgeset.begin();
        while( itr !=edgeset.end())
        {
            if((*itr).from == (*s3).from && (*itr).to == (*s3).to && (*itr).p_i==(*s3).p_i)
            {
                (*itr).w = (*itr).w-t.w;
                if ((*itr).w < 1)
                {
                    edgeset.erase(itr);
                }
                break;
            }
            else if((*itr).from <= (*s3).from ) 
            {
                ++itr;
            }
            else if((*itr).from > (*s3).from) break;
        }
        s3++;
    }
}




//edge to exon:for output
void edge2exon(vector<edge> pathset)
{
    vector<edge>::iterator it1=pathset.begin();
    int c=0;
    while (c < pathset.size() && it1 != pathset.end())
    {
        vector<node>::iterator it2=nodeset.begin();
        while(it2 != nodeset.end())
        {
            if((*it1).from==(*it2).index)
            {
                exonset.push_back((*it2).start);
                exonset.push_back((*it2).end);
                break;
            }
            it2++;
        }
        it1++;
        c++;
    }
    vector<node>::iterator it3=nodeset.begin();
    while(it3 != nodeset.end())
    {
        if(pathset.at(pathset.size()-1).to==(*it3).index)
        {
            exonset.push_back((*it3).start);
            exonset.push_back((*it3).end);
            break;
        }
        it3++;
    }
}

//exonset delete start and end -> junctionset
vector<int> junction(vector<int> exonset)
{
    vector<int> junctionset;
    for(int i=0;i<exonset.size()-1;i++)
    {
        if(i!=0) junctionset.push_back(exonset.at(i));
    }
    for(auto itr=junctionset.begin();itr!=junctionset.end();)
    {
        int temp=*itr;
        itr++;
        if(*itr==temp+1) 
        {
            if(junctionset.size()==2)
            {
                junctionset.clear();
                break;
            }
            junctionset.erase(itr);
            junctionset.erase(itr-1);
            itr--;
        }
        else break;
    }
    for(auto itr=junctionset.end()-1;itr!=junctionset.begin();)
    {
        int temp=*itr;
        itr--;
        if(*itr==temp-1)
        {
            if(junctionset.size()==2)
            {
                junctionset.clear();
                break;
            }
            itr--;
            junctionset.erase(itr+1);
            junctionset.erase(itr+1);
        }
        else break;
    }
    return junctionset;
}


void add_rm_copy()
{
    if(junction(exonset).empty()) return;
    if(Path.empty()) 
    {
        Path.push_back(exonset);
        Path_junction.push_back(junction(exonset));
    }
    else
    {
        vector<int> junctionset;
        junctionset=junction(exonset);
        for(auto itr=Path_junction.begin();itr!=Path_junction.end();itr++)
        {
            if((*itr)==junctionset) 
            {
                return;
            }
            //remove included path
            if(junctionset.size() < (*itr).size())
            {
                int i=0;
                bool flag=false;
                if(junctionset[0] < (*itr)[0])  flag=true;
                else
                {
                    for(i=0;i<(*itr).size();i++)
                    {
                        if(junctionset[0] == (*itr)[i]) break;
                    }
                    if(junctionset.size()+i<=(*itr).size()) 
                    {
                        for(int j=0;j<junctionset.size();j++)
                        {
                            if(junctionset[j] != (*itr)[i+j]) 
                            {
                                flag=true;
                                break;
                            }
                        }
                    }
                }
                if(!flag)
                {
                    return;
                }
            }
            if(itr==Path_junction.end()-1) 
            {
                Path.push_back(exonset);
                Path_junction.push_back(junctionset);
                return;
            }
        }
    }
}
