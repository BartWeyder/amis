#include "load_music_in_ram.h"
#include <stdlib.h>

int dump_list (SONG_INFO* first_element) {
    SONG_INFO* current_element = first_element;
    while (current_element!=NULL) {
        printf("%s -- %s \n", current_element->song_artist, current_element->song_name);
        current_element = current_element->song_next;
    }
}
