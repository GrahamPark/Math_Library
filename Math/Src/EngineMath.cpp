#include "Precompiled.h"
#include "EngineMath.h"

//Static Vars
namespace Math
{
	
}

//General
namespace Math
{
	float Sqrt(float Value)
	{
		return sqrtf(Value);
	}

	float Sqr(float Value)
	{
		return Value * Value;
	}

	float Lerp(float p0, float p1, float t)
	{
		return p0 + ((p1 - p0) * t);
	}

	float Clamp(float Value, float Min, float Max)
	{
		return Value < Min ? Min : (Value > Max ? Max : Value);
	}

	float Max(float left, float right)
	{
		return left > right ? left : right;
	}

	float Min(float left, float right)
	{
		return left < right ? left : right;
	}

	float MagnitudeSqr(const Vector3& v)
	{
		return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	}

	float Magnitude(const Vector3& v)
	{
		return Sqrt(MagnitudeSqr(v));
	}
}

namespace Math
{
	Vector3 Up()
	{
		return YAxis();
	}

	Vector3 XAxis()
	{
		return Vector3(1.0f, 0.0f, 0.0f);
	}
	
	Vector3 YAxis()
	{
		return Vector3(0.0f, 1.0f, 0.0f);
	}

	Vector3 ZAxis()
	{
		return Vector3(0.0f, 0.0f, 1.0f);
	}
}

//Matrix::
namespace Math
{
	Matrix4 CreateTranslationMatrix(const Vector3& V)
	{
		return Matrix4::CreateMatrix
		(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			V.x, V.y, V.z, 1.f
		);
	}

	Matrix4 CreateRotAxis(const Vector3& Axis, float Rad)
	{
		const Vector3 u = Axis.Normalized();

		const float x = u.x;
		const float y = u.y;
		const float z = u.z;
		const float s = sin(Rad);
		const float c = cos(Rad);

		return Matrix4::CreateMatrix
		(
			c + (x * x * (1.f - c)),
			x * y * (1.f - c) + z * s,
			x * z * (1.f - c) - y * s,
			0.f,

			x * y * (1.f - c) - z * s,
			c + (y * y * (1.f - c)),
			y * z * (1.f - c) + x * s,
			0.f,

			x * z * (1.f - c) + y * s,
			y * z * (1.f - c) - x * s,
			c + (z * z * (1.f - c)),
			0.f,

			0.f,
			0.f,
			0.f,
			1.f
		);
	}

	Matrix4 CreateScaleMatrix(const TVector<float, 3>& S)
	{
		return Matrix4::CreateMatrix
		(
			S.x, 0.f, 0.f, 0.f,
			0.f, S.y, 0.f, 0.f,
			0.f, 0.f, S.z, 0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	Matrix4 CreateLookAtMatrix(const Vector3& From, const Vector3& To, const Vector3& Up)
	{
		Vector3 fwd = (From - To).Normalized();
		Vector3 right = Vector3::Cross(Up.Normalized(), fwd);
		Vector3 relativeUp = Vector3::Cross(fwd, right);

		return Matrix4::CreateMatrix
		(
			right.x,		right.y,		right.z,		0,
			relativeUp.x,	relativeUp.y,	relativeUp.z,	0,
			fwd.x,			fwd.y,			fwd.z,			0,
			From.x,			From.y,			From.z,			1.0f
		);
	}

	Matrix4 CreateRotMatrixX(float Rad)
	{
		const float c = cos(Rad);
		const float s = sin(Rad);

		return Matrix4::CreateMatrix
		(
			1.f, 0.f, 0.f, 0.f,
			0.f, c, s, 0.f,
			0.f, -s, c, 0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	Matrix4 CreateRotMatrixY(float Rad)
	{
		const float c = cos(Rad);
		const float s = sin(Rad);

		return Matrix4::CreateMatrix
		(
			c, 0.f, -s, 0.f,
			0.f, 1.f, 0.f, 0.f,
			s, 0.f, c, 0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	Matrix4 CreateRotMatrixZ(float Rad)
	{
		const float c = cos(Rad);
		const float s = sin(Rad);

		return Matrix4::CreateMatrix
		(
			c, s, 0.f, 0.f,
			-s, c, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	Vector3 TransformCoord(const Vector3& v, const Matrix4& m)
	{
		return Vector3
		(
			v.x * m._11 + v.y * m._21 + v.z * m._31 + m._41,
			v.x * m._12 + v.y * m._22 + v.z * m._32 + m._42,
			v.x * m._13 + v.y * m._23 + v.z * m._33 + m._43
		);
	}

	Vector3 TransformNormal(const Vector3& v, const Matrix4& m)
	{
		return Vector3
		(
			v.x * m._11 + v.y * m._21 + v.z * m._31,
			v.x * m._12 + v.y * m._22 + v.z * m._32,
			v.x * m._13 + v.y * m._23 + v.z * m._33
		);
	}
}
//~Matrix::

//Quaternion::
namespace Math
{
	Quaternion CreateAngleAxis(const Vector3& Axis, float Angle)
	{
		float HalfAngle = Angle * 0.5f;

		float qx = Axis.x * sin(HalfAngle);
		float qy = Axis.y * sin(HalfAngle);
		float qz = Axis.z * sin(HalfAngle);
		float qw = cos(HalfAngle);

		return Quaternion(qx, qy, qz, qw);
	}

	Matrix4 CreateRotationMatrix(const Quaternion& Quat)
	{
		Matrix4 RotationMatrix;

		RotationMatrix._11 = 1 - 2 * Sqr(Quat.y) - 2 * Sqr(Quat.z);
		RotationMatrix._12 = (2 * Quat.x * Quat.y) - (2 * Quat.w * Quat.z);
		RotationMatrix._13 = (2 * Quat.x * Quat.z) - (2 * Quat.w * Quat.y);
		RotationMatrix._21 = (2 * Quat.x * Quat.y) - (2 * Quat.w * Quat.z);
		RotationMatrix._22 = 1 - 2 * Sqr(Quat.x) - 2 * Sqr(Quat.z);
		RotationMatrix._23 = (2 * Quat.y * Quat.z) - (2 * Quat.w * Quat.x);
		RotationMatrix._31 = (2 * Quat.x * Quat.z) - (2 * Quat.w * Quat.y);
		RotationMatrix._32 = (2 * Quat.y * Quat.z) - (2 * Quat.w * Quat.x);
		RotationMatrix._33 = 1 - 2 * Sqr(Quat.x) - 2 * Sqr(Quat.y);

		return RotationMatrix;
	}

	AxisAngle GetAxisAngle(const Quaternion& Quat)
	{
		float sqrtDenominator = sqrt(1 - Quat.w * Quat.w);

		AxisAngle NewAngleAxis;

		NewAngleAxis.angle = 2 * acos(Quat.w);
		NewAngleAxis.axis.x = Quat.x / sqrtDenominator;
		NewAngleAxis.axis.y = Quat.y / sqrtDenominator;
		NewAngleAxis.axis.z = Quat.z / sqrtDenominator;

		return NewAngleAxis;
	}

	Vector3 GetEulerAngles(const Quaternion& Quat)
	{
		float x = atan2((Quat.data[2] * Quat.data[3] + Quat.data[0] * Quat.data[1]), .5f - (Sqr(Quat.data[1]) + Sqr(Quat.data[2])));
		float y = asin(-2 * (Quat.data[1]*Quat.data[3] + Quat.data[0] * Quat.data[2]));
		float z = atan2((Quat.data[1] * Quat.data[2] + Quat.data[0] * Quat.data[3]), .5f - (Sqr(Quat.data[2]) + Sqr(Quat.data[3])));

		return Vector3(x, y, z);
	}
}
//~Quaternion::

namespace Math
{
	namespace Constant
	{
		Float4x4::Float4x4()
		{
			CopyFromMatrix(Math::Matrix4::Identity());
		}

		Float4x4::Float4x4(const Matrix4& InMatrix)
		{
			CopyFromMatrix(InMatrix);
		}

		void Float4x4::CopyFromMatrix(const Matrix4& InMatrix)
		{
			_11 = InMatrix._11;
			_12 = InMatrix._12;
			_13 = InMatrix._13;
			_14 = InMatrix._14;

			_21 = InMatrix._21;
			_22 = InMatrix._22;
			_23 = InMatrix._23;
			_24 = InMatrix._24;

			_31 = InMatrix._31;
			_32 = InMatrix._32;
			_33 = InMatrix._33;
			_34 = InMatrix._34;

			_41 = InMatrix._41;
			_42 = InMatrix._42;
			_43 = InMatrix._43;
			_44 = InMatrix._44;
		}
	}
}

namespace Math
{
	namespace Color
	{
		Color4 Red()		{ return Color4(1.0f, 0.0f, 0.0f, 1.0f); }
		Color4 Green()		{ return Color4(0.0f, 1.0f, 0.0f, 1.0f); }
		Color4 Blue()		{ return Color4(0.0f, 0.0f, 1.0f, 1.0f); }
		Color4 White()		{ return Color4(1.0f, 1.0f, 1.0f, 1.0f); }
		Color4 Black()		{ return Color4(0.0f, 0.0f, 0.0f, 1.0f); }
		Color4 Yellow()		{ return Color4(1.0f, 1.0f, 0.0f, 1.0f); }
		Color4 Magenta()	{ return Color4(1.0f, 0.0f, 1.0f, 1.0f); }
		Color4 Cyan()		{ return Color4(0.0f, 1.0f, 1.0f, 1.0f); }
	}
}