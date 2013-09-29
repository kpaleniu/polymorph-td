#pragma once

#include <io/IOException.hpp>
#include <gr/TextureManager.hpp>

namespace polymorph { namespace io {

class OutputStream;
class InputStream;

} }

namespace polymorph { namespace gr {

class Mesh;

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

} }