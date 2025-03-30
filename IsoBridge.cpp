#include "def.h"
#include "info.h"         //info
#include "pre-del.h"      //del_node,del_pairset
#include "bridge_or.h"       //bridge_p, bridge, bridge_reduction,del_bridge
#include "greedy.h"       //greedy,del_edge2,edge2exon,add_rm_copy
#include "delpath.h"      //del_path,2,3,4
#include "output.h"       //output



void cl()
{
    edgeset.clear();
    edgeset.shrink_to_fit();
    edgeset_copy.clear();
    edgeset_copy.shrink_to_fit();
    nodeset.clear();
    nodeset.shrink_to_fit();
    pairset.clear();
    pairset.shrink_to_fit();
}


int main(int argc, char* argv[])
{

    ifstream fin;
    fin.open(argv[1],ios::in);
    if(!fin.is_open()) //if file not open
    {
        cerr<<"cannot open the file"<<endl;
        return 0;
    }
    int i=1;
    int j,k,count=0;
    int nopair=0,noedge=0,overedge=0;
    bool p;
    bool ov;
    string temp;
    pathset.reserve(200);
    while(getline(fin,temp))
    {
        info(fin,temp);
        del_node(); 
        del_pairset();
        for(auto copy=edgeset.begin();copy!=edgeset.end();copy++)
        {
            edgeset_copy.push_back(*copy);
        }
        ov=0;p=1;
        Path.clear();
        Path_junction.clear();
        j=1;
        k=bridge_p();
        // information already
        if (k==2)  
        {
            overedge += 1;
        }
        else if (k==1) nopair += 1;
        else if(k==0)  
        {
            ov=1;
            count += 1;
        }
        if(edgeset.empty()) 
        {
            cl();
            continue;
        }
        if(ov)  
        {
            bridge();
            bridge_reduction();
            while (!edgeset.empty())
            {
                greedy(edgeset);
                if(pathset.size() == 0) break;
                del_edge(pathset);
                vector<int> junctionset;
                vector<vector<int>> Path_junction;
                vector<edge>::iterator it1=edgeset.begin();
                while( it1 !=edgeset.end())
                {
                    if((*it1).w <= 0)
                    {
                        cout << "error" << endl;
                        p=0;
                        break;
                    }
                    ++it1;
                }
                if(!p)  break;
                bool bridge_exist=0;
                for(auto itr=pathset.begin();itr != pathset.end();itr++)
                {
                    if((*itr).p_i !=0 ) 
                    {
                        bridge_exist=1;
                        break;
                    }
                }
                if(bridge_exist)
                {
			        del_bridge();
                    if(del_path3(pathset)==1 && t.w>=1)
                	{
                        edge2exon(pathset);
                	    add_rm_copy();
                    }
		        }
                exonset.clear();
                pathset.clear();
            }
        }
        if(Path.size() != 0)
        {
            del_path1();
            del_path2(Path_junction,Path);
        }
        for(auto path=Path.begin(); path != Path.end(); path++)
        {
            outgtf(i,j);
            j++;
        }
        if(j != 1) i++;
        cl();
    }
    /*cout << "no overdemanded edge graph:"<<count <<endl;
    cout << "no pair graph :"<<nopair <<endl;
    cout << "pair include nonexist edge :" <<noedge <<endl;
    cout << "include overdemanded edge graph:" << overedge <<endl;*/
    return 0;
}
    
