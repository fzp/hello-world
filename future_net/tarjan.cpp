#include"tarjan.h"
#include"define.h"
#include<memory.h>
Tarjan::Tarjan()
{
    memset(DFN,0,sizeof(DFN));
}

Tarjan::~Tarjan()
{
}

void Tarjan::tarjan(int i,int N, int* V)
{
    int j;
    DFN[i]=LOW[i]=Dindex;
	Dindex++;
    instack[i]=true;
    Stap[++Stop]=i;
	for (j=0;j<length;j++)
    {
		if(*(V+N*i+j)== MAX_COST || *(V+N*i+j)==0){continue;}
        if (!DFN[j])
        {
            tarjan(j,N,V);
            if (LOW[j]<LOW[i])
                LOW[i]=LOW[j];
        }
        else if (instack[j] && DFN[j]<LOW[i])
            LOW[i]=DFN[j];
    }
    if (DFN[i]==LOW[i])
    {
        Bcnt++;
        do
        {
            j=Stap[Stop--];
            instack[j]=false;
            belong[j]=Bcnt;
        }
        while (j!=i);
    }
}
void Tarjan::solve(int l, int N, int* V)
{
    int i;
	length = l;
    Stop=Bcnt=Dindex=0;
    for (i=0;i<length;i++)
        if (!DFN[i])
            tarjan(i, N, V);
	get_group_num();
}

void Tarjan::get_group_num(){
	group_num = belong[0];
	for(int i=1;i<length;i++){
		if(group_num < belong[i]){
			group_num = belong[i];
		}
	}
	group_num++;
}