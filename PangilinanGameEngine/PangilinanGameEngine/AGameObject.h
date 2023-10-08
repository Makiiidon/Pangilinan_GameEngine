#pragma once
#include "PixelShader.h"
#include "VertexShader.h"
#include "DeviceContext.h"

#include <iostream>
#include <string>

#include "Vector3D.h"
#include "Matrix4x4.h"

class VertexShader;
class PixelShader;

class AGameObject
{
public:
	AGameObject(std::string name);
	~AGameObject();
	virtual void update(float deltaTime) = 0;
	virtual void draw(RECT rc, VertexShader* vertexShader, PixelShader* pixelShader) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D position);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rotation);
	Vector3D getLocalRotation();

protected:
	std::string name;
	Vector3D localScale;
	Vector3D localPosition;
	Vector3D localRotation;
	Matrix4x4 transform;

	__declspec(align(16))
		struct constant
	{
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_projection;
		float m_angle;
	};

	struct vertex
	{
		Vector3D position;
		Vector3D color;
		Vector3D color1;
	};

private:
	friend class VertexShader;
	friend class PixelShader;

	
};

