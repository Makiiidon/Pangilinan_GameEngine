#include "ToolBar.h"
#include "GameObjectManager.h"
#include "GraphicsEngine.h"

ToolBar::ToolBar(std::string name) : AUIScreen(name)
{

}

ToolBar::~ToolBar()
{
}

void ToolBar::drawUI()
{
	ImGui::BeginMainMenuBar();

	// FILE
	if (ImGui::BeginMenu("File")) {
		ImGui::MenuItem("New");
		ImGui::MenuItem("Save");
		ImGui::MenuItem("Open");
		ImGui::MenuItem("Exit");
		ImGui::EndMenu();
	}
	
	// GAME OBJECTS
	if (ImGui::BeginMenu("Game Object")) {
		
		if (ImGui::MenuItem("Create Cube")) 
		{
			void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

			GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE, shader_byte_code, size_shader);
			GraphicsEngine::get()->releaseCompiledShader();

		}
		else if (ImGui::MenuItem("Create Sphere"))
		{
			void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

			GameObjectManager::getInstance()->createObject(GameObjectManager::SPHERE, shader_byte_code, size_shader);
			GraphicsEngine::get()->releaseCompiledShader();
		}
		else if (ImGui::MenuItem("Create Plane")) 
		{
			void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

			GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE, shader_byte_code, size_shader);
			GraphicsEngine::get()->releaseCompiledShader();

		}
		else if (ImGui::MenuItem("Create Physics Cube"))
		{
			void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

			GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_CUBE, shader_byte_code, size_shader);
			GraphicsEngine::get()->releaseCompiledShader();

		}
		else if (ImGui::MenuItem("Create Physics Plane"))
		{
			void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

			GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_PLANE, shader_byte_code, size_shader);
			GraphicsEngine::get()->releaseCompiledShader();

		}
		// LIGHTS
		if (ImGui::BeginMenu("Light")) {
			ImGui::MenuItem("Create Point Light");
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();

}


