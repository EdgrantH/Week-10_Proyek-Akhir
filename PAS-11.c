/****************************************************************************\
| Tujuan Program     : Menghitung ketinggian gedung
| Nama Pembuat       : 
|                  1. Edgrant Henderson Suryajaya   (2206025016)
|                  2. Farhan Nuzul Noufendri        (2206024442)
| Tanggal pembuatan  : 27 Mei 2023
| Versi Program      : 0.4
\****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <omp.h>
#include "Utilites.h"

#define PI 3.14159265358979323846

struct node{
    char namaGedung[99];
    double tinggiGedung;
    struct node *next;
};

typedef struct node node_t;

//functinon perhitungan
double degree_to_radian(double derajat);
double power(double nilai, int eksponen);
double mutlak(double num);
double akar(double x);
double factorial(int n);
double maclaurin_sin(double sudut, int keakuratan);
double maclaurin_cos(double sudut, int keakuratan);
double maclaurin_tan(double sudut, int keakuratan);

//function pendataan
node_t *create_new_node (char namaGedung[], double tinggiGedung);
node_t *insert_at_head (node_t **head, node_t *tmp);
void printList(node_t *head);
// void delete_node (node_t **head, int position);
void sort_list(node_t **head);

//function menu
void help();
void menu_penutup();
void menu_hitung(int coloPreference, node_t **head);
void menu_setting(int colorPreference);
void menu_kalkulasi_sin(int colorPreference);

//function lainnya
void write_settings(int input);
int read_setting();

int main(){
    //batas=====================================================
    node_t *head = NULL;
    node_t *tmp;    
    int n, colorPreference = BLUE, endProgram = 0, menuInput;
    char nama_main[50];
    double nilai_main;

    while (!endProgram){
        omp_set_num_threads(omp_get_max_threads());
        colorPreference = read_setting();//membuat warna program sesuai dengan setting

        print_box(colorPreference, "Main Menu", 60, 5);
        printf ("1. Help\n");
        printf ("2. Menghitung tinggi gedung\n");
        printf ("3. Kalkulator sin\n");
        printf ("4. List gedung tersimpan\n");
        printf ("5. Settings\n");
        printf ("6. Keluar Program\n");
        printf ("Pilih menu selanjutnya: "); scanf("%d", &menuInput);


        switch (menuInput){
            
            //help
            case (1):
                help();
                break;
            
            //Menghitung tinggi gedung
            case (2):
                menu_hitung(colorPreference, &head);
                break;
            
            //Kalkulator sin
            case (3):
                menu_kalkulasi_sin(colorPreference);
                break;
            
            //List gedung tersimpan
            case (4):
                printf("\n");
                sort_list(&head);
                printList(head);   
                printf("\n");
                getch();
                break;

            // Settings
            case (5):
                menu_setting(colorPreference);
                break;

            //keluar program
            case (6):
                endProgram = 1;//untuk menghentikan loop
                menu_penutup();
                break;
            
            default:
                display_error();
                break;
        }
    }

    // printf ("\nMasukan jumlah bangunan: ");
    // scanf("%d", &n);

    // for (int i = 0; i < n; i++){
    //     printf ("\nGedung ke-%d:", i+1);
    //     printf("\nMasukan nama bangunan: ");
    //     scanf(" %[^\n]", nama_main);
    //     printf("Masukan nilai bangunan: ");
    //     scanf(" %lf", &nilai_main);
    //     tmp = create_new_node(nama_main, nilai_main);
    //     insert_at_head (&head, tmp);
    // }

    // printf("\n");
    // printList(head);   
    // printf("\n");

    

    // // Print the sorted list
    // printf("Linked list setelah diurutkan:\n");
    // printList(head);    
    //batas==================================================

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



node_t *create_new_node (char namaGedung[], double tinggiGedung){   
    node_t *result = malloc(sizeof(node_t));
    strcpy(result->namaGedung, namaGedung);
    result->tinggiGedung = tinggiGedung;
    result->next = NULL;
    return result;
}

node_t *insert_at_head (node_t **head, node_t *tmp){
    node_t *current = *head; //hoo kalo tidak pakai current, headnya lari ke tail
    //penggunaan **?
    if (*head == NULL){
        *head = tmp;
    }
    else{
        while (current->next != NULL){
            current = current->next;
        }
        current->next = tmp;
    }
}

void printList(node_t *head){
    node_t *tmp = head;
    int i = 1;
    int colorPreference = read_setting();

    print_box(colorPreference, "Data dalam list", 60, 5);

    if (head == NULL){
        printf ("\nTidak ada data dalam yang tersimpan\n");
        return;
    }


    printf ("\nData yang ada di dalam linked list adalah:\n");

    while (tmp != NULL){
        printf("\nGedung tertinggi ke-%d\n", i);
        printf ("Nama:\t%s\n", tmp->namaGedung);
        printf ("Tinggi:\t%.3lf m\n", tmp->tinggiGedung);
        tmp = tmp->next;
        i++;
    }
    printf("\n");
}

// void delete_node (node_t **head, int position){
//     node_t *current = *head;
//     node_t *prev = NULL;
//     int i = 1;

//     if (*head == NULL)
//         return; 

//     if (position == 1){
//         *head = (*head)->next;
//         free(current);
//         return;
//     }

//     while (current != NULL && i < position){
//         prev = current;
//         current = current->next;
//         i++;
//     }

//     if (current != NULL){
//         prev->next = current->next;
//         free(current); 
//     }
// }

void sort_list(node_t **head) {
    node_t *current = *head;
    node_t *index = NULL;
    char tempNama[100];
    double tempTinggi;

    if (*head == NULL)
        return;

    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            if (current->tinggiGedung < index->tinggiGedung) {
                strcpy(tempNama, current->namaGedung);
                tempTinggi = current->tinggiGedung;

                strcpy(current->namaGedung, index->namaGedung);
                current->tinggiGedung = index->tinggiGedung;

                strcpy(index->namaGedung, tempNama);
                index->tinggiGedung = tempTinggi;
            }
            index = index->next;
        }
        current = current->next;
    }
}


void menu_penutup(){
    print_box(GREEN, "Terima kasih udah memakai program kita", 60, 5);
    getch();
    exit(0);
}

void menu_hitung(int colorPreference, node_t **head){
    char namaGedung[127];
    double jarakGedung, sudutElevasi, tinggiGedung;
    int menuInput;

    print_box(colorPreference, "Perhitungan Tinggi Gedung", 60, 3);

    printf("%-42s: ", "Jarak pengamat ke dasar gedung"); scanf(" %lf", &jarakGedung);
    printf("%-42s: ", "Sudut elevasi ke puncak gedung (derajat)"); scanf(" %lf", &sudutElevasi);

    tinggiGedung = hitung_tinggi(sudutElevasi, jarakGedung, 8);

    printdup('-', 60);
    printf ("Tinggi gedung = %.3lf\n", tinggiGedung);
    printdup('-', 60);

    printf ("\nApakah anda ingin save data ini?\n");
    printf ("1. Iya\n");
    printf ("2. Tidak\n");
    scanf ("%d", &menuInput);

    if (menuInput == 2) return;// menghentikan function
    
    print_box(colorPreference, "Savnig Data", 60, 3);
    printf("%-20s: ", "Nama/label gedung"); scanf(" %[^\n]s", namaGedung);
    
    node_t *tmp = create_new_node(namaGedung, tinggiGedung);
    insert_at_head (head, tmp);
}

void menu_setting(int colorPreference){
    int i, input;

    print_box(colorPreference, "Settings", 60, 5);

    printdup('-', 60);
    printf ("Pilih warna: \n");
    printf ("1. biru \n");
    printf ("2. merah \n");
    printf ("3. hijau \n");
    printf ("4. kuning \n");
    printdup('-', 60);
    printf ("Input: ");
    scanf ("%d", &input);

    if (input < 1 || input > 4){
        display_error();
    }

    write_settings(input-1);
}

void menu_kalkulasi_sin(int colorPreference){
    int threadInput;
    double sudut, output;

    print_box(colorPreference, "Kalkulator sin", 60, 3);
    printf ("Jumlahthread: "); scanf("%d", &threadInput);
    printf ("Sudut (derajat): "); scanf("%lf", &sudut);
    
    //set berapa banyak thread
    omp_set_num_threads(threadInput);

    //Menghitung sin dengan parallel programing
    #pragma omp parallel
    {
        #pragma omp single
        {
            printdup('-', 60);
            printf("Number of threads: %d\n", omp_get_num_threads());
        }

        #pragma omp task
        {
            output = maclaurin_sin(sudut, threadInput);
        }

        #pragma omp break
        printf ("\tKalkulasi pada thread ke-%d selesai\n", omp_get_thread_num());
    }

    printdup('-', 60);
    printf("Sin(%.0lf) = %.3lf\n", sudut, output);
    getch();
}

void write_settings(int input){
	FILE *fptr = fopen("settings.txt", "w+");

	if (fptr == NULL){
		display_error();
	}

	fprintf(fptr, "%d", input);

	fclose(fptr);
}

int read_setting(){
    int input;
	FILE *fptr = fopen("settings.txt", "r");

	if (fptr == NULL){
		write_settings(BLUE);
		fptr = fopen("settings.txt", "r");
	}

	fscanf(fptr, "%d", &input);

	fclose(fptr);
	return input;
}

void help(){
    int colorPreference = read_setting();
    print_box(colorPreference, "Help", 60, 5);
    printf ("\nDESKRIPSI PROGRAM\n");
    printf ("Program  ini  adalah  program  yang  ditujukan untuk menyelesaikan tugas\n");
    printf ("akhir  mata  kuliah  Pemrograman   Lanjutan.  Program  ini  dikembangkan \n");
    printf ("untuk memecahkan  masalah aplikatif  dengan  minimal mengimplementasikan\n");
    printf ("fungsi/modular,  user-friendly,  error handling, dynamic data structure, \n");
    printf ("searching/sorting, file handling (read/write data ke file), dan parallel \n");
    printf ("programming.\n\n");
    printf ("NAMA PEMBUAT\n");
    printf ("1. Edgrant Henderson Suryajaya   (2206025016)\n");
    printf ("2. Farhan Nuzul Noufendri        (2206024442)\n");

    getch();
    print_box(colorPreference, "Help", 60, 5);
    printf("Menu 1: Help\n");
    printf("Deskripsi: Menampilkan bantuan dan penjelasan tentang program ini.\n\n");
    printf("Menu 2: Menghitung tinggi gedung\n");
    printf("Deskripsi: Menghitung tinggi sebuah gedung berdasarkan jarak pengamat ke dasar gedung dan sudut elevasi ke puncak gedung.\n\n");
    printf("Menu 3: Kalkulator sin\n");
    printf("Deskripsi: Menghitung nilai sinus dari sebuah sudut menggunakan metode Maclaurin.\n\n");
    printf("Menu 4: List gedung tersimpan\n");
    printf("Deskripsi: Menampilkan daftar gedung-gedung yang telah disimpan beserta tinggi masing-masing gedung.\n\n");
    printf("Menu 5: Settings\n");
    printf("Deskripsi: Mengatur preferensi warna program.\n\n");
    printf("Menu 6: Keluar Program\n");
    printf("Deskripsi: Keluar dari program.\n\n");
    getch();
}

