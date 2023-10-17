#include "Camera.h"
#include "InputSystem.h"
#include "EngineTime.h"

Camera::Camera(std::string name) : AGameObject(name)
{
	InputSystem::getInstance()->addListener(this);
	this->localMatrix.setIdentity();
	localPosition = (Vector3D(0, 0, -3.0f));
	this->updateViewMatrix();

}

Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
	Vector3D localPos = this->getLocalPosition();
	Vector3D temp = localPos;

	// Vertical Movement
	// InputSystem::getInstance()->isKeyDown('D')
	if (isW)
	{
		//temp += localMatrix.getFront() * deltaTime * moveSpeed;
		temp.m_z += deltaTime * moveSpeed;
		this->setPosition(temp);
		this->updateViewMatrix();
	}
	else if (isS)
	{
		temp.m_z -= deltaTime * moveSpeed;
		this->setPosition(temp);
		this->updateViewMatrix();
	}

	// Horizontal Movement
	if (isD)
	{
		temp.m_x += deltaTime * moveSpeed;
		this->setPosition(temp);
		this->updateViewMatrix();
	}
	else if (isA)
	{
		temp.m_x -= deltaTime * moveSpeed;
		this->setPosition(temp);
		this->updateViewMatrix();
	}

	if (isE) 
	{
		temp.m_y += deltaTime * moveSpeed;
		this->setPosition(temp);
		this->updateViewMatrix();
	}
	else if (isQ)
	{
		temp.m_y -= deltaTime * moveSpeed;
		this->setPosition(temp);
		this->updateViewMatrix();
	}

	//localPosition.debugPrint();
}

void Camera::draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader)
{
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam;	worldCam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.m_x);
	worldCam = worldCam.multiplyTo(temp);

	temp.setRotationY(localRot.m_y);
	worldCam = worldCam.multiplyTo(temp);

	temp.setTranslation(this->getLocalPosition());
	worldCam = worldCam.multiplyTo(temp);

	worldCam.getInverse();
	this->localMatrix = worldCam;
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
}

void Camera::release()
{
}

void Camera::onKeyDown(int key)
{
	if (key == 'W')
	{
		isW = true;
	}
	else if (key == 'S')
	{
		isS = true;
	}

	if (key == 'D')
	{
		isD = true;
	}
	else if (key == 'A')
	{
		isA = true;
	}

	if (key == 'Q')
	{
		isQ = true;
	}
	else if (key == 'E')
	{
		isE = true;
	}
}

void Camera::onKeyUp(int key)
{
	if (key == 'W')
	{
		isW = false;
	}
	else if (key == 'S')
	{
		isS = false;
	}

	if (key == 'D')
	{
		isD = false;
	}
	else if (key == 'A')
	{
		isA = false;
	}

	if (key == 'Q')
	{
		isQ = false;
	}
	else if (key == 'E')
	{
		isE = false;
	}
}

void Camera::onMouseMove(const Point deltaPos)
{
	if (!isMouseRight) return;

	// Mouse Movement
	localRotation.m_x -= deltaPos.getY() * EngineTime::getDeltaTime() * lookSensitivity;
	localRotation.m_y -= deltaPos.getX() * EngineTime::getDeltaTime() * lookSensitivity;

	this->updateViewMatrix();
	//std::cout << "X: " << localRotation.m_x << " Y: " << localRotation.m_y << " Z: " << localRotation.m_z << "\n";

}

void Camera::onLeftMouseDown(const Point deltaPos)
{
}

void Camera::onLeftMouseUp(const Point deltaPos)
{
}

void Camera::onRightMouseDown(const Point deltaPos)
{
	isMouseRight = true;
}

void Camera::onRightMouseUp(const Point deltaPos)
{
	isMouseRight = false;
}
