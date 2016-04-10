#ifndef  __DFS_H__
#define  __DFS_H__

#include <vector>
#include "define.h"
#include <hash_set>
#include <algorithm>  

using namespace std;

class DFS
{
	public:
		DFS();
		~DFS();
		vector<id_dis> *best_path;
		void Search(int start, int end,int V[MAX_VERTEX_NUM][MAX_VERTEX_NUM], int N,hash_set<int> including_set);

	private:
		vector<id_dis> current_path;
		vector<id_dis> *candidates;
		stack<vector<id_dis>> candidates_stack;
		hash_set<int> remain_including_set;
		hash_set<int> remain_vertex;
		void forward();
		vector<id_dis> get_full_path(int end,int V[MAX_VERTEX_NUM][MAX_VERTEX_NUM],int N);
		vector<id_dis>* get_sorted_candidates(id_dis current,int end,int V[MAX_VERTEX_NUM][MAX_VERTEX_NUM],int N,Floyd &dist);
};
class id_dis
{  
	public:
		id_dis(){};
		id_dis(int id){
			this->id = id;
			this->dis = 0;
		};
		int id;
		int dis;
};

#endif