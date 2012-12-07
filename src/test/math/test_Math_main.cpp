
#include "math/Matrix.hpp"
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{
	using namespace math;

	Matrix4x4_r m44(1.0f);

	cout << m44;

	return 0;
}
