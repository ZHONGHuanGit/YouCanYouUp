#include "Battle/Character.h"
#include "Battle/BodyInfo.h"

#ifndef MANAGERINFOMATION_DEFINE
#define MANAGERINFOMATION_DEFINE


/**
*   �洢body���ĸ���λ��
*/ 
struct BodyPos{
public:
	Vec2 * pos;
	void normalPoints();
	
	bool operator < (const BodyPos & p2) const{
		return pos[1].y > p2.pos[1].y;//�Ƚϵ������Ͻǵ�λ��
	}
};



/**
*	�洢EnemyManager������Ҫ��Ϣ
*/
class ManagerInfo{

protected:
	Character * hero;
	std::vector<Character*> enemys;
	BodyInfo* bodyInfo;
	
public:

	const static int NUM=10;
	const static int posNum=10;  //��¼λ�õ�����
		std::list<Vec2> eList[NUM];   //�洢enemy��ǰ���λ��
		std::list<Vec2> hList[NUM];    //�洢heroǰ���λ��
		int eListSize[NUM];      //�洢eList�ĳ���
		int hListSize[NUM];   //�洢hList�ĳ���

	std::vector<BodyPos> bodyPos;
	std::vector<bool> isOK;

	Character * getHero(){return hero;}
	void setHero(Character * hero){this->hero=hero;}

	void addEnemy(Character* enemy){
		enemys.push_back(enemy);
		CCLOG("size %d  ",enemys.size());
	}

	std::vector<Character*> & getEnemys(){
	//	CCLOG("enemys  size: %d",enemys.size());
		return enemys;
	}

	void setBodyInfo(BodyInfo * bodyInfo)
	{
		this->bodyInfo=bodyInfo;
	}

	BodyInfo* getBodyInfo()
	{
		return bodyInfo;
	}

	//����bodyIndo��body��Ϣ
	void  handleBodyInfo();
};

#endif