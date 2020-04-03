// CSC A48 - Exercise 10 - Breaking Caesar Cipher+
// Complete where indicated below.
//
// Do not add any additional functions
// and do not leave any print statements
// in your final submission for testing!
//
// Updated by F. Estrada, March 2020.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>		// Yes, you can use functions from the string library!

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

int verify_str(char string[MAX_STR_LEN]){
    int count = 0;
    char verified_chars[1024] = "'\n,.;:{}[]()-?! 1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM\0";
    for (int i=0; i<strlen(verified_chars);i++){
        for (int k=0; k<strlen(string); k++){
            if (verified_chars[i]==string[k]){
                count++;
            }
        }
    }
    return strlen(string)==count;
}

int pick_pacoified(char passes[10][MAX_STR_LEN], count){
    char dictionary[19][MAX_STR_LEN]={
        "chocolate", 
        "on-line",
        "watch",
        "read",
        "recursion", 
        "sort", 
        "search", 
        "memory",
        "allocate",
        "free",
        "A48",
        "lecture",
        "BST",
        "assignment",
        "complexity",
        "sorting",
        "notes",
        "learn"
        "linear"
        "Paco",
        "Estrada",
        "Zucchini",
        "Carrot",
        "Radish",
        "Broccoli",
        "Eggplant",
        "Cilantro",
        "Sweet Potato",
        "Tomatoes",
        "Garlic",
        "Arugula"};
    int scores[count];
    int max_index=0; //Possible case: If multiple decruptions have the same score, pick the first one added the list initially.
    for (int i=0; i<count; i++){

        scores[i]=0;
        for (int k=0; k<19;k++){
            if ((dictionary[k]) <= passes[i] && strstr(passes[i],dictionary[k])){
                scores[i]++;
            }
        }
        if (scores[i]>max_index){//Replace maximum score
            max_index=i;
        }
    }
    return max_index;
}

void caesar_breaker(unsigned char crypto_message[MAX_STR_LEN], unsigned char password[MAX_STR_LEN], unsigned char dictionary[10][MAX_STR_LEN]){
     // This function takes as input 
     // - One line of text encrypted using Caesar Cipher+ 
     // - An array to hold the password that cracks the cipher 
     // - A dictionary to be used for a dictionary-attack (here it only has 10 entries,each is a string) 
     // 
     // The function determines which is the word in the dictionary that cracks the cipher, and returns it 
     // by updating the 'password' string with the correct password. 
     // 
     // TO DO: Complete this function 
     // // Constraints: You can assume the input message contains only valid text characters (letters, numbers, 
     //              and punctuation signs) 
     //              The message is somehow related to A48, it was written by Paco 
     //              That's it, you should think about how to use this information to solve your task. 
     //              there are many ways to approach this problem, some better than others. Think carefully!
    char decrypted_words[10][MAX_STR_LEN];
    char valid_passwords[10][MAX_STR_LEN];
    int count =0;
    char current[MAX_STR_LEN];

    for (int pass=0; pass<10; pass++){ 
        strcpy(current, crypto_message);
        caesar_decipher(current, dictionary[pass]);

        // Verify every character in current decipher
        if (verify_str(current)==1){
            strcpy(decrypted_words[count], current);
            strcpy(valid_passwords[count], dictionary[pass]);
            count++;
        }
    }

    if (count ==1)
        strcpy(password, valid_passwords[0]);
    else if (count >1){
        int index = pick_pacoified(decrypted_words, count);
        strcpy(password, valid_passwords[index]);
    }
    // Else case: count == 0 -> unchanged password.
}


#ifndef __testing

int main()
{

    unsigned char a_passage[5][MAX_STR_LEN]={"Hello All A48 people! this is a reminder that the on-line lecture\n",
                                    "will be on recursion, please make sure you've read the notes,\n",
                                    "before you watch the lecture!\n",
                                    "Also, don't forget to complete your BST assignment. We hope you've\n",
                                    "learned lots about complexity and sorting!\n"};

    unsigned char dictionary[10][MAX_STR_LEN]={
                      "Zucchini",
				      "Carrot",
                      "Radish",
				      "Broccoli",
				      "Eggplant",
				      "Cilantro",
				      "Sweet Potato",
				      "Tomatoes",
				      "Garlic",
				      "Arugula"};

    unsigned char password[MAX_STR_LEN];

    printf("\n**** Original input text lines:\n\n");
    for (int i=0; i<5; i++)
        printf("%s",a_passage[i]);

    // Encode the input test lines
    caesar_cipher(a_passage[0],dictionary[0]);
    caesar_cipher(a_passage[1],dictionary[3]);
    caesar_cipher(a_passage[2],dictionary[5]);
    caesar_cipher(a_passage[3],dictionary[8]);
    caesar_cipher(a_passage[4],dictionary[9]);

    // VERY IMPORTANTLY
    // It should be clear to you, we will test your code with a DIFFERENT message,
    // encoded using DIFFERENT entries in the dictionary, and also a DIFFERENT
    // dictionary! so be sure to test very well!
    
    printf("\n**** Encrypted text lines:\n\n");
    for (int i=0; i<5; i++)
        printf("%s",a_passage[i]);

    // Crack the passwords for each text line, and use them to decrypt the text
    printf("\n\n***** Decoding message! *****\n\n");
    for (int i=0; i<5; i++)
    {
        memset(&password[0],0,MAX_STR_LEN*sizeof(unsigned char));   // Clear out password
        caesar_breaker(a_passage[i],password,dictionary);           // Try to get the password for this message
	caesar_decipher(a_passage[i],password);                     // Use the password to decrypt
	// You should check here that your code retrieved the correct password!
	printf("Password=%s, decoded message=%s",password,a_passage[i]);
    }

    return 0;
}

#endif
