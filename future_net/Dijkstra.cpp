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
	vector<bool> s;                 //�Ƿ��Ѿ���S������  
	s.reserve(0);  
	s.assign(N, false);

   /*��ʼ��dist��prev����*/  
    for(int i =0; i < N; ++i)  
    {  
		dist[ i ] = find_cost( start,i,valid_vertex,V,start);  
        if(dist[ i ] < MAX_COST)  
            prev[ i ] = start;  
        else  
            prev[ i ] = -1;       //��ʾ����֪��ǰһ���ڵ���ʲô  
    }  
    prev[ start ] = -1;  
      
    /*��ʼʹ��̰��˼��ѭ��������S�����е�ÿһ���ڵ�*/  
    s[start] = true;          //��ʼ�ڵ����S������  
      
      
    int u = start;  
      
    for (int i = 1; i < N; i ++)      //����ѭ����1��ʼ����Ϊ��ʼ�ڵ��Ѿ������S���ˣ�����N-1���ڵ�Ҫ����  
    {  
          
        /*ѡ��dist��С��һ���ڵ�*/  
        int nextVertex = u;  
        int tempdist = MAX_COST;  
        for(int j = 0; j < N; ++j)  
        {  
            if((s[j] == false) && (dist[j] < tempdist))//Ѱ�Ҳ���S�����е�dist��С�Ľڵ�  
            {  
                nextVertex = j;  
                tempdist = dist[j];  
            }  
        }  
        s[nextVertex] = true;//����S������  
        u = nextVertex;//��һ��Ѱ�ҵĿ�ʼ�ڵ�  
          
          
        /*����dist*/  
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
