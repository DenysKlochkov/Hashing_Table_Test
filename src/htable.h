#ifndef _HTABLE_H
#define _HTABLE_H

#define H_TYPE unsigned long int
#define PRIME_0 59
#define PRIME_1 1531
#define PRIME_2 7919
#include <cstring>
#include <iostream>
#include <locale.h>
using namespace std;

class mHashTable{
public:
	struct record{
	int instances;
	record * Next;
	wchar_t * text;

	record(const wchar_t * nText, const int & nSize):instances(1),Next(nullptr){ 
		text= new wchar_t[nSize+1]; 
		wcscpy(text,nText);
	}
	~record(){delete [] text;}
};


private:



const H_TYPE K;
bool hash_version;
record ** myRecords;

H_TYPE getHash(const wchar_t * text){
	H_TYPE hash=0;
	int i=0;
	int size = wcslen(text);
	if(hash_version){
	while(i++<size)hash+=(H_TYPE)(*(text+i));
	
	hash%=K;
	} 
	else{
	while(i++<size)hash=((hash<<5)+hash)+(H_TYPE)(*(text+i));
	hash%=K;	
	}

	return hash;
}



friend wostream& operator<<(wostream& os, const mHashTable& mht);
public:
	mHashTable(const H_TYPE& tableSize, bool hversion):K(tableSize),hash_version(hversion){
			myRecords = new record *[tableSize]{nullptr};
	}
	~mHashTable(){
		for(H_TYPE i =0; i<K;i++){
			record * prev = myRecords[i];
			record * next = prev;
			while ( prev !=nullptr){
				next = prev->Next;
				delete prev;
				prev = next;
			}
		}
	}

int insert( const wchar_t * nText){
	record * tmp;
	H_TYPE nHash = getHash(nText);
	int depth=0;
	int nSize=wcslen(nText);
	tmp = myRecords[nHash];
	if(tmp==nullptr){myRecords[nHash] = new record ( nText , nSize);
	return depth;}  // there were no elements with the givem hash
	while(1){ //comparing new element with already existing with the same hash
		++depth;
		if(wcscmp(tmp->text,nText)==0){
			tmp->instances++;        //if found - increasing the instances count of an element
			return depth;}
		
	if(tmp->Next!=nullptr)tmp=tmp->Next;
	else break;
	}


		tmp->Next = (record*)new record ( nText , nSize); // if not found - inserting new element
		return depth;
}

bool remove( const wchar_t * nText){
	record * tmp;
	record * tmp_prev;
			int nSize=wcslen(nText);
	H_TYPE nHash = getHash(nText);

	tmp = myRecords[nHash];
	if(tmp==nullptr)return false;//if there were no elements with the given hash - unable to remove
	tmp_prev = tmp;
	do{ 
		if(wcscmp(tmp->text,nText)==0){
			tmp->instances--;       
			if(tmp->instances==0 && tmp_prev == tmp){
				myRecords[nHash]=tmp->Next;
				delete tmp;
			}
			else if(tmp->instances==0){
				tmp_prev->Next=tmp->Next;
				delete tmp;
			}
			return true;
		}
		tmp_prev=tmp;
		tmp=tmp->Next;
	}
	while (tmp!=nullptr);
	return false;//if element not found among the elements with the same hash - unable to remove
}



};


wostream& operator<<(wostream& os, const mHashTable& mht){
	for(H_TYPE i = 0; i<mht.K;i++){
		if(mht.myRecords[i]!=nullptr){
			mHashTable::record * tmp = mht.myRecords[i];
			os<<'('<<i<<"):\t";
			do{if(tmp->instances!=1)os<<'('<<tmp->instances<<"x)";os<<tmp->text<<"->";tmp=tmp->Next;}
			while(tmp!=nullptr);
			os<<"\b\b  "<<'\n';

		}
	
	}
		os<<"===========================================================\n";
}


#endif