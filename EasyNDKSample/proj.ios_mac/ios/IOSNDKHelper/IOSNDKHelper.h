//
//  IOSNDKHelper.h
//  EasyNDK-for-cocos2dx
//
//  Created by Amir Ali Jiwani on 23/02/2013.
//
//

#ifndef __EasyNDK_for_cocos2dx__IOSNDKHelper__
#define __EasyNDK_for_cocos2dx__IOSNDKHelper__

#import "IOSNDKHelper-C-Interface.h"

@interface IOSNDKHelper : NSObject

+ (void)setNDKReceiver:(NSObject *)receiver;
+ (void)sendMessage:(NSString *)methodName withParameters:(NSDictionary *)parameters;

@end

#endif /* defined(__EasyNDK_for_cocos2dx__IOSNDKHelper__) */