#include <conio.h>
#include "inc/fmod.h"
#include <stdbool.h>
#include <stdio.h>

//function description
int play_audiofile (char audiofile_path[]) {
    FMOD_SOUND* handle;
    char skip_song_button;
    FMOD_SYSTEM *system;
    FMOD_CHANNEL *chanel = 0;
    FMOD_BOOL *isplaying;
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 10, FMOD_INIT_NORMAL, 0);
    FMOD_System_CreateSound(system, audiofile_path, FMOD_2D, 0, &handle);
    FMOD_Sound_SetMode(handle, FMOD_LOOP_OFF);
    FMOD_System_PlaySound (system, handle, 0, false, &chanel);
    *isplaying = true;
    while (*isplaying==true&&(skip_song_button = getch())!='s')
    {
        FMOD_Channel_IsPlaying(chanel, isplaying);
    }
    skip_song_button = '\0';
    FMOD_Sound_Release(handle);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    return 1;
}
