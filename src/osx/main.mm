/**
 * @file main.mm
 *
 * Main entry point for OSX and iOS(?) builds
 */

#import <Cocoa/Cocoa.h>
#include <sys/WorldSystem.hpp>

int main(int argc, char *argv[])
{
    return NSApplicationMain(argc, (const char**)argv);
}