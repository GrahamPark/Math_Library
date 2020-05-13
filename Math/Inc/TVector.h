#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

namespace Math
{
	template <typename T, int n>
	class VectorData
	{
	public:
		T data[n];
	};

	template <> class VectorData<float, 2> 
	{
	public:
		union
		{
			float data[2];
			struct { float x, y; };
		};
	};

	template <> class VectorData<float, 3> 
	{
	public:
		union
		{
			float data[3];
			struct { float x, y, z; };
			VectorData<float, 2> xy;
		};
	};

	template <> class VectorData<float, 4> 
	{
	public:
		union
		{
			float data[4];
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			VectorData<float, 2> xy;
			VectorData<float, 3> xyz;
			VectorData<float, 3> rgb;
		};
	};

	template <typename T, int n>
	class TVector : public VectorData<T,n>
	{
	public:
		using VectorData<T, n>::data;

		TVector();
		TVector(T x, T y);
		TVector(T x, T y, T z);
		TVector(T x, T y, T z, T w);

		int GetNumAxis() {return n;}

		//Calculations
		T Length() const;
		T LengthSq() const;
		TVector Normalized() const;
		int GetAsArray(T* OutArray) const;

		//Static Functions
		static TVector Zero();
		static TVector One();

		static T Dot(const TVector& Left, const TVector& Right);
		static TVector Cross(const TVector& Left, const TVector& Right);
		static TVector Proj(const TVector& Left, const TVector& Right);
		static TVector Perp(const TVector& Left, const TVector& Right);

		static TVector Min(const TVector& Left, const TVector& Right);
		static TVector Max(const TVector& Left, const TVector& Right);
		static TVector Abs(const TVector& Left);
		static TVector Clamp(const TVector& Vect, T Vmin, T Vmax);
		static TVector Lerp(const TVector& Start, const TVector& End, float Time);

		//Operator overloads
		T& operator[](int index);
		const T& operator[](int index) const;

		TVector operator-();
		TVector operator+(const TVector& Rhs) const;
		TVector operator-(const TVector& Rhs) const;
		TVector operator*(T S) const;
		TVector operator/(T S) const;

		TVector operator+=(const TVector& Rhs);
		TVector operator-=(const TVector& Rhs);
		TVector operator*=(T S);
		TVector operator/=(T S);
	};

	typedef TVector<float, 2> Vector2;
	typedef TVector<float, 3> Vector3;
	typedef TVector<float, 4> Vector4;
	typedef TVector<float, 4> Color4;

	typedef TVector<int, 2> iVector2;
	typedef TVector<int, 3> iVector3;
	typedef TVector<int, 4> iVector4;

#include "../Src/TVector.inl"
}

#endif
