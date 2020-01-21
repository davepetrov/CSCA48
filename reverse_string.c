#include <stdlib.h>
#include <stdio.h>
#define MAX_STR_LEN 1024

void reverse(char *input, char *output);

int main(){
    char input[MAX_STR_LEN]="ABCDEF";                  //Original
    char output[MAX_STR_LEN]="Junk";                   //Final
    reverse(&input[0], &output[0]);
    
    printf("Output: %s\n", output);
}

void reverse(char *input, char *output){
    int size = 0;
    while (*(input+size)!= '\0'){
        size+=1;
    }
    for (int k=size; k>=0; k--){
        *(output+size-k) = *(input + k-1);
    }

}