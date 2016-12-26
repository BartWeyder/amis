#ifndef PLAYLIST_H_INCLUDED
#define PLAYLIST_H_INCLUDED

#include "list.h"

typedef struct playlist_info {
    char path[200];
    int songs_counter;
} P_INFO;

P_INFO* input_playlist();
int validate_playlist (char playlist_path[200]);
int playlist_save (SONG_INFO* first_element, char playlist_path[]);

#endif // PLAYLIST_H_INCLUDED
