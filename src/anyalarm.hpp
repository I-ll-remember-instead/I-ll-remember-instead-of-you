#include <string>
#include <cstring>
#include <vector>
#include <cstdio>
#include <ctime>
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
			int returnIU();
	};
	class Index{ // 내용물. 즉 할일과 중요도
		private:
			IU_matrix *matrix;
			char name[1000];
			time_t Times[3]; //1시작 시간 2끝 시간 3현재시간
			const int timesU=1; // 값이 1이면 1마다 증가시킨다는 의미.
			int plusedU=0; // 증가된 긴급도.
		public:
			Index(int i, int u, char name[], time_t term);
			IU_matrix returnMatrix();
			int * returnMatrixInt();
			int returnImportance();
			int returnUrgency();
			char * returnName();
			void print();
			void setTime(time_t t);
			void printStartTime();
			void printEndTime();
			void update();
			int returnIU();
	};
	class TDList{ // todo 리스트
		private:
		public:
			vector<Index *> indexes;
			TDList();
			Index index(int i);
			void print();
			void push(Index * index1);
			Index pop();
	};
};