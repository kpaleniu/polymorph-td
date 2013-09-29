#pragma once

#include "gr/Texture.hpp"
#include <resource/ResourceManager.hpp>

namespace polymorph { namespace gr {

/**
 * Texture manager type.
 *
 * NOTE: Textures should only be constructed on the 
 *       graphics thread (i.e. in GraphicsSystemRunner).
 */
typedef resource::ResourceManager<Texture> TextureManager;

} }
