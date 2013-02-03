/**
 * @file main.mm
 *
 * Main entry point for OSX and iOS(?) builds
 */

#import <Cocoa/Cocoa.h>

#include "game/Game.hpp"

#include "sys/UISystem.hpp"
#include "sys/GraphicsSystem.hpp"

#include "Debug.hpp"

@interface AppDelegate : NSObject
{
    sys::Window* window;
}
@end

@implementation AppDelegate

-(id) init
{
    if ( self = [super init] )
    {
        sys::Window::ConstructionData data = { self, { 10, 10, 800, 600 }};
        window = new sys::Window(data)
    }
    return self;
}

-(void) applicationWillFinishLaunching : (NSNotification*) notification
{
    
    window->applicationWillFinishLaunching();
}

-(void) applicationDidFinishLaunching : (NSNotification*) notification
{
    
    window->applicationDidFinishLaunching();
}

-(void) dealloc
{
    delete window;
    [super dealloc];
}

@end

int main(int argc, char *argv[])
{
    // create an autorelease pool
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    // make sure the application singleton has been instantiated
    NSApplication * application = [NSApplication sharedApplication];
    
    // instantiate our application delegate
    AppDelegate * applicationDelegate = [[[AppDelegate alloc] init] autorelease];
    
    // assign our delegate to the NSApplication
    [application setDelegate:applicationDelegate];
    
    // call the run method of our application
    [application run];
    
    // drain the autorelease pool
    [pool drain];
    
    // execution never gets here ..
    return 0;
}