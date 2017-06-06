/*
* About music
* 2013 08
* Joung Daun..
*/
//http://skyfe.tistory.com/135 -> background sound code
//http://blog.naver.com/PostView.nhn?blogId=euclid1001&logNo=40185205516 -> background sound API

#ifndef __MUSIC_H__
#define __MUSIC_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

class music : public cocos2d::Layer
{

public:
	music();
	music(int, int);


    void bgStart(std::string);
	void bgStop();
	void bgPause();
	void bgRestart();

	void effectStart(std::string);
	
	void setEffectSoundVolume(int);
	int getEffectSoundVolume();
	
	void setBgSoundVolume(int);
	int getBgSoundVolume();

	bool effectSoundVolumeUp();
	bool effectSoundVolumeDown();

	bool bgSoundVolumeUp();
	bool bgSoundVolumeDown();


private:
	 int effectSoundVolume;		// »ø∞˙¿Ω¿« «ˆ¿Á ≈©±‚∏¶ ∞°¡ˆ∞Ì ¿÷¥Ÿ.   volume of effect sound
	 int bgSoundVolume;			// πË∞Ê¿Ωæ‡¿« «ˆ¿Á ≈©±‚∏¶ ∞°¡ˆ∞Ì ¿÷¥Ÿ. volume of background sound

};


#endif  // __MUSIC_H__
