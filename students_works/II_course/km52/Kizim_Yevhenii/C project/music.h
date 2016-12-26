#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

typedef struct IDv3Tag
{
    char signature[3];
    char name[30];
    char artist[30];
    char album[30];
    char year[4];
    char description[30];
    unsigned short genre;
} ID3TAG;

ID3TAG* output_audiofile_info(char audiofile_path[]);
int play_audiofile (char audiofile_path[]);

#endif // MUSIC_H_INCLUDED
