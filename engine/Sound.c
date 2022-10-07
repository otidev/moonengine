#include "Sound.h"

void InitMusic(Music* music, char* filename) {
	music->music = Mix_LoadMUS(filename);
	if (music->music == NULL)
		fprintf(stderr, "\033[1mError\033[0m: Couldn't load music: %s\n", Mix_GetError());
	// NIMP: Safe to say you're using a window.
	AddToArray(globalWindow->musicArray, music, MUSICARRAYSIZE);
}

void InitSound(Sound* sound, char* filename) {
	sound->sound = Mix_LoadWAV(filename);
	if (sound->sound == NULL)
		fprintf(stderr, "\033[1mError\033[0m: Couldn't load music: %s\n", Mix_GetError());
	AddToArray(globalWindow->soundArray, sound, SOUNDARRAYSIZE);
}

void SetPosMusic(Music* music, double playPos) {
	Mix_SetMusicPosition(playPos);
	music->lastPlayPos = playPos;
}

void PlayMusic(Music* music, int numLoops) {
	Mix_PlayMusic(music->music, numLoops);
}

void PlaySound(Sound* sound, int numLoops) {
	Mix_PlayChannel(-1, sound->sound, numLoops);
}

void PauseMusic(void) {
	Mix_PauseMusic();
}

void ResumeMusic(void) {
	Mix_ResumeMusic();
}


void StopMusic(void) {
	Mix_HaltMusic();
}

void SetSoundVolume(int volume) {
	Mix_Volume(-1, volume);
}

void SetMusicVolume(int volume) {
	Mix_VolumeMusic(volume);
}

static void FreeMusic(Music* music) {
	Mix_FreeMusic(music->music);
	music->music = NULL;
}

static void FreeSound(Sound* sound) {
	Mix_FreeChunk(sound->sound);
	sound->sound = NULL;
}

void FreeSoundArray(Sound* arrayPtr[], int size) {
	if (size == 0)
		fprintf(stderr, "\033[1mError\033[0m: No size for arrayptr.");
	
	int i = 0;

	while (arrayPtr[i] != NULL) {
		#ifdef DEBUG
			fprintf(stderr, "Unloaded pointer to sound: %p\n", arrayPtr[i]);
		#endif
		FreeSound(arrayPtr[i]);
		i++;
	}
}

void FreeMusicArray(Music* arrayPtr[], int size) {
	if (size == 0)
		fprintf(stderr, "\033[1mError\033[0m: No size for arrayptr.");
	
	int i = 0;

	while (arrayPtr[i] != NULL) {
		#ifdef DEBUG
			fprintf(stderr, "Unloaded pointer to music: %p\n", arrayPtr[i]);
		#endif
		FreeMusic(arrayPtr[i]);
		i++;
	}
}