#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "list.h"

int dump_list (SONG_INFO* first_element, int current_element_id, int chosen_element_id);
SONG_INFO* playlist_menu(SONG_INFO* first_element, int* song_amount);
SONG_INFO* add_new_song_to_list_menu (SONG_INFO* song_list);
int player_interface (SONG_INFO* song);
int playlist_save_menu (SONG_INFO* first_element, char playlist_path[]);
int main_menu();

#endif // MENU_H_INCLUDED
