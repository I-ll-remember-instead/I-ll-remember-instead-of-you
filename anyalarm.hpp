#include <string>

#include <cstring>
using std::wstring;
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
	class Index{
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
	};
};