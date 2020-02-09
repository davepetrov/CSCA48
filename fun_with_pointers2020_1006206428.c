#include<stdio.h>
#include<stdlib.h>
#define MAX_STR_LEN 1024

int get_size(char *source){
    int size = 0;
    while (*(source+size)!= '\0') size+=1;
    return size-1;
}
void remove_edgeSpaces(char *source){
    int size=get_size(source);
    //front
    int k, j, i;
    for(k=0; *(source+k)==' '; k++);
 
	for(j=0; *(source+k); k++){
		*(source + j++) = *(source+k);
	}
	*(source+j) = '\0';

    //back
    for (i=size; i>0; i--){
        if (*(source+i)==' ' && *(source+i-1)!=' ') {
            *(source+i+1)='\0';
            break;
        }
        
        else if (*(source+i)==' ' && *(source+i-1)==' ') {
            *(source+i) = '\0';
        }
        else{
            *(source+i+1)=' ';
            *(source+i+2)='\0';
            break;
        }
    }

}
void wordSwapper(char *source, char *destination){
    int end_index = 0;
    int word_count = 0;
    remove_edgeSpaces(source);
    int size = get_size(source);
    int d_size = get_size(destination);

    while (d_size < size){
        *(destination+d_size+1) = 'X';
        *(destination+d_size+2) = '\0';
        d_size = get_size(destination);
    }
    
    for (int i = 0; i <= size; i++){
        if (*(source+i) != ' '){
            end_index += 1;
        }
    }
    for (int i=0; i<size; i++){
        if( (*(source+i) != ' ') && ((*(source+i+1) == ' ') || (*(source+i+1) == '\0') ))
        word_count++;
    }

    *(destination+end_index+word_count) = '\0';
    int dest_size = get_size(destination)-1;
    int letter_count = 0;
    int start_index = 0;

    for (int i=0; i<=size; i++){
        if (*(source+i) != ' ')letter_count++;
        if ((*(source+i-1) != ' ') && ((*(source+i) == ' ') || (*(source+i) == '\0') )){
            start_index = i-letter_count;
            for (int k=0; k < letter_count; k++){
                *(destination+dest_size-(letter_count-k)+1) =* (source +start_index+k);
            }
            *(destination + dest_size - (letter_count)) = ' ';
            dest_size -= letter_count+1;
            letter_count = 0;
        }
        
    }
    *(destination+end_index+word_count-1)='\0';
    
}

#ifndef __TESTING
int main()
{
    char source[MAX_STR_LEN]="    abc d e fg hij  k  ";
    char destination[MAX_STR_LEN]="I am a destination string and I contain lots of junk 1234517265716572@qsajdkuhasdgsahiehwjauhiuiuhdsj!";

    printf("The original string is: \n%s\n",source);

    // Call word swapper with the address of the first character in 'source' and the first character in 'destination'
    wordSwapper(&source[0],&destination[0]);
    // You could also call wordSwapper like this: wordSwapper(source,destination) since, as we will have seen in
    // lecture this week, the array's name can be used to pass into a function the address of the first entry
    // in the array.
    
    printf("Destination string after swapping: \n%s\n",destination);    
}
#endif
