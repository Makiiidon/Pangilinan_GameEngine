#pragma once
#include <iostream>
#include "VertexShader.h"
#include "PixelShader.h"
#include "Vector3D.h"
#include "Matrix4x4.h"

class VertexShader;
class PixelShader;
class GameObjectManager;

class AGameObject
{
public:
	AGameObject(std::string name);
	~AGameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader) = 0;
	virtual void release() = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D position);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	void setScale(float scale);
	Vector3D getScale();

	void setRotation(float x, float y, float z);
	void setRotation(float value);
	void setRotation(Vector3D rotation);
	Vector3D getLocalRotation();

	void setLocalMatrix(float matrix[16]);
	Matrix4x4 getLocalMatrix();
	float* getPhysicsLocalMatrix();
	std::string getName();

	void setActive(bool value);
	bool isGameObjectActive();

protected:
	std::string name;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;

	bool isActive = true;

	struct vertex
	{
		Vector3D position;
		Vector3D position1;
		Vector3D color;
		Vector3D color1;
	};

	__declspec(align(16))
		struct constant
	{
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_projection;
		float m_angle;
	};

private:
	friend class GameObjectManager;
};

