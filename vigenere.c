#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// define max length of plaintext input
#define TXT_LEN 40


// ignore spaces, preserve case, case in key makes no difference


int main(int argc, char * argv[])
{
    // return usage info if too many or too few args
    if (argc != 2) 
    {
        printf("Usage: ./vigenere keyword\n"); 
        return 1;
    }
    
    // count number of non-alphabetic chars in arg and return usage info if more than 0
    char * in_key = argv[1];
    int arg_len = strlen(in_key);
    int count = 0;
    for (int i = 0; i < arg_len; i++) 
    {
        count+= isdigit(in_key[i]);
    }   
    if (count != 0) 
    {
        printf("Usage: ./vigenere keyword\n"); 
        return 1;
    }
    
    // convert key to lowercase. Irrelevant upper or lower just need to choose one
    for (int i = 0; i < arg_len; i++)
    {
        in_key[i] = tolower(in_key[i]);
    }
        
    
    // assign numeric values of key to array, using 97 as ASCII val of 'a'
    int * num_key = malloc(sizeof(int)*arg_len);
    for (int i = 0; i < arg_len; i++)
    {
        num_key[i] = (int)in_key[i] - 97;
    }
    
    // ask for user input with fgets
    printf("plaintext:  ");
    char * buff = malloc(sizeof(char)*TXT_LEN);
    
    // wrap in IF to catch EOF or other errors
    if(!(fgets(buff,TXT_LEN,stdin))) return 2;
    
    // append with null char stripping newline
    buff[strlen(buff) - 1] = '\0';
    
    //apply key shifts to input 
    
    int buff_len = strlen(buff);
    // separate index for the shift value
    int offset_ind = 0;
    for (int i = 0; i < buff_len; i++)
    {
        // if char in user entry is alphabetic then shift else ignore and move to next
        if isalpha(buff[i])
        {
            // loop round the shift array using the modulus of the index with the shift length
            offset_ind = (offset_ind + 1) % arg_len;
            
            //  need to add in bounds to this as can make Z or z go out of bounds
            buff[i] = (int)buff[i] + num_key[offset_ind];
        } 
    }
    
    //print output and free memory
    printf("ciphertext:  ");
    puts(buff);
    free(buff);
    free(num_key);
}
