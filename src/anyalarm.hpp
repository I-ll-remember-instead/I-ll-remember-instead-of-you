#include <string>
#include <cstring>
#include <vector>
#include <cstdio>
using std::wstring;
using std::vector;
namespace anyalarm{
	// IU matrix는 중요도-긴급도 매트리스
	class IU_matrix{
		private:
			int i=0; // 중요도
			int u=0; // 긴급도
		public:
			IU_matrix(int i, int u);
			int* returnMatrix();
			int returnImportance();
			int returnUrgency();
	};
	class Index{ // 내용물. 즉 할일과 중요도
		private:
			IU_matrix *matrix;
			char name[1000];
		public:
			Index(int i, int u, char name[]);
			IU_matrix returnMatrix();
			int * returnMatrixInt();
			int returnImportance();
			int returnUrgency();
			char * returnName();
			void print();
	};
	class TDList{ // todo 리스트
		private:
		public:
			vector<Index> indexes;
			TDList();
			Index index(int i);
			void print();
	};
};