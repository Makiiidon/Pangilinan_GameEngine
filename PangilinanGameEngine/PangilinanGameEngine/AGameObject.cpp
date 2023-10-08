#include "AGameObject.h"

AGameObject::AGameObject(std::string name)
{
	this->name = name;
	this->localScale = Vector3D::ones();
	this->localPosition = Vector3D::zeros();
	this->localRotation = Vector3D::zeros();
	transform.setIdentity();
}

AGameObject::~AGameObject()
{
}

void AGameObject::update(float deltaTime)
{
}

void AGameObject::draw(RECT rc, VertexShader* vertexShader, PixelShader* pixelShader)
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	localPosition = Vector3D( x, y, z );
}

void AGameObject::setPosition(Vector3D position)
{
	this->localPosition = position;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D( x, y, z );
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
}

Vector3D AGameObject::getScale()
{
	return this->localScale;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D( x, y, z );
}

void AGameObject::setRotation(Vector3D rotation)
{
	this->localRotation = rotation;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
}

