/*
* volume �� ���� ������ ������ �ִ� Ŭ�����Դϴ�.
* ��� ���� ũ��� ȿ���� ũ�⸦ �����ϴ�.

   This is class about volume size.
   It has background volume size and effect volume size.

   volume size is from 0 to 6.
*/

#include "music.h"
#include "userData.h"
/*
	constructor

	set background volume level and effect volume level to 3 as a default.
*/
music::music()
{
	setBgSoundVolume(3);
	setEffectSoundVolume(3);
}
/*
	Constructor
	volume(background sound level , effect sound level)

	set background volume level and effect volume level
*/
music::music(int BG, int EFFECT)
{
	setBgSoundVolume(BG);
	setEffectSoundVolume(EFFECT);
}

/*
	start background music
*/
void music::bgStart(std::string musicName)
{
	if(userData::sharedInstance()->getBGM())
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
			musicName.c_str(),	// ����� ���� ���� �̸�
			true);			// �ݺ��������
}

/*
	stop background music
*/
void music::bgStop()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

/*
	pause background music
*/
void music::bgPause()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

/*
	restart background music
*/
void music::bgRestart()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}


// effect sound start
void music::effectStart(std::string effectName)
{
	if(userData::sharedInstance()->getEFFECT())
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
			effectName.c_str(),
			false);	

	// true�� �����ϸ� �ݺ���
}




/*
	setEffectSoundVolume( effect volume level)

	set effect volume level.
*/
void music::setEffectSoundVolume(int EFFECT)
{
	effectSoundVolume = EFFECT;
}
/*
	getEffectSoundVolume()

	return now effect volume level.
*/
int music::getEffectSoundVolume()
{
	return effectSoundVolume;
}



void music::setBgSoundVolume(int BG)
{
	bgSoundVolume = BG;
}
int music::getBgSoundVolume()
{
	return bgSoundVolume;
}

bool music::effectSoundVolumeUp()
{
	effectSoundVolume ++;
	return true;
}
bool music::effectSoundVolumeDown()
{
	effectSoundVolume--;
	return true;
}

bool music::bgSoundVolumeUp()
{
	bgSoundVolume++;
	return true;
}
bool music::bgSoundVolumeDown()
{
	bgSoundVolume--;
	return true;
}
