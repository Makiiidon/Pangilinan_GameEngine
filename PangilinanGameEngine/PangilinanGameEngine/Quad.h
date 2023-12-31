#pragma once

#include "AGameObject.h"

#include "VertexBuffer.h"

#include "ConstantBuffer.h"


class Quad : public AGameObject
{
public:
	Quad(std::string name, void* shaderByteCode, size_t sizeShader);
	~Quad();

	virtual void update(float deltaTime) override;
	virtual void draw(RECT rc, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void setAnimSpeed(float speed);

	void release();

private:
	VertexBuffer* vb;
	ConstantBuffer* cb;

	constant cc;

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;


};

