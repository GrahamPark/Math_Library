#include "Precompiled.h"
#include "Quaternion.h"

namespace Math
{

	Quaternion::Quaternion()
		: x(0.f)
		, y(0.f)
		, z(0.f)
		, w(1.0f)
	{}

	Quaternion::Quaternion(float X, float Y, float Z, float W)
		: x(X)
		, y(Y)
		, z(Z)
		, w(W)
	{}

	void Quaternion::Set(float X, float Y, float Z, float W)
	{
		x = X;
		y = Y;
		z = Z;
		w = W;
	}

	Quaternion Quaternion::Normalize(const Quaternion& Q)
	{
		const float magSqr = (Q.x * Q.x) + (Q.y * Q.y) + (Q.z * Q.z) + (Q.w * Q.w);
		const float magInv = 1.0f / sqrt(magSqr);
		return Q * magInv;
	}

	Quaternion Quaternion::Lerp(Quaternion Q0, Quaternion Q1, float Time)
	{
		return Q0 * (1.0f - Time) + (Q1 * Time);
	}

	Quaternion Quaternion::Slerp(const Quaternion& Q0, const Quaternion& Q1, float Time)
	{
		Quaternion ActualQ1 = Q1;

		float dot = (Q0.x * Q1.x) + (Q0.y * Q1.y) + (Q0.z * Q1.z) + (Q0.w * Q1.w);

		// Determine the direction of the rotation.
		if (dot < 0.0f)
		{
			dot = -dot;
			ActualQ1.x = -Q1.x;
			ActualQ1.y = -Q1.y;
			ActualQ1.z = -Q1.z;
			ActualQ1.w = -Q1.w;
		}
		else if (dot > 0.999f)
		{
			return Normalize(Lerp(Q0, ActualQ1, Time));
		}

		float theta = acosf(dot);
		float sintheta = sinf(theta);
		float scale0 = sinf(theta * (1.0f - Time)) / sintheta;
		float scale1 = sinf(theta * Time) / sintheta;

		// Perform the slerp
		return Quaternion
		(
			(Q0.x * scale0) + (ActualQ1.x * scale1),
			(Q0.y * scale0) + (ActualQ1.y * scale1),
			(Q0.z * scale0) + (ActualQ1.z * scale1),
			(Q0.w * scale0) + (ActualQ1.w * scale1)
		);
	}

	Quaternion Quaternion::Inverse(const Quaternion& Quat)
	{
		float Mag = Magnitude(Quat);

		return Conjugate(Quat) / (Mag * Mag);
	}

	Quaternion Quaternion::Conjugate(const Quaternion& Quat)
	{
		return Quaternion(-Quat[0], -Quat[1], -Quat[2], Quat[3]);
	}

	float Quaternion::Magnitude(const Quaternion& Quat)
	{
		return sqrt((Quat[0] * Quat[0]) + (Quat[1] * Quat[1]) + (Quat[2] * Quat[2]) + (Quat[3] * Quat[3]));
	}

	inline Quaternion Quaternion::Zero()
	{
		return Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
	}

	inline Quaternion Quaternion::Identity()
	{
		return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	}

	float Quaternion::operator[](int index) const
	{
		ASSERT(index >= 0 && index <= 3, "[Math::Quaternion] Accessing invalid index");

		return data[index];
	}

	float& Quaternion::operator[](int index)
	{
		ASSERT(index >= 0 && index <= 3, "[Math::Quaternion] Accessing invalid index");

		return data[index];
	}

	Quaternion Quaternion::operator+(const Quaternion& rhs) const
	{
		return Quaternion(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	Quaternion Quaternion::operator*(const Quaternion& rhs) const
	{
		Quaternion outQuat;

		outQuat[0] = (data[0] * rhs[0] - data[1] * rhs[1] - data[2] * rhs[2] - data[3] * rhs[3]);
		outQuat[1] = (data[0] * rhs[1] + data[1] * rhs[0] - data[2] * rhs[3] + data[3] * rhs[2]);
		outQuat[2] = (data[0] * rhs[2] + data[1] * rhs[3] + data[2] * rhs[0] - data[3] * rhs[1]);
		outQuat[3] = (data[0] * rhs[0] - data[1] * rhs[1] + data[2] * rhs[2] + data[3] * rhs[3]);

		return outQuat;
	}

	Quaternion Quaternion::operator*=(const Quaternion& rhs) const
	{
		return (*this * rhs);
	}

	Quaternion Quaternion::operator*(float S) const
	{
		return Quaternion(x * S, y * S, z * S, w * S);
	}

	Quaternion Quaternion::operator/(float s) const
	{
		Quaternion outQuat;

		float div = 1.0f / s;

		outQuat.x = x * div;
		outQuat.y = y * div;
		outQuat.z = z * div;
		outQuat.w = w * div;

		return outQuat;
	}


}