#include "playlist_validation.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

int validate_playlist (char* playlist_path) {
    FILE *playlist_file;
    char buff[200];
    int songs_counter=0;

    playlist_file=fopen(playlist_path,"r");

    if (playlist_file==NULL)
        return 0;

    while (!EOF) {
        fgets(buff, 200, playlist_file);
        songs_counter++;
    }
    fclose(playlist_file);
    return songs_counter;
}
