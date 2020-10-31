#include <iostream>
#include "anyalarm.hpp"

using namespace std;
using namespace anyalarm;
void pushTDList(int y, int m, int d, int h, int min, int s, TDList * list, int i, int u, char * message);
int main(int argc, char* argv[]) {
	TDList *a = new TDList();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> ydis(2020, 2030);
	std::uniform_int_distribution<int> mdis(1, 12);
	std::uniform_int_distribution<int> ddis(28, 1);
	std::uniform_int_distribution<int> hdis(0, 23);
	std::uniform_int_distribution<int> mindis(0, 59);
	std::uniform_int_distribution<int> sdis(0, 59);
	
	std::uniform_int_distribution<int> iudis(0, 99);
	std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
	int y=ydis(gen), m=mdis(gen), d=ddis(gen), h=hdis(gen), min=mindis(gen), s=sdis(gen);
	for(int i=0; i<100; i++){
		y=ydis(gen); m=mdis(gen); d=ddis(gen); h=hdis(gen); min=mindis(gen); s=sdis(gen);
		pushTDList(y,m,d,h,min,s,a,iudis(gen), iudis(gen), "message");
	}
	std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
	auto diff = end - start;
	cout << diff.count();
	return 0;
}

void pushTDList(int y, int m, int d, int h, int min, int s, TDList * list, int i, int u, char * message){
	//scanf("%d %d %d %d %d %d", &y, &m, &d, &h, &min, &s);
	struct tm buffTm;
	buffTm.tm_year=y-1900;
	buffTm.tm_mon=m-1;
	buffTm.tm_mday=d;
	buffTm.tm_hour=h;
	buffTm.tm_min=min;
	buffTm.tm_sec=s;
	
	time_t term=mktime(&buffTm);
	if(term==-1){
		printf("요류");
		return;
	}
	list->push(new Index(1,1,(char*)"d",term));
}
