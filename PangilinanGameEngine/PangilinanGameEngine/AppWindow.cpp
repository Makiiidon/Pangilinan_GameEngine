#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h";

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"


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
	//m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
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

	SceneCameraHandler::initialize();

	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	// load vertex shader
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	// Create Game Objects
#pragma region Cube
	/*Cube* cube = new Cube("Cube", shader_byte_code, size_shader);
	Vector3D position = Vector3D(0, 1, 0);
	Vector3D rotation = Vector3D::zeros();
	cube->setPosition(position);
	cube->setRotation(rotation);
	cube->setAnimationSpeed(randomFloat(1, 3.75f));
	cube->setScale(1);
	m_gameObjects.push_back(cube);

	Cube* cube2 = new Cube("Cube", shader_byte_code, size_shader);
	position = Vector3D(-2, 1, 0);
	rotation = Vector3D::zeros();
	cube2->setPosition(position);
	cube2->setRotation(rotation);
	cube2->setAnimationSpeed(randomFloat(1, 3.75f));
	cube2->setScale(1);
	m_gameObjects.push_back(cube2);

	Cube* cube3 = new Cube("Cube", shader_byte_code, size_shader);
	position = Vector3D(-2, 1, 4);
	rotation = Vector3D::zeros();
	cube3->setPosition(position);
	cube3->setRotation(rotation);
	cube3->setAnimationSpeed(randomFloat(1, 3.75f));
	cube3->setScale(1);
	m_gameObjects.push_back(cube3);*/

	for (int i = 0; i < 50; i++) 
	{
		Cube* cube = new Cube("Cube", shader_byte_code, size_shader);
		Vector3D position = Vector3D(
			randomFloat(-4.0f, 4.0f), 
			randomFloat(-4.0f, 4.0f), 
			randomFloat(-4.0f, 4.0f)
		);
		Vector3D rotation = Vector3D::zeros();
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setAnimationSpeed(randomFloat(1, 3.75f));
		cube->setScale(1);
		m_gameObjects.push_back(cube);
	}
#pragma endregion

#pragma region Plane
	/*Plane* plane = new Plane("Plane", shader_byte_code, size_shader);
	position = Vector3D(0, -1, 0);
	rotation = Vector3D(0, 0, 0);
	plane->setPosition(position);
	plane->setRotation(rotation);
	plane->setAnimationSpeed(randomFloat(-3.75f, 3.75f));
	plane->setScale(1);
	m_gameObjects.push_back(plane);*/
#pragma endregion


	GraphicsEngine::get()->releaseCompiledShader();

	// load pixel shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();


	// GUI
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(Window::getHWND());
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getDevice(), GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::getInstance()->update();
	SceneCameraHandler::getInstance()->update();

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow(); // Show demo window! :)
	ImGui::Text("Hello World!");

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	m_delta_time += EngineTime::getDeltaTime();


	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		// Update the transforms of the Game Objects
		m_gameObjects[i]->update(EngineTime::getDeltaTime());

		// Renders the Game Objects
		m_gameObjects[i]->draw(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);

	}

	// Rendering GUI
	// (Your code clears your framebuffer, renders your other stuff etc.)
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	m_swap_chain->present(true);

	EngineTime::LogFrameEnd();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();

	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->release();
	}

	InputSystem::destroy();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	GraphicsEngine::get()->release();
}

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::InputUpdate()
{
}

void AppWindow::onKeyDown(int key)
{
}

void AppWindow::onKeyUp(int key)
{
}

void AppWindow::onMouseMove(const Point deltaPos)
{
}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
	
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
	
}
