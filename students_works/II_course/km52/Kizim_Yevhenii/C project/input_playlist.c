#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "input_playlist.h"
#include "playlist_validation.h"

P_INFO* input_playlist() {
    P_INFO* user_playlist=malloc(sizeof(P_INFO));
    char* temp_input=NULL;
    int name_length=0;
    user_playlist->path=malloc(sizeof(char)*(sizeof(".playlist")+1));
    //start input from keyboard
    while (1) {
        *temp_input=getchar();
        if (*temp_input==13) {
            if (name_length==0)
                printf("Please enter at least one character!\n");
            else
                break;
        }
        else {
        name_length++;
        user_playlist->path=realloc(user_playlist->path,sizeof(char)*(sizeof(".playlsit"+name_length+1)));
        strcat(user_playlist->path,temp_input);
        }
    };
    strcat(user_playlist->path,".playlist");
    //validating input
    user_playlist->songs_counter = validate_playlist(user_playlist->path);
    if (user_playlist->songs_counter==0) {
        printf("Playlist is empty or does not exist! \n");
        return NULL;
    }
    else
        return user_playlist;
}
