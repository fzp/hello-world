#include "floyd.h"
#include "define.h"

Floyd::Floyd(){
}

Floyd::~Floyd()
{
}

void Floyd::initialvector(int *V, int N){  
	vertexnum = N;
	weight.resize(vertexnum);//路径权重数组  
	path.resize(vertexnum);//保存最短路径数组,记录前继  
	for(int i = 0;i < vertexnum;i++){//建立数组  
		weight[i].resize(vertexnum,MAX_COST);  
		path[i].resize(vertexnum,-1);  
	}
	for(int from = 0;from< vertexnum;from++)
	{
		for(int to = 0;to<vertexnum;to++)
		{
			if(from == to)
			{
				weight[from][to] = 0;
				path[from][to] = from;
			}
			else if(V[from * vertexnum + to]>0)
			{
				weight[from][to] = V[from * vertexnum + to];
				path[from][to] = from;
			}
			else
			{
				weight[from][to] = MAX_COST;
				path[from][to] = -1;
			}

		}
	}
}  

void Floyd::floyd(){  
    for(int k = 0;k < vertexnum;k++) 
	{
        for(int i= 0;i < vertexnum;i++)  
		{
            for(int j = 0;j < vertexnum;j++){  
				if(i == j)
				{
					continue;
				}
                if((weight[i][k] > 0 && weight[k][j] && weight[i][k] < MAX_COST && weight[k][j] < MAX_COST) && (weight[i][k] + weight[k][j] < weight[i][j])){//前面一部分是防止加法溢出  
                    weight[i][j] = weight[i][k] + weight[k][j];  
                    path[i][j] = path[k][j];  
                }  
            }
		}
	}
}    