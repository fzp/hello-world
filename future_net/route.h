#ifndef __ROUTE_H__
#define __ROUTE_H__
#include<hash_set>

using namespace std;

void init(int *array,int length);
bool find_DAG_path(int length, int *groups,int group_num);
void search_route(char *graph[5000], int edge_num, char *condition);

#endif
