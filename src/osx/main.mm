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

const char *TAG = "OsxMain";

@interface AppDelegate : NSObject<NSApplicationDelegate>
{
    sys::UISystem   uiSystem;
    game::Game      game;
}
@end

@implementation AppDelegate

-(id) init
{
    if ( self = [super init] )
    {
        sys::Window::ConstructionData construct_data = { this, { 64, 64, 800, 600 } };
        
        INFO_OUT(TAG, "Starting systems");
        
        try
        {
            uiSystem = sys::UISystem(winData);
            uiSystem.start();
        }
        catch (...)
        {}
    }
    return self;
}

-(void) applicationWillFinishLaunching : (NSNotification*) notification
{
    uiSystem.window().applicationWillFinishLaunching();
}

-(void) applicationDidFinishLaunching : (NSNotification*) notification
{
    uiSystem.window().applicationDidFinishLaunching();
    [self start];
}

-(void) start
{
    try
    {
        sys::GraphicsSystem& grSystem = uiSystem.waitForGraphicsSystem();
    
        game = game::Game(uiSystem, grSystem);
        try
        { theGame.enter(); }
        catch (...)
        {}
        
        uiSystem.interrupt();
        uiSystem.join();
        
        INFO_OUT(TAG, "Systems shut down");
    }
    catch(...)
    {
    }
    
    profiler::ThreadProfiler::dumpAll(std::cout);
    profiler::ThreadProfiler::shutdown();
    text::clearInterned();
}

-(void) dealloc
{
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
