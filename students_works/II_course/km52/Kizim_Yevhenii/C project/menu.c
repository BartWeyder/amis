#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "menu.h"
#include "list.h"
#include "rlutil.h"
#include "playlist.h"
#include "music.h"

//declarating local functions
int get_page_id (int element_id);

int get_page_id (int element_id){
    int page = (int)floor(element_id/10);
    return page;
}

int dump_list (SONG_INFO* first_element, int current_element_id, int chosen_element_id) {
    if (first_element == NULL)
        return 0;

    SONG_INFO* current_element = first_element;
    int page = get_page_id(current_element_id);
    int i;

    printf("Current playlist:\n\n");
    current_element = get_element_by_id(first_element, page*10);
    if ((page == get_page_id(chosen_element_id))&&(chosen_element_id!=0)) {
        if (current_element_id<chosen_element_id) {
            //output elements that are before current
            for (i = 1; i<(current_element_id % 10); i++) {
                printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
                current_element = current_element->song_next;
            }
            //output current element
            setColor(LIGHTGREEN);
            printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
            current_element = current_element->song_next;
            setColor(BLACK);
            //output elements before chosen
            for (i=i+1; i<(chosen_element_id % 10); i++) {
                printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
                current_element = current_element->song_next;
            }
            //output chosen
            setColor(LIGHTRED);
            printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
            current_element = current_element->song_next;
            setColor(BLACK);
            //output rest
            for (i=i+1; i<10; i++) {
                if (current_element == NULL)
                    break;
                printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
                current_element = current_element->song_next;
            }
        }
        if (current_element_id>chosen_element_id) {
            //output elements that are before chosen
            for (i = 1; i<(chosen_element_id % 10); i++) {
                printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
                current_element = current_element->song_next;
            }
            //output chosen
            setColor(LIGHTRED);
            printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
            current_element = current_element->song_next;
            setColor(BLACK);
            //output elements before current
            for (i=i+1; i<(current_element_id % 10); i++) {
                printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
                current_element = current_element->song_next;
            }
            //output current element
            setColor(LIGHTGREEN);
            printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
            current_element = current_element->song_next;
            setColor(BLACK);
            //output rest
            for (i=i+1; i<10; i++) {
                if (current_element == NULL)
                    break;
                printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
                current_element = current_element->song_next;
            }
        }
        if (current_element_id == chosen_element_id) {
            //output elements that are before current
            for (i = 1; i<(current_element_id % 10); i++) {
                printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
                current_element = current_element->song_next;
            }
            //output current element
            setColor(MAGENTA);
            printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
            current_element = current_element->song_next;
            setColor(BLACK);
            //output rest
            for (i=i+1; i<10; i++) {
                if (current_element == NULL)
                    break;
                printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
                current_element = current_element->song_next;
            }
        }
    }
    else {
        //output elements that are before current
        for (i = 1; i<(current_element_id % 10); i++) {
            printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
            current_element = current_element->song_next;
        }
        //output current element
        setColor(LIGHTGREEN);
        printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
        current_element = current_element->song_next;
        setColor(BLACK);
        //output rest
        for (i=i+1; i<10; i++) {
            if (current_element == NULL)
                break;
            printf("%i%i. %s - %s \n", page, i, current_element->song_artist, current_element->song_name);
            current_element = current_element->song_next;
        }
    }
    printf("Use cursors to navigate menu, ENTER to choose song, 'a' to add new song\n");
    printf("and ESC to exit from this menu.\n");
    printf("Remember: there are only 9 songs on the page, go down to explore more.");
    return 1;
}

int playlist_menu(SONG_INFO* first_element, int song_amount) {
    int current = 1;
    int chosen = 0;
    bool swap = false;
    bool finish = false;
    char input_symbol = '\0';
    SONG_INFO* temp_list = NULL;

    if (dump_list(first_element, 1, 0)==0)
        return 0;

    while (finish == false) {
        input_symbol = getch();
        if (input_symbol == -32)
            input_symbol = getch();
        switch (input_symbol) {
        case 13:
            if (current == chosen) {
                swap = false;
                system("cls");
                chosen = 0;
                dump_list(first_element, current, 0);
            }
            else {
                if (chosen == 0) {
                    chosen = current;
                    system("cls");
                    dump_list(first_element, current, chosen);
                    printf("\nPress 's' to swap this song and choose second song.\n");
                    printf("Press 'd' to delete current song.\n");
                }
                else {
                    if (swap == true) {
                        if (chosen < current)
                            first_element = swap_song(first_element, chosen, current);
                        else
                            first_element = swap_song(first_element, current, chosen);
                        swap = false;
                        chosen = 0;
                        system("cls");
                        dump_list(first_element, current, 0);
                        printf("\nSongs swapped successfully.\n");
                    }
                    else {
                        chosen = current;
                        system("cls");
                        dump_list(first_element, current, chosen);
                    }
                }
            }
            break;
        case 27:
            finish = true;
            break;
        case 's':
            if (chosen!=0) {
                swap = true;
                system("cls");
                dump_list(first_element, current, chosen);
                printf("\n Now choose second element to swap.");
            }
            else
                printf("\a");
            break;
        case 'd':
            if (chosen!=0) {
                first_element = delete_element_by_id(first_element, chosen);
                system("cls");
                if (chosen == 1)
                    dump_list(first_element, chosen, 0);
                else
                    dump_list(first_element, chosen-1, 0);
                chosen = 0;
                swap = false;
            }
            else
                printf("\a");
            break;
        case 72:
            if (current == 1)
                printf("\a");
            else {
                current--;
                system("cls");
                dump_list(first_element, current, chosen);
                if (swap == true)
                    printf("\n Now choose second element to swap.");
            }
            break;
        case 80:
            if (current == song_amount)
                printf("\a");
            else {
                current++;
                system("cls");
                dump_list(first_element, current, chosen);
                if (swap == true)
                    printf("\n Now choose second element to swap.");
            }
            break;
        case 'a':
            temp_list = first_element;
            temp_list = add_new_song_to_list_menu(temp_list);
            if (temp_list == NULL)
                printf("\nAdding aborted.");
            else {
                first_element = temp_list;
                song_amount++;
                current = song_amount;
                system("cls");
                dump_list(first_element, current, 0);
                printf("\nAdded successfully.");
            }
            break;
        default:
            printf("\a");
            break;
        }
    }
    return 1;
}

SONG_INFO* add_new_song_to_list_menu(SONG_INFO* song_list) {
    char button;
    char temp_song_path[50];
    SONG_INFO* new_element = add_element();
    SONG_INFO* current_element = song_list;
    while (true) {
        system("cls");
        printf("Enter file name without extension: ");
        gets(temp_song_path);
        strcat(temp_song_path, ".mp3");
        strcpy(new_element->song_path, "music\\");
        strcat(new_element->song_path, temp_song_path);
        if (add_song_info(new_element)==0) {
            printf("This file doesn't exist in \\music folder.\n");
            printf("Press ESC to abort adding or any other button to retry.");
            button = getch();
            if (button == 27) {
                free(new_element);
                return NULL;
            }
        }
        else {
            while (current_element->song_next!=NULL)
                current_element = current_element->song_next;
            current_element->song_next = new_element;
            return song_list;
        }
    }
}

int player_interface (SONG_INFO* song) {
    if (song == NULL)
        return 0;
    printf("            **************************************************\n");
    printf("            *                   RADIO 'KPI'                  *\n");
    printf("            **************************************************\n\n\n\n\n");
    printf("             Currently playing\n");
    printf("                Artist:       %s\n", song->song_artist);
    printf("                Song  :       %s\n", song->song_name);
    printf("                Album :       %s\n", song->song_album);
    printf("                Year  :       %s\n\n\n\n", song->song_year);
    printf("             Press 's' to skip song or 'e' to exit from playback...");
    return 1;
}

int playlist_save_menu (SONG_INFO* first_element, char playlist_path[]) {
    char user_choice;

    system("cls");
    printf("Do you want save as? (y/n) ");
    user_choice = getch();
    if (user_choice == 'y') {
        char file_name[30];
        char file_path[50];
        strcpy(file_path,"playlists\\");
        while (true) {
            system("cls");
            printf("Enter name of file here (without extension): ");
            gets(file_name);
            strcat(file_path, file_name);
            if (playlist_save(first_element, file_path)==1) {
                printf("\n Saved successfully.");
                printf("\n Press ENTER to continue.");
                getchar();
                return 1;
            }
            else {
                printf("\nERROR. Press ENTER and try again...");
                getchar();
            }
        }
    }
    else {
        if (user_choice == 'n') {
            playlist_save(first_element, playlist_path);
            return 1;
        }
        else
            printf("\a");
    }
}

int main_menu() {
    char user_choice;
    SONG_INFO* all_music = NULL;
    SONG_INFO* playlist = NULL;
    SONG_INFO* current_element;
    P_INFO* new_playlist_file;
    bool playlist_opened = false;

    while (true) {
        system("cls");
        printf("Press 1-6 buttons to choose:\n");
        printf("1. Launch all music\n");
        printf("2. Open playlist\n");
        printf("3. Launch playlist\n");
        printf("4. Edit playlist\n");
        printf("5. Save playlist\n");
        printf("6. Exit\n");
        user_choice = getch();
        switch (user_choice) {
        case '1':
            all_music = get_all_music();
            current_element = all_music;
            while (current_element!=NULL) {
                system("cls");
                player_interface(current_element);
                printf("\n All music playing.");
                if (play_audiofile(current_element->song_path) == 0)
                    break;
                current_element = current_element->song_next;
            }
            break;
        case '2':
            new_playlist_file = input_playlist();
            playlist_opened = true;
            playlist = get_music_from_playlist(new_playlist_file->path);
            break;
        case '3':
            if (playlist_opened == true) {
                current_element = playlist;
                while (current_element!=NULL) {
                    system("cls");
                    player_interface(current_element);
                    printf("\n Playlist playing.");
                    if (play_audiofile(current_element->song_path) == 0)
                        break;
                    current_element = current_element->song_next;
                }
            }
            else {
                printf("\a\nOpen playlist first.\n");
                printf("Press ENTER to continue...");
                getchar();
            }
            break;
        case '4':
            if (playlist_opened == true) {
                system("cls");
                current_element = playlist;
                playlist_menu(playlist, new_playlist_file->songs_counter);
            }
            else {
                printf("\a\nOpen playlist first.\n");
                printf("Press ENTER to continue...");
                getchar();
            }
            break;
        case '5':
            if (playlist_opened == true) {
                current_element = playlist;
                playlist_save_menu(current_element, new_playlist_file->path);
            }
            else {
                printf("\a\nOpen playlist first.\n");
                printf("Press ENTER to continue...");
                getchar();
            }
            break;
        case '6':
            free_memory(all_music);
            free_memory(playlist);
            free(new_playlist_file);
            return 0;
            break;
        default:
            printf("\a");
            break;
        }
    }
}
