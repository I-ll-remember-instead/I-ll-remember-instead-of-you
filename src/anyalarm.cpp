#include "anyalarm.hpp"
#include <stdexcept>


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
	printf("내용: %s - 중요도: %d 긴급도: %d\n", this->name, this->matrix->returnImportance(), this->matrix->returnUrgency()+plusedU);
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
	Index returnBuff=indexes.at(0);
	int heapSize=indexes.size();
	int key=0, nextkey;
	Index tmp;
	while(heapSize>=key*2){
		if(key*2+1>heapSize && indexes[key*2].returnIU()>indexes[key].returnIU()){
			try{
				tmp=*indexes.at(key*2);
			}catch(std::out_of_range& e){
				break;
			}
			key*=2;
		}
		else if (key * 2 + 1 > heapSize) break;
		else {
			if(indexes[key*2].returnIU()>indexes[key*2+1].returnIU()){
				tmp = *indexes[key * 2];
				nextkey = key * 2;
			}
			else {
				tmp = *indexes[key * 2 + 1];
				nextkey = key * 2 + 1;
			}
			if (tmp.returnIU() < indexes[key].returnIU()){
				tmp=*indexes[key];
				indexes[key]=indexes[nextkey];
				*indexes[nextkey]=tmp;
			}
			else break;
		}
	}
}