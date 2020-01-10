#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h> 
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>    

#define MAX_WORD_SIZE 32
#define NUMBER 100
#define FILL 2                   
//fill = 2 - > 50% fill = 3 -> 33% etc.
using namespace std;

int main( int argc, char * argv[]){
	setlocale(LC_ALL, "");
	if(argc!=4){wcout<<"Usage ./generator file.txt -seq=(0,1) WORD_COUNT\n";return -1;}
	FILE * mfile;
	mfile=fopen(argv[1],"r");
	bool sequential;
	if(strcmp(argv[2],"-seq=0")==0)sequential=false;
	else if(strcmp(argv[2],"-seq=1")==0)sequential=true;
	else {wcout<<"Incorrect seq parameter given\n";return -1;}
	long int word_count = atol(argv[3]);
	long int given_word_count=word_count;
if(word_count<=0){wcout<<"Negative word count given"; return -1;}
	if(!sequential)srand(time(NULL));

	
	wchar_t  write[MAX_WORD_SIZE]={};
	wint_t read;
	int i=0;

	while(word_count>0){
		 	
		    read=fgetwc(mfile);
		 	if(read==WEOF) {
		 		write[i]=L'\0';
		 		 if(i>=1){wcout<<write<<L'\n';
		 		
		 		 word_count--;}
		 		 if(word_count==given_word_count){wcout<<"Given text file does not contain proper words\n"; return -1;}
		 		 fseek(mfile, 0, SEEK_SET);             //if reached the end of the file but not enough words generated - start from the top again
		 		 i=0;
		 		 continue;
		 	}
			else if(read ==' ' || read =='\n'){
				if(i>=MAX_WORD_SIZE) i=MAX_WORD_SIZE-1;
				write[i]=L'\0'; 
				if(i!=0&&sequential){
					wcout<<write<<L'\n';
			
					word_count--;
				} 
				else if(i!=0&&!sequential&&
					    rand()%NUMBER<=NUMBER/FILL){
			
						wcout<<write<<L'\n';
	
						word_count--;
				}

				i=0; 
				continue;
			}
			if(i >=  MAX_WORD_SIZE)continue;
		 	if( (read) >= 'a' && (read) <= 'z' || 
		 		read == 261 || read == 263 || read == 281 || read == 322 || //polish small letter codes
		 		read == 324 || read == 243 || read == 347 || read == 378 ||
		 		read == 380)  
		 		{
		 		write[i++]=read;                     //if the symbol is a small letter, we keep it
	
		 	}
		 	else if( (read) >= 'A' && (read) <='Z')
		 	{
		
		 			write[i++]= towlower(read);            
		 	}
		 	else if( read == 260 || read == 262 || read == 280 || read == 321 ||  //polish Capital letter codes
		 		read == 323 || read == 242 || read == 346 || read == 377 ||
		 		read == 379){
				write[i++]=(wint_t)(read+1);            //if the symbol is a capital letter, we make it small   

			}



		 }
				

fclose(mfile);
	

}
