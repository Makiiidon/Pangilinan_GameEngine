#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include "Vector3D.h"
#include "Matrix4x4.h"

struct vertex
{
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
}; 

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_projection;
	float m_angle;
};

AppWindow* AppWindow::sharedInstance = NULL;

AppWindow::AppWindow()
{
	sharedInstance = this;
	if (sharedInstance == nullptr) {
		std::cout << "Could not Initialize!";
	}
}

void AppWindow::updateQuadPosition()
{
	constant cc;
	m_delta_time += EngineTime::getDeltaTime();

	Matrix4x4 temp;

	cc.m_world.setScale(Vector3D(1, 1, 1));

	temp.setIdentity();
	temp.setTranslation(Vector3D(0,0,0));
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationZ(m_delta_time);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_delta_time);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_delta_time);
	cc.m_world *= temp;

	cc.m_view.setIdentity();
	cc.m_projection.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 400.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 400.0f,
		-4.0f,
		4.0f
	);

	// Using a diagonal sine wave (sinx + x) makes the time move from fast to slow and vice versa
	//cc.m_angle = m_angle + ((sin(m_angle / 10.0f) + (m_angle / 10.0f))) * 100.0f;
	cc.m_angle += m_delta_time;
	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	// load vertex shader
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	// Create Cubes
	cube = new Cube("Cube", shader_byte_code, size_shader);
	cube->setPosition(-.7f, .7f, 0);
	cube->setAnimationSpeed(2.f);
	cube->setScale(0.2f);

	cube2 = new Cube("Cube", shader_byte_code, size_shader);
	cube2->setPosition(.7f, -.7f, 0);
	cube2->setAnimationSpeed(1.f);

	cube2->setScale(0.1f);

	cube3 = new Cube("Cube", shader_byte_code, size_shader);
	cube3->setPosition(.0f, .0f, 0);
	cube3->setAnimationSpeed(3.f);
	cube3->setScale(0.12f);

	cube4 = new Cube("Cube", shader_byte_code, size_shader);
	cube4->setPosition(-.3f, -.4f, 0);
	cube4->setAnimationSpeed(4.f);
	cube4->setScale(0.15f);

	cube5 = new Cube("Cube", shader_byte_code, size_shader);
	cube5->setPosition(.3f, -.4f, 0);
	cube5->setAnimationSpeed(7.f);
	cube5->setScale(0.3f);


	GraphicsEngine::get()->releaseCompiledShader();

	// load pixel shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	
	

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	m_delta_time += EngineTime::getDeltaTime();

	// Update the transforms of the cubes
	cube->update(EngineTime::getDeltaTime());
	cube2->update(-EngineTime::getDeltaTime());
	cube3->update(-EngineTime::getDeltaTime());
	cube4->update(-EngineTime::getDeltaTime());
	cube5->update(-EngineTime::getDeltaTime());

	cube->setRotation(m_delta_time, m_delta_time, 0);
	cube2->setRotation(m_delta_time, m_delta_time, m_delta_time);
	cube3->setRotation(m_delta_time, -m_delta_time, 0);
	cube4->setRotation(m_delta_time, 0, m_delta_time);
	cube5->setRotation(m_delta_time, 0, m_delta_time);


	cube->draw(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	cube2->draw(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	cube3->draw(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	cube4->draw(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	cube5->draw(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);


	m_swap_chain->present(true);

	EngineTime::LogFrameEnd();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vb->release();
	m_ib->release();
	m_cb->release();

	cube->release();
	cube2->release();
	cube3->release();
	cube4->release();
	cube5->release();

	GraphicsEngine::get()->release();
}

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}
