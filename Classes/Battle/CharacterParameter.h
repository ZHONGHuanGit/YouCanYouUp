#pragma once
#include "cocos2d.h"
#include "GameSetting.h"
/**
*�����洢��ɫ��������
*/

class CharacterParameter
{
public:
	/*
	CharacterParameter();
	~CharacterParameter();
	*/
	
	//�����Դλ��
	static std::string getResource(GameSetting::Character character);
	//�������
	static float getMass(GameSetting::Character character);
	//����������ֵ
	static int getMaxHealth(GameSetting::Character character);
	//��õ���
	static float getRestitution(GameSetting::Character character);


	
	
private:
	//character1
	static const std::string character1_resource;
	static const float character1_mass;
	static const int character1_maxHealth;
	static const float character1_restitution;

	//character2
	static const std::string character2_resource;
	static const float character2_mass;
	static const int character2_maxHealth;
	static const float character2_restitution;
};

//const String CharacterParameter::character1_resource = "Character/monster1.png";

//const float CharacterParameter::character1_mass= 500 ;
//const float CharacterParameter::character1_maxHealth= 100 ;
//const float CharacterParameter::character1_restitution= 1 ;


