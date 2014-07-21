#include "BattleScene.h"

USING_NS_CC;

Scene* BattleScene::createScene(bool online, GameSetting::Character hero, GameSetting::Map map, std::vector<GameSetting::Character> enemy){
	//�������� 
	auto scene = Scene::createWithPhysics();
	//����������
	auto mapLayer = BattleScene::selectMap(map);
	//������ɫ��
	CharacterLayer *characterLayer;
	if(online)
	{
		characterLayer = MPCharacterLayer::create();
	}
	else
	{
		characterLayer = SPCharacterLayer::create();
	}
		
	characterLayer->setHero(hero);
	characterLayer->setEnemy(enemy);

	auto uiLayer = HUDLayer::create();

	//������ӵ�������
	scene->addChild(mapLayer);
	scene->addChild(characterLayer);
	scene->addChild(uiLayer);

	//���������������ɼ�
	//scene->getPhysicsWorld()->setDebugDrawMask(true);
	//������������������ͱ���
	scene->getPhysicsWorld()->setGravity(Vec2(0,-300));
	scene->getPhysicsWorld()->setSpeed(1.5f);

	return scene;
}

bool BattleScene::init(){
	return true;
}

Layer* BattleScene::selectMap(GameSetting::Map map){
	if(map==GameSetting::Map::FOREST){
		return ForestMapLayer::create();
	}
	if(map==GameSetting::Map::ISLAND){
		return IslandMapLayer::create();
	}
	if(map==GameSetting::Map::DESERT){
		return DesertMapLayer::create();
	}
	return nullptr;
}
