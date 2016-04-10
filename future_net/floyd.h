#ifndef  __FLOYD_H__
#define  __FLOYD_H__

#include <vector>
#include <stack>

using namespace std;
	class Floyd
	{
		public:
			Floyd();
			~Floyd();
			vector<vector<int>> weight;  
			vector<vector<int>> path;  

			void initialvector(int *V, int N);
			void floyd();

		private:
			int vertexnum; 
			

	};
#endif