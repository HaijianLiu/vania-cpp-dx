
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Audio::Audio(const char* path) {
	this->path = path;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Audio::~Audio() {
	if (this->soundBuffer != NULL) this->soundBuffer->Release();
}


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
bool Audio::LoadAudio() {
	this->directSound = GetDirectSound();
	LPDIRECTSOUNDBUFFER  pBaseBuffer = NULL;
	DSBUFFERDESC buff;

	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	MMRESULT mmRes;
	MMCKINFO riffChunk, formatChunk, dataChunk;
	DWORD size;
	WAVEFORMATEX pcm;

	LPVOID pBlock;
	DWORD  dwSize;

	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen((LPSTR)this->path, &mmioInfo, MMIO_READ);
	if(!hMmio) return false;

	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);
	if(mmRes != MMSYSERR_NOERROR) { mmioClose(hMmio, 0); return false; }

	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);
	if(mmRes != MMSYSERR_NOERROR) { mmioClose(hMmio, 0); return false; }
	size = mmioRead(hMmio, (HPSTR)&pcm, formatChunk.cksize);
	if(size != formatChunk.cksize) { mmioClose(hMmio, 0); return false; }
	mmioAscend(hMmio, &formatChunk, 0);

	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);
	if(mmRes != MMSYSERR_NOERROR) { mmioClose(hMmio, 0); return false; }
	char *pData = new char[dataChunk.cksize];
	size = mmioRead(hMmio, (HPSTR)pData, dataChunk.cksize);
	if(size != dataChunk.cksize) { delete[] pData; return false; }

	ZeroMemory(&buff, sizeof(DSBUFFERDESC));
	buff.dwSize = sizeof(DSBUFFERDESC);
	buff.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;
	buff.dwBufferBytes = size;
	buff.lpwfxFormat = &pcm;
	if (FAILED(this->directSound->CreateSoundBuffer(&buff, &pBaseBuffer, NULL))) return false;
	if (FAILED(pBaseBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&this->soundBuffer))) return false;
	pBaseBuffer->Release();

	if (FAILED(this->soundBuffer->Lock(0, 0, &pBlock, &dwSize, NULL, NULL, DSBLOCK_ENTIREBUFFER))) return false;
	memcpy(pBlock, pData, dwSize);
	delete[] pData;
	this->soundBuffer->Unlock(pBlock, dwSize, 0, 0);

	return true;
}

void Audio::Play() {
	this->soundBuffer->Play(0, 0, this->loop);
}

bool Audio::Playing() {
	DWORD status;
	this->soundBuffer->GetStatus(&status);
	if (status & DSBSTATUS_PLAYING) return true;
	return false;
}

void Audio::Stop() {
	DWORD status;
	this->soundBuffer->GetStatus(&status);
	if (status & DSBSTATUS_PLAYING ) this->soundBuffer->Stop();
}

void Audio::Reset() {
	this->soundBuffer->SetCurrentPosition(0);
}
