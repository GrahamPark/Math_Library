#ifndef MATH_QUATERNION_H
#define MATH_QUATERNION_H

namespace Math
{
	class Quaternion
	{
	public:
		union
		{
			float data[4];
			struct { float x, y, z, w; };
		};

		Quaternion();
		Quaternion(float X, float Y, float Z, float W);

		void Set(float X, float Y, float Z, float W);

		static Quaternion Normalize(const Quaternion& Q);
		static Quaternion Lerp(Quaternion Q0, Quaternion Q1, float Time);
		static Quaternion Slerp(const Quaternion& Q0, const Quaternion& Q1, float Time);
		static Quaternion Inverse(const Quaternion& Quat);
		static Quaternion Conjugate(const Quaternion& Quat);
		static float Magnitude(const Quaternion& Quat);
		
		static Quaternion Zero();
		static Quaternion Identity();

		float operator[](int index) const;
		float& operator[](int index);

		Quaternion operator+(const Quaternion& rhs) const;
		Quaternion operator*(const Quaternion& rhs) const;
		Quaternion operator*=(const Quaternion& rhs) const;
		Quaternion operator*(float S) const;
		Quaternion operator/(float s) const;
	};
}

#endif