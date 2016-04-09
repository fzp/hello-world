#ifndef  __TARJAN_H__
#define  __TARJAN_H__
	class Tarjan
	{
		public:
			Tarjan();
			~Tarjan();
			void Tarjan::solve(int N, int* V);
			int belong[600];

		private:
			int LOW[600];
			int DFN[600];
			int instack[600];
			int Stap[600];
			int Dindex,Bcnt,Stop;
			void Tarjan::tarjan(int i, int N, int* V);
	};
#endif