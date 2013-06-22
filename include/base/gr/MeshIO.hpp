#ifndef GR_MESH_IO_HPP_
#define GR_MESH_IO_HPP_

#include <io/IOException.hpp>

namespace io {

class OutputStream;
class InputStream;

}

namespace gr {

class Mesh;
class TextureManager;

PM_MAKE_EXCEPTION_CLASS(MeshFileFormatException, io::IOException);

class MeshIO
{
public:
	static void writeMesh(io::OutputStream& ostream,
						  const Mesh& mesh, 
						  bool outputBigEndian=false);
	
	static Mesh readMesh(io::InputStream& istream, 
						 const TextureManager& textureManager,
						 bool inputBigEndian=false);
	
private:
	MeshIO() {} // Class for static use only.
};

}

#endif