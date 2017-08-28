
#ifndef _AUDIO_H_
#define _AUDIO_H_

class Audio {
private:
	IDirectSound8* directSound;
	LPDIRECTSOUNDBUFFER8 soundBuffer = NULL;
	const char* path;

public:
	bool loop = false;

	Audio(const char* path);
	~Audio();

	bool LoadAudio();
	void Play();
};

#endif
