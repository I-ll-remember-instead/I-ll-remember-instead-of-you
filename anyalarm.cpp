#include "anyalarm.hpp"

using namespace anyalarm;

IU_matrix::IU_matrix(int i, int u){
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

Index::Index(int i, int u, char name[]){
	strcpy(this->name,name);
	this->matrix=new IU_matrix(i,u);
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
TDList::TDList(){
	
}
Index TDList::index(int i){
	if(this->index.at[i]!=std::out_of_range){
		return this->index.at[i];
	}
	else{
		return null;
	}
}