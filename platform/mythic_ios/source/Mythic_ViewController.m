//
//  Mythic_ViewController.m
//  mythic-ios
//
//  Created by Chris Johnson on 1/2/16.
//  Copyright © 2016 Chris Johnson. All rights reserved.
//

#import "Mythic_ViewController.h"
#import "OpenGL_View.h"


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
    
    [self.view addGestureRecognizer:single_finger_tap];
    [single_finger_tap release];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)on_single_tap:(UITapGestureRecognizer *)recognizer {
    CGPoint location = [recognizer locationInView:self.view];
    input_single_tap(location.x, location.y);
}

@end
