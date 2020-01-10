#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>
#include "htable.h"
#include <iomanip>
#define MAX_WORD_SIZE 32
#define WORD_NR_MANUAL 50


using namespace std;


int main( int argc, char * argv[]){
	setlocale(LC_ALL, "");

	bool hash_type;
	bool manual=true;
H_TYPE tableSize;
	if(argc<3||argc>=5){wcout<<"Usage ./htable -htype=(0,1) -size=(0,1,2) (-test)\n";return -1;}
	if(strcmp(argv[1],"-htype=0")==0)hash_type=false;
	else if(strcmp(argv[1],"-htype=1")==0)hash_type=true;
	else {wcout<<"Wrong Parameter -htype given\n"<<"Usage ./htable -htype=(0,1) -size=(0,1,2) (-test)\n";return -1;}

	if(strcmp(argv[2],"-size=0")==0)tableSize=PRIME_0;
	else if(strcmp(argv[2],"-size=1")==0)tableSize=PRIME_1;	
	else if(strcmp(argv[2],"-size=2")==0)tableSize=PRIME_2;	
	else {wcout<<"Wrong Parameter -size given\n"<<"Usage ./htable -htype=(0,1) -size=(0,1,2) (-test)\n";return -1;}

	if(argc==4&&(strcmp(argv[3],"-test")==0))manual=false;
	

	mHashTable A (tableSize,hash_type);

if(!manual){
	wchar_t  a[MAX_WORD_SIZE];
	ofstream resultFile("results.rs");
	
	std::chrono::steady_clock::time_point start, end;
    std::chrono::duration<double> elapsed_seconds;
    
    long int i=0;
    int dpth;
	int repeat_number = 10000;
	double time_count;
	double avg_dpth=0;
	double tot_time=0;
	wclog<<"--Testing in progress, current #           ";
		vector<pair <double, double>> v;
	while(	wcin>>a){
		time_count=0;
		
			start = std::chrono::steady_clock::now();
		for(int cnt =0; cnt<repeat_number;cnt++){
			A.insert(a);
		}	
		end = std::chrono::steady_clock::now();
		dpth=A.insert(a);
		for(int cnt =0; cnt<repeat_number;cnt++){
			A.remove(a);
		}//repeat_count+1 insertions, repeat_count deletions, aggregate is 1 insertion

		avg_dpth+=dpth;
		elapsed_seconds =end - start;
		time_count+=elapsed_seconds.count();
		time_count /=repeat_number;
		tot_time+=time_count;
		
		resultFile << (i++) <<'\t'<<time_count <<'\t' << wcslen(a)<<'\t'<<dpth<<'\n';
		v.push_back(make_pair(time_count, time_count / (wcslen(a)*(1+dpth))));	// T = c * length_of_string * depth+1 - > c= T/length/(depth+1)
			wclog<<"\b\b\b\b\b\b\b\b"<<setw(8)<<i;
	}//testing for each word; writing average insertion time over repeat_number insertions, length of the word and insertion depth
	wclog<<"\n--Average insertion depth over "<<i<<" insertions: "<<(double)avg_dpth/i;
	wclog<<"\n--Total insertion time : "<<tot_time<<"s. with " <<repeat_number<<" repeats \n";
	resultFile.close();	
	wclog<<"\n--Results written to results.rs file\n";

	

	double c;
	sort(v.begin(),v.end());
	c = v[i/2].second;  //getting the median
	wclog<<"--Median found, calculated c="<<c<<'\n';

	resultFile.open("results2.rs");
	ifstream input2("results.rs");
	
	long int tmp_number=0;
	double tmp_time;
	int tmp_length;
	int tmp_depth;

	while(tmp_number!=i-1){
		input2>>tmp_number;
		input2>>tmp_time;
		input2>>tmp_length;
		input2>>tmp_depth;
		//wcout<<tmp_number<<'\n';
		resultFile<<tmp_number<<'\t'<<tmp_time<<'\t'<<tmp_time / (tmp_length*(1+tmp_depth)) / c <<'\n' ;
	}
	wclog<<"--Final results written to results2.rs file\n";
	input2.close();
	resultFile.close();


#ifdef _WIN32
	system("gnuplot gplot/results_plot.p");
	system("gnuplot gplot/results2_plot.p");
	system("results.png & results2.png");  
#endif

#ifndef _WIN32	
	system("gnuplot gplot/results_plot.p;gnuplot gplot/results2_plot.p; display results.png & display results2.png");
#endif
}
else{

wchar_t  a[MAX_WORD_SIZE];
wchar_t buf[WORD_NR_MANUAL][MAX_WORD_SIZE];
int i=0;
while(i++<WORD_NR_MANUAL&&	wcin>>a ){
	if(wcslen(a)>MAX_WORD_SIZE|| wcslen(a)==0){i--;continue;}
copy(begin(a),end(a),begin(buf[i]));
A.insert(a);
wcout<<"--Inserted "<<a << ":\n";
wcout<<A;
}
wcout<<"Deletion\n";
for(int z=0;z<i;z++){
	A.remove(buf[z]);
wcout<<"--Deleted "<<buf[z] << ":\n";
wcout<<A;

}
}
}
