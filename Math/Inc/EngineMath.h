#ifndef MATH_ENGINEMATH_H
#define MATH_ENGINEMATH_H

//Add all math includes here
//#include "Vector3.h"
#include "TVector.h"
#include "TMatrix.h"
#include "Quaternion.h"

#include <xtgmath.h>
#include <math.h>

namespace Math
{
	struct AxisAngle
	{
		Vector3 axis;
		float angle;

		AxisAngle()
			: axis(Vector3::Zero())
			, angle(0)
		{}

		AxisAngle(const Vector3& Axis, float Angle)
			: axis(Axis)
			, angle(Angle)
		{}
	};

	namespace Constant
	{
		struct Float4x4
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;

			Float4x4();
			Float4x4(const Matrix4& InMatrix);

			void CopyFromMatrix(const Matrix4& InMatrix);
		};
	}

	namespace Color
	{
		Color4 Red();
		Color4 Green();
		Color4 Blue();
		Color4 White();
		Color4 Black();
		Color4 Yellow();
		Color4 Magenta();
		Color4 Cyan();
	}

	const float kPi = 3.14159265358979f;
	const float kTwoPi = 6.28318530717958f;
	const float kPiByTwo = 1.57079632679489f;
	const float kRootTwo = 1.41421356237309f;
	const float kRootThree = 1.73205080756887f;
	const float kDegToRad = kPi / 180.0f;
	const float kRadToDeg = 180.0f / kPi;

	float Sqrt(float Value);
	float Sqr(float Value);
	float Lerp(float p0, float p1, float t);
	float Clamp(float Value, float Min, float Max);
	float Max(float left, float right);
	float Min(float left, float right);

	float MagnitudeSqr(const Vector3& v);
	float Magnitude(const Vector3& v);

	Vector3 Up();
	Vector3 XAxis();
	Vector3 YAxis();
	Vector3 ZAxis();

	Matrix4 CreateTranslationMatrix(const Vector3& V);
	Matrix4 CreateRotAxis(const Vector3& Axis, float Rad);
	Matrix4 CreateScaleMatrix(const TVector<float, 3>& S);
	Matrix4 CreateLookAtMatrix(const Vector3& From, const Vector3& To, const Vector3& Up = Math::Up());

	Matrix4 CreateRotMatrixX(float Rad);
	Matrix4 CreateRotMatrixY(float Rad);
	Matrix4 CreateRotMatrixZ(float Rad);
	
	Vector3 TransformCoord(const Vector3& v, const Matrix4& m);
	Vector3 TransformNormal(const Vector3& v, const Matrix4& m);

	Quaternion CreateAngleAxis(const Vector3& Axis, float Angle);
	Matrix4 CreateRotationMatrix(const Quaternion& Quat);
	AxisAngle GetAxisAngle(const Quaternion& Quat);
	Vector3 GetEulerAngles(const Quaternion& Quat);
}

#endif