#include <stdio.h>

//sumber https://stackoverflow.com/questions/26423537/how-to-position-the-input-text-cursor-in-c
#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

enum color {BLUE, RED, GREEN, YELLOW};

//mengprint karakter x sebanyak y kali, dalam python ini adalah print("x"*y)
void printdup(char symbol, int panjang){
	int i;
	for(i = 0; i < panjang; i++) printf("%c", symbol); 
	printf("\n");
}

//mengprint karakter x yang mengimpin kosong dengan total panjang y
void printBorder(char symbol, int panjang){
	int i;
    printf("%c", symbol); 
	for(i = 0; i < panjang-2; i++) printf(" "); 
	printf("%c\n", symbol);
}

void box(char alas, char dinding, int lebar, int tinggi){
    int i, j;
    if(tinggi >= 3 || lebar >= 2){
        printdup(alas, lebar);
        for (j = 0; j < tinggi - 2; j++){
            printBorder(dinding, lebar); 
        } 
        printdup(alas, lebar);
    }
}

//print text to align center
void center_print(char *output, int length){
	int strLength = strlen(output);
	int offset = (length - strLength)/2;
	int i;
	for (i = 0; i < offset; i++) {
		printf(" ");
	}
    printf("%s", output);
}
//menghilangkan semua text di console dan mengganti warnanya
void resetScreen(int color){
	clear();
	
	switch (color){
		case (BLUE):
			system("color 90");
			break;
		case (RED):
			system("color 4f");
			break;
		case (GREEN):
			system("color A0");
			break;
		case (YELLOW):
			system("color E0");
			break;
		default:
			system("color 07");
			break;
	}
}


void print_box(int colorPreference, char *string, int length, int height){
    resetScreen(colorPreference);
    box('=', '|', length, height);
    gotoxy(3, (height + 1)/2);
    center_print (string, length);
    gotoxy(1, (height + 1));
}
