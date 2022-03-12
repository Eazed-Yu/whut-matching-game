#include "pch.h"
#include "BackgroundMusic.h"
#include<MMSystem.h>
#include<Digitalv.h>

#pragma comment(lib,"Winmm.lib")

//��������
void BackgroundMusic::playBackgroundMusic()
{
	PlaySound(_T("source\\music\\TimeSpace.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

//ֹͣ���ֲ���
void BackgroundMusic::pauseBackgroundMusic()
{
	PlaySound(NULL, NULL, SND_FILENAME);
}