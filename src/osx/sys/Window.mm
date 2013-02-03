#include "sys/Window.hpp"
#import <Cocoa/Cocoa.h>

namespace sys {
    
struct AppDelegate;

struct WindowImpl
{
    NSWindow*       window;
    NSView*         view;
    AppDelegate*    appDelegate;
};

Window::Window(const ConstructionData& data)
    : _impl(new WindowImpl())
{
    _impl->app = data.app;
    
    Rect& r = data.rect;
    NSRect contentSize = NSMakeRect(r.top, r.left, r.w, r.h);
    
    _impl->window = [[NSWindow alloc]
               initWithContentRect: contentSize
               styleMask: NSTitledWindowMask
               backing: NSBackingStoreBuffered
               defer: YES ];
    _impl->view = [[NSOpenGLView alloc] initWithFrame: contentSize];
}

Window::~Window()
{
    if (_impl)
    {
        [_impl->window release];
        [_impl->view release];
        delete _impl;
    }
    /* App pointer should obviously not be released here */
}

bool Window::show(bool show)
{
    if (show)
        [_impl->window orderFront: _impl->appDelegate];
    else
        [_impl->window orderOut: _impl->appDelegate];
}

void Window::applicationWillFinishLaunching()
{
    /* Attach view to the window */
    [_impl->window setContentView: YES];
}

void Window::applicationDidFinishLaunching()
{
    /* Make the window visible */
    [_impl->window makeKeyAndOrderFront: _impl->appDelegate];
}

} /* namespace sys */