#pragma once
#include "AGameObject.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"


class Cube : public AGameObject
{
public:
	Cube(std::string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

	virtual void update(float deltaTime) override;
	virtual void draw(RECT rc, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void setAnimSpeed(float speed);

	void release();

private:
	VertexBuffer* vb;
	ConstantBuffer* cb;
	IndexBuffer* ib;

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;

	constant cc;

	
};

