#ifndef SONG_PLAYER_H
#define SONG_PLAYER_H

#include "song.h"  // Ensure this contains the definition for the Song structure

typedef struct {
    // Define any song player specific data here
    void(*play_song)(Song* song);
} SongPlayer;

// Extern declarations for the songs array and the count of songs
extern Song* songs[];
extern unsigned int n_songs; // Declaration for n_songs

// Function to create a new SongPlayer instance
SongPlayer* create_song_player();

// Function to initialize the song player (rename it to avoid conflict)
int init_song_player();

// Function to play a song
void play_song(Song *song);

#endif // SONG_PLAYER_H
