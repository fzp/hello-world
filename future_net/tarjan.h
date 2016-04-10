#ifndef  __TARJAN_H__
#define  __TARJAN_H__
	class Tarjan
	{
		public:
			Tarjan();
			~Tarjan();
			void solve(int l, int N, int* V);
			int belong[600];
			int group_num;
			int length;

		private:
			int LOW[600];
			int DFN[600];
			int instack[600];
			int Stap[600];
			int Dindex,Bcnt,Stop;
			void tarjan(int i, int N, int* V);
			void get_group_num();
	};
#endif