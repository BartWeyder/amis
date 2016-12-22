#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "playlist_save.h"
#include "load_music_in_ram.h"

int playlist_save (SONG_INFO* first_element, char playlist_path[]) {
    FILE* playlist_file = NULL;
    //char playlist_file_path [200];
    //strcpy(playlist_file_path,"playlists\\");
    //strcat(playlist_file_path,name);
    if ((playlist_file = fopen(playlist_path,"w")) == NULL)
        return 0;
    SONG_INFO* current_element = first_element;
    while (current_element!=NULL) {
        fputs(current_element->song_path, playlist_file);
        current_element = current_element->song_next;
    }
    fclose(playlist_file);
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
