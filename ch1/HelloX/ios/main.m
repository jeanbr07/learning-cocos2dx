//
//  main.m
//  HelloX
//
//  Created by Greg Heo on 2013-02-05.
//  Copyright Ferocious Apps 2013. All rights reserved.
//

#import <UIKit/UIKit.h>

int main(int argc, char *argv[]) {
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, @"AppController");
    [pool release];
    return retVal;
}
