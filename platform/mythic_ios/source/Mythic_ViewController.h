//
//  Mythic_ViewController.h
//  mythic-ios
//
//  Created by Chris Johnson on 1/2/16.
//  Copyright © 2016 Chris Johnson. All rights reserved.
//

#import <UIKit/UIKit.h>

void input_single_tap(int x, int y);

void input_touch_down(int x, int y);
void input_touch_move(int x, int y);
void input_touch_up(int x, int y);

@interface Mythic_ViewController : UIViewController {
    
}

-(void) will_resign_active;
-(void) will_enter_background;
-(void) will_enter_foreground;
-(void) did_become_active;
@end
