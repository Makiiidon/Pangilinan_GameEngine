#pragma once
#include "AGameObject.h"
#include "InputListener.h"
class Camera : public AGameObject, public InputListener
{
public:
	Camera(std::string name);
	~Camera();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader) override;
	void updateViewMatrix();
	Matrix4x4 getViewMatrix();

	void release() override;


	void onKeyDown(int key) override;
	void onKeyUp(int key) override;
	void onMouseMove(const Point deltaPos) override;

	void onLeftMouseDown(const Point deltaPos) override;
	void onLeftMouseUp(const Point deltaPos) override;

	void onRightMouseDown(const Point deltaPos) override;
	void onRightMouseUp(const Point deltaPos) override;

private:
	float moveSpeed = 10.0f;
	Matrix4x4 worldCam;
	bool isW = false,
		isS = false,
		isA = false,
		isD = false,
		isMouseRight = false;
};

