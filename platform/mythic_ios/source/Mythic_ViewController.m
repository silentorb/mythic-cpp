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

//@interface Custom_Gesture_Recognizer : UIGestureRecognizer {
//    Mythic_ViewController *controller;
//}
//@end
//
//@implementation Custom_Gesture_Recognizer
//
//-(id)initWithController:(Mythic_ViewController *)view_controller
//{
//    self = [super init];
//    if (self) {
//        self->controller = view_controller;
//    }
//    return self;
//}
//
//-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
//[controller touch
//}
//
//-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event{
//    
//}
//
//-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
//    
//}
//
//@end

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
 
//- (void)touch_down:(Custom_Gesture_Recognizer *)recognizer {
//    CGPoint location = [recognizer locationInView:self.view];
//    input_touch_down(location.x * self.view.contentScaleFactor, location.y * self.view.contentScaleFactor);
//}
//
//- (void)touch_move:(Custom_Gesture_Recognizer *)recognizer {
//    CGPoint location = [recognizer locationInView:self.view];
//    input_touch_move(location.x * self.view.contentScaleFactor, location.y * self.view.contentScaleFactor);
//}
//
//- (void)touch_up:(Custom_Gesture_Recognizer *)recognizer {
//    CGPoint location = [recognizer locationInView:self.view];
//    input_touch_up(location.x * self.view.contentScaleFactor, location.y * self.view.contentScaleFactor);
//}

-(BOOL)prefersStatusBarHidden{
    return YES;
}

@end
