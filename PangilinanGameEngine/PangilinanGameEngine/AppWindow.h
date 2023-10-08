#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "EngineTime.h"


#include "Quad.h"

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
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;

	/*unsigned long m_old_time = 0;*/
	float m_delta_time = 0;
	//float m_angle = 0;
	float m_time = 5000.0f;

	Quad* quad1;
	//Quad* quad2;
	//Quad* quad3;
};