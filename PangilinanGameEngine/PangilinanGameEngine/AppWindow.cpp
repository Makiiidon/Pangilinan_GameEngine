#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include "Vector3D.h"
#include "Matrix4x4.h"

struct vertex
{
	Vector3D position;
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

	//if (m_delta_time > 1.0f) m_delta_time = 0.0f;

	Matrix4x4 temp;

	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, -2), Vector3D(2, 2, 2), m_angle));
	/*cc.m_world.setScale(Vector3D::lerp(Vector3D(1,1,0), Vector3D(.5f, .5f, 0), (sin(m_delta_time) + 1.0f / 2.0f)));

	temp.setTranslation(Vector3D::lerp(Vector3D(-.2f, -.2f, 0), Vector3D(.2f, .2f, 0), (sin(m_delta_time) + 1.0f / 2.0f)));

	cc.m_world *= temp;*/

	cc.m_world.setScale(Vector3D( 1, 1, 1 ));

	temp.setIdentity();
	temp.setRotationX(m_delta_time);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_delta_time);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationZ(m_delta_time);
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
	//cc.m_angle += m_angle *100.0f;
	//m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
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

	GraphicsEngine::get()->releaseCompiledShader();

	// load pixel shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	// load pixel shader
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	cube = new Cube( "Cube1", shader_byte_code, size_shader );

	cube->setAnimSpeed(10.0f);

	//quad = new Quad("Quad1", shader_byte_code, size_shader);
	//quad->setAnimSpeed(10.0f);

	/*constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));*/
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

	//updateQuadPosition();

	cube->update(EngineTime::getDeltaTime());


	// DRAW OBJECTS
	//quad1->drawQuad(m_cb);
	cube->draw(rc, m_vs, m_ps);

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	//m_vb->release();
	//quad1->release();
	//m_ib->release();
	//m_cb->release();
	GraphicsEngine::get()->release();
}

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}
