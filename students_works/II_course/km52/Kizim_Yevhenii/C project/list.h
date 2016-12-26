#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct song_info {
    char song_path[50];
    struct song_info* song_next;
    char song_name[30];
    char song_artist[30];
    char song_album[30];
    char song_year[4];
} SONG_INFO;

SONG_INFO* add_element();
int add_song_info(SONG_INFO* song);
SONG_INFO* get_all_music();
SONG_INFO* get_music_from_playlist(char playlist_path[]);
SONG_INFO* get_element_by_id (SONG_INFO* first_element, int id);
SONG_INFO* swap_song(SONG_INFO* first_element, int song_i, int song_j);
SONG_INFO* delete_element_by_id (SONG_INFO* first_element, int id);
int free_memory(SONG_INFO* music_list);

#endif // LIST_H_INCLUDED
