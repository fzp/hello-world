#ifndef  __DIJKSTRA_H__
#define  __DIJKSTRA_H__

#include <vector>
#include <stack>

using namespace std;

using namespace std;
	class Dijkstra
	{
		public:
			Dijkstra();
			~Dijkstra();

			int dist[600];
			int prev[600];

			void dijkstra(int start, int* V, int N);

		private:
			
			int vertexnum; 
			

	};
#endif