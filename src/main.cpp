#include <iostream>
#include "anyalarm.hpp"

using namespace std;
using namespace anyalarm;
void pushTDList(int y, int m, int d, int h, int min, int s, TDList * list, int i, int u, char message[]);
int main(int argc, char* argv[]) {
	int aS, bS;
	scanf("%d %d", &aS, &bS);
	vector<int> t;
	srand(time(NULL));
	TDList *a = new TDList();
	for(int j=0; j<aS; j++){
		
	
	for(int i=0; i<bS; i++){
		pushTDList(rand()%10+2020,rand()%12+1,rand()%28+1,rand()%24,rand()%60,rand()%60,a,rand()%99+1, rand()%99+1, (char *)"message");
	}
	a->print();
	std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
	//a->quickSort();
	a->insertionSort();
	//a->chooseSort();
	//a->shellSort();
		
	std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
	auto diff = end - start;
	cout << diff.count() << "나노초\n" << diff.count()/1000.0 << "마이크로초\n" << diff.count()/1000000.0 << "밀리초";
	
	/*for(int i=0; i<100; i++){
		a->pop().print();
		printf("\n\n");
	}*/
	printf("\n\n정렬 후\n----------\n");
	a->print();
		t.push_back(diff.count());
		getchar();
	}
	long long int sum=0;
	for(int i=0; i<t.size(); i++){
		sum+=t[i];
	}
	cout << (sum)/(t.size()) << "나노초\n";
	return 0;
}

void pushTDList(int y, int m, int d, int h, int min, int s, TDList * list, int i, int u, char message[]){
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
	
	list->indexes.push_back(new Index(i,u,message,term));
	
}
