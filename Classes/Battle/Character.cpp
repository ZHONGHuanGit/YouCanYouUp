#include "Character.h"

//��ͼƬ�Ĺ��캯��
Character::Character(GameSetting::Character character)
{
	who = character;
	std::string res =CharacterParameter::getResource(character);
	sprite = Sprite::create(res); 
	sprite->setScale(0.3f);
	body = PhysicsBody::createCircle(sprite->getContentSize().width *0.3/ 2);

	//��������ھ�����
	sprite->setPhysicsBody(body);
	//����λ��
   // sprite->setPosition(p);
    
	//���ø����shape�ĵ���
	body->getShape(0)->setRestitution(CharacterParameter::getRestitution(character));
	
	init();
	mass=body->getMass();

}
//û��ͼƬ�Ĺ��캯��
Character::Character(){
	sprite = Sprite::create();
	body = PhysicsBody::createCircle(40);
	sprite->setPhysicsBody(body);
   // sprite->setPosition(p);

}

//����character������
float Character::getMass(){
	return mass;
}

void Character::init()
{
	//���������������ʼ���������������ͬ
	maxHealth = CharacterParameter::getMaxHealth(who);
	health = maxHealth;
	//��������
	body->setMass(CharacterParameter::getMass(who));
}


Sprite* Character::getSprite(){
	return sprite;
}

PhysicsBody* Character::getBody(){
	return body;
}

Character::~Character(void)
{
	
}


void Character::applyImpulse(Vec2 vec){
	//body->applyForce(vec);
	
	//vec.x*=200;
	//vec.y*=200;
	vec*= body->getMass()/2;
	int temHealth=vec.length()/10000;
	//CCLOG("%d",temHealth);
	if(useHealth(5)) 
		body->applyImpulse(vec);
}

Vec2 Character::getPosition(){
	return body->getPosition();
}

void Character::setPosition(Vec2 pos){
	//auto parent =sprite->getParent();
	sprite->setPosition(pos);
}

bool Character::useHealth(int v){
	if(v<=health){
		health-= v;
		return true;
	}else return false;
}

void Character::recovery(int v){
	health+=v;
	if(health>maxHealth) health= maxHealth;
}

int Character::getHealth(){
	return health;
}
/*
Vec2 Character::getLastForce(){
	return this->lastForce;
}

void Character::setLastForce(Vec2 newForce){
	lastForce= newForce;
}*/