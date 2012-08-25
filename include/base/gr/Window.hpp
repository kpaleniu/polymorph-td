/**
 * @file Window.hpp
 *
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

namespace gr
{
	class Window
	{
	public:
		struct ConstructionData;
		class PIMPL;

	public:
		Window(ConstructionData &data);
		~Window();

	private:
		PIMPL *_pimpl;
	};
}


#endif /* WINDOW_HPP_ */
