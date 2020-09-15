//
//  main.c
//  inner_join
//
//  Created by Malhar Pandya on 29/01/20.
//  Copyright © 2020 Malhar Pandya. All rights reserved.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 128
#define MAX_ROW_COUNT 100
#define DELIMITER ','

bool cmp_name(char row_n[MAX_STRING_LENGTH], char row_f[MAX_STRING_LENGTH]){
    for(int p=0; row_n[p]!=','; p++){
        if(row_n[p]!=row_f[p]){
            return false;}}
    return true;}

void innerJoin(char nationalities_table[MAX_ROW_COUNT][MAX_STRING_LENGTH],
               char foods_table[MAX_ROW_COUNT][MAX_STRING_LENGTH],
               char joined_table[MAX_ROW_COUNT][MAX_STRING_LENGTH * 2]){
    int row_joined=0;
    int i=0;
    while(strcmp(nationalities_table[i], "")!=0){
        int j=0;
        while(strcmp(foods_table[j], "")!=0){
            if (cmp_name(nationalities_table[i], foods_table[j])){
                strcpy(joined_table[row_joined], nationalities_table[i]);
                strcat(joined_table[row_joined], strchr(foods_table[j], DELIMITER));
                row_joined++;}
            j++;}
        i++;}}

#ifndef __TESTING
int main(){
    char example_nationalities_table[MAX_ROW_COUNT][MAX_STRING_LENGTH] ={
        "Paco Estrada,Mexico",
        "Joe Armitage,England",
        "Angela Zavaleta,Peru",
        "Nyah Way,Canada",
        "Anya Tafliovich,Ukraine",
        "Brian Harrington,Canada",
        "",};
    char example_foods_table[MAX_ROW_COUNT][MAX_STRING_LENGTH] ={
        "Brian Harrington,Avocado Salad",
        "Paco Estrada,Chocolate",
        "Joe Armitage,Chocolate",
        "Angela Zavaleta,Green Eggs",
        "Jack Long,Ham",
        "",};
    char joined[MAX_ROW_COUNT][MAX_STRING_LENGTH * 2] = {""};
    innerJoin(example_nationalities_table, example_foods_table, joined);
    for (int idx = 0; 0 != strcmp("", joined[idx]); idx++){
        printf("%s\n", joined[idx]);}}
#endif


