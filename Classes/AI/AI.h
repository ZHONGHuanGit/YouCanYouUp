#include "Battle/Character.h"
#include "Battle/BodyInfo.h"
#include <vector>
#include "ManagerInfo.h"
#include <list>

#ifndef AI_DEFINE
#define AI_DEFINE

class StateNode{

private:

protected:
	ManagerInfo * info;
	Character * enemy;

		//�жϾ���enemy����box��ͨ������жϷ���
	Vec2 getCloseVec(Vec2 now);

	//�жϷ���
	int judgeDir(Character * enmey,int i);

public:

	StateNode(ManagerInfo * info, Character * enemy) :info(info), enemy(enemy){}

	//��������״̬ʱ��ȡ�Ĳ���
	virtual void enter()=0;

	//�����ڸ�״̬ʱ�Ķ���
	virtual void action()=0;

	//��Ҫ���ھ���
	void saveMe();

	//�����뿪��״̬ʱ��ȡ�Ĳ���
	virtual void exit()=0;

	virtual StateNode* changeState()=0;
};

//�����ؽڵ�
class DefendStateNode: public StateNode{

public:

	DefendStateNode(ManagerInfo * info, Character * enemy):StateNode(info,enemy){}

	void enter();
	void action();
	void exit();
	StateNode* changeState();
};

//�������ڵ�
class AttackStateNode: public StateNode{
public:
	AttackStateNode(ManagerInfo * info, Character * enemy):StateNode(info,enemy){}
	void enter();
	void action();
	void exit();
	StateNode* changeState();
};

//���ò��Խڵ�
class StrategyStateNode: public StateNode{
public:
	StrategyStateNode(ManagerInfo * info, Character * enemy):StateNode(info,enemy){}
	void enter();
	void action();
	void exit();
	StateNode* changeState();
};


class AI{
protected:
	ManagerInfo * info;
	std::vector<StateNode*> states;
	bool ready;	//�ж���Ϣ�Ƿ��ȡ




public:

	const static int delta = 20;

	

	AI(ManagerInfo * info) : info(info), ready(false)
	{
		for(int i=0;i<info->NUM;i++)
		{
			info->eListSize[i]=0;
			info->hListSize[i]=0;
		}
	}

	void init();

	//�ı�����enemy��state
	void changeState();

	//ÿ��enemy��Ҫִ�ж���
	void actions();

	void addState(Character* enemy){
		states.push_back(new DefendStateNode(info,enemy));
	}

	void setReady(bool ready){
		this->ready=ready;
	}

	bool getReady()
	{return ready;}
};

#endif