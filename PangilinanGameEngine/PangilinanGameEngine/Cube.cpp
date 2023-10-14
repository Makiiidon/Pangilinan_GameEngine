#include "Cube.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"

Cube::Cube(std::string name, void* shaderByteCode, size_t sizeShader) : AGameObject(name)
{
	vertex vertex_list[] = {
		// FRONT FACE
		{ Vector3D(-0.5f, -0.5f, -0.5f),    Vector3D(1,0,0),  Vector3D(1,0,0) },
		{ Vector3D(-0.5f,  0.5f, -0.5f),    Vector3D(1,1,0),  Vector3D(1,1,0) },
		{ Vector3D(0.5f,  0.5f, -0.5f),    Vector3D(1,1,0),  Vector3D(1,1,0) },
		{ Vector3D(0.5f, -0.5f, -0.5f),    Vector3D(1,0,0),  Vector3D(1,0,0) },

		// BACK FACE
		{ Vector3D(0.5f, -0.5f,  0.5f),    Vector3D(0,1,0),  Vector3D(0,1,0) },
		{ Vector3D(0.5f,  0.5f,  0.5f),    Vector3D(0,1,1),  Vector3D(0,1,1) },
		{ Vector3D(-0.5f,  0.5f,  0.5f),    Vector3D(0,1,1),  Vector3D(0,1,1) },
		{ Vector3D(-0.5f, -0.5f,  0.5f),    Vector3D(0,1,0),  Vector3D(0,1,0) },
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_vertex = ARRAYSIZE(vertex_list);

	unsigned int index_list[] = {
		// FRONT FACE
		0, 1, 2,
		2, 3, 0,
		// BACK FACE
		4, 5, 6,
		6, 7, 4,
		// TOP FACE
		1, 6, 5,
		5, 2, 1,
		// BOTTOM FACE
		7, 0, 3,
		3, 4, 7,
		// RIGHT FACE
		3, 2, 5,
		5, 4, 3,
		// LEFT FACE
		7, 6, 1,
		1, 0, 7
	};

	m_ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);

	// Create a vertex buffer
	m_vb = GraphicsEngine::get()->createVertexBuffer();

	m_vb->load(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);


	constant ccc;
	ccc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&ccc, sizeof(constant));
}



Cube::~Cube()
{
}

void Cube::update(float deltaTime)
{
	m_deltaTime = deltaTime;
	m_ticks += m_deltaTime * m_speed;

	Matrix4x4 temp;

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

void Cube::draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader)
{

	cc.m_view.setIdentity();
	cc.m_projection.setOrthoLH
	(
		(width) / 400.0f,
		(height) / 400.0f,
		-4.0f,
		4.0f
	);

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
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	// Draw Square
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Cube::setAnimationSpeed(float speed)
{
	m_speed = speed;
}

void Cube::release()
{
	m_vb->release();
	m_ib->release();
	m_cb->release();
}