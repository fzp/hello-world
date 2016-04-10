#include "DFS.h"
#include "define.h"
#include "floyd.h"
#include <vector>
#include <stack>

bool cmp(id_dis a, id_dis b)
{
	return a.dis>b.dis;
}

void DFS::forward(){
	current_path.push_back(candidates->back());
	remain_including_set.erase(candidates->back().id);
	remain_vertex.erase(candidates->back().id);
	candidates->pop_back();
	candidates_stack.push(*candidates);
}

vector<id_dis> DFS::get_full_path(int end,int *V,int N){
	//��dijkstra��������ʣ��·����������һ��·��vector
}

vector<id_dis>* DFS::get_sorted_candidates(id_dis current,int end,int* V,int N){
	//������еĺ�ѡ�ڵ㲢�������ȼ�Խ�ߣ�λ��Խ��
	//ע�⣺��ȡ��ѡ�ڵ�ʱ��������·����֦
}

vector<id_dis> DFS::Search(int start, int end,int* V, int N,hash_set<int> including_set)  
{  
	Floyd dist;
	dist.initialvector(V,N);
	dist.floyd();
	remain_including_set = including_set;
	current_path.push_back(id_dis(start));

	while(!current_path.empty()){
		bool backtrack = false;
		if(remain_including_set.empty()){
			//�Ѿ����������м�ڵ�
			vector<id_dis> current_full_path = get_full_path(end, V, N);
			if(!current_full_path.empty() && current_full_path.back().dis < best_path->back().dis){
				best_path = &current_full_path;
			}
			backtrack = true;
		}else{
			candidates = get_sorted_candidates(current_path.back(),end,V,N);
			if(!candidates->empty()){
				forward();
			}else{
				backtrack = true;
			}
		}
		while(backtrack){
			//��ǰ·������
			id_dis back_track_vertex = current_path.back();
			remain_vertex.insert(back_track_vertex.id);
			if(including_set.count(back_track_vertex.id)){
				remain_including_set.insert(back_track_vertex.id);
			}
			//��ǰջ����
			if(!candidates_stack.empty()){
				candidates = &candidates_stack.top();
				candidates_stack.pop();
				if(!candidates->empty()){
					forward();
					break;
				}
			}
		}
	} 
}  