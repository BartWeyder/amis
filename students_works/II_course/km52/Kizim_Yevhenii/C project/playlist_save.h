#ifndef PLAYLIST_SAVE_H_INCLUDED
#define PLAYLIST_SAVE_H_INCLUDED

#include "load_music_in_ram.h"

int playlist_save (SONG_INFO* first_element, char playlist_path[]);
int playlist_save_menu (SONG_INFO* first_element, char playlist_path[]);

#endif // PLAYLIST_SAVE_H_INCLUDED
