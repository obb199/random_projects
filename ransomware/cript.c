#include "cript.h"
#include <time.h>

void encrypt(char dir_file[], int key){
    FILE * file;
    file = fopen(dir_file, "rb");

    if (file == NULL) return;
    char encrypt_txt[1000];
    char caractere;
    int i = 0;

    while((caractere = fgetc(file)) != EOF){
        encrypt_txt[i] = caractere + key;
        i++;
    }

    fclose(file);


    file = fopen(dir_file, "wb");

    if (file == NULL) return;

    for(register int j = 0; j < i; j++){
        fputc(encrypt_txt[j], file);
    }

    fclose(file);
}


void decrypt(char dir_file[], int key){
    FILE * file;
    file = fopen(dir_file, "rb");

    if (file == NULL) return;
    char encrypt_txt[1000];
    char caractere;
    int i = 0;

    while((caractere = fgetc(file)) != EOF){
        encrypt_txt[i] = caractere - key;
        i++;
    }

    fclose(file);


    file = fopen(dir_file, "wb");

    if (file == NULL) return;

    for(register int j = 0; j < i; j++){
        fputc(encrypt_txt[j], file);
    }

    fclose(file);

}
