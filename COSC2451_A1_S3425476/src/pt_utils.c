#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pt_utils.h"

int pt_rand(int nbits) {
    int mask;
    if (0 < nbits && nbits < sizeof(int)*8) {
        // the least significant nbits bits will be 1, others will be 0
        mask = ~(~((unsigned int) 0) << nbits); 
    }
    else {
        // the mask will be all ones
        mask = ~((unsigned int) 0);
    }
    // get the next random number and keep only nbits bits
    return rand() & mask;
}

int * gen_rand_int_array(int length, int nbits) {

    int * a = malloc(sizeof(int)*length);
    for (int i = 0; i < length; i++) {
        a[i] = pt_rand(nbits);
    }
    return a;
}

void copy_int_array(int src[], int dst[], int length) {

    for (int i = 0; i < length; i++) {
        dst[i] = src[i];
    }
}

int * clone_int_array(int a[], int length) {

    int * clone = malloc(sizeof(int)*length);
    copy_int_array(a, clone, length);
    
    return clone;
}

void print_int_array(int a[], int length) {

    for (int i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int getIntLength(int x){
    if(x == 0){
        return 1;
    } else {
        return (int)log10(x)+1;
    }
}