#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "music.h"
#include "inc/fmod.h"

#define ID3_MAX_SIZE 128

long idv3_file_offset(FILE* audio_file)
{
    fseek(audio_file, 0L, SEEK_END);
    return ftell(audio_file) - ID3_MAX_SIZE;
}

ID3TAG* output_audiofile_info(char audiofile_path[]) {
    FILE* audiofile = NULL;
    if ((audiofile = fopen(audiofile_path,"r")) == NULL)
        return NULL;

    char* buf = (char*)malloc(ID3_MAX_SIZE);
    memset((void*)buf, 0x00, ID3_MAX_SIZE);

    fseek(audiofile, idv3_file_offset(audiofile), SEEK_SET);
    fread(buf, 1, ID3_MAX_SIZE, audiofile);

    ID3TAG* pId3Tag = NULL;
    if ((pId3Tag = (ID3TAG*)(buf)) != NULL)
    {
        //may be some messages
    }
    fclose(audiofile);
    return pId3Tag;
}

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
