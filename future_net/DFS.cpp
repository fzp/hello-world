#include "DFS.h"
#include "define.h"
#include "floyd.h"
#include "Dijkstra.h"
#include <vector>
#include <stack>


bool cmp(id_dis a, id_dis b)
{
	return a.dis>b.dis;
}

void DFS::forward(){
	current_path.push_back(candidates.back());
	remain_including_set.erase(candidates.back().id);
	remain_vertex.erase(candidates.back().id);
	candidates.pop_back();
	candidates_stack.push(candidates);
}

vector<id_dis> DFS::get_full_path(int end,int V[MAX_VERTEX_NUM][MAX_VERTEX_NUM],int vertex_num){
	//用dijkstra方法走完剩余路径，并返回一个路径vector

	int current_start = current_path.back().id;
	Dijkstra min_path;

	min_path.dijkstra(current_start,V,vertex_num,remain_vertex);
	
	vector<id_dis> remain_path;

	while(end != -1 && end != current_start)
	{
		id_dis pre_v(end);
		pre_v.dis = min_path.dist[end]+current_path.back().dis;
		remain_path.push_back(pre_v);
		end = min_path.prev[end];
	}
	
	for(vector<id_dis>::reverse_iterator i = current_path.rbegin();i!=current_path.rend();i++)
	{
		remain_path.push_back(*i);
	}
	reverse(remain_path.begin(),remain_path.end());
	return remain_path;



}

vector<id_dis> DFS::get_sorted_candidates(id_dis current,int end,int V[MAX_VERTEX_NUM][MAX_VERTEX_NUM],int vertex_num,Floyd *dist){
	//获得所有的候选节点并排序，优先级越高，位置越后
	//注意：获取候选节点时，不可行路径剪枝
	//TODO: 使用连接表优化遍历过程
	vector<id_dis> valid_vertex;
	for(int i=0;i<vertex_num;i++){
		if(V[current.id][i] != MAX_COST && remain_vertex.count(i) && i != end){
			if(dist->weight[i][end] == MAX_COST){break;}
			bool break_flag = false;	
			int min_cost = MAX_COST;
			int current_cost = V[current.id][i] + current.dis;
			hash_set<int>::iterator iter;
			for(iter=remain_including_set.begin();iter!=remain_including_set.end();iter++){
				if(dist->weight[i][*iter] == MAX_COST){
					break;
				}
				//下面作为启发函数如何？
				//int predicted_cost = dist.weight[i][*iter]+dist.weight[*iter][end];
				int predicted_cost = dist->weight[i][*iter];
				if(dist->weight[i][*iter] < min_cost){
					min_cost = dist->weight[i][*iter];
				}
				if(!best_path.empty()){
					int predicted_cost = current_cost + dist->weight[i][*iter]+dist->weight[*iter][end];
					if(predicted_cost > best_path.back().dis){
						break_flag = true;
						break;
					}
				}
			}
			if(break_flag){break;}
			if(iter==remain_including_set.end())
				valid_vertex.push_back(id_dis(i,V[current.id][i]+min_cost));
		}
	}
	sort(valid_vertex.begin(),valid_vertex.end(),cmp);
	for(vector<id_dis>::iterator iter=valid_vertex.begin();iter!=valid_vertex.end();iter++){
		iter->dis = current.dis+V[current.id][iter->id];
	}
	return valid_vertex;
}

void DFS::Search(int start, int end,int V[MAX_VERTEX_NUM][MAX_VERTEX_NUM], hash_set<int> vertex_set,hash_set<int> including_set)  
{  
	//TODO: 需要添加初始化
	remain_vertex = vertex_set;
	remain_vertex.erase(start);
	Floyd dist;
	dist.initialvector(V,vertex_set.size());
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
			//已经走完所有中间节点
			vector<id_dis> current_full_path = get_full_path(end, V, vertex_set.size());
			if(!current_full_path.empty() && (best_path.empty() || current_full_path.back().dis < best_path.back().dis)){
				best_path = current_full_path;
			}
			backtrack = true;
		}else{
			candidates = get_sorted_candidates(current_path.back(),end,V,vertex_set.size(), &dist);
			if(!candidates.empty()){
				forward();
			}else{
				backtrack = true;
			}
		}
		while(backtrack){
			//当前路径回溯
			if(current_path.empty()){
				break;
			}
			id_dis back_track_vertex = current_path.back();
			current_path.pop_back();
			remain_vertex.insert(back_track_vertex.id);
			if(including_set.count(back_track_vertex.id)){
				remain_including_set.insert(back_track_vertex.id);
			}
			//当前栈回溯
			if(!candidates_stack.empty()){
				candidates = candidates_stack.top();
				candidates_stack.pop();
				if(!candidates.empty()){
					forward();
					break;
				}
			}
		}
	} 
}  