#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define MAX_STR_LEN 1024

int getlen(char input[MAX_STR_LEN]){
    int i = 0;
    while (input[i]!='\0')  i++;
    return i;
}
void pidgin(char input[MAX_STR_LEN]){
    int len = getlen(input);
    int mod = len % 2;
    for (int i =0; i<len-mod; i+=2){
        char temp = input[i+1];
        input[i+1] = input[i] ;
        input[i] = temp;
    }
}

void vowel_caser(char input[MAX_STR_LEN]){
    char vowels[5] = "aeiou";
    int len = getlen(input);

    for (int i = 0; i < len; i++){
        for (int k = 0; k < 5; k++){
            if (input[i] == tolower(vowels[k])){
                input[i] = toupper(vowels[k]);
            }
            else if (input[i] == toupper(vowels[k])){
                input[i] = tolower(vowels[k]);
            }
        }
    }
}

int main(){
    char string[MAX_STR_LEN] = "A strIng is jUst a bunch Of chArs sittIng togEthEr in A row!\0";
    printf("%s\n", string); //original

    pidgin(string);
    printf("%s\n", string); // after pidgin

    vowel_caser(string);
    printf("%s\n", string); // after vowel caser

    return 0;
}