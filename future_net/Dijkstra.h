#ifndef  __DIJKSTRA_H__
#define  __DIJKSTRA_H__

#include <vector>
#include <stack>
#include "define.h"
#include <hash_set>

using namespace std;

using namespace std;
	class Dijkstra
	{
		public:
			Dijkstra();
			~Dijkstra();

			int dist[MAX_VERTEX_NUM];
			int prev[MAX_VERTEX_NUM];

			void dijkstra(int start, int V[MAX_VERTEX_NUM][MAX_VERTEX_NUM], int N, hash_set<int> &valid_vertex);

		private:
			
			int vertexnum; 
			

	};
#endif