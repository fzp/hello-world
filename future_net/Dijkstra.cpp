#include "Dijkstra.h"
#include "define.h"

Dijkstra::Dijkstra()
{
}

Dijkstra::~Dijkstra()
{
}

int find_cost(int i,int j,hash_set<int> &valid_vertex,int V[MAX_VERTEX_NUM][MAX_VERTEX_NUM],int start){
	if(j!= start && !valid_vertex.count(j)){
		return MAX_COST;
	}else{
		return V[i][j];
	}
}

void Dijkstra::dijkstra(int start, int V[MAX_VERTEX_NUM][MAX_VERTEX_NUM], int N,hash_set<int> &valid_vertex)
{
	int  VV = V[5][19];
	vector<bool> s;                 //是否已经在S集合中  
	s.reserve(0);  
	s.assign(N, false);

   /*初始化dist和prev数组*/  
    for(int i =0; i < N; ++i)  
    {  
		dist[ i ] = find_cost( start,i,valid_vertex,V,start);  
        if(dist[ i ] < MAX_COST)  
            prev[ i ] = start;  
        else  
            prev[ i ] = -1;       //表示还不知道前一个节点是什么  
    }  
    prev[ start ] = -1;  
      
    /*开始使用贪心思想循环处理不在S集合中的每一个节点*/  
    s[start] = true;          //开始节点放入S集合中  
      
      
    int u = start;  
      
    for (int i = 1; i < N; i ++)      //这里循环从1开始是因为开始节点已经存放在S中了，还有N-1个节点要处理  
    {  
          
        /*选择dist最小的一个节点*/  
        int nextVertex = u;  
        int tempdist = MAX_COST;  
        for(int j = 0; j < N; ++j)  
        {  
            if((s[j] == false) && (dist[j] < tempdist))//寻找不在S集合中的dist最小的节点  
            {  
                nextVertex = j;  
                tempdist = dist[j];  
            }  
        }  
        s[nextVertex] = true;//放入S集合中  
        u = nextVertex;//下一次寻找的开始节点  
          
          
        /*更新dist*/  
        for (int j =0; j < N; j ++)  
        {
			int uj = find_cost( u,j,valid_vertex,V,start);
            if (s[j] == false && uj < MAX_COST)  
            {  
                int temp = dist[ u ] + uj;  
                if (temp < dist[ j ])  
                {  
                    dist[ j ] = temp;  
                    prev[ j ] = u;  
                }  
            }  
        }  
    }  
         
} 
