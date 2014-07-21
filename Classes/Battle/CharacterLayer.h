#ifndef _CHARACTERLAYER_H_
#define _CHARACTERLAYER_H_

#include "cocos2d.h"
#include "Character.h"
#include "Health.h"
#include <vector>

class CharacterLayer : public cocos2d::Layer
{

protected:

	//������������ʼ����ֹ��
	Point posBegan,posEnded;

	//�ٿؽ�ɫ
	Character* hero;

	int hero_lives;
	int enemy_lives;

	//�ж�ʤ��
	virtual void CheckResult() = 0;
	//��ɫ����
	virtual void Rebirth(Character* cha) = 0;

	//������ʼ�¼�
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) = 0;
	//������ֹ�¼�
	virtual void onTouchEnded(Touch *touch, Event *unused_event) = 0;

	Health* heroHealth;
	int getHeroHealth(){return hero->getHealth();};

	//�жϽ��schedule
	virtual void checkResSchedule(float delta){ CheckResult(); };

	//�ָ�schedule 
	virtual void recoverySchedule(float delta) = 0;

public:

	virtual void setHero(GameSetting::Character hero){};
	virtual void setEnemy(std::vector<GameSetting::Character> enemy){};

};

#endif
