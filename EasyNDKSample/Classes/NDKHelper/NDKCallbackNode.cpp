//
//  NDKCallbackNode.cpp
//  EasyNDK-for-cocos2dx
//
//  Created by Amir Ali Jiwani on 23/02/2013.
//  Updated by Alfonso Cejudo March, 2014.
//
//

#include "NDKCallbackNode.h"

USING_NS_CC;

NDKCallbackNode::NDKCallbackNode(const char *groupName, const char *name, FuncNV sel, Node *target)
{
    this->groupName = groupName;
    this->name = name;
    this->sel = sel;
    this->target = target;
}

std::string NDKCallbackNode::getGroup()
{
    return this->groupName;
}

std::string NDKCallbackNode::getName()
{
    return this->name;
}

FuncNV NDKCallbackNode::getSelector()
{
    return this->sel;
}

Node *NDKCallbackNode::getTarget()
{
    return this->target;
}
