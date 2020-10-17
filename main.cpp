#include <iostream>
#include "anyalarm.hpp"

using namespace std;
using namespace anyalarm;

int main(int argc, char* argv[]) {
	Index *a = new Index(1,2, "오");
	wcout << (a->returnImportance()) << " "<< (a->returnUrgency()) << " " << (a->returnName());
	return 0;
}