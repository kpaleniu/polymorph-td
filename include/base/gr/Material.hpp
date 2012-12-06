/**
 * @file Material.hpp
 *
 */

#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

namespace gr {

class Shader;
class Texture;

class Material
{
public:
	Material(Shader& shader, Texture& tex);

	Shader& shader();
	Texture& texture();

	// TODO
	void activeate(){};
	void deactivate(){};
	//

private:
	Shader& _shader;
	Texture& _tex;
};

}


#endif /* MATERIAL_HPP_ */
