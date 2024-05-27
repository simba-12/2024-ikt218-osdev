#include "song.h"   // Definitions for Note and Song
#include "pit.h"    // PIT definitions and initializations
#include "idt.h"    // Interrupt handling functionalities
#include "libc/stdio.h"
#include "util.h"
#include <stdint.h>

extern "C"
{
    #include "song_player.h"
}


extern volatile uint32_t timer_ticks;  // Imported from where it's defined

#define PC_SPEAKER_PORT 0x61
#define PIT_CMD_PORT 0x43
#define PIT_CHANNEL2_PORT 0x42

// Function to enable PC speaker
void enable_speaker() {
    uint8_t temp = inPortB(PC_SPEAKER_PORT);
    outb(PC_SPEAKER_PORT, temp | 3);
}


// Define a static instance of SongPlayer
//static SongPlayer songPlayerInstance;

// Function to create a new SongPlayer instance
SongPlayer* create_song_player() {
    auto* player = new SongPlayer();
    player->play_song = play_song;
    // Return a pointer to the static instance
    return player;
}


// Function to disable PC speaker
void disable_speaker() {
    uint8_t temp = inPortB(PC_SPEAKER_PORT);
    outb(PC_SPEAKER_PORT, temp & ~3);
}

// Function to play a sound of a given frequency
void play_sound(uint32_t frequency) {
    if (frequency == 0) {
        disable_speaker();
        return;
    }

    uint32_t divisor = 1193180 / frequency;  // Assume base frequency for PIT
    outb(PIT_CMD_PORT, 0xB6);  // Command byte for channel 2, square wave
    outb(PIT_CHANNEL2_PORT, divisor & 0xFF);
    outb(PIT_CHANNEL2_PORT, (divisor >> 8) & 0xFF);

    enable_speaker();
}

// Function to stop the sound
void stop_sound() {
    disable_speaker();
}

// Function to play a song
void play_song(Song *song) {
    enable_speaker();
    for (uint32_t i = 0; i < song->length; i++) {
        Note note = song->notes[i];
        printf("Playing frequency %u Hz for %u ms\n", note.frequency, note.duration);

        play_sound(note.frequency);
        // uint32_t start_tick = timer_ticks;
        //uint32_t ticks_needed = note.duration * (PIT_BASE_FREQUENCY / 1000);
        sleep_busy(note.duration);
        /*while ((timer_ticks - start_tick) < ticks_needed) {
            // Busy wait for the duration of the note
        }*/

        stop_sound();
        sleep_busy(50);
    }
    disable_speaker();
}

// The timer handler is assumed to be defined in another source file
// Rename the function to avoid conflict with the main kernel entry point
int init_song_player() {
    
    //init_pit();   // Initialize PIT if not already initialized elsewhere
    //initIdt();    // Initialize IDT if not already initialized elsewhere

    Note music[] = {{440, 500}, {440, 500}, {0, 500}, {660, 500}, {440, 500}};
    Song song = {music, sizeof(music) / sizeof(Note)};
    play_song(&song);

    return 0;
}
