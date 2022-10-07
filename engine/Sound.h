#ifndef MOON_ENGINE_SOUND_H
#define MOON_ENGINE_SOUND_H

#include "Include.h"
#include "Window.h"
#include "Array.h"

// Initialises music
void InitMusic(Music* music, char* filename);

// Initialises a sound(effect)
void InitSound(Sound* sound, char* filename);

// Sets music position
void SetPosMusic(Music* music, double playPos);

// Plays music for a amount of loops (-1 being infinite)
void PlayMusic(Music* music, int numLoops);

// Plays a sound for a amount of loops (-1 being infinite)
void PlaySound(Sound* sound, int numLoops);

// Pauses music in current stream
void PauseMusic(void);

// Resumes music in current stream
void ResumeMusic(void);

// Stops music in the current stream
void StopMusic(void);

// Set music volume
void SetMusicVolume(int volume);

// Set sound volume
void SetSoundVolume(int volume);

// Frees a sound array
void FreeSoundArray(Sound* arrayPtr[], int size);

// Frees a music array
void FreeMusicArray(Music* arrayPtr[], int size);
#endif