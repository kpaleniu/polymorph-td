
#include "math/Matrix.hpp"
#include "math/Transform.hpp"
#include "math/Projection.hpp"

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

		Vector4_r vec4( array<float, 4>{{0,0,0,1}} );
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

void testTransform()
{
	cout << "============== 3 ==============" << endl;
	{
		//Vector3_r vec(array<float, 3>{0,2,0});
		Matrix<real_t, 3u, 1u, false> vec(array<float, 3>{{0,2,0}});

		auto trans1 = Transform<real_t>::identity();
		auto trans2 = Transform<real_t>::translate(vec);

		auto trans3 = trans2 * trans1;
		auto trans4 = Transform<real_t>::translate(Vector3_r(array<float, 3>{{1.0f,1.0f,1.0f}}))
					  * Transform<real_t>::rotateAxis(Vector3_r(array<float, 3>{{0,0,1}}), 1.0f)
					  * Transform<real_t>::scale(2.0f);

		cout << trans3 << trans4;

		Matrix<real_t, 3u, 1u, false> vec2(array<float, 3>{{1,1,1}});

		cout << "Before translation: " << vec2 << endl;
		cout << "After translation: " << (trans2 * vec2) << endl;
	}
}

void testProjection()
{
	cout << "============== 4 ==============" << endl;
	{
		auto proj1 = Projection<real_t>::ortho(-1, 1, -1, 1, 1, -1);
	}
}

int main(int argc, char* argv[])
{
	testMatrix();
	testMapMat();
	testTransform();
	testProjection();

	return 0;
}
