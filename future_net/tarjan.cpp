#include"tarjan.h"
#include<memory.h>
Tarjan::Tarjan()
{
    memset(DFN,0,sizeof(DFN));
}

Tarjan::~Tarjan()
{
}

void Tarjan::tarjan(int i, int N, int* V)
{
    int j;
    DFN[i]=LOW[i]=++Dindex;
    instack[i]=true;
    Stap[++Stop]=i;
    for (j=0;j<N;j++)
    {
		if(*(V+N*i+j)==0){continue;}
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
void Tarjan::solve(int N, int* V)
{
    int i;
    Stop=Bcnt=Dindex=0;
    for (i=0;i<N;i++)
        if (!DFN[i])
            tarjan(i, N, V);
}