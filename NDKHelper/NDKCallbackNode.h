//
//  NDKCallbackNode.h
//  EasyNDK-for-cocos2dx
//
//  Created by Amir Ali Jiwani on 23/02/2013.
//  Updated by Alfonso Cejudo March, 2014.
//
//

#ifndef __EasyNDK_for_cocos2dx__NDKCallbackNode__
#define __EasyNDK_for_cocos2dx__NDKCallbackNode__

#include "cocos2d.h"

typedef std::function<void(cocos2d::Node *, cocos2d::Value)> FuncNV;

class NDKCallbackNode
{
public:
    NDKCallbackNode(const char *groupName, const char *name, FuncNV sel, cocos2d::Node *target);
    std::string getGroup();
    std::string getName();
    FuncNV getSelector();
    cocos2d::Node *getTarget();
    
private:
    std::string groupName;
    std::string name;
    FuncNV sel;
    cocos2d::Node *target;
};

#endif /* defined(__EasyNDK_for_cocos2dx__NDKCallbackNode__) */
