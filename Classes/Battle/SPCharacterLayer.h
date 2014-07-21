#include "cocos2d.h"
#include "Character.h"
#include "CharacterLayer.h"
#include "Health.h"
#include "AI/EnemyManager.h"

#include "SimpleAudioEngine.h"

class SPCharacterLayer : public CharacterLayer
{
private:

	//ר�����˹���
	EnemyManager* enemyManager;

	//�ж�ʤ��
	void CheckResult();
	//��ɫ����
	void Rebirth(Character* cha);

	//������ʼ�¼�
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	//������ֹ�¼�
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	//�ж�schedule
	virtual void actionSchedule(float delta);

	//�ָ�schedule 
	virtual void recoverySchedule(float delta);

public:

	virtual bool init();  
	~SPCharacterLayer();
	CREATE_FUNC(SPCharacterLayer);

	void setHero(GameSetting::Character hero);
	void setEnemy(std::vector<GameSetting::Character> enemy);

};

