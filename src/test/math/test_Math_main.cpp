
#include "math/Matrix.hpp"
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{
	using namespace math;

	Matrix4x4_r m44(1.0f);

	cout << m44;
	m44 /= 2.0f;
	cout << m44;
	m44 *= 2.0f;
	cout << m44;

	Vector4_r vec4(array<float, 4>{0,0,0,1});
	cout << vec4;
	Vector4_r prod = m44 * vec4;
	cout << prod;


	return 0;
}
