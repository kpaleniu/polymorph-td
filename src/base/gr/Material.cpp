

#include "gr/Material.hpp"
#include "gr/Shader.hpp"
#include "gr/Texture.hpp"

namespace gr {

Material::Material(Shader& shader, Texture& tex)
:	_shader(shader),
 	_tex(tex)
{
}

Shader& Material::shader()
{
	return _shader;
}

Texture& Material::texture()
{
	return _tex;
}

}
