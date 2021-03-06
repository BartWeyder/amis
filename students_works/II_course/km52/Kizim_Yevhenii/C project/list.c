#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "music.h"

SONG_INFO* add_element() {
    SONG_INFO* new_element = malloc(sizeof(SONG_INFO));
    new_element->song_next=NULL;
    return new_element;
}

int add_song_info(SONG_INFO* song) {
    ID3TAG* temp_song_info;
    temp_song_info = output_audiofile_info(song->song_path);
    if (temp_song_info==NULL)
        return 0;
    else {
        strcpy(song->song_artist, temp_song_info->artist);
        strcpy(song->song_name, temp_song_info->name);
        strcpy(song->song_album, temp_song_info->album);
        strcpy(song->song_year, temp_song_info->year);
        free(temp_song_info);
        return 1;
    }
}

SONG_INFO* get_all_music() {
    DIR *music_directory;
    struct dirent *music_file;
    music_directory = opendir ("music\\");
    SONG_INFO* first_element = NULL;
    SONG_INFO* current_element = NULL;

    if (music_directory != NULL){
        //add first element
        first_element = add_element();
        //read file from directory
        music_file = readdir(music_directory);
        music_file = readdir(music_directory);
        music_file = readdir(music_directory);
        //get name path of file
        strcpy(first_element->song_path,"music\\");
        strcat(first_element->song_path, music_file->d_name);
        current_element = first_element;
        //get info about song
        add_song_info(current_element);
        //continue same with next files
        while (music_file = readdir (music_directory)){
            current_element->song_next = add_element();
            current_element = current_element->song_next;
            strcpy(current_element->song_path,"music\\");
            strcat(current_element->song_path, music_file->d_name);
            add_song_info(current_element);
        }
        (void) closedir (music_directory);
        return first_element;
    }
    else
    return NULL;
}

SONG_INFO* get_music_from_playlist(char playlist_path[]) {
    FILE *playlist_file;
    char buff[200];
    SONG_INFO* first_element=NULL;
    SONG_INFO* current_element=NULL;
    char *token = NULL;

    playlist_file = fopen(playlist_path,"r");

    //add first element
    fgets(buff, 200, playlist_file);
    token = strtok(buff, ";");
    first_element = add_element();
    strcpy(first_element->song_path, token);
    if (add_song_info(first_element)==0) {
        free(first_element);
        return NULL;
    }
    current_element = first_element;

    //add next elements
    while (!feof(playlist_file)) {
        fgets(buff, 200, playlist_file);
        token = strtok(buff, ";");
        current_element->song_next = add_element();
        current_element = current_element->song_next;
        strcpy(current_element->song_path, token);
        if (add_song_info(current_element)==0)
            free(current_element);
    }
    return first_element;
}

SONG_INFO* get_element_by_id (SONG_INFO* first_element, int id) {
    SONG_INFO* found_element = first_element;
    for (int counter_element = 0; counter_element<id-1; counter_element++) {
        found_element = found_element->song_next;
    }
    return found_element;
}

SONG_INFO* swap_song(SONG_INFO* first_element, int song_i, int song_j) {
    if (song_i>=song_j)
        return 0;

    SONG_INFO* song_i_prev_element = NULL;
    SONG_INFO* song_i_element = NULL;
    SONG_INFO* song_i_next_element = NULL;
    SONG_INFO* song_j_prev_element = NULL;
    SONG_INFO* song_j_element = NULL;
    SONG_INFO* song_j_next_element = NULL;

    //get our elements
    if (song_i==1) {
        song_i_element = first_element;
        //if we have non-neighbor elements
        if ((song_j-song_i)==1) {
            song_j_element = song_i_element->song_next;
            song_i_element->song_next = song_j_element->song_next;
            song_j_element->song_next = song_i_element;
            first_element = song_j_element;
        }
        else {
            song_j_prev_element = get_element_by_id(first_element, song_j-1);
            song_j_element = song_j_prev_element->song_next;
            song_j_next_element = song_j_element->song_next;
            song_j_element->song_next = song_i_element->song_next;
            song_j_prev_element->song_next = song_i_element;
            song_i_element->song_next = song_j_next_element;
            first_element = song_j_element;
        }
    }
    else {
        song_i_prev_element = get_element_by_id(first_element, song_i-1);
        song_i_element = song_i_prev_element->song_next;
        if ((song_j-song_i)==1) {
            song_j_element = song_i_element->song_next;
            song_i_element->song_next = song_j_element->song_next;
            song_i_prev_element->song_next = song_j_element;
            song_j_element->song_next = song_i_element;
        }
        else {
            song_i_next_element = song_i_element->song_next;
            song_j_prev_element = get_element_by_id(song_i_element, song_j-song_i+1);
            song_j_element = song_j_prev_element->song_next;
            song_j_next_element = song_j_element->song_next;
            song_j_element->song_next = song_i_next_element;
            song_i_element->song_next = song_j_next_element;
            song_i_prev_element->song_next = song_j_element;
            song_j_prev_element->song_next = song_i_element;
        }
    }
    return first_element;
}

SONG_INFO* delete_element_by_id(SONG_INFO* first_element, int id) {
    if (first_element==NULL)
        return NULL;

    SONG_INFO* prev_element = NULL;
    SONG_INFO* current_element = NULL;

    if (id == 1) {
        prev_element = first_element;
        first_element = first_element->song_next;
        free(prev_element);
        return first_element;
    }

    prev_element = get_element_by_id(first_element, id-1);
    current_element = prev_element->song_next;
    prev_element->song_next = current_element->song_next;
    free(current_element);
    return first_element;
}

int free_memory(SONG_INFO* music_list) {
    SONG_INFO* current_element = NULL;

    while (current_element!=NULL) {
        current_element = music_list->song_next;
        free(music_list);
        music_list = current_element;
    }
    return 1;
}
