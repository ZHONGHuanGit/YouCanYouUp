#include "LoginScene.h"
#include "CCSGUIReader.h"
#include "SignupScene.h"
#include "OnlineScene.h"
#include "MainScene.h"
#include "base/CCUserDefault.h"
#include "Global.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace network;

bool LoginScene::init()
{
	if(!Scene::init()){
		return false;
	}

	Widget *pNode = (Widget*)(GUIReader::getInstance()->widgetFromJsonFile("OnlineUI5.ExportJson"));
	this->addChild(pNode);
	Button *return_ = (Button*)(ui::Helper::seekWidgetByName(pNode, "return"));
	return_->addTouchEventListener(CC_CALLBACK_2(LoginScene::returnEvent, this));
	Button *signup = (Button*)(ui::Helper::seekWidgetByName(pNode, "register"));
	signup->addTouchEventListener(CC_CALLBACK_2(LoginScene::signupEvent, this));
	
	Button *login = (Button*)(ui::Helper::seekWidgetByName(pNode, "login"));
	login->addTouchEventListener(CC_CALLBACK_2(LoginScene::loginEvent, this));
	// �ҵ����������
	username = (TextField*)(ui::Helper::seekWidgetByName(pNode, "username"));
	password = (TextField*)(ui::Helper::seekWidgetByName(pNode, "code"));
	// ��UserDefault�ж�ȡ�û���Ϣ
	username->setText(UserDefault::getInstance()->getStringForKey("username"));
	password->setText(UserDefault::getInstance()->getStringForKey("password"));
	return true;
}

void LoginScene::returnEvent(Ref *pSender, Widget::TouchEventType type)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/button.wav"); //������Ч
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *main = MainScene::create();
		TransitionScene *transition = TransitionFade::create(0.5, main);
		Director::getInstance()->replaceScene(transition);
		break;
	}	
}

void LoginScene::signupEvent(Ref *pSender, Widget::TouchEventType type)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/button.wav"); //������Ч
	switch(type){
	case Widget::TouchEventType::ENDED:
		Scene *signup = SignupScene::create();
		TransitionScene *transition = TransitionFade::create(1, signup);
		Director::getInstance()->pushScene(transition);
		break;
	}	
}

void LoginScene::loginEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/button.wav"); //������Ч
	switch(type){
	case Widget::TouchEventType::ENDED:
		std::string username_s = username->getStringValue();
		std::string password_s = password->getStringValue();
		CCLOG("GET-Login");
		HttpRequest* request = new HttpRequest();  
		std::string url = LOGIN_SERVER_URL + username_s + "/" + password_s;
		request->setUrl(url.c_str());  
		request->setRequestType(HttpRequest::Type::GET);  
		request->setResponseCallback(this, httpresponse_selector(LoginScene::onHttpRequestCompleted));    
		request->setTag("GET-Login");  
		HttpClient::getInstance()->send(request);  
		request->release();
		break;
	}	
}

void LoginScene::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response) 
{  
	if(!response || !response->isSucceed())
		return;

    std::vector<char>* buffer = response->getResponseData();  
    char res = (*buffer)[0];
	// ��¼�ɹ�
	if(res == '1')
	{
		// �����û���Ϣ
		UserDefault *ud = UserDefault::getInstance();
		ud->setStringForKey("username", username->getStringValue());
		ud->setStringForKey("password", password->getStringValue());
		ud->flush();

		Scene *online = OnlineScene::create(); 
		TransitionScene *transition = TransitionFade::create(0.5, online);
		Director::getInstance()->pushScene(transition);
	}
	// ��¼ʧ�ܡ�������������
	else
	{
		username->setText("");
		password->setText("");
	}
}  