/**
 * @file Texture.hpp
 *
 */

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

namespace gr {

class Texture
{
public:
	friend class TextureManager;

private:
	Texture()
	{
	}
	~Texture()
	{
	}

	Texture(const Texture &)
	{
	}
	Texture &operator=(const Texture &)
	{
	}
};

}

#endif /* TEXTURE_HPP_ */
