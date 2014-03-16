#include "HelloWorldScene.h"
#include "NDKHelper.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    /*
     * Register selectors in a global space so the native environment can
     * respond to the selector when the specified method is called
     * NOTE: Group name is used to easily remove selectors
     */
    NDKHelper::addSelector("HelloWorldSelectors",
                           "gameTestMethod",
                           CC_CALLBACK_2(HelloWorld::gameTestMethod, this),
                           this);
    
    /* Let's send some parameters to the native environment that
       has a method named "nativeTestMethod" */
    ValueMap valueMap;
    valueMap["test_message"] = "Hello from your game!";
    valueMap["test_double"] = 3.14;
    
    Value parameters = Value(valueMap);
    
    sendMessageWithParams("nativeTestMethod", parameters);
    
    return true;
}

/* Your method must have these Node* and Value parameters */
void HelloWorld::gameTestMethod(Node *sender, Value data)
{
    if (!data.isNull() && data.getType() == Value::Type::MAP) {
        ValueMap valueMap = data.asValueMap();
        
        std::string response = valueMap["test_response"].asString();
        CCLOG("Response sent from native: %s", response.c_str());
        
        ValueVector testVector = valueMap["fibonacci"].asValueVector();
        
        size_t vectorSize = testVector.size();
        for (int i = 0; i < vectorSize; i++) {
            CCLOG("Vector value #%d: %d", i, testVector.at(i).asInt());
        }
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

HelloWorld::~HelloWorld()
{
    NDKHelper::removeSelectorsInGroup("HelloWorldSelectors");
}
