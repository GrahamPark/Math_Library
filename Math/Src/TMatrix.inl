template <typename T, int rows, int cols>
TMatrix<T, rows, cols>::TMatrix()
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			data[i][j] = 0;
		}
	}
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::CreateMatrix(float _11, float _12, float _13,
	float _21, float _22, float _23,
	float _31, float _32, float _33)
{
	TMatrix<T, rows, cols> retMatrix;

	retMatrix.data[0][0] = _11;
	retMatrix.data[0][1] = _12;
	retMatrix.data[0][2] = _13;

	retMatrix.data[1][0] = _21;
	retMatrix.data[1][1] = _22;
	retMatrix.data[1][2] = _23;

	retMatrix.data[2][0] = _31;
	retMatrix.data[2][1] = _32;
	retMatrix.data[2][2] = _33;

	return retMatrix;
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::CreateMatrix(float _11, float _12, float _13, float _14,
	float _21, float _22, float _23, float _24,
	float _31, float _32, float _33, float _34,
	float _41, float _42, float _43, float _44)
{
	TMatrix<T, rows, cols> retMatrix;

	retMatrix.data[0][0] = _11;
	retMatrix.data[0][1] = _12;
	retMatrix.data[0][2] = _13;
	retMatrix.data[0][3] = _14;

	retMatrix.data[1][0] = _21;
	retMatrix.data[1][1] = _22;
	retMatrix.data[1][2] = _23;
	retMatrix.data[1][3] = _24;

	retMatrix.data[2][0] = _31;
	retMatrix.data[2][1] = _32;
	retMatrix.data[2][2] = _33;
	retMatrix.data[2][3] = _34;

	retMatrix.data[3][0] = _41;
	retMatrix.data[3][1] = _42;
	retMatrix.data[3][2] = _43;
	retMatrix.data[3][3] = _44;

	return retMatrix;
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::Zero()
{
	TMatrix<T, rows, cols> retMatrix;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			retMatrix.data[i][j] = 0;
		}
	}

	return retMatrix;
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::Identity()
{
	TMatrix<T, rows, cols> retMatrix;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (i == j)
			{
				retMatrix.data[i][j] = 1;
			}
			else
			{
				retMatrix.data[i][j] = 0;
			}
		}
	}

	return retMatrix;
}

template <typename T, int rows, int cols>
float TMatrix<T, rows, cols>::Determinant(const TMatrix& m)
{
	T det = 0;
	det = (m.data[0][0] * (m.data[1][1] * (m.data[2][2] * m.data[3][3] - (m.data[3][2] * m.data[2][3])) - m.data[1][2] * (m.data[2][1] * m.data[3][3] - (m.data[3][1] * m.data[2][3])) + m.data[1][3] * (m.data[2][1] * m.data[3][2] - (m.data[3][1] * m.data[2][2]))));
	det -= (m.data[0][1] * (m.data[1][0] * (m.data[2][2] * m.data[3][3] - (m.data[3][2] * m.data[2][3])) - m.data[1][2] * (m.data[2][0] * m.data[3][3] - (m.data[3][0] * m.data[2][3])) + m.data[1][3] * (m.data[2][0] * m.data[3][2] - (m.data[3][0] * m.data[2][2]))));
	det += (m.data[0][2] * (m.data[1][0] * (m.data[2][1] * m.data[3][3] - (m.data[3][1] * m.data[2][3])) - m.data[1][1] * (m.data[2][0] * m.data[3][3] - (m.data[3][0] * m.data[2][3])) + m.data[1][3] * (m.data[2][0] * m.data[3][1] - (m.data[3][0] * m.data[2][1]))));
	det -= (m.data[0][3] * (m.data[1][0] * (m.data[2][1] * m.data[3][2] - (m.data[3][1] * m.data[2][2])) - m.data[1][1] * (m.data[2][0] * m.data[3][2] - (m.data[3][0] * m.data[2][2])) + m.data[1][2] * (m.data[2][0] * m.data[3][1] - (m.data[3][0] * m.data[2][1]))));
	return det;
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::Adjoint(const TMatrix& m)
{
	return CreateMatrix
	(
		(m.data[1][1] * ((m.data[2][2] * m.data[3][3]) - (m.data[3][2] * m.data[2][3])) - m.data[1][2] * ((m.data[2][1] * m.data[3][3]) - (m.data[3][1] * m.data[2][3])) + m.data[1][3] * ((m.data[2][1] * m.data[3][2]) - (m.data[3][1] * m.data[2][2]))),
		-(m.data[0][1] * ((m.data[2][2] * m.data[3][3]) - (m.data[3][2] * m.data[2][3])) - m.data[0][2] * ((m.data[2][1] * m.data[3][3]) - (m.data[3][1] * m.data[2][3])) + m.data[0][3] * ((m.data[2][1] * m.data[3][2]) - (m.data[3][1] * m.data[2][2]))),
		(m.data[0][1] * ((m.data[1][2] * m.data[3][3]) - (m.data[3][2] * m.data[1][3])) - m.data[0][2] * ((m.data[1][1] * m.data[3][3]) - (m.data[3][1] * m.data[1][3])) + m.data[0][3] * ((m.data[1][1] * m.data[3][2]) - (m.data[3][1] * m.data[1][2]))),
		-(m.data[0][1] * ((m.data[1][2] * m.data[2][3]) - (m.data[2][2] * m.data[1][3])) - m.data[0][2] * ((m.data[1][1] * m.data[2][3]) - (m.data[2][1] * m.data[1][3])) + m.data[0][3] * ((m.data[1][1] * m.data[2][2]) - (m.data[2][1] * m.data[1][2]))),

		-(m.data[1][0] * ((m.data[2][2] * m.data[3][3]) - (m.data[3][2] * m.data[2][3])) - m.data[2][0] * ((m.data[1][2] * m.data[3][3]) - (m.data[1][3] * m.data[3][2])) + m.data[3][0] * ((m.data[1][2] * m.data[2][3]) - (m.data[1][3] * m.data[2][2]))),
		(m.data[0][0] * ((m.data[2][2] * m.data[3][3]) - (m.data[3][2] * m.data[2][3])) - m.data[0][2] * ((m.data[2][0] * m.data[3][3]) - (m.data[3][0] * m.data[2][3])) + m.data[0][3] * ((m.data[2][1] * m.data[3][2]) - (m.data[3][0] * m.data[2][2]))),
		-(m.data[0][0] * ((m.data[1][2] * m.data[3][3]) - (m.data[3][2] * m.data[1][3])) - m.data[0][2] * ((m.data[1][0] * m.data[3][3]) - (m.data[3][0] * m.data[1][3])) + m.data[0][3] * ((m.data[1][0] * m.data[3][2]) - (m.data[3][0] * m.data[1][2]))),
		(m.data[0][0] * ((m.data[1][2] * m.data[2][3]) - (m.data[2][2] * m.data[1][3])) - m.data[0][2] * ((m.data[1][0] * m.data[2][3]) - (m.data[2][0] * m.data[1][3])) + m.data[0][3] * ((m.data[1][0] * m.data[2][2]) - (m.data[2][0] * m.data[1][2]))),

		(m.data[1][0] * ((m.data[2][1] * m.data[3][3]) - (m.data[3][1] * m.data[2][3])) - m.data[2][0] * ((m.data[1][1] * m.data[3][3]) - (m.data[3][1] * m.data[1][3])) + m.data[3][0] * ((m.data[1][1] * m.data[2][3]) - (m.data[2][1] * m.data[1][3]))),
		-(m.data[0][0] * ((m.data[2][1] * m.data[3][3]) - (m.data[3][1] * m.data[2][3])) - m.data[2][0] * ((m.data[0][1] * m.data[3][3]) - (m.data[3][1] * m.data[0][3])) + m.data[3][0] * ((m.data[0][1] * m.data[2][3]) - (m.data[2][1] * m.data[0][3]))),
		(m.data[0][0] * ((m.data[1][1] * m.data[3][3]) - (m.data[3][1] * m.data[1][3])) - m.data[0][1] * ((m.data[1][0] * m.data[3][3]) - (m.data[3][0] * m.data[1][3])) + m.data[0][3] * ((m.data[1][0] * m.data[3][1]) - (m.data[3][0] * m.data[1][1]))),
		-(m.data[0][0] * ((m.data[1][1] * m.data[2][3]) - (m.data[2][1] * m.data[1][3])) - m.data[1][0] * ((m.data[0][1] * m.data[2][3]) - (m.data[2][1] * m.data[0][3])) + m.data[2][0] * ((m.data[0][1] * m.data[1][3]) - (m.data[1][1] * m.data[0][3]))),

		-(m.data[1][0] * ((m.data[2][1] * m.data[3][2]) - (m.data[3][1] * m.data[2][2])) - m.data[2][0] * ((m.data[1][1] * m.data[3][2]) - (m.data[3][1] * m.data[1][2])) + m.data[3][0] * ((m.data[1][1] * m.data[2][2]) - (m.data[2][1] * m.data[1][2]))),
		(m.data[0][0] * ((m.data[2][1] * m.data[3][2]) - (m.data[3][1] * m.data[2][2])) - m.data[0][1] * ((m.data[2][0] * m.data[3][2]) - (m.data[3][0] * m.data[2][2])) + m.data[0][2] * ((m.data[2][0] * m.data[3][1]) - (m.data[3][0] * m.data[2][1]))),
		-(m.data[0][0] * ((m.data[1][1] * m.data[3][2]) - (m.data[3][1] * m.data[1][2])) - m.data[0][1] * ((m.data[1][0] * m.data[3][2]) - (m.data[3][0] * m.data[1][2])) + m.data[0][2] * ((m.data[1][0] * m.data[3][1]) - (m.data[3][0] * m.data[1][1]))),
		(m.data[0][0] * ((m.data[1][1] * m.data[2][2]) - (m.data[2][1] * m.data[1][2])) - m.data[0][1] * ((m.data[1][0] * m.data[2][2]) - (m.data[2][1] * m.data[1][2])) + m.data[0][2] * ((m.data[1][0] * m.data[2][1]) - (m.data[2][0] * m.data[1][1])))
	);
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::Inverse(const TMatrix& m)
{
	const float determinant = Determinant(m);
	const float invDet = 1.0f / determinant;
	return Adjoint(m) * invDet;
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::Transpose(const TMatrix& m)
{
	TMatrix<T, rows, cols> retMatrix;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			retMatrix.data[i][j] = m.data[j][i];
		}
	}

	return retMatrix;
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::RotationX(float rad)
{
	const float c = cos(rad);
	const float s = sin(rad);

	return CreateMatrix
	(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, c, s, 0.0f,
		0.0f, -s, c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::RotationY(float rad)
{
	const float c = cos(rad);
	const float s = sin(rad);

	return CreateMatrix
	(
		c, 0.0f, -s, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		s, 0.0f, c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::RotationZ(float rad)
{
	const float c = cos(rad);
	const float s = sin(rad);

	return CreateMatrix
	(
		c, s, 0.0f, 0.0f,
		-s, c, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

template <typename T, int rows, int cols>
T TMatrix<T, rows, cols>::GetValue(int row, int col) const
{
	return data[row][col];
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::operator-() const
{
	return (*this) * -1;
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::operator+(const TMatrix<T, rows, cols>& rhs) const
{
	TMatrix<T, rows, cols> retMatrix;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			retMatrix.data[i][j] = data[i][j] + rhs.data[i][j];
		}
	}

	return retMatrix;
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::operator-(const TMatrix<T, rows, cols>& rhs) const
{
	TMatrix<T, rows, cols> retMatrix;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			retMatrix.data[i][j] = data[i][j] - rhs.data[i][j];
		}
	}

	return retMatrix;
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::operator*(const TMatrix<T, rows, cols>& rhs) const
{
	TMatrix<T, rows, cols> retMatrix;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			for (int k = 0; k < cols; ++k)
			{
				retMatrix.data[i][j] += GetValue(i,k) * rhs.GetValue(k,j);
			}
		}
	}

	return retMatrix;
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::operator*(float s) const
{
	TMatrix<T, rows, cols> retMatrix;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			retMatrix.data[i][j] = data[i][j] * s;
		}
	}

	return retMatrix;
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::operator/(float s) const
{
	//assert(s != 0);//S can be 0
	TMatrix<T, rows, cols> retMatrix;
	const float inv = 1.0f / s;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			retMatrix.data[i][j] = data[i][j] * inv;
		}
	}

	return retMatrix;
}

template <typename T, int rows, int cols>
TMatrix<T, rows, cols> TMatrix<T, rows, cols>::operator+=(const TMatrix& rhs)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			data[i][j] += rhs.data[i][j];
		}
	}

	return *this;
}