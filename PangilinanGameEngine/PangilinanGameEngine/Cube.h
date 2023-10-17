#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"

#include "InputListener.h"


class Cube : public AGameObject, public InputListener
{
public:
	Cube(std::string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader) override;
	void setAnimationSpeed(float speed);

	void release() override;

	// Keyboard pure virtual callback functions
	void onKeyDown(int key) override;
	void onKeyUp(int key) override;

	// Mouse pure virtual callback functions
	void onMouseMove(const Point deltaPos) override;

	void onLeftMouseDown(const Point deltaPos) override;
	void onLeftMouseUp(const Point deltaPos) override;

	void onRightMouseDown(const Point deltaPos) override;
	void onRightMouseUp(const Point deltaPos) override;

private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;
	float m_ticks = 0.0f;
	float m_deltaPos = 0.0f;
	float m_deltaTime = 0.0f;
	float m_speed = 2.0f;
	float m_scaleTicks = 0.0f;
	constant cc;


	bool isScaleUp   = false,
		 isScaleDown = false;
};

