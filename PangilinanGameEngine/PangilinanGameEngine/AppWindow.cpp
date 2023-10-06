#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include "Vector3D.h"
#include "Matrix4x4.h"

struct vec3
{
	float x, y, z;
};

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

	//if (m_delta_time > 1.0f) m_delta_time = 0.0f;

	Matrix4x4 temp;

	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, -2), Vector3D(2, 2, 2), m_angle));
	cc.m_world.setScale(Vector3D::lerp(Vector3D(1,1,0), Vector3D(.5f, .5f, 0), (sin(m_delta_time) + 1.0f / 2.0f)));

	temp.setTranslation(Vector3D::lerp(Vector3D(-.2f, -.2f, 0), Vector3D(.2f, .2f, 0), (sin(m_delta_time) + 1.0f / 2.0f)));

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

	vertex quadList1[] = {
		{Vector3D( -0.5f, -0.5f,  0.0f ),  Vector3D( -0.32f, -0.11f, 0.0f ),   Vector3D( 0, 0, 0 ),   Vector3D( 0, 1, 0 )}, // POS1 - Lower Left
		{Vector3D( -0.5f,  0.5f,  0.0f ),  Vector3D( -0.11f,  0.78f, 0.0f ),   Vector3D( 1, 1, 0 ),   Vector3D( 1, 1, 0 )}, // POS2 - Upper Left
		{Vector3D(  0.5f, -0.5f,  0.0f ),  Vector3D(  0.75f, -0.73f, 0.0f ),   Vector3D( 0, 0, 1 ),   Vector3D( 1, 0, 0 )}, // POS3 - Lower Right
		{Vector3D(  0.5f,  0.5f,  0.0f ),  Vector3D(  0.88f,  0.77f, 0.0f ),   Vector3D( 1, 1, 1 ),   Vector3D( 0, 0, 1 )}, // POS4 - Upper Right
	};

	//vertex quadList2[] = {
	//	{ -0.1f, -0.1f,	0.0f,  -0.2f, -0.2f, 0.0f,   1, 0, 0,   0, 1, 1}, // POS1
	//	{ -0.1f,  0.1f,	0.0f,  -0.2f,  0.2f, 0.0f,   0, 1, 1,   0, 1, 0}, // POS2
	//	{  0.1f, -0.1f,	0.0f,   0.2f, -0.2f, 0.0f,   1, 0, 1,   0, 0, 1}, // POS3
	//	{  0.1f,  0.1f,	0.0f,   0.2f,  0.2f, 0.0f,   0, 1, 0,   0, 0, 1}, // POS4
	//};

	//vertex quadList3[] =
	//{
	//	//	//X - Y - Z
	//	{ -0.8f, -1.0f,	0.0f,  -0.7f, -0.6f, 0.0f,   1, 0, 0,   0, 1, 1}, // POS1
	//	{ -0.8f,  0.2f, 0.0f,  -0.5f,  0.3f, 0.0f, 0, 1, 1, 0, 1, 0}, // POS2
	//	{ 0.8f, -0.1f,	0.0f,  -0.5f, -0.2f, 0.0f,   1, 0, 1,   0, 0, 1 }, // POS3
	//	{ 0.8f,  0.1f,	0.0f,  -0.5f,  0.2f, 0.0f,   0, 1, 0,   0, 0, 1 }, // POS4
	//};

	UINT size_quadList1 = ARRAYSIZE(quadList1);
	//UINT size_quadList2 = ARRAYSIZE(quadList2);
	//UINT size_quadList3 = ARRAYSIZE(quadList3);


	// INITIALIZE QUADS
	quad1 = new Quad(quadList1, sizeof(vertex), size_quadList1);
	//quad2 = new Quad(quadList2, sizeof(vertex), size_quadList2);
	//quad3 = new Quad(quadList3, sizeof(vertex), size_quadList3);

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
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


	updateQuadPosition();


	// DRAW QUADS
	quad1->drawQuad(m_cb);

	m_swap_chain->present(true);

	EngineTime::LogFrameEnd();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	//m_vb->release();
	quad1->release();
	GraphicsEngine::get()->release();
}

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}
