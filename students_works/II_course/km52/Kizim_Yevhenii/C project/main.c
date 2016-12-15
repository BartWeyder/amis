#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "output_audiofile_info.h"
#include "input_playlist.h"
#include "edit_playlist_interface.h"
#include "play_audio.h"

int main()
{
    //main text;
    SONG_INFO* new_list = get_all_music();
    SONG_INFO* current_song = new_list;
    while (current_song!=NULL) {
        printf("Artist:        %s \n", current_song->song_artist);
        printf("Song name:     %s \n", current_song->song_name);
        printf("Press 's' button to skip track...");
        play_audiofile(current_song->song_path);
        current_song = current_song->song_next;
        system("cls");
    }
    free_memory(new_list);
    return 0;
}


