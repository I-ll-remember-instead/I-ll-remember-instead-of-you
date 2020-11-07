#include "anyalarm.hpp"
#include <stdexcept>
#include <queue>

using namespace anyalarm;

IU_matrix::IU_matrix(int i, int u){
	this->i=i;
	this->u=u;
}
void IU_matrix::set(int i, int u){
	this->i=i;
	this->u=u;
}
int* IU_matrix::returnMatrix(){
	int *a=new int[2];
	a[0]=this->i;
	a[1]=this->u;
	return a;
}
int IU_matrix::returnImportance(){
	return i;
}
int IU_matrix::returnUrgency(){
	return u;
}
int IU_matrix::returnIU(){
	return i*u;
}



Index::Index(){
	this->matrix=new IU_matrix(0,0);
	//
}
Index::Index(int i, int u, char name[],time_t term){
	strcpy(this->name,name);
	this->matrix=new IU_matrix(i,u);
	Times[0]=time(nullptr);
	Times[1]=term;
}
IU_matrix Index::returnMatrix(){
	return *(this->matrix);
}
int * Index::returnMatrixInt(){
	return this->matrix->returnMatrix();
}
int Index::returnImportance(){
	return matrix->returnImportance();
}
int Index::returnUrgency(){
	return matrix->returnUrgency();
}
char * Index::returnName(){
	return this->name;
}
void Index::print(){
	printf("내용: %s - 중요도: %d 긴급도: %d 중요X긴급: %d\n", this->name, this->matrix->returnImportance(), this->matrix->returnUrgency()+plusedU, this->matrix->returnImportance()*(this->matrix->returnUrgency()+this->returnPlusedU()));
	printStartTime();
	printf("\n");
	printEndTime();
}
void Index::printStartTime(){
	struct tm buffTm;
	localtime_r(&Times[0],&buffTm);
	int y=buffTm.tm_year+1900;
	int m=buffTm.tm_mon+1;
	int d=buffTm.tm_mday;
	int h=buffTm.tm_hour;
	int min=buffTm.tm_min;
	int s=buffTm.tm_sec;
	printf("시작시간 %04d:%02d:%02d - %02d:%02d:%02d", y,m,d,h,min,s);
}
void Index::printEndTime(){
	struct tm buffTm;
	localtime_r(&Times[1],&buffTm);
	int y=buffTm.tm_year+1900;
	int m=buffTm.tm_mon+1;
	int d=buffTm.tm_mday;
	int h=buffTm.tm_hour;
	int min=buffTm.tm_min;
	int s=buffTm.tm_sec;
	printf("완료 시간 %04d:%02d:%02d - %02d:%02d:%02d", y,m,d,h,min,s);
}
void Index::setTime(time_t t){
	Times[1]=t;
}
void Index::update(){
	int k=Times[1] - Times[0]-(Times[1] - time(0));
	k/=3600;
	k/=timesU;
	plusedU=k;
}
int Index::returnIU(){
	return matrix->returnImportance()*(matrix->returnUrgency()+plusedU);
}
time_t* Index::returnTime(){
	return Times;
}
int Index::returnTimesU(){
	return timesU;
}
int Index::returnPlusedU(){
	return plusedU;
}
Index Index::operator=(Index input){
	this->matrix->set(input.matrix->returnImportance(), input.matrix->returnUrgency());
	strcpy(this->name, input.returnName());
	time_t * tBuff=input.returnTime();
	this->Times[0]=tBuff[0];
	this->Times[1]=tBuff[1];
	this->Times[2]=tBuff[2];
	this->timesU=input.returnTimesU();
	this->plusedU=input.returnPlusedU();
	return *this;
}



TDList::TDList(){
	
}
Index TDList::index(int i){
	try{
		return *(this->indexes.at(i));
	}catch(std::out_of_range& e){
		//
	}
	return Index(0,0, (char *)"", (time_t)0);
}
void TDList::print(){
	for(long long int i=0;i<indexes.size();i++){
		indexes[i]->update();
		indexes[i]->print();
		printf("추가긴급도 %d", this->indexes[i]->returnPlusedU());
		printf("\n");
	}
}	
	
void TDList::push(Index * index1){
	int key=this->indexes.size(); //key=배열사이즈 즉 하나가 추가되었을 때의 끝 지점이다. 마지막 내용을 가리킴.
	this->indexes.push_back(index1);
	while(key>1){
		if(this->indexes[key]->returnIU()>this->indexes[key/2]->returnIU()){
			Index bufIn=*(this->indexes[key]);
			*(this->indexes[key])=(*(this->indexes[key/2]));
			*(this->indexes[key/2])=bufIn;
			key/=2;
		}
		else break;
	}
}

Index TDList::pop(){
	Index returnBuff;
	try{
		returnBuff=*(indexes.at(0));
	}catch(std::out_of_range e){
		return Index();
	}
	int heapSize=indexes.size();
	int key=0, nextkey;
	Index tmp;
	while(heapSize>=key*2){
		if(key*2+1>heapSize && indexes[key*2]->returnIU()>indexes[key]->returnIU()){
			try{
				tmp=*indexes.at(key*2);
			}catch(std::out_of_range& e){
				break;
			}
			key*=2;
		}
		else if (key * 2 + 1 > heapSize) break;
		else {
			if(indexes[key*2]->returnIU()>indexes[key*2+1]->returnIU()){
				tmp = *indexes[key * 2];
				nextkey = key * 2;
			}
			else {
				tmp = *indexes[key * 2 + 1];
				nextkey = key * 2 + 1;
			}
			if (tmp.returnIU() < indexes[key]->returnIU()){
				tmp=*indexes[key];
				indexes[key]=indexes[nextkey];
				*indexes[nextkey]=tmp;
			}
			else break;
		}
	}
	return returnBuff;
}

void TDList::insertionSort(){
	const int left=0; const int right=this->indexes.size()-1;
  for (int i = left; i < right; ++i){
    for (int j = i + 1; j > left && this->indexes[j]->returnIU()>this->indexes[j-1]->returnIU(); --j){
      std::swap(this->indexes[j], this->indexes[j - 1]);
    }
  }
}

void TDList::quickSort(){
	this->quick(0,this->indexes.size()-1);
}

void TDList::quick(int start,int end){
	if (start >= end){
		return;
	}
	int key = start;
	int i = start + 1, j = end;
	Index temp;
	while(i<=j){
		while(i <= end && this->indexes[i]->returnIU() <= this->indexes[key]->returnIU()){
			i++;
		}
		while(j > start && this->indexes[j]->returnIU() >= this->indexes[key]->returnIU()){
			j--;
		}
		if (i > j){
			//std::swap(this->indexes[key],this->indexes[j]);
			temp=*(this->indexes[j]);
			*(this->indexes[j])=*(this->indexes[key]);
			*(this->indexes[key])=temp;
		}
		else {
			//std::swap(this->indexes[i],this->indexes[j]);
			temp=*(this->indexes[i]);
			*(this->indexes[i])=*(this->indexes[j]);
			*(this->indexes[j])=temp;
		}
	}
	
	this->quick(start,j-1);
	this->quick(j+1,end);
}
/*
void TDList::radix(int begin, int end)
{
    
}

void TDList::heapSort(){
	
}

void TDList::makeheap(int indsize){
	for (int i=1;i<indsize;i++){
		int c=i;
		while(c>0){
			int root=(i-1)/2;
			if (this->indexes[root]->returnIU() < )
		}
	}
}

void TDList::baillantSort(){
	std::queue<Index> radix[10]; // 자리수에 대한 큐 배열
 
    int max = this->indexes[0]->returnIU();
    int d = 1; // 최대자리수
 
    // 최대 자리수를 구하기 위해서 최댓값을 찾아낸다.
    for (int i = 1; i < this->indexes.size(); i++)
        if (max < this->indexes[i]->returnIU()) max = this->indexes[i]->returnIU();
 
    // 최대 자리수를 구해낸다.
    while (max/10){
        d *= 10;
        max /= 10;
    }
 
    int mod = 10;
    int dMin = 1;
 
    while (dMin<=d){
        // 자리수에 따라 큐에 집어넣는다.
        for (int i = 0; i < indexes.size(); i++){
            radix[(this->indexes[i]->returnIU() % mod)/dMin].push(*(this->indexes[i]));
        }
 
        // 큐에 들어간 값들을 자리수 크기 순으로 다시 배열에 집어넣는다.
        for (int i = 0, j = 0; i < 10;){
            if (radix[i].size()){
                *(this->indexes[j++]) = radix[i].front();
                radix[i].pop();
            }
            else i++;
        }
 
        dMin *= 10;
        mod *= 10;
    }
 
    //for (int i = 0; i < 8; i++) std::cout << this->indexes[i] << ' ';
 
    return;
}

void TDList::tjsxorSort(){
	int min_idx;
    for(int i=0; i<this->indexes->size(); i++){
        min_idx = i;
 
        for(int j=i+1; j<this->indexes->size(); j++){
            if(this->indexes[min_idx]->returnIU() > this->indexes[j]->returnIU()){
                min_idx = j;
            }
        }
        std::swap(this->indexes[min_idx], this->indexes[i]);
    }
}
*/

void TDList::chooseSort(){
	int minp;
	Index temp;
	for (int i=0;i<this->indexes.size();i++){
		minp=i;
		for (int j=0;j<this->indexes.size();j++){
			if (this->indexes[j]->returnIU() < this->indexes[minp]->returnIU()){
				minp=j;

				//minp=i; 요로코롬 하면 되나
			}
			temp=*(this->indexes[i]);
			*(this->indexes[i]) = *(this->indexes[minp]);
			*(this->indexes[minp]) = temp;
		}
	}
}