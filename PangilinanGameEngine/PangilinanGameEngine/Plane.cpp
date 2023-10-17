#include "Plane.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "SceneCameraHandler.h"


Plane::Plane(std::string name, void* shaderByteCode, size_t sizeShader) : AGameObject(name)
{
	vertex vertex_list[] = {
		// FRONT FACE
		{ Vector3D(-1.0f,  0.0f,  -1.0f),    Vector3D(1,1,0),  Vector3D(1,1,0) },
		{ Vector3D(-1.0f,  0.0f,   1.0f),    Vector3D(1,1,0),  Vector3D(1,1,0) },
		{ Vector3D( 1.0f,  0.0f,  -1.0f),    Vector3D(1,1,0),  Vector3D(1,1,0) },
		{ Vector3D( 1.0f,  0.0f,   1.0f),    Vector3D(1,0,0),  Vector3D(1,0,0) },
	};


	// Create a vertex buffer
	m_vb = GraphicsEngine::get()->createVertexBuffer();


	// load the vertices
	m_vb->load(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);
	constant ccc;
	ccc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&ccc, sizeof(constant));
}

Plane::~Plane()
{
}

void Plane::update(float deltaTime)
{
	m_deltaTime = deltaTime;
	m_ticks += m_deltaTime * m_speed;

	Matrix4x4 temp;

	localRotation.m_y = sin(m_ticks);
	localPosition.m_x = sin(m_ticks);

	cc.m_world.setScale(localScale);

	temp.setIdentity();
	temp.setRotationZ(localRotation.m_z * m_speed);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(localRotation.m_y * m_speed);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(localRotation.m_x * m_speed);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setTranslation(localPosition);
	cc.m_world *= temp;
}

void Plane::draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader)
{
	cc.m_view.setIdentity();
	/*cc.m_projection.setOrthoLH
	(
		(width) / 400.0f,
		(height) / 400.0f,
		-4.0f,
		4.0f
	);*/

	cc.m_projection.setPerspectiveFovLH(1.57f, ((float)width / height), 0.1f, 100.f);

	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.m_view = cc.m_view.multiplyTo(cameraMatrix);

	// Using a diagonal sine wave (sinx + x) makes the time move from fast to slow and vice versa
	//cc.m_angle = m_angle + ((sin(m_angle / 10.0f) + (m_angle / 10.0f))) * 100.0f;
	cc.m_angle += m_deltaTime;
	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);


	// Set Constant Buffer Data
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertex_shader, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixel_shader, m_cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertextShader(vertex_shader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixel_shader);

	// Set Vertex Data
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// Draw Quad
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStip(m_vb->getSizeVertexList(), 0);
}

void Plane::setAnimationSpeed(float speed)
{
	m_speed = speed;
}


void Plane::release()
{
	m_vb->release();
	m_cb->release();
}
