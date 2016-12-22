#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "output_audiofile_info.h"

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
    }
    fclose(audiofile);
    return pId3Tag;
}
