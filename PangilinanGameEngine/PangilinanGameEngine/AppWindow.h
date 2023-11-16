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
#include "InputListener.h"


#include "Quad.h"
#include "Cube.h"
#include "Plane.h"
#include <iostream>
#include <vector>

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();

	void updateQuadPosition();

	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	void onKeyDown(int key) override;
	void onKeyUp(int key) override;
	void onMouseMove(const Point deltaPos) override;

	void onLeftMouseDown(const Point deltaPos) override;
	void onLeftMouseUp(const Point deltaPos) override;

	void onRightMouseDown(const Point deltaPos) override;
	void onRightMouseUp(const Point deltaPos) override;

	AppWindow* getInstance();
	static AppWindow* sharedInstance;
private:
	SwapChain* m_swap_chain;
	VertexShader* m_vs;
	PixelShader* m_ps;
	/*VertexBuffer* m_vb;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;*/

	/*unsigned long m_old_time = 0;*/
	float m_delta_time = 0;


	//float m_angle = 0;
	float m_time = 5000.0f;
	
	//Cube* cube;
	std::vector<AGameObject*> m_gameObjects;

	
	float randomFloat(float a, float b) 
	{
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}

	void InputUpdate();
};