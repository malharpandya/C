//
//  fun_with_pointers2020_1005893008.c
//
//
//  Created by Malhar Pandya on 23/01/20.
//

#include<stdio.h>
#include<stdlib.h>
#define MAX_STR_LEN 1024

int end_index(char *string)
{
    int index=0;
    while(*(string+index)!='\0'){
        index++;}
    return index-1;
}

void strip_extra_spaces(char* string, int end){
    while(*(string+end)==' '){
        *(string+end)='\0';
        end--;}
    int i, x;
    for(i=x=0; *(string+i); i++){
        if(*(string+i)!=' ' || (i > 0 && *(string+i-1)!=' ')){
            *(string+x++) = *(string+i);}}
    *(string+x) = '\0';}

void wordSwapper(char *source, char *destination){
    int end;
    int counter=0;
    end=end_index(source);
    strip_extra_spaces(source, end);
    end=end_index(source);
    for(int i=end; i>=0; i--){
        while(*(source+i)!=' ' && i>=0){
            counter++;
            i--;}
        for(int j=0; j<counter; j++){
            *(destination+j)=*((source+i+1)+j);}
        *(destination+counter)=' ';
        destination=destination+counter+1;
        counter=0;}
    *(destination-1)='\0';}

#ifndef __TESTING

int main(){
    char source[MAX_STR_LEN]="silence .is a looking bird:the turning; edge, of life. e. e. cummings";
    char destination[MAX_STR_LEN]="I am a destination string and I contain lots of junk 1234517265716572@qsajdkuhasdgsahiehwjauhiuiuhdsj!";
    printf("The original string is: \n%s\n",source);
    wordSwapper(&source[0],&destination[0]);
    printf("Destination string after swapping: \n%s\n",destination);}

#endif


