#include <iostream>
#include "anyalarm.hpp"

using namespace std;
using namespace anyalarm;

int main(int argc, char* argv[]) {
	TDList *a = new TDList();
	a->indexes.push_back(new Index(1,1,"d"));
	cout << (a->index(0).returnImportance()) << " "<< (a->index(0).returnUrgency()) << " " << (a->index(0).returnName());
	return 0;
}