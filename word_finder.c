#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef int bool;
#define true 1
#define false 0

void checkArguments();

void checkFileSize();

int generateOutput();

void cleanOutput();

void invalidInput();

char * prefix = NULL;
char * filePath = NULL;
int interupt = 0;
int lengthOfFile = 512;
int counter = 0;

int main(int argc, char * argv[]){

    if(argc != 4){
        invalidInput();
    }
    checkArguments(argv[1], argv[2], argv[3], argc);

    checkFileSize(argv[2]);

    char buf[lengthOfFile];
    int lPrefix = strlen(argv[1]);
    char output[lengthOfFile];
    int oPointer = 0;
    cleanOutput(output);

    int pBuf = -1;
    char * pointer = buf;
    FILE * f = fopen(argv[2], "r");
    bool flag = false;
    bool generateFlag = false;
    while (1)
    {
        fread(pointer, sizeof(char), 1, f);
        pBuf++;
        if(feof(f)){
            *pointer = '\0';
            printf("%s\n", buf);
            return 0;
        }
        if(*pointer == argv[1][oPointer] && (flag || buf[pBuf-1] == 32 || pBuf == 0)){
            flag = true;
            output[oPointer] = *pointer;
            if(oPointer == lPrefix - 1){
                while(*pointer != 32 && pBuf != lengthOfFile - 1){
                    pointer++;
                    oPointer++;
                    fread(pointer, sizeof(char), 1, f);
                    pBuf++;
                    if(feof(f)){
                        *pointer = '\0';
                        generateOutput(output, *argv[3]);
                        printf("%s\n", buf);
                        return 0;
                    }
                    output[oPointer] = *pointer;
                }
                int n = generateOutput(output, *argv[3]);
                printf("%s\n", buf);
                generateFlag = true;
                flag = false;
                if (!n) return 0;
                oPointer = 0;
                cleanOutput(output);
            }
            if(!generateFlag){
                oPointer++;
                generateFlag = false;
            }
        }else{
            oPointer = 0;
            flag = false;
            generateFlag = false;
        } 
        pointer++;
    }
    *pointer = '\0';
    printf("%s\n", buf);
    return 0;
}

void invalidInput(){
    fprintf(stderr, "First argument: Prefix, Second argument: File Path, Third argument: Interupt option");
    exit(0);
}

void checkArguments(char * pref, char * path, int inter, int n){
    if(pref == NULL || path == NULL ){
        fprintf(stderr, "NULL argument error!\n");
        fprintf(stderr, "First argument: Prefix, Second argument: File Path, Third argument: Interupt option");
        exit(0);
    }else{
        prefix = pref;
        filePath = path;
    }
    if(inter == 1){
        interupt = 1;
    }
    if(n > 4){
        fprintf(stderr, "NULL argument error!\n");
        fprintf(stderr, "First argument: Prefix, Second argument: File Path, Third argument: Interupt option");
        exit(0);
    }
}

void checkFileSize(char * path)
{
	struct stat st;
	size_t size;

	stat(path, &st);
	if (st.st_size > lengthOfFile)
	{
		fprintf(stderr, "Try a smaller file.\n");
		exit(1);
	}
}


int generateOutput(char * o, int opt){
    counter++;
    printf("%d. ", counter);
    int i = 0;
    for(i = 0; i < lengthOfFile; i++){
        if (*(o + i) == '\0')
        {
            break;
        }
        printf("%c", *(o + i));
    }
    int inpCounter = 0;
    printf("\n");
    if(opt==49){
        printf("Do you want to continue? Y/N ");
        char c = 'T';
        scanf(" %c", &c);
        while(c != 89 && c != 'N'){
            inpCounter++;
            if (inpCounter == 4)
            {
                fprintf(stderr, "The program is exited!");
                exit(0);
            }
            printf("Alert %d. Enter a valid response: ", inpCounter);
            scanf(" %c", &c);
            usleep(inpCounter * 10000);
        }
        if(c == 'N') return 0;
        else return 1;
    }else return 0;
}

void cleanOutput(char * o){
    int i = 0;
    for(i = 0; i < lengthOfFile; i++){
        *(o + i) = '\0';
    }
}