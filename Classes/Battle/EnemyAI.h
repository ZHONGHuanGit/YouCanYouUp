#include "Character.h"

class EnemyAI
{
private:
	//��ɫ
	Character* cha;
	//�Ѷ�
	int difficulty;
	//AI�ľ����ж�
	void chase(Vec2 vec);
	void escape(Vec2 vec);
	void dodge(Vec2 vec);
public:
	//��AI��ȡ�ж�
	void action(Character* target);
	EnemyAI(Character* cha);
	~EnemyAI();
};