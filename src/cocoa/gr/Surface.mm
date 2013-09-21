#include <Surface.hpp>
#include <Cocoa/Cocoa.h>

namespace gr {
    
@interface OpenGLSurface : NSOpenGLView
{
    CVDisplayLinkRef displayLink;
    IRenderer* renderer;
}

- (void) setRenderer: (IRenderer*) gr;

@end
    
@implementation OpenGLSurface

- (void) setRenderer: (IRenderer*) gr
{
    renderer = gr;
}

- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime
{
    /* TODO */
    
    
    [self setNeedsDisplay:YES];
    
    return kCVReturnSuccess;
}

// This is the renderer output callback function
static CVReturn DLCallback(CVDisplayLinkRef displayLink,
                                      const CVTimeStamp *inNow,
                                      const CVTimeStamp *inOutputTime,
                                      CVOptionFlags flagsIn,
                                      CVOptionFlags *flagsOut,
                                      void *displayLinkContext)
{
    @autoreleasepool {
        GraphicsOpenGLView *view = (__bridge GraphicsOpenGLView*)displayLinkContext;
        CGLContextObj context = (CGLContextObj)[[view openGLContext] CGLContextObj];
        
        [[view openGLContext] makeCurrentContext];
        CGLLockContext(context); // This is needed because this isn't running on the main thread.
        
        CVReturn result = [view getFrameForTime:inOutputTime];
        
        CGLUnlockContext(context);
        CGLFlushDrawable(context); // This does glFlush() for you.
        
        return result;
    }
}


- (void)prepareOpenGL
{
    [super prepareOpenGL];
    
    // Synchronize buffer swaps with vertical refresh rate
    GLint swapInt = 1;
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
    // Create a display link capable of being used with all active displays
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
    
    // Set the renderer output callback function
    CVDisplayLinkSetOutputCallback(displayLink, &CLCallback, (__bridge void*)self);
    
    // Set the display link for the current renderer
    CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat] CGLPixelFormatObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
    
    // Activate the display link
    CVDisplayLinkStart(displayLink);
}

- (void)dealloc
{
    // Release the display link
    CVDisplayLinkRelease(displayLink);
    
    [super dealloc];
}

@end
    
class Surface::Impl
{
    OpenGLSurface* _surface;
    
public:
    Impl(void* windowHandle)
    {
        NSRect contentSize = NSMakeRect(rect.getTop(), rect.getLeft(),
                                        rect.getWidth(), rect.getHeight());
        
        GLuint pixelFormatAttributes[] =
        {
            NSOpenGLPFAWindow,         // choose among pixelformats capable of rendering to windows
            NSOpenGLPFAAccelerated,    // require hardware-accelerated pixelformat
            NSOpenGLPFADoubleBuffer,   // require double-buffered pixelformat
            NSOpenGLPFAColorSize, 24,  // require 24 bits for color-channels
            NSOpenGLPFAAlphaSize, 8,   // require an 8-bit alpha channel
            NSOpenGLPFADepthSize, 24,  // require a 24-bit depth buffer
            NSOpenGLPFAMinimumPolicy,  // select a pixelformat which meets or exceeds these requirements
            0
        };
        
        _surface = [[OpenGLSurface alloc]
                            initWithFrame: contentSize];
        
        NSWindow* window = (NSWindow*)windowHandle;
        _view = [[GraphicsOpenGLView alloc]
                    initWithFrame: [[window contentView] frame]
                    pixelFormat: [[NSOpenGLPixelFormat alloc] initWithAttributes: pixelFormatAttributes] autorelease];
        
        [_view setAutoresizingMask: NSViewWidthSizable | NSViewHeightSizable ];
    }
    
    ~Impl()
    {
        [_surface dealloc];
    }
    
    void* handle()
    {
        return _surface;
    }
};
    
Surface::Surface(void* windowHandle) :
    _impl(new SurfaceImpl())
{
}

Surface::~Surface()
{
}

void* Surface::nativeHandle() const
{
    return _impl->handle();
}

}