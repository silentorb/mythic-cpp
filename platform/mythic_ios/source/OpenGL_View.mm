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
#include "lookinglass/Graphic_Options.h"
#include <glow.h>

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
    lookinglass::Graphic_Options graphic_options(0, 0, 4);
    mythic = new Mythic_iOS(_context, self, graphic_options);
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

    int multisample = 4;
    
    color_buffer = 0;
    GLuint _depthRenderBuffer = 0;
    GLuint _stencilBuffer = 0;
    int width = self.frame.size.width * self.contentScaleFactor;
    int height = self.frame.size.height * self.contentScaleFactor;
    
    glGenRenderbuffers(1, &color_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, color_buffer);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eagl_layer];
    
    glGenRenderbuffers(1, &_depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, width, height);
    
//    glGenRenderbuffers(1, &_stencilBuffer);
//    glBindRenderbuffer(GL_RENDERBUFFER, _stencilBuffer);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
    
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, color_buffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
    
    if (multisample) {
        GLuint sampleColorRenderbuffer, sampleDepthRenderbuffer;
        glGenFramebuffers(1, &sample_framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, sample_framebuffer);
        
        glGenRenderbuffers(1, &sampleColorRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, sampleColorRenderbuffer);
        glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, 4, GL_RGBA8_OES, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, sampleColorRenderbuffer);
        
        glGenRenderbuffers(1, &sampleDepthRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, sampleDepthRenderbuffer);
        glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8_OES, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, sampleDepthRenderbuffer);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, sampleDepthRenderbuffer);
        
        glow::set_default_framebuffer(sample_framebuffer);
    }
    else {
        glBindRenderbuffer(GL_RENDERBUFFER, color_buffer);
        glow::set_default_framebuffer(framebuffer);
    }
}

- (void)setup_frame_buffer {

}

- (void)render:(CADisplayLink*)link {
    CFTimeInterval current_time = [link timestamp];
    if (previous_time == 0) {
        previous_time = current_time;
    }
    else {
        CFTimeInterval delta_time = current_time - previous_time;
        float delta = (float)delta_time;
        previous_time = current_time;
        mythic->update(delta);
    }
}

- (void)setup_display_link {
    link = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
    [link addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        previous_time = 0;
        self.contentScaleFactor = [[UIScreen mainScreen] scale];
        [self setup_layer];
        [self setup_context];
        [self setup_render_buffer];
        [self setup_frame_buffer];
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

-(void)will_resign_active {
    link.paused = true;
    //Call glFinish() here if any OpenGL resources are ever manually deleted through this function.
}

-(void)will_enter_background {
    
}

-(void)will_enter_foreground {
    
}

-(void)did_become_active {
    link.paused = false;
}
@end
