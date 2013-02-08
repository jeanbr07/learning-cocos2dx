//
//  HelloXAppController.h
//  HelloX
//
//  Created by Greg Heo on 2013-02-05.
//  Copyright Ferocious Apps 2013. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate>

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

