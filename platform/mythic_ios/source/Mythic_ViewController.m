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
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
