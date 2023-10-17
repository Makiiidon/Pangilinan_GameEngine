#pragma once

#include "AGameObject.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"


class Plane : public AGameObject
{
public:
	Plane(std::string name, void* shaderByteCode, size_t sizeShader);
	~Plane();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader) override;
	void setAnimationSpeed(float speed);

	void release() override;

private:
	VertexBuffer* m_vb;
	ConstantBuffer* m_cb;

	float m_ticks = 0.0f;
	float m_deltaPos = 0.0f;
	float m_deltaTime = 0.0f;
	float m_speed = 10.0f;

	constant cc;

};

