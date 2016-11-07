#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "input.h"

int input_playlist(char* playlist_path) {
    FILE *playlist_file;

    playlist_file=fopen(playlist_path,"r");

    if (playlist_file==NULL) {
        printf("No file detected with this name.");
        return ;
    }

}
