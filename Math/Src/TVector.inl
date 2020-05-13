
template <typename T, int n>
TVector<T, n>::TVector()
{
	for (int i = 0; i < n; ++i)
	{
		data[i] = 0;
	}
}

template <typename T, int n>
TVector<T, n>::TVector(T x, T y)
{
	T inputMap[]{ x, y };

	for (int i = 0; i < 2; i++)
	{
		if (n > i)
		{
			data[i] = inputMap[i];
		}
	}
}

template <typename T, int n>
TVector<T, n>::TVector(T x, T y, T z)
{
	T inputMap[]{ x, y, z };

	for (int i = 0; i < 3; i++)
	{
		if (n > i)
		{
			data[i] = inputMap[i];
		}
	}
}

template <typename T, int n>
TVector<T, n>::TVector(T x, T y, T z, T w)
{
	T inputMap[]{ x, y, z, w };

	for (int i = 0; i < 4; i++)
	{
		if (n > i)
		{
			data[i] = inputMap[i];
		}
	}
}

template <typename T, int n>
T TVector<T, n>::Length() const
{
	T Len = 0;

	for (int i = 0; i < n; ++i)
	{
		Len += (data[i] * data[i]);
	}

	return Len;
}

template <typename T, int n>
T TVector<T, n>::LengthSq() const
{
	return sqrt(Length());
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::Normalized() const
{
	T len = LengthSq();
	TVector<T, n> returnVec;

	for (int i = 0; i < n; i++)
	{
		returnVec[i] = data[i] / len;
	}

	return returnVec;
}

template <typename T, int n>
int TVector<T, n>::GetAsArray(T* OutArray) const
{
	T arr[n];
	for (int i = 0; i < n; ++i)
	{
		arr[i] = data[i];
	}

	OutArray = static_cast<T*>(arr);

	return n;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::Zero()
{
	TVector<T, n> returnVec;

	for (int i = 0; i < n; i++)
	{
		returnVec[i] = 0;
	}

	return returnVec;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::One()
{
	TVector<T, n> returnVec;

	for (int i = 0; i < n; i++)
	{
		returnVec[i] = 1;
	}

	return returnVec;
}

template <typename T, int n>
T TVector<T, n>::Dot(const TVector<T, n>& Left, const TVector<T, n>& Right)
{
	T dot = 0;

	for (int i = 0; i < n; i++)
	{
		dot += (Left.data[i] * Right.data[i]);
	}

	return dot;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::Cross(const TVector<T, n>& Left, const TVector<T, n>& Right)
{
	TVector<T, n> outVector;

	if (n >= 3)
	{
		outVector.data[0] = (Left.data[1] * Right.data[2]) - (Left.data[2] * Right.data[1]);
		outVector.data[1] = (Left.data[2] * Right.data[0]) - (Left.data[0] * Right.data[2]);
		outVector.data[2] = (Left.data[0] * Right.data[1]) - (Left.data[1] * Right.data[0]);
	}

	return outVector;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::Proj(const TVector<T, n>& Left, const TVector<T, n>& Right)
{
	T Numerator = Dot(Left, Right);
	T Denominator = Right.LengthSq() * Right.LengthSq();

	//assert(Denominator != 0);

	return Right * (Numerator / Denominator);
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::Perp(const TVector<T, n>& Left, const TVector<T, n>& Right)
{
	return Left - Proj(Left, Right);
}

template <typename T, int n>
T& TVector<T, n>::operator[](int index)
{
	return data[index];
}

template <typename T, int n>
const T& TVector<T, n>::operator[](int index) const
{
	return data[index];
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::operator-()
{
	for (int i = 0; i < n; i++)
	{
		data[i] *= -1;
	}

	return *this;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::operator+(const TVector<T, n>& Rhs) const
{
	TVector<T, n> returnVect;

	for (int i = 0; i < n; i++)
	{
		returnVect[i] = data[i] + Rhs[i];
	}

	return returnVect;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::operator-(const TVector<T, n>& Rhs) const
{
	TVector<T, n> returnVect;

	for (int i = 0; i < n; i++)
	{
		returnVect[i] = data[i] - Rhs[i];
	}

	return returnVect;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::operator*(T S) const
{
	TVector<T, n> returnVect;

	for (int i = 0; i < n; i++)
	{
		returnVect[i] = data[i] * S;
	}

	return returnVect;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::operator/(T S) const
{
	assert(S != 0);

	TVector<T, n> returnVect;

	for (int i = 0; i < n; i++)
	{
		returnVect[i] = data[i] / S;
	}

	return returnVect;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::operator+=(const TVector<T, n>& Rhs)
{
	for (int i = 0; i < n; i++)
	{
		data[i] += Rhs[i];
	}

	return *this;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::operator-=(const TVector<T, n>& Rhs)
{
	for (int i = 0; i < n; i++)
	{
		data[i] -= Rhs[i];
	}

	return *this;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::operator*=(T S)
{
	for (int i = 0; i < n; i++)
	{
		data[i] *= S;
	}

	return *this;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::operator/=(T S)
{
	for (int i = 0; i < n; i++)
	{
		data[i] /= S;
	}

	return *this;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::Min(const TVector<T, n>& Left, const TVector<T, n>& Right)
{
	bool bLeft = TVector<T, n>::Length(Left) < TVector<T, n>::Length(Right);

	return bLeft ? Left : Right;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::Max(const TVector<T, n>& Left, const TVector<T, n>& Right)
{
	bool bLeft = TVector<T, n>::Length(Left) > TVector<T, n>::Length(Right);

	return bLeft ? Left : Right;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::Abs(const TVector<T, n>& Left)
{
	TVector<T, n> Vect;

	for (int i = 0; i < n; i++)
	{
		Vect[i] = abs(Left[i]);
	}

	return Vect;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::Clamp(const TVector<T, n>& Vect, T Vmin, T Vmax)
{
	TVector<T, n> RetVect;

	for (int i = 0; i < n; i++)
	{
		RetVect[i] = Vect[i] > Vmax ? Vmax : Vect[i];
		RetVect[i] = Vect[i] < Vmin ? Vmin : Vect[i];
	}

	return RetVect;
}

template <typename T, int n>
TVector<T, n> TVector<T, n>::Lerp(const TVector<T, n>& Start, const TVector<T, n>& End, float Time)
{
	TVector<T, n> dir = End - Start;

	TVector<T, n> Vect;

	for (int i = 0; i < n; i++)
	{
		Vect[i] = Start[i] + dir * Time;
	}

	return Vect;
}
