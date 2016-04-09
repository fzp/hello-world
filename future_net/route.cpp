#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <hash_set>
#include <string>
#include <vector>

using namespace std;

int scc[600];
int scc_order[600];
int scc_including[600];
int costs[600][600];
int edge[600][600];
int start_point;
int end_point;
int useful_edge_num;
hash_set<int> including_set;
hash_set<int> vertex_set;

vector<string> split(const  string& s, const string& delim)  
{  
    vector<string> elems;  
    size_t pos = 0;  
    size_t len = s.length();  
    size_t delim_len = delim.length();  
    if (delim_len == 0) return elems;  
    while (pos < len){  
        int find_pos = s.find(delim, pos);  
        if (find_pos < 0)  {  
            elems.push_back(s.substr(pos, len - pos));  
            break;  
        }  
        elems.push_back(s.substr(pos, find_pos - pos));  
        pos = find_pos + delim_len;  
    }  
    return elems;  
}

void fill_demand(char * demand){
    string s_demand(demand);
    vector<string> result = split(s_demand,",");
	start_point = atoi(result[0].c_str());
    end_point = atoi(result[1].c_str());
	result = split(result[2],"|");
	for(vector<string>::iterator iter=result.begin();iter!=result.end();iter++){
		including_set.insert(atoi((*iter).c_str()));
	}
}

void fill_distance(char *topo[5000],int edge_num){
    int linkID,sourceID,destinationID,cost;
    vector<string> result;
    for(int i=0;i<edge_num;i++){
        string s_topo(topo[i]);
        result = split(s_topo,",");
        sourceID = atoi(result[1].c_str());
		if(sourceID == end_point){ 
			edge_num--;
			continue;}
        destinationID = atoi(result[2].c_str());
        if(destinationID == start_point){
			edge_num--;
			continue;}
        linkID = atoi(result[0].c_str());
        cost = atoi(result[3].c_str());
        vertex_set.insert(sourceID);
        vertex_set.insert(destinationID);
        if(costs[sourceID][destinationID]==0 || costs[sourceID][destinationID] > cost){
            costs[sourceID][destinationID] = cost;
            edge[sourceID][destinationID] = linkID;
			if(costs[sourceID][destinationID] > cost){edge_num--;}
        }
    }
	useful_edge_num = edge_num;
}

void search_route(char *topo[5000], int edge_num, char *demand){
    unsigned short result[] = {2, 6, 3};
    fill_demand(demand);
    fill_distance(topo,edge_num);
    for (int i = 0; i < 3; i++)
        record_result(result[i]);
}
