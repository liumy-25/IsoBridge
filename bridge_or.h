
//pair case 1,2,3
int bridge_p()
{
    edge temp;
    //no pairs return 1
    if(pairset.size() == 0) return 1;
    else
    {
      for(auto it1=pairset.begin(); it1 != pairset.end(); it1++)
      {
          vector<int>::iterator it2=(*it1).eds.begin();
          while(it2 != (*it1).eds.end())
          {
              temp.from=*it2;
              it2++;
              if(it2 == (*it1).eds.end()) break;
              temp.to=(*it2);
              for(auto it3=edgeset.begin(); it3 != edgeset.end(); it3++)
              {
                  if((*it3).from == temp.from && (*it3).to == temp.to)
                  {
                      (*it3).p_w += (*it1).w;
                      break;
                  }
              }
          }
      }
      return 0;
    }
}



//construct bridge
void bridge()
{
    edge e_p;
    vector<pairs>::iterator  it1=pairset.begin();
    int i=1;
    while(it1 != pairset.end())
    {
        //add an edge to edgeset
        e_p.from=(*(*it1).eds.begin());
        e_p.to=(*it1).eds.back();
        e_p.w=(*it1).w;
        e_p.p_w=0;
        e_p.p_i=i;
        e_p.ps=0;
        vector<edge>::iterator it2=edgeset.begin();
        while(it2 != edgeset.end())
        {
            if((*it2).from==e_p.from && (*it2).to >= e_p.to) 
            {   
                edgeset.insert(it2,e_p);
                break;
            }
            else if((*it2).from > e_p.from)
            {
                edgeset.insert(it2,e_p);
                break;
            } 
            it2++;
        }
        it1++;
        i++;
    }
    vector<edge>::iterator it2=edgeset.begin();
    while(it2 != edgeset.end())
    {
        //delete edge with w=0
        (*it2).w -= (*it2).p_w;
        if((*it2).w<=0) edgeset.erase(it2);
        else it2++;
    }

}

//reduce bridge: edge included in pair ,weight - fmin
void bridge_reduction()
{
    edge e_t;
    edge ep;
    int i=1;
    bool edge_exist;
    float fmin=5000;
    for(auto it1=pairset.begin(); it1 != pairset.end(); it1++)
    {
        for(auto it2=(*it1).eds.begin(); it2 != (*it1).eds.end(); )
        {
            e_t.from=(*it2);
            it2++;
            if(it2 == (*it1).eds.end()) break;
            e_t.to=(*it2);
            edge_exist=false;
            for(auto it3=edgeset.begin(); it3 != edgeset.end(); it3++)
            {
                if((*it3).from == e_t.from && (*it3).to == e_t.to && (*it3).p_i==0)
                {
                    fmin=min((*it3).w,fmin);
                    edge_exist=true;
                    (*it3).ps=i;
                    break;
                }
            }
            if(edge_exist==false) break;
        }
        if(edge_exist)
        {
            for(auto it4=edgeset.begin(); it4 != edgeset.end();)
            {
                if((*it4).ps==i) (*it4).w -= fmin;
                if( (*it4).p_i==i )
                {
                    (*it4).w += fmin;
                }
                if((*it4).w==0) edgeset.erase(it4);
                else it4++;
            }
        }
        i++;
    }
}



//edges replace bridge
void del_bridge()
{
    vector<edge>::iterator itr=pathset.begin();
    while(itr != pathset.end())
    {
        if((*itr).p_i != 0)
        {
            int i = (*itr).p_i-1;
            edge e_or;
            e_or.w=(*itr).w;
            e_or.p_w=0;
            for (auto it1 = pairset.at(i).eds.begin(); (*it1) != pairset.at(i).eds.back(); )
            {
                e_or.from=*it1;
                it1++;
                if(it1==pairset.at(i).eds.end()) break;
                e_or.to=*it1;
                e_or.p_i=0;
                temp.push_back(e_or);
            }
            pathset.erase(itr);
            pathset.insert(itr,temp.begin(),temp.end());
            temp.clear();
        }
        else itr++;
    }
}
