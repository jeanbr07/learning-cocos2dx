//
//  SpaceVikingXAppController.h
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-09.
//  Copyright Ferocious Apps 2013. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

