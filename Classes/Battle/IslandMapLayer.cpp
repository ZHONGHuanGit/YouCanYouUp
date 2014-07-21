#include "IslandMapLayer.h"
USING_NS_CC;
bool IslandMapLayer::init(){
	if ( !MapLayer::init() )
    {
        return false;
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//����
	auto background = Sprite::create("Map/map2.jpg");
	background->setPosition(visibleSize/2);
	this->addChild(background);

	//���ϣ��ұ߽�
	Vec2* edge =  new Vec2[4];
	edge[0] = Vec2(0,0);
	edge[1] = Vec2(0,visibleSize.height);
	edge[2] = Vec2(visibleSize.width,visibleSize.height);
	edge[3] = Vec2(visibleSize.width,0);
	auto edgeBody = PhysicsBody::createEdgeChain(edge,4,PHYSICSBODY_MATERIAL_DEFAULT,3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(0,0));
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);
	delete [] edge;

	//ƽ̨

	auto plateBody =PhysicsBody::createBox(Size(558,184),PHYSICSBODY_MATERIAL_DEFAULT,Vec2::ZERO);
	plateBody->setDynamic(false);//������
	auto plateNode = Node::create();
	plateNode->setPhysicsBody(plateBody);
	plateNode->setPosition(visibleSize/2-Size(20,0));
	this->addChild(plateNode);

	addBody(plateBody);
	addShape(ShapeType::BOX);


	return true;
}