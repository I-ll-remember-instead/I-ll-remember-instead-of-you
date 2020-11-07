#include <string>
#include <cstring>
#include <vector>
#include <cstdio>
#include <ctime>
#include <random>
#include <chrono>

using std::wstring;
using std::vector;

#ifndef localtime_r
#ifdef localtime_s
#define localtime_r(i, j) localtime_s(j, i)
#endif
#endif

#ifdef _WIN32
   #include <conio.h>
   #ifdef _WIN64
		//
   #endif
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif

namespace anyalarm{
	// IU matrix는 중요도-긴급도 매트리스
	class IU_matrix{
		private:
			int i=0; // 중요도
			int u=0; // 긴급도
		public:
			IU_matrix(int i, int u);
			void set(int i, int u);
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
			int timesU=1; // 값이 1이면 1마다 증가시킨다는 의미.
			int plusedU=0; // 증가된 긴급도.
		public:
			Index();
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
			time_t* returnTime();
			int returnTimesU();
			int returnPlusedU();
			Index operator=(Index input);
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
			void insertionSort();
			void quickSort();
			void quick(int start,int end);
			void radix();
			void baillantSort();
			void tjsxorSort();
			void chooseSort();
	};
};
