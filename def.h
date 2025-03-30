
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;





struct edge {
    int from;   //edge_start
    int to;    //edge_end
    float w;    //edge_weight
    int p_w;    //pair_weight
    int p_i;    //pair_index
    int ps;    //original edge in which pair
    int num;
}e;

struct node{
    int start;
    int end;
    int index;
    float w;
}v;

struct exon{
    int index;
    int from;
    int to;
};

struct transcript
{
    /* data */
    vector<exon> exon_used;
    string chr;
    string chain;
    float w;
}t;

struct pairs
{
    /* data */
    vector<int> eds;
    int w;
}p;

vector<edge> edgeset;
vector<edge> edgeset_copy;
vector<node> nodeset;
vector<edge> pathset;
vector<pairs> pairset;
vector<vector<int>> Path;
vector<vector<int>> Path_junction;
vector<int> exonset;
vector<edge> temp;
exon e_used;



