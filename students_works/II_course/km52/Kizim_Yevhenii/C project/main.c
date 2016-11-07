#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define ID3_MAX_SIZE 128

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

long idv3_file_offset(FILE* fp)
{
    fseek(fp, 0L, SEEK_END);
    return ftell(fp) - ID3_MAX_SIZE;
}

int main()
{
    FILE* fp = NULL;
    const char* filename = "test.mp3";
    if ((fp = fopen(filename,"r")) == NULL)
        printf("Unable to open file %s for reading\n", filename);

    //char* buf = new char[ID3_MAX_SIZE];
    char* buf = (char*)malloc(ID3_MAX_SIZE);
    memset((void*)buf, 0x00, ID3_MAX_SIZE);

    fseek(fp, idv3_file_offset(fp), SEEK_SET);
    fread(buf, 1, ID3_MAX_SIZE, fp);

    ID3TAG* pId3Tag = NULL;
    if ((pId3Tag = (ID3TAG*)(buf)) != NULL)
    {
        printf("Name:        %s\n",pId3Tag->name);
        printf("Artist:      %s\n",pId3Tag->artist);
        printf("Album:       %s\n",pId3Tag->album);
        printf("Year:        %s\n",pId3Tag->year);
        printf("Description: %s\n",pId3Tag->description);
        printf("Genre:       %d\n",pId3Tag->genre);
    }

    fclose(fp);

    _getch();

    return 0;
}
/*U#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char* filepath="playlists/playlist1.playlist";
    FILE* file;
    if ((file = fopen(filepath,"r")) == NULL)
        printf("Unable to open file Playlist1.txt for reading\n");
    else printf("Hello World!");
    fclose(file);
    getch();
    return 0;
}*/


