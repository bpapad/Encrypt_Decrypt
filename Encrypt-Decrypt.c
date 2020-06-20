#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	int j, i=0;
	char a, rename[100], buffer[10];
// Argument Number Check
	if(argc != 5){
		printf("\nWrong Syntax, try:\n\nprojectED -e/-d filename1.datatype filename2.datatype KEY\n\nOr try typing:\n''filename.datatype'' or''full_filepath''\n");
		return 0;
	}
// Encryption or Decryption Arguement Check
	if( (strcmp(argv[1],"-e") != 0) && (strcmp(argv[1],"-d") != 0) ){
		printf("\nInvalid Command:\n\nprojectED [-e/-d] file1.datatype file2.datatype KEY\n\nEncrypt --> -e\nDecrypt --> -d\n");
		return 0;
	}
// File 1  Opening and Check
	FILE *f1 = fopen(argv[2],"rb");
	if(f1 == NULL){
	   printf("\nFile 1 not found\nTry typing: ''filename.datatype'' or ''full_filepath''\nprojectED -e/-d [filename1.datatype] filename2.datatype KEY\n");
	   return 0;
	}
//File 2 Opening and Choosing to Overwrite it If it Exists	
	FILE *f2 = fopen(argv[3],"rb");
	if(f2 != NULL){
		printf("\nFile %s already exists, OVERWRITE ?\nYES --> Y/y\nNO --> N/n\n",argv[3]);
		do{
		a = getchar();
		}while(a!='Y' && a!='y' && a!='N' && a!='n');	
		if(a == 'N' || a == 'n'){
			printf("\nName new File2 [filename.datatype]:\n");
			scanf("%s",&rename);
			f2 = fopen(rename,"rb");
			while(f2 != NULL){
				printf("\nGiven File exists as well, name new File2 [filename.datatype]:\n");
				scanf("%s",&rename);
				f2 = fopen(rename,"rb");
			}
			f2 = fopen(rename,"wb");
		}
		else{
		    f2 = fopen(argv[3],"wb");
 	    }
	}
	else{
		f2 = fopen(argv[3],"wb");
	}
// Counting the KEY's Number of Characters for Later Use
	for(j=0; argv[4][j]!='\0'; j++);
// Reading File 1 then Encrypting or Decrypting it and finally writing it to File 2 (1 Byte per Loop)
	fseek(f1, 0, SEEK_SET);
	if(strcmp(argv[1],"-e") == 0){
	  while(!feof(f1)){
	  	   fread(buffer, 1, 1, f1);
	       *buffer += argv[4][i%j] - 'b';
	       i++;
	       fwrite(buffer, 1, 1, f2);
	  }
    }  
	else{
		while(!feof(f1)){
			fread(buffer, 1, 1, f1);
	        *buffer -= argv[4][i%j] - 'b';
	        i++;
	        fwrite(buffer, 1, 1, f2);
	    }
	}
    if(strcmp(argv[1],"-e") == 0)
      printf("\nEncryption of File1: [%s] to File2: [%s] with KEY: [%s] successfull!\n",argv[2], (a == 'N' || a == 'n')?rename:argv[3], argv[4]);
    else
      printf("\nDecryption of File1: [%s] to File2: [%s] with KEY: [%s] successfull!\n",argv[2], (a == 'N' || a == 'n')?rename:argv[3], argv[4]);
//Closing Both Files to Exit the Programm Safely  
    fclose(f1);
	fclose(f2);   
    return 0;
}
