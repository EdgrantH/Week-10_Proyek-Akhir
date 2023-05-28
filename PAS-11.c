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

struct node{
    char namaGedung[99];
    double tinggiGedung;
    struct node *next;
};

typedef struct node node_t;


double degree_to_radian(double sudut);
double power(double nilai, int eksponen);
double factorial(int n);
double maclaurin_sin(double sudut, int keakuratan);

node_t *create_new_node (char namaGedung[], double tinggiGedung);
node_t *insert_at_head (node_t **head, node_t *tmp);
void printList(node_t *head);
void delete_node (node_t **head, int position);
void sort_list(node_t **head);

int main(){
    printf("%lf", maclaurin_sin(degree_to_radian(90), 10));
//batas=====================================================
    node_t *head = NULL;
    node_t *tmp;    
    int n;
    char nama_main[50];
    double nilai_main;

    printf ("\nMasukan jumlah bangunan: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++){
        printf ("\nMakanan ke-%d:", i+1);
        printf("\nMasukan nama bangunan: ");
        scanf(" %[^\n]", nama_main);
        printf("Masukan nilai bangunan: ");
        scanf(" %lf", &nilai_main);
        tmp = create_new_node(nama_main, nilai_main);
        insert_at_head (&head, tmp);
    }

    
    printf("\n");
    printList(head);   
    printf("\n");

    sort_list(&head);
    
    // Print the sorted list
    printf("Linked list setelah diurutkan:\n");
    printList(head);    
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

    printf ("\nData yang ada di dalam linked list adalah:\n");

    while (tmp != NULL){
        printf("\nGedung ke-%d\n", i);
        printf ("%s\n", tmp->namaGedung);
        printf ("%lf\n", tmp->tinggiGedung);
        tmp = tmp->next;
        i++;
    }
    printf("\n");
}

void delete_node (node_t **head, int position){
    node_t *current = *head;
    node_t *prev = NULL;
    int i = 1;

    if (*head == NULL)
        return; 

    if (position == 1){
        *head = (*head)->next;
        free(current);
        return;
    }

    while (current != NULL && i < position){
        prev = current;
        current = current->next;
        i++;
    }

    if (current != NULL){
        prev->next = current->next;
        free(current); 
    }
}

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
            if (current->tinggiGedung > index->tinggiGedung) {
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

// void insert_list(){
//     //kopas praktikum aja
// }

// void remove_list_element(){
//     //kopas praktikum aja
// }

// void print_list(){
//     //kopas praktikum aja
// }

// void sort_list(){
//     //ini gw gak tau gimana, tanya chatgpt
// }

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
