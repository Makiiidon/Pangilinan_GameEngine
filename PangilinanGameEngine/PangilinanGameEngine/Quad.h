#pragma once

#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"


class Quad
{
public:
	Quad(void* list, UINT size_vertex, UINT size_list);
	~Quad();

	void drawQuad(ConstantBuffer *buffer);

	void release();

private:
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

};

