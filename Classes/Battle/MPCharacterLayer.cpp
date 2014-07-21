#include "MPCharacterLayer.h"
#include "CmdTool.h"
#include "Global.h"
#include "ResultLayer.h"

using namespace network;

bool MPCharacterLayer:: init()
{
	int hero_lives = INITIAL_LIVES;
	int enemy_lives = INITIAL_LIVES;

		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(false); //�ر�ԭ�ȵı�������

	// ---------- WebSocket ---------
	_wsiClient = new cocos2d::network::WebSocket();
	_wsiClient->init(*this, WS_SERVER_URL);
	this->schedule(schedule_selector(MPCharacterLayer::sendFightCmd),1.0f);
	// ---------- WebSocket ---------

	//�����¼�����
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MPCharacterLayer::onTouchBegan,this);
	//listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(MPCharacterLayer::onTouchEnded,this);
	listener->setSwallowTouches(true);//�����´��ݴ���
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//��ʱ�ָ�����
	this->schedule(schedule_selector(MPCharacterLayer::recoverySchedule), .5f);
	//��ʱ�жϽ��
	this->schedule(schedule_selector(MPCharacterLayer::checkResSchedule), 1.f);

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/fighting.mp3",true); //���ű�������


	return true;
}

void MPCharacterLayer::sendFightCmd(float fDelta)
{
	_wsiClient->send("fight");
	this->unschedule(schedule_selector(MPCharacterLayer::sendFightCmd));
}


void MPCharacterLayer::recoverySchedule(float fDelta){
	hero->recovery(3);//ÿ�λָ�3hp
}

bool MPCharacterLayer::onTouchBegan(Touch *pTouch, Event *pEvent){
	posBegan = pTouch->getLocation();
	return true;
}

void MPCharacterLayer::onTouchEnded(Touch *touch, Event *unused_event){
	posEnded = touch->getLocation();
	Vec2 force=2*(posEnded-posBegan);

	_wsiClient->send("fight!key="+enemyKey+"&px="+std::to_string(hero->getPosition().x)+"&py="+
		std::to_string(hero->getPosition().y)+"&fx="+std::to_string(force.x)+"&fy="+std::to_string(force.y));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/touch.wav"); //������Ч

}

void MPCharacterLayer::CheckResult(){
	float heroY = hero->getSprite()->getPositionY();
	if(heroY<0){
		if(--hero_lives){
			NotificationCenter::sharedNotificationCenter()->postNotification("loseHeroLife",NULL);
			Rebirth(hero);
		}
		else{
			CCLOG("You lose!");
			enemy_lives = INITIAL_LIVES;
			this->getScene()->addChild(ResultLayer::create(Result::LOSE));
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(false); //�رձ�������
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/lost.wav"); //������Ч
			Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
		}
	}
	float enemyY = enemy->getSprite()->getPositionY();
	if(enemy<0){
		if(--enemy_lives){
				NotificationCenter::sharedNotificationCenter()->postNotification("loseEnemyLife",NULL);
				Rebirth(enemy);
			}
			else{
				CCLOG("You win!");
				hero_lives = INITIAL_LIVES;
				this->getScene()->addChild(ResultLayer::create(Result::WIN));

				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(false); //�رձ�������
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/win.wav"); //������Ч

				Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
				CCLOG("GET-AddScore");
				HttpRequest* request = new HttpRequest();  
				std::string username_s = UserDefault::getInstance()->getStringForKey("username");
				std::string url = ADD_SCORE_SERVER_URL + username_s;
				request->setUrl(url.c_str());  
				request->setRequestType(HttpRequest::Type::GET);  
				request->setTag("GET-AddScore");  
				HttpClient::getInstance()->send(request);  
				request->release();
			}
	}
}

void MPCharacterLayer::Rebirth(Character* cha){
	Vec2 force = Vec2::ZERO;
	Vec2 vec = Vec2(300, 500);
	cha->setPosition(vec);
	_wsiClient->send("fight!key="+enemyKey+"&px="+std::to_string(vec.x)+"&py="+
	std::to_string(vec.y)+"&fx="+std::to_string(force.x)+"&fy="+std::to_string(force.y));
}

MPCharacterLayer::~MPCharacterLayer(){
	delete hero;
	
}

void MPCharacterLayer::setHero(GameSetting::Character hero)
{
	//������ɫ
	this->hero = new Character(hero);
	this->hero->setPosition(Vec2(300,500));
	this->addChild(this->hero->getSprite());
}

void MPCharacterLayer::setEnemy(std::vector<GameSetting::Character> enemy)
{
	this->enemy = new Character(enemy[0]);
	this->enemy->setPosition(Vec2(500,500));
	this->addChild(this->enemy->getSprite());
}

// ------------------ websocket function -----------------------
// ��ʼsocket����
void MPCharacterLayer::onOpen(cocos2d::network::WebSocket* ws)
{
    CCLOG("connect");
}

// ���յ�����Ϣ
void MPCharacterLayer::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)
{
    
    std::string msgStr = data.bytes;
    CCLOG("�յ�����Ϣ��%s",msgStr.c_str());
    std::string cmdStr = CmdTool::getCmd(msgStr);
    std::string cmdPara = CmdTool::getCmdPara(msgStr);

		int initNum = 0;
		if (cmdStr == "enemy0") {
			CCLOG("ƥ�䵽���֣�����Key=%s",cmdPara.c_str());
			enemyKey = cmdPara;
			initNum = 0;
			initBattleScene(initNum);
		}
    
		if (cmdStr == "enemy1") {
			CCLOG("ƥ�䵽���֣�����Key=%s",cmdPara.c_str());
			enemyKey = cmdPara;
			initNum = 1;
			initBattleScene(initNum);
		}
 
    // ---------- �յ����������͵Ĵ��¼� ----------
    if (cmdStr == "fight") {
        string cmdKey = CmdTool::getCmdKey(msgStr);
        string px = CmdTool::getFightPx(msgStr);
        string py = CmdTool::getFightPy(msgStr);
        string fx = CmdTool::getFightFx(msgStr);
        string fy = CmdTool::getFightFy(msgStr);
        CCLOG("key = %s",CmdTool::getCmdKey(msgStr).c_str());
        CCLOG("px = %s",CmdTool::getFightPx(msgStr).c_str());
        CCLOG("py = %s",CmdTool::getFightPy(msgStr).c_str());
        CCLOG("fx = %s",CmdTool::getFightFx(msgStr).c_str());
        CCLOG("fy = %s",CmdTool::getFightFy(msgStr).c_str());
        if(cmdKey == enemyKey){
			enemy->applyImpulse(Vec2(atof(fx.c_str()),atof(fy.c_str())));
			enemy->setPosition(Vec2(atof(px.c_str()),atof(py.c_str())));
		} else {
			hero->applyImpulse(Vec2(atof(fx.c_str()),atof(fy.c_str())));
			hero->setPosition(Vec2(atof(px.c_str()),atof(py.c_str())));

		}
    }
 
}

// ���ӹر�
void MPCharacterLayer::onClose(cocos2d::network::WebSocket* ws)
{
    if (ws == _wsiClient)
    {
        _wsiClient = NULL;
    }
    CC_SAFE_DELETE(ws);
    CCLOG("onClose");
}

// ��������
void MPCharacterLayer::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)
{
    if (ws == _wsiClient)
    {
        char buf[100] = {0};
        sprintf(buf, "an error was fired, code: %d", error);
    }
    CCLOG("Error was fired, error code: %d", error);
}


void MPCharacterLayer::initBattleScene(int index){

	
    // -----------------
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    CCLOG("visibleSize = %f,%f",visibleSize.width,visibleSize.height);
    CCLOG("origin = %f,%f",origin.x,origin.y);
 
    // �����������ս
    if(index == 0){
		hero->setPosition(Vec2(visibleSize.width / 4 , visibleSize.height / 2));
        enemy->setPosition(Vec2(visibleSize.width / 4 * 3 , visibleSize.height / 2));
    }
    
    // ����ǿͳ���ս
    else{
        hero->setPosition(Vec2(visibleSize.width / 4 * 3 , visibleSize.height / 2));
        enemy->setPosition(Vec2(visibleSize.width / 4 , visibleSize.height / 2));
    }

    
}
