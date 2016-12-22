#ifndef EDIT_PLAYLIST_INTERFACE_H_INCLUDED
#define EDIT_PLAYLIST_INTERFACE_H_INCLUDED
#include "load_music_in_ram.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int dump_list (SONG_INFO* first_element, int current_element_id, int chosen_element_id);
int playlist_menu(SONG_INFO* first_element, int song_amount);
SONG_INFO* add_new_song_to_list(SONG_INFO* song_list);

#endif // EDIT_PLAYLIST_INTERFACE_H_INCLUDED
