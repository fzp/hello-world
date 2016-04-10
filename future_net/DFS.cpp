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

vector<id_dis> DFS::get_full_path(int end,int V[MAX_VERTEX_NUM][MAX_VERTEX_NUM],int vertex_num){
	//��dijkstra��������ʣ��·����������һ��·��vector
}

vector<id_dis>* DFS::get_sorted_candidates(id_dis current,int end,int V[MAX_VERTEX_NUM][MAX_VERTEX_NUM],int vertex_num,Floyd &dist){
	//������еĺ�ѡ�ڵ㲢�������ȼ�Խ�ߣ�λ��Խ��
	//ע�⣺��ȡ��ѡ�ڵ�ʱ��������·����֦
	//TODO: ʹ�����ӱ��Ż���������
	int min_cost = MAX_COST;
	vector<id_dis> valid_vertex;
	for(int i=0;i<vertex_num;i++){
		if(V[current.id][i] != MAX_COST && remain_vertex.count(i) && i != end){
			if(dist.weight[i][end] == MAX_COST){break;}
			bool break_flag = false;
			for(hash_set<int>::iterator iter=remain_including_set.begin();iter!=remain_including_set.end();iter++){
				if(dist.weight[i][*iter] == MAX_COST){
					break_flag = true;
					break;
				}
			}
			if(break_flag){break;}
		}
	}
}

void DFS::Search(int start, int end,int V[MAX_VERTEX_NUM][MAX_VERTEX_NUM], int vertex_num,hash_set<int> including_set)  
{  
	//TODO: ��Ҫ��ӳ�ʼ��
	Floyd dist;
	dist.initialvector(V,vertex_num);
	dist.floyd();
	for(hash_set<int>::iterator iter=including_set.begin();iter!=including_set.end();iter++){
		if(dist.weight[start][*iter] == MAX_COST || dist.weight[start][*iter] == MAX_COST){
			return;
		}
	}
	remain_including_set = including_set;
	current_path.push_back(id_dis(start));

	while(!current_path.empty()){
		bool backtrack = false;
		if(remain_including_set.empty()){
			//�Ѿ����������м�ڵ�
			vector<id_dis> current_full_path = get_full_path(end, V, vertex_num);
			if(!current_full_path.empty() && current_full_path.back().dis < best_path->back().dis){
				best_path = &current_full_path;
			}
			backtrack = true;
		}else{
			candidates = get_sorted_candidates(current_path.back(),end,V,vertex_num, dist);
			if(!candidates->empty()){
				forward();
			}else{
				backtrack = true;
			}
		}
		while(backtrack){
			//��ǰ·������
			id_dis back_track_vertex = current_path.back();
			current_path.erase(current_path.end()-1);
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