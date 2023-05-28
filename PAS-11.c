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

#define PI 3.14159265358979323846

//typdef node {}
//nanti tambahin node linked list, gw saraninnya doubly linked list, tapi bebas. Datanya ada nama gedung dan tinggi gedung


double degree_to_radian(double derajat);
double power(double nilai, int eksponen);
double mutlak(double num);
double akar(double x);
double factorial(int n);
double maclaurin_sin(double sudut, int keakuratan);
double maclaurin_cos(double sudut, int keakuratan);
double maclaurin_tan(double sudut, int keakuratan);


int main(){
    double start_time, end_time, elapsed_time;
    int maxThread = omp_get_max_threads();
    omp_set_num_threads(maxThread);

    start_time = omp_get_wtime();
    printf("%lf\n", maclaurin_tan(36.8, maxThread));
    end_time = omp_get_wtime();

    elapsed_time = end_time - start_time;

    printf("Elapsed time: %f seconds\n", elapsed_time);

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

    #pragma omp parallel for reduction(*:output)
    for (i = 0; i < eksponen; i++) {
        output *= nilai;
    }

    return output;
}

double mutlak(double num) {
     return (num < 0) ? -num : num;
}

double akar(double x) {
    if (x <= 0) {
        return 0;
    }

    double guess = x;
    double nextGuess = 0.5 * (guess + x / guess);
    double epsilon = 1e-7; // Desired level of precision
    int stopCalculation = 0; // Flag to indicate stopping the calculation
    int terminateLoop = 0; // Flag to indicate terminating the loop

    #pragma omp parallel shared(stopCalculation, terminateLoop)
    {
        while (!terminateLoop) {
            guess =+ omp_get_thread_num();
            // Check if the stopCalculation flag is set
            #pragma omp critical
            {
                if (stopCalculation) {
                    terminateLoop = 1;
                }
            }

            guess = nextGuess;
            nextGuess = 0.5 * (guess + x / guess);

            // Check if the desired value is reached
            if (mutlak(nextGuess - guess) < epsilon) {
                // Set the stopCalculation flag for all threads
                #pragma omp critical
                {
                    stopCalculation = 1;
                }
            }
        }
    }

    return guess;
}

//menghitung factorial dari n
double factorial(int n) {
    double result = 1;
    int i;

    #pragma omp parallel for reduction(*:result)
    for (i = 2; i <= n; i++) {
        result *= i;
    }

    return result;
}

//menghitung sin, sudut dalam bentuk radian
double maclaurin_sin(double sudut, int keakuratan) {
    double output = 0;
    int i;

    sudut = degree_to_radian(sudut);

    //Menentukan sin dengan aproximasi maclaurin dan menggunakan multithreading dengan reduction variabel
    #pragma omp parallel for reduction(+:output)
    for (i = 0; i < keakuratan; i++) {
        int eksponen = 2 * i + 1;
        double term = power(-1, i) * power(sudut, eksponen) / factorial(eksponen);
        output += term;
    }

    return output;
}

double maclaurin_cos(double sudut, int keakuratan) {
    double output = 0;
    int i;

    sudut = degree_to_radian(sudut);

    //Menentukan cos dengan aproximasi maclaurin
    #pragma omp parallel for
    for (i = 0; i < keakuratan; i++) {
        int eksponen = 2 * i;
        double term = power(-1, i) * power(sudut, eksponen) / factorial(eksponen);

        //barier untuk memastikan tidak ada yang bentrok mengakses variabel
        #pragma omp critical
        {
            output += term;
        }
    }

    return output;
}

//menghitung tan sebuah sudut dengan menggunakan sin
double maclaurin_tan(double sudut, int keakuratan){
    double sinValue = maclaurin_sin(sudut, keakuratan);
    double cosValue = maclaurin_cos(sudut, keakuratan);

    double tanValue = sinValue / cosValue;

    return tanValue;
}

//menghitung tinggi sebuah gedung dengan sudut elevasi dan jarak dari alas
double hitung_tinggi(double sudut, double jarak, int keakuratan){
    double tinggi;

    tinggi = maclaurin_tan(sudut, keakuratan) * jarak;

    return tinggi;
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