#include "memory.h"
#include "vga.h"

//#include "song.h" // Include Song header file

extern "C"
{
    #include "song_player.h"
    #include "song.h"
}
// Overloaded new and delete operators
void* operator new(size_t size) {
    return malloc(size);
}
void operator delete(void* ptr) noexcept {
    free(ptr);
}
void* operator new[](size_t size) {
    return malloc(size);
}
void operator delete[](void* ptr) noexcept {
    free(ptr);
}

// For C++14 sized deallocation (required by C++20 as warnings indicate)
void operator delete(void* ptr, size_t) noexcept {
    free(ptr);
}

void operator delete[](void* ptr, size_t) noexcept {
    free(ptr);
}

extern "C" int kernel_main(void);
int kernel_main() {
    // Allocate and free memory
    //void* ptr1 = malloc(1024);
    //void* ptr2 = malloc(4096);
    //char* ptr3 = (char*)malloc(2048); // Allocate memory using malloc
    //free(ptr1);
    //free(ptr3); // Free memory using free
    //print_memory_layout();
    //void* ptr4 = malloc(0xFFFFFFFF);  // Try to allocate more memory than available
    //if (ptr4 == NULL) {
        //printf("Out of memory: Unable to allocate memory.\n");
    //}


       // Create array of Songs
    Song* songs[] = {new Song({starwars_theme, sizeof(starwars_theme) / sizeof(Note)})};

    Song * temp = songs[0];
    uint32_t n_songs = sizeof(songs)/(sizeof(Song*));

    // Create SongPlayer instance
    SongPlayer* player = create_song_player();
    //player->play_song(temp);
    //while (true) {
    for (uint32_t i = 0; i < n_songs; i++) {
        //printf("Playing Song...\n");
        player->play_song(songs[i]);
        //printf("Finished playing the song.\n");
    }
    //}

    while(1)
    {

    }

    return 0;
}
