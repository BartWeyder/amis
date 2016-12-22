#include <conio.h>
#include "inc/fmod.h"
#include <stdbool.h>
#include <stdio.h>
#include "load_music_in_ram.h"

//function description
int play_audiofile (char audiofile_path[]) {
    FMOD_SOUND* handle;
    char song_control_button;
    FMOD_SYSTEM *system;
    FMOD_CHANNEL *chanel = 0;
    FMOD_BOOL isplaying;
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 10, FMOD_INIT_NORMAL, 0);
    FMOD_System_CreateSound(system, audiofile_path, FMOD_2D, 0, &handle);
    FMOD_Sound_SetMode(handle, FMOD_LOOP_OFF);
    FMOD_System_PlaySound (system, handle, 0, false, &chanel);
    isplaying = 1;
    while (isplaying==1)//&&(skip_song_button = getch())!='s')
    {
        FMOD_Channel_IsPlaying(chanel, &isplaying);
        if (kbhit()) {
            song_control_button = getch();
            switch (song_control_button) {
            case 's':
                isplaying = 0;
                break;
            case 'e':
                FMOD_Sound_Release(handle);
                FMOD_System_Close(system);
                FMOD_System_Release(system);
                return 0;
                break;
            default:
                printf("\a");
            }
        }
    }
    //skip_song_button = '\0';
    FMOD_Sound_Release(handle);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    return 1;
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
