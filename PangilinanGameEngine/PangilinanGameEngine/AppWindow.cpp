#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"

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
	srand(time(NULL));

	Window::onCreate();
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(this);

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
	for (int i = 0; i < 10; i++) 
	{
		Cube* cube = new Cube("Cube", shader_byte_code, size_shader);

		Vector3D position = Vector3D(randomFloat(-0.75, 0.75f), randomFloat(-0.75, 0.75f), randomFloat(-0.75, 0.75f));
		Vector3D rotation = Vector3D(randomFloat(0.0f, 360.0f), randomFloat(-0.75, 0.75f), randomFloat(-0.75, 0.75f));

		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setAnimationSpeed(randomFloat(-3.75f, 3.75f));
		cube->setScale(0.25f);
		m_gameObjects.push_back(cube);
	}

	GraphicsEngine::get()->releaseCompiledShader();

	// load pixel shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::getInstance()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	m_delta_time += EngineTime::getDeltaTime();

	InputUpdate();

	// Update the transforms of the Game Objects
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update(EngineTime::getDeltaTime());
	}
	// Rotates the Game Objects
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->setRotation(m_rotation);
	}

	// Renders the Game Objects
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	}

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

	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->release();
	}

	GraphicsEngine::get()->release();
}

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::InputUpdate()
{
	if (isW)
	{
		m_rotation += EngineTime::getDeltaTime();
	}
	else if (isS)
	{
		m_rotation -= EngineTime::getDeltaTime();
	}
}

void AppWindow::onKeyDown(int key)
{
	// InputSystem::getInstance()->isKeyDown('W')
	if (key == 'W')
	{
		isW = true;
	}

	else if (key == 'S')
	{
		isS = true;
	}
	

}

void AppWindow::onKeyUp(int key)
{
	// InputSystem::getInstance()->isKeyUp('W')
	if (key == 'W')
	{
		isW = false;
	}

	if (key == 'S')
	{
		isS = false;
	}
}
