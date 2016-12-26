#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "playlist.h"
#include "list.h"

P_INFO* input_playlist() {
    P_INFO* user_playlist=malloc(sizeof(P_INFO));
    char buff [200]={0};
    //start input from keyboard
    memset(user_playlist->path,0,sizeof(user_playlist->path));
    strcpy(user_playlist->path,"playlists/");
    char* prohibited="\"|\\/*:?<>";
    while (true) {
        printf("Enter name of playlist without extension:\n");
        gets(buff);
        if (strpbrk(prohibited,buff)!=NULL) {
            printf("\aSymbols '\"','|','\\','/','*',':','?','>','<' are not allowed!\n");
            printf("Press any key to try again");
            getch();
            system("cls");
        }
        else{
            if (strlen(buff)==0){
                printf("\aEnter at least one symbol!\n");
                printf("Press any key to try again");
                getch();
                system("cls");
            }
            else break;
        }
    }
    strcat(user_playlist->path, buff);
    strcat(user_playlist->path,".playlist");
    //validating input
    printf("\n%s", user_playlist->path);
    user_playlist->songs_counter = validate_playlist(user_playlist->path);
    if (user_playlist->songs_counter==0) {
        printf("\nPlaylist is empty or does not exist! \n");
        printf("Press ENTER to continue...");
        getchar();
        return NULL;
    }
    else{
        printf("\nThere are %d song(s) in current playlist.", user_playlist->songs_counter);
        printf("Press ENTER to continue...");
        getchar();
        return user_playlist;
    }
}

int validate_playlist (char playlist_path[200]) {
    FILE *playlist_file;
    char buff[200];
    int songs_counter=0;

    playlist_file=fopen(playlist_path,"r");

    if (playlist_file==NULL)
        return 0;

    while (!feof(playlist_file)) {
        fgets(buff, 200, playlist_file);
        songs_counter++;
    }
    fclose(playlist_file);
    return songs_counter;
}

int playlist_save (SONG_INFO* first_element, char playlist_path[]) {
    FILE* playlist_file = NULL;
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
