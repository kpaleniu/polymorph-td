#ifndef WINDOW_COCOA_IMPL_HPP_
#define WINDOW_COCOA_IMPL_HPP_

#import <NSWindow.h>

namespace sys {

struct WindowImpl {
	WindowImpl();

	NSWindow * const _window;
};

}

#endif /* WINDOW_COCOA_IMPL_HPP_ */
