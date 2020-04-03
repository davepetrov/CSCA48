// CSC A48 - Exercise 9 - Caesar Cipher v2.0
// Complete where indicated below.
//
// Do not add any additional functions
// and do not leave any print statements
// in your final submission for testing!
//
// F. Estrada, Updated March 2020.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STR_LEN 2048

void caesar_cipher(unsigned char plaintext[MAX_STR_LEN], unsigned char password[MAX_STR_LEN]){
    int k =0;
    char new_password[strlen((char*)plaintext)];
    for (int i=0; i<strlen((char*)plaintext); i++){
        if (k>=strlen((char*)password)){
            k=0;
        }
        new_password[i] = password[k];
        k++;
        //Cipher Offsetting process
        plaintext[i] = (char)((int)plaintext[i] + (int)new_password[i]);
    }
}

void caesar_decipher(unsigned char cryptotext[MAX_STR_LEN], unsigned char password[MAX_STR_LEN]){
    int k =0;
    char new_password[strlen((char*)cryptotext)];
    for (int i=0; i<strlen((char*)cryptotext); i++){
        if (k>=strlen((char*)password)){
            k=0;
        }
        new_password[i] = password[k];
        k++;
        //De-Cipher Offsetting process
        cryptotext[i] = (char)((int)cryptotext[i] - (int)new_password[i]);
    }     
}

#ifndef __testing

int main()
{
    
    char a_passage[5][MAX_STR_LEN]={"When did the world begin and how? \n   I asked a lamb, a goat, a cow:\n",
                                    "What’s it all about and why? \n    I asked a hog as he went by:\n",
                                    "Where will the whole thing end, and when? \n   I asked a duck, a goose and a hen:\n",
                                    "And I copied all the answers too, \n   A quack, a honk, an oink, a moo.\n",
                                    " --- Robert Clairmont\n"};

    printf("**** Original input text lines:\n\n");
    for (int i=0; i<5; i++)
        printf("%s",a_passage[i]);

    // Encode the input test lines
    caesar_cipher(&a_passage[0][0],"password");
    caesar_cipher(&a_passage[1][0],"password");
    caesar_cipher(&a_passage[2][0],"password");
    caesar_cipher(&a_passage[3][0],"password");
    caesar_cipher(&a_passage[4][0],"password");

    printf("\n**** Encrypted text lines:\n\n");
    for (int i=0; i<5; i++)
        printf("%s",a_passage[i]);
    
    // Decode the encrypted strings
    caesar_decipher(&a_passage[0][0],"password");
    caesar_decipher(&a_passage[1][0],"password");
    caesar_decipher(&a_passage[2][0],"password");
    caesar_decipher(&a_passage[3][0],"password");
    caesar_decipher(&a_passage[4][0],"password");

    printf("\n**** Decoded text lines (should be identical to original input!):\n\n");
    for (int i=0; i<5; i++)
        printf("%s",a_passage[i]);
    
    return 0;
}

#endif
