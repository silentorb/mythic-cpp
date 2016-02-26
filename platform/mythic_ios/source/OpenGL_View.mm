//
//  OpenGL_View.m
//  mythic-ios
//
//  Created by Chris Johnson on 1/1/16.
//  Copyright © 2016 Chris Johnson. All rights reserved.
//

#import "OpenGL_View.h"
#import "Mythic_iOS.h"
#import "Gamepad_Manager.h"

@interface OpenGL_View() {    
    Mythic_iOS *mythic;
    Gamepad_Manager* gamepad_manager;
    UIView                  *input_view;
}
@end

@implementation OpenGL_View


+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (void)initialize_mythic {
    mythic = new Mythic_iOS(_context);
    gamepad_manager = [[Gamepad_Manager alloc] init];
    input_view = [[UIView alloc] initWithFrame:CGRectZero];
}

- (void)setup_layer {
    _eagl_layer = (CAEAGLLayer*) self.layer;
    _eagl_layer.opaque = YES;
}

- (void)setup_context {
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    _context = [[EAGLContext alloc] initWithAPI:api];
    if (!_context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext:_context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
}

- (void)setup_render_buffer {
    glGenRenderbuffers(1, &_color_render_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _color_render_buffer);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eagl_layer];
}

- (void)setup_frame_buffer {
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER, _color_render_buffer);
}

- (void)render:(CADisplayLink*)link {
//     glClear(GL_COLOR_BUFFER_BIT);
//   bool result = [_context presentRenderbuffer:GL_RENDERBUFFER];
    mythic->update();
    
}

- (void)setup_display_link {
    CADisplayLink* link = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
    [link addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setup_layer];
        [self setup_context];
        [self setup_render_buffer];
        [self setup_frame_buffer];
        
        glClearColor(0, 1, 1, 1);
      glViewport(0, 0, self.frame.size.width, self.frame.size.height);
        
        [self initialize_mythic];
        [self setup_display_link];
         [self becomeFirstResponder];
    }
    return self;
}

- (void)dealloc
{
    _context = nil;
//    delete mythic;
}


- (void)didEnterBackground {
        [self resignFirstResponder];
}

- (void)didBecomeActive {
        [self becomeFirstResponder];
}

- (BOOL)canBecomeFirstResponder {
    return YES;
}

- (UIView*) inputView {
    return input_view;
}

- (void)insertText:(NSString *)text {
    NSLog(@"Keypress %@", text);
}

- (void)deleteBackward {
    
}

- (BOOL)hasText {
    return false;
}

@end
