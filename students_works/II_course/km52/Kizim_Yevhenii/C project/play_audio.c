//including own headers
#include "play_audio.h"
#include "input_playlist.h"
#include "output_audiofile_info.h"
//function description
int play_audiofile (char* audiofile_path) {
    *P_INFO current_playlist = input_playlist();

    //play audiofile code

    output_audiofile_info(audiofile_path);
}
