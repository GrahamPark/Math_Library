#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

namespace Math
{
	template <typename T, int rows, int cols>
	class MatrixData
	{
	public:
		union
		{
			T data[rows][cols];
		};
	};

	template<> class MatrixData<float, 4, 4>
	{
	public:
		union
		{
			float data[4][4];
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
		};
	};

	template <typename T, int rows, int cols>
	class TMatrix : public MatrixData<T, rows, cols>
	{
	public:
		using MatrixData<T, rows, cols>::data;

		TMatrix();

		static TMatrix CreateMatrix(float _11, float _12, float _13,
			float _21, float _22, float _23,
			float _31, float _32, float _33);

		static TMatrix CreateMatrix(float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44);

		//Static Functions
		static TMatrix Zero();
		static TMatrix Identity();

		static float Determinant(const TMatrix& m);
		static TMatrix Adjoint(const TMatrix& m);
		static TMatrix Inverse(const TMatrix& m);
		static TMatrix Transpose(const TMatrix& m);

		static TMatrix RotationX(float rad);
		static TMatrix RotationY(float rad);
		static TMatrix RotationZ(float rad);

		T GetValue(int row, int col) const;

		//operator overloading
		TMatrix operator-() const;

		TMatrix operator+(const TMatrix& rhs) const;
		TMatrix operator-(const TMatrix& rhs) const;
		TMatrix operator*(const TMatrix& rhs) const;
		TMatrix operator*(float s) const;
		TMatrix operator/(float s) const;

		TMatrix operator+=(const TMatrix& rhs);
	};

	typedef TMatrix<float, 3, 3> Matrix3;
	typedef TMatrix<float, 4, 4> Matrix4;

	typedef TMatrix<int, 3, 3> iMatrix3;
	typedef TMatrix<int, 4, 4> iMatrix4;

#include "../Src/TMatrix.inl"
}

#endif