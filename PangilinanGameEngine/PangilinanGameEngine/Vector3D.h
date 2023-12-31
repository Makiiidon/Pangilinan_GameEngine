#pragma once


class Vector3D 
{
public:
	Vector3D() : m_x(0), m_y(0), m_z(0)
	{

	}

	Vector3D(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
	{

	}

	Vector3D(const Vector3D& vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z)
	{

	}

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta) 
	{
		Vector3D v;

		v.m_x = start.m_x * ( 1.0f - delta ) + end.m_x * delta;
		v.m_y = start.m_y * ( 1.0f - delta ) + end.m_y * delta;
		v.m_z = start.m_z * ( 1.0f - delta ) + end.m_z * delta;

		return v;
	}

	static Vector3D zeros() 
	{
		Vector3D v;

		v.m_x = 0;
		v.m_y = 0;
		v.m_z = 0;

		return v;
	}

	static Vector3D ones()
	{
		Vector3D v;

		v.m_x = 1;
		v.m_y = 1;
		v.m_z = 1;

		return v;
	}

	static Vector3D scale_by(const Vector3D& input, float scale_amount)
	{
		Vector3D v;

		v.m_x = input.m_x * scale_amount;
		v.m_y = input.m_y * scale_amount;
		v.m_z = input.m_z * scale_amount;

		return v;
	}

	static Vector3D add_by(const Vector3D& base, const Vector3D& add_amount)
	{
		Vector3D v;

		v.m_x = base.m_x + add_amount.m_x;
		v.m_y = base.m_y + add_amount.m_y;
		v.m_z = base.m_z + add_amount.m_z;

		return v;
	}


	~Vector3D() 
	{

	}

public:
	float m_x, m_y, m_z;
};