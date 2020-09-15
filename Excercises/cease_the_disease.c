//////////////////////////////////////////////////////////////////////////////
// CSC A48 - Winter 2020 - Exercise 5.
//
// Please have a look at the Quercus description of the problem, *before* you
// attempt to implement anything here!
//
// Starter code: (c) 2020 William Song & Joe Armitage.
//////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TISSUE_SIZE (10)

typedef char Tissue[TISSUE_SIZE][TISSUE_SIZE];

bool canLeoEat(Tissue tissue_sample, int x, int y){
    int i, j;
    for(i=-2; i<=2; i+=2){
        for(j=-2; j<=2; j+=2){
            if(0<=(x+i) && (x+i)<TISSUE_SIZE && 0<=(y+j) && (y+j)<TISSUE_SIZE){
                if(tissue_sample[x+i][y+j]=='L'){
                    return true;}}}}
    return false;}

bool canWillEat(Tissue tissue_sample, int x, int y){
    int i, j;
    for(i=-3; i<=3; i++){
        if(0<=(x+i) && (x+i)<TISSUE_SIZE){
            if(tissue_sample[x+i][y]=='W'){
                return true;}
            if(abs(i)==3){
                for(j=-1; j<=1; j+=2){
                    if(tissue_sample[x+i][y+j]=='W'){
                        return true;}}}}}
    for(j=-3; j<=3; j++){
        if(0<=(y+j) && (y+j)<TISSUE_SIZE){
            if(tissue_sample[x][y+j]=='W'){
                return true;}
            if(abs(j)==3){
                for(i=-1; i<=1; i+=2){
                    if(tissue_sample[x+i][y+j]=='W'){
                        return true;}}}}}
    return false;}

int percentKilled(Tissue tissue_sample){
    float total=0;
    float kills=0;
    int x, y;
    for(x=0; x<TISSUE_SIZE; x++){
        for(y=0; y<TISSUE_SIZE; y++){
            if(tissue_sample[x][y]=='I'){
                total++;
                if(canLeoEat(tissue_sample, x, y) || canWillEat(tissue_sample, x, y)){
                    kills++;}}}}
    if(total==0){
        return 0;}
    return round(100*kills/total);}

void printTissueSample(Tissue tissue_sample)
{
    printf("   A B C D E F G H I J\n");
    for (int x = 0; x < TISSUE_SIZE; x++)
    {
        printf("%2d ", x + 1);
        for (int y = 0; y < TISSUE_SIZE; y++) printf("%c ", tissue_sample[x][y]);
        printf("\n");
    }
}

#ifndef __TESTING
int main()
{
    printf("====Deep's Sample====\n");
    Tissue deep_sample = {{'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', '_', 'L', '_', 'I', '_', '_', '_'},
                          {'_', '_', '_', '_', 'I', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', '_', 'I', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', 'W', '_', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'}};
    printTissueSample(deep_sample);
    printf("Calculated: Killed %03d%% of bacteria\n", percentKilled(deep_sample));
    printf("  Expected: Killed 067%% of bacteria\n");

    printf("====Donnie's Sample====\n");
    char donnie_sample[TISSUE_SIZE][TISSUE_SIZE] = {
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', '_', '_', '_', '_', '_', 'I', '_'},
        {'_', '_', '_', '_', '_', 'I', '_', '_', 'I', '_'},
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', 'I'},
        {'_', '_', '_', 'I', '_', '_', '_', '_', 'I', 'W'},
        {'_', '_', '_', 'I', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', 'L', '_', '_', '_', '_', 'L', '_'},
        {'_', '_', '_', '_', '_', '_', '_', 'I', 'I', 'I'},
        {'_', '_', '_', '_', '_', '_', '_', '_', 'I', '_'}};
    printTissueSample(donnie_sample);
    printf("Calculated: Killed %03d%% of bacteria\n", percentKilled(donnie_sample));
    printf("  Expected: Killed 064%% of bacteria\n");
    
    printf("====Malhar's Sample====\n");
    Tissue malhar_sample = {
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', 'L', '_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', '_', 'W', '_', 'L', '_', '_', '_'},
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', '_', '_', 'L', '_', '_', '_', 'W'},
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', '_', '_', '_', '_', '_', 'L', '_'},
        {'_', '_', '_', '_', '_', '_', 'W', '_', '_', '_'},
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'}};
    printTissueSample(malhar_sample);
    printf("Calculated: Killed %03d%% of bacteria\n", percentKilled(malhar_sample));
    printf("  Expected: Killed 000%% of bacteria\n");
}
#endif

