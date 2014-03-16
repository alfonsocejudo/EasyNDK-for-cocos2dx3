//
//  CallFuncNV.cpp
//  MechaDragoon
//
//  Created by Alfonso Cejudo on 3/15/14.
//
//

#include "CallFuncNV.h"

USING_NS_CC;

CallFuncNV *CallFuncNV::create(const std::function<void(Node *, Value)> &func)
{
    auto ret = new CallFuncNV();
    
    if (ret && ret->initWithFunction(func)) {
        ret->autorelease();
        
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    
    return nullptr;
}

void CallFuncNV::setValue(Value value)
{
    _value = value;
}

void CallFuncNV::execute() {
    if (_functionNV) {
        _functionNV(_target, _value);
    }
}

bool CallFuncNV::initWithFunction(const std::function<void(Node *, Value)> &func)
{
    _functionNV = func;
    
    return true;
}

CallFuncNV *CallFuncNV::clone() const
{
	// no copy constructor
	auto a = new CallFuncNV();
    
    if (_functionNV) {
        a->initWithFunction(_functionNV);
    }
    
	a->autorelease();
    
	return a;
}
