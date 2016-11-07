#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

typedef struct playlist_info {
    char* path;
    int songs_counter;
} P_INFO;

P_INFO* input_playlist();

#endif // INPUT_H_INCLUDED
