#include <iostream>
#include "anyalarm.hpp"

using namespace std;
using namespace anyalarm;

int main(int argc, char* argv[]) {
	int y, m, d, h, min,s;
	scanf("%d %d %d %d %d %d", &y, &m, &d, &h, &min, &s);
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
		return 0;
	}
	TDList *a = new TDList();
	a->push(new Index(1,1,(char*)"d",term));
	a->print();
	return 0;
}