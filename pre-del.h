
//delete pair include non-existent edges
void del_pairset()
{
  int max_pairsize=0;
  for(auto itr=pairset.begin();itr != pairset.end();itr++)
  {
    max_pairsize=((*itr).eds.size()>max_pairsize)?(*itr).eds.size():max_pairsize;
  }
  if(pairset.size()==1 && pairset[0].w<=2) pairset.clear();
  else
  {
    for(auto itr=pairset.begin();itr!=pairset.end();)
    {
     	if(((*itr).eds.size()<=2*max_pairsize/3 && (*itr).w<=2) || (*itr).w==1 )
        {
            pairset.erase(itr);
            continue;
        }
        bool pair_exists=0;
        for(auto itr2=(*itr).eds.begin();itr2!=(*itr).eds.end();)
        {
            edge temp;
            temp.from=(*itr2);
            itr2++;
            if(itr2!=(*itr).eds.end()) temp.to=(*itr2);
            else break;
            pair_exists=0;
            for(auto itr3=edgeset.begin();itr3!=edgeset.end();++itr3)
            {
                if((*itr3).from==temp.from && (*itr3).to==temp.to)
                {
                    pair_exists=1;
                    break;
                }
            }
            if(pair_exists==0) break;
        }
        if(pair_exists==0) pairset.erase(itr);
        else itr++;
     }
  }
}

//delete nodes with weight less than threshold
void del_node()
{
    int s;
    float arge_edgeweight=0;
    float arge_nodeweight=0;
    for(auto itr=nodeset.begin();itr != nodeset.end();itr++)
    {
        arge_nodeweight += (*itr).w;
    }
    for(auto itr=edgeset.begin();itr != edgeset.end();itr++)
    {
        arge_edgeweight += (*itr).w;
    }
    if(nodeset.size() != 0) arge_nodeweight = arge_nodeweight/nodeset.size();
    if(edgeset.size() != 0) arge_edgeweight = arge_edgeweight/edgeset.size();
    float edge_threshould=2,node_threshould=2;
    if(arge_edgeweight <10) 
    edge_threshould=arge_edgeweight/5;
    if(arge_edgeweight >20) 
    node_threshould=arge_nodeweight/10;
    for (auto it=nodeset.begin(); it!=nodeset.end();)
    {
        s=(*it).end;
        it++;
        if(it!=nodeset.end() &&(*it).w<node_threshould)
	    {
            for(auto itr=edgeset.begin(); itr!=edgeset.end();)
            {
                if(((*itr).from ==(*it).index || (*itr).to == (*it).index )
				) 
                {
                    edgeset.erase(itr);
                }
                else itr++;
            }
            it++;
        }
    }
    
}
