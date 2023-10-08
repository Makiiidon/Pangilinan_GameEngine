#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "EngineTime.h"


#include "Quad.h"
#include "Cube.h"

class AppWindow : public Window
{
public:
	AppWindow();

	void updateQuadPosition();

	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	AppWindow* getInstance();
	static AppWindow* sharedInstance;
private:
	SwapChain* m_swap_chain;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

	float m_delta_time = 0;

	float m_time = 5000.0f;

	Quad* quad;
	Cube* cube;
};