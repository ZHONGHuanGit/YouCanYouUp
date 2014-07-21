#include "EnemyAI.h"

void EnemyAI::chase(Vec2 vec){
	//Vec2 vec = target->getPosition()-cha->getPosition();
	
	//vec*=50;
	cha->applyImpulse(vec);
}

void EnemyAI::escape(Vec2 vec){
	vec*=-1;
	//vec*=50;
	cha->applyImpulse(vec);
}

void EnemyAI::dodge(Vec2 vec){
	//vec*=50;
	/*
	float temp = vec.y;
	vec.y=vec.x;
	vec.x = temp;//x��y����*/

	vec.x*=-1;//������ת90��
	cha->applyImpulse(vec);
}

void EnemyAI::action(Character* target){

	//Ŀ����ϴ�������λ��
	//Vec2 tLastForce = target->getLastForce();
	Vec2 tPos = target->getPosition();

	//AI���ϴ�������λ��
	//Vec2 lastForce = cha->getLastForce();
	Vec2 pos = cha->getPosition();

	//AI��Ŀ�������
	Vec2 vec = tPos- pos;
	/*
	//�ж��ж�
	if(tPos.y>pos.y){
		//Ŀ����AI�·�
		if(tLastForce.cross(pos)>1/2){
			//Ŀ�����AI,AI���(����ֵ����1/2)
			dodge(vec);
		}
		else{
			//Ŀ��Զ��AI��AI׷��
			chase(vec);
		}
	}
	else{
		//Ŀ����AI�Ϸ���AI׷��
		chase(vec);
	}
	*/
	chase(vec*2);
	//cha->setLastForce(Vec2(0,0));
}


EnemyAI::EnemyAI(Character* cha){
	this->cha = cha;
}
EnemyAI::~EnemyAI(){
}