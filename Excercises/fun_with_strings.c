//
//  fun_with_strings.c
//
//
//  Created by Malhar Pandya on 14/01/20.
//

#define MAX_STR_LEN 1024
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

void pidgin(char input[MAX_STR_LEN])
{
    int i;
    for (i=0; i<MAX_STR_LEN; i+=2)
    {
        if (input[i] == '\0' || input[i+1] == '\0') break;
        char temp;
        temp = input[i];
        input[i] = input[i+1];
        input[i+1] = temp;
    }
}

int is_vowel(char ch)
{
    char c = toupper(ch);
    if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') return 1;
    return 0;
}

void vowel_caser(char input[MAX_STR_LEN])
{
    int i;
    for (i=0; i<MAX_STR_LEN; i++)
    {
        if (input[i] == '\0') break;
        int vowel = is_vowel(input[i]);
        if (vowel == 1)
        {
            if (isupper(input[i])) input[i] = tolower(input[i]);
            else input[i] = toupper(input[i]);
        }
    }
}

int main()
{
    char input[MAX_STR_LEN] = "And Once There Was An Active Volcano On The Island";
    printf("%s\n", input);
    pidgin(input);
    printf("%s\n", input);
    vowel_caser(input);
    printf("%s\n", input);
    return 0;
}
