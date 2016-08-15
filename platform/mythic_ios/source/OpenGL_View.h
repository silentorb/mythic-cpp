//
//  OpenGL_View.h
//  mythic-ios
//
//  Created by Chris Johnson on 1/1/16.
//  Copyright © 2016 Chris Johnson. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

@interface OpenGL_View : UIView<UIKeyInput> {
    CAEAGLLayer* _eagl_layer;
    EAGLContext* _context;
    GLuint _color_render_buffer;
    
@public
    GLuint framebuffer;
    GLuint sample_framebuffer, color_buffer;
}

@end