/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "RootViewController.h"
#import "cocos2d.h"
#import "CCEAGLView.h"
#import "IOSNDKHelper.h"

@implementation RootViewController

// The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
        
        /* Let the helper know that this class wants to receive data from your game */
        [IOSNDKHelper setNDKReceiver:self];
    }
    
    return self;
}

/*
 // Implement loadView to create a view hierarchy programmatically, without using a nib.
 - (void)loadView {
 }
 */

/*
 // Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
 - (void)viewDidLoad {
 [super viewDidLoad];
 }
 
 */
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate
{
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];
    
    cocos2d::GLView *glview = cocos2d::Director::getInstance()->getOpenGLView();
    
    if (glview)
    {
        CCEAGLView *eaglview = (CCEAGLView*) glview->getEAGLView();
        
        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

/* Your method must have this NSObject* parameter */
- (void)nativeTestMethod:(NSObject *)parametersObject
{
    NSDictionary *parameters = (NSDictionary *)parametersObject;
    
    if (parameters != nil) {
        NSString *messageFromGame = (NSString *)[parameters objectForKey:@"test_message"];
        double pi = [[parameters objectForKey:@"test_double"] doubleValue];
        
        NSLog(@"Message received from game: %@", messageFromGame);
        NSLog(@"Value of test double: %f", pi);
        
        /* Let's send a message back to the game */
        NSMutableArray *numbersArray = [[NSMutableArray alloc] init];
        [numbersArray addObject:[NSNumber numberWithInt:1]];
        [numbersArray addObject:[NSNumber numberWithInt:1]];
        [numbersArray addObject:[NSNumber numberWithInt:2]];
        [numbersArray addObject:[NSNumber numberWithInt:3]];
        [numbersArray addObject:[NSNumber numberWithInt:5]];
        [numbersArray addObject:[NSNumber numberWithInt:8]];
        
        NSDictionary *parameters = [[NSDictionary alloc] initWithObjectsAndKeys:
                                    @"Greetings from iOS!", @"test_response",
                                    numbersArray, @"fibonacci",
                                    nil];
        
        // Send C++ a message with parameters
        // C++ will receive this message only if the selector list has a method
        // of the same name as specified - in this case, "gameTestMethod"
        [IOSNDKHelper sendMessage:@"gameTestMethod" withParameters:parameters];
    }
}

- (void)dealloc
{
    [super dealloc];
}

@end
