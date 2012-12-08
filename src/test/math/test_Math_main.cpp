
#include "math/Matrix.hpp"
#include <iostream>

using namespace std;
using namespace math;

void testMatrix()
{
	cout << "============== 1 ==============" << endl;
	{
		array<float, 4*4> data;
		for (int i = 0; i < 4*4; ++i)
			data[i] = i;
		Matrix<real_t, 4, 4, false> m44_cm(data);
		Matrix<real_t, 4, 4, true> m44_rm(data);
		cout << m44_cm << m44_rm;

		cout << "Data cm" << endl;
		for (int i = 0; i < 4*4; ++i)
			cout << m44_cm.data()[i] << " ";
		cout << endl;

		cout << "Data rm" << endl;
		for (int i = 0; i < 4*4; ++i)
			cout << m44_rm.data()[i] << " ";
		cout << endl;
	}
	{
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
	}
}

void testMapMat()
{
	cout << "============== 2 ==============" << endl;
	{
		array<float, 4*4> data;
		for (int i = 0; i < 4*4; ++i)
			data[i] = i;

		MapMatrix4x4_r mat(data.data());
		cout << mat;
	}
}

int main(int argc, char* argv[])
{
	testMatrix();
	testMapMat();


	return 0;
}
