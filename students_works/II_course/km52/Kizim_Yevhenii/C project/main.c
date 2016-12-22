#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "output_audiofile_info.h"
#include "input_playlist.h"
#include "playlist_edit.h"
#include "play_audio.h"
#include "playlist_edit.h"
#include "playlist_save.h"

int main()
{
    //main text
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
                play_audiofile(current_element->song_path);
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
                    play_audiofile(current_element->song_path);
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
                playlist_menu(current_element, new_playlist_file->songs_counter);
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
    return 0;
}


