#include <stdio.h>
#include <hash_set>
#include <string>
#include <vector>
#include "route.h"
#include "lib_record.h"
#include "define.h"
#include "tarjan.h"
#include <iostream>
#include <stack>
#include "DFS.h"

using namespace std;

int scc[MAX_VERTEX_NUM];
int scc_order[MAX_VERTEX_NUM];
int scc_including[MAX_VERTEX_NUM];
int costs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
int edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
int DAG[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
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
	int useless_edge_num = 0;
    vector<string> result;
    for(int i=0;i<edge_num;i++){
        string s_topo(topo[i]);
        result = split(s_topo,",");
        sourceID = atoi(result[1].c_str());
		if(sourceID == end_point){ 
			useless_edge_num++;
			continue;}
        destinationID = atoi(result[2].c_str());
        if(destinationID == start_point){
			useless_edge_num++;
			continue;}

        linkID = atoi(result[0].c_str());
        cost = atoi(result[3].c_str());
        vertex_set.insert(sourceID);
        vertex_set.insert(destinationID);
        if(costs[sourceID][destinationID] > cost){
            costs[sourceID][destinationID] = cost;
            edge[sourceID][destinationID] = linkID;
			if(costs[sourceID][destinationID] > cost){edge_num--;}
        }
    }
	useful_edge_num = edge_num - useless_edge_num;
}

void search_route(char *topo[5000], int edge_num, char *demand){
	//bool valid;
    //unsigned short result[] = {2, 6, 3};
	init((int*)costs,MAX_VERTEX_NUM);
    fill_demand(demand);
    fill_distance(topo,edge_num);
	DFS dfs;
	int  VV = costs[5][19];
	dfs.Search(start_point,end_point,costs,vertex_set,including_set);
	for(vector<id_dis>::iterator iter=dfs.best_path.begin();iter!=dfs.best_path.end();iter++){
		record_result(iter->id);
	}
	cout << "hello" << endl;
	/*
	Tarjan tarjan;
	tarjan.solve(vertex_set.size(),MAX_VERTEX_NUM,(int*)costs);
	valid = find_DAG_path(vertex_set.size(),tarjan.belong,tarjan.length);
	if(!valid){return;}
    for (int i = 0; i < 3; i++)
        record_result(result[i]);
		*/
}

void init(int *array,int length){
	for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++)
		{
			if(i == j)
				*array = 0;
			else
				*array = MAX_COST;
			array = array + 1;
		}
}

bool find_DAG_path(int length, int *groups,int group_num){
	hash_set<int> DAG_including_set;
	//×ª»¯³ÉDAGÍ¼
	init((int*)DAG,group_num);
	for(int i=0;i<length;i++){
		for(int j=0;j<length;j++){
			if(costs[i][j] == MAX_COST || costs[i][j] == 0){continue;}
			DAG[groups[i]][groups[j]] = 1;
		}
	}
	for(hash_set<int>::iterator i=including_set.begin();i!=including_set.end();i++){
		DAG_including_set.insert(groups[*i]);
	}
	//find valid path
	return false;

}
