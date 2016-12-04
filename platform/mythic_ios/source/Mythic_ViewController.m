//
//  Mythic_ViewController.m
//  mythic-ios
//
//  Created by Chris Johnson on 1/2/16.
//  Copyright © 2016 Chris Johnson. All rights reserved.
//

#import "Mythic_ViewController.h"
#import "OpenGL_View.h"
#import "UIKit/UIGestureRecognizerSubclass.h"

@interface Mythic_ViewController ()

@end

@implementation Mythic_ViewController

- (void)loadView
{
    CGRect screen_bounds = [[UIScreen mainScreen] bounds];
    self.view = [[OpenGL_View alloc] initWithFrame:screen_bounds];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    UITapGestureRecognizer *single_finger_tap =
    [[UITapGestureRecognizer alloc] initWithTarget:self
                                            action:@selector(on_single_tap:)];
//
//    Custom_Gesture_Recognizer * gesture =
//    [[Custom_Gesture_Recognizer alloc] initWithTarget:self
//                                            action:@selector(on_gesture:)];
    
    [self.view addGestureRecognizer:single_finger_tap];
    [single_finger_tap release];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)on_single_tap:(UITapGestureRecognizer *)recognizer {
    CGPoint location = [recognizer locationInView:self.view];
    input_single_tap(location.x * self.view.contentScaleFactor, location.y * self.view.contentScaleFactor);
}

 -(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
     for(UITouch* touch in touches) {
         CGPoint location = [touch locationInView:self.view];
         input_touch_down(location.x * self.view.contentScaleFactor, location.y * self.view.contentScaleFactor);
     }
     
     [super touchesBegan:touches withEvent:event];
 }
 
 -(void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
     for(UITouch* touch in touches) {
         CGPoint location = [touch locationInView:self.view];
         input_touch_move(location.x * self.view.contentScaleFactor, location.y * self.view.contentScaleFactor);
     }
     [super touchesMoved:touches withEvent:event];
 }
 
 -(void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
     for(UITouch* touch in touches) {
         CGPoint location = [touch locationInView:self.view];
         input_touch_up(location.x * self.view.contentScaleFactor, location.y * self.view.contentScaleFactor);
     }
     [super touchesEnded:touches withEvent:event];
 }

-(BOOL)prefersStatusBarHidden{
    return YES;
}

-(UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return UIInterfaceOrientationLandscapeLeft | UIInterfaceOrientationMaskLandscapeRight;
}

-(void)will_resign_active {
    [self.view will_resign_active];
}

-(void)will_enter_background {
        [self.view will_enter_background];
}

-(void)will_enter_foreground {
        [self.view will_enter_foreground];
}

-(void)did_become_active {
        [self.view did_become_active];
}

@end
