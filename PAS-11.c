/****************************************************************************\
| Tujuan Program     : Menghitung ketinggian gedung
| Nama Pembuat       : 
|                  1. Edgrant Henderson Suryajaya   (2206025016)
|                  2. Farhan Nuzul Noufendri        (2206024442)
| Tanggal pembuatan  : 27 Mei 2023
| Versi Program      : 0.0.1E
\****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <omp.h>
#include "Utilites.h"

#define PI 3.1415926432 

//typdef node {}
//nanti tambahin node linked list, gw saraninnya doubly linked list, tapi bebas. Datanya ada nama gedung dan tinggi gedung


double degree_to_radian(double sudut);
double power(double nilai, int eksponen);
double factorial(int n);
double maclaurin_sin(double sudut, int keakuratan);

int main(){
    printf("%lf", maclaurin_sin(degree_to_radian(90), 10));

    return 0;
}

//mengubah sudut dalam bentuk derajat ke radian
double degree_to_radian(double derajat){
    double radian;

    radian = derajat * PI/180;

    return radian;
}

//membuatan manual function pow() dari math.h
double power(double nilai, int eksponen) {
    double output = 1;
    int i;

    for (i = 0; i < eksponen; i++) {
        output *= nilai;
    }

    return output;
}

//menghitung factorial dari n
double factorial(int n) {
    double result = 1;
    int i;

    for (i = 2; i <= n; i++) {
        result *= i;
    }

    return result;
}

//menghitung sin, sudut dalam bentuk radian
double maclaurin_sin(double sudut, int keakuratan) {
    double output = 0;
    int i;

    //pendekatan maclaurin untuk sin
    for (i = 0; i < keakuratan; i++) {
        int eksponen = 2 * i + 1;
        double term = power(-1, i) * power(sudut, eksponen) / factorial(eksponen);
        output += term;
    }

    return output;
}

//menghitung tan sebuah sudut dengan menggunakan sin
float my_tan(float sudut){

}

//menghitung tinggi sebuah gedung dengan sudut elevasi dan jarak dari alas
float hitung_tinggi(float sudut, float jarak){
    
}



void insert_list(){
    //kopas praktikum aja
}

void remove_list_element(){
    //kopas praktikum aja
}

void print_list(){
    //kopas praktikum aja
}

void sort_list(){
    //ini gw gak tau gimana, tanya chatgpt
}

void write_setting(){
    //kopas proyek dulu, beneran sama persis
}

int read_setting(){
    //kopas proyek dulu, beneran sama persis
}