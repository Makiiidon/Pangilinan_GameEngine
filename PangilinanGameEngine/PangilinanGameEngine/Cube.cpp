#include "Cube.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"

Cube::Cube(std::string name, void* shaderByteCode, size_t sizeShader) : AGameObject(name)
{
	vertex vertex_list[] = {
		// Front
		{Vector3D( -0.5f, -0.5f,  -0.5f),     Vector3D(0, 0, 0),   Vector3D(0, 0, 0)}, // POS1 - Lower Left
		{Vector3D( -0.5f,  0.5f,  -0.5f),     Vector3D(1, 1, 0),   Vector3D(1, 1, 0)}, // POS2 - Upper Left
		{Vector3D(  0.5f,  0.5f,  -0.5f),     Vector3D(0, 0, 1),   Vector3D(0, 0, 1)}, // POS3 - Lower Right
		{Vector3D(  0.5f, -0.5f,  -0.5f),     Vector3D(1, 1, 1),   Vector3D(1, 1, 1)}, // POS4 - Upper Right

		// Back
		{Vector3D(  0.5f, -0.5f,  0.5f),     Vector3D(0, 0, 0),   Vector3D(0, 0, 0)}, // POS1 - Lower Left
		{Vector3D(  0.5f,  0.5f,  0.5f),     Vector3D(1, 1, 0),   Vector3D(1, 1, 0)}, // POS2 - Upper Left
		{Vector3D( -0.5f,  0.5f,  0.5f),     Vector3D(0, 0, 1),   Vector3D(0, 0, 1)}, // POS3 - Lower Right
		{Vector3D( -0.5f, -0.5f,  0.5f),     Vector3D(1, 1, 1),   Vector3D(1, 1, 1)}, // POS4 - Upper Right
	};

	// Create a vertex buffer
	vb = GraphicsEngine::get()->createVertexBuffer();
	vb->load(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);

	unsigned int index_list[] =
	{
		// Front side
		0,1,2, // First Triangle
		2,3,0, // Second Triangle

		// Back Side
		4,5,6,
		6,7,4,

		// Top Side
		1,6,5,
		5,2,1,

		// Bottom Side
		7,0,3,
		3,4,7,

		// Right Side
		3,2,5,
		5,4,3,

		// Left Side
		7,6,1,
		1,0,7
	};

	ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	ib->load(index_list, size_index_list);

	constant cc;
	cc.m_angle = 0;

	cb = GraphicsEngine::get()->createConstantBuffer();
	cb->load(&cc, sizeof(constant));
}

Cube::~Cube()
{

}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	transform.setIdentity();
	transform.setScale(localScale);
	this->cc.m_world *= transform;

	transform.setIdentity();
	transform.setTranslation(localPosition);
	this->cc.m_world *= transform;

	transform.setIdentity();
	transform.setRotationX(localRotation.m_x);
	this->cc.m_world *= transform;

	transform.setIdentity();
	transform.setRotationY(localRotation.m_y);
	this->cc.m_world *= transform;

	transform.setIdentity();
	transform.setRotationZ(localRotation.m_z);
	this->cc.m_world *= transform;

	ticks += this->deltaTime;
	//Using a diagonal sine wave (sinx + x) makes the time move from fast to slow and vice versa
	//cc.m_angle = m_delta_time + ((sin(m_delta_time / 10.0f) + (m_delta_time / 10.0f))) * 100.0f;
	this->cc.m_angle += ticks * speed;
}

void Cube::draw(RECT rc, VertexShader* vertexShader, PixelShader* pixelShader)
{
	this->cc.m_view.setIdentity();
	this->cc.m_projection.setOrthoLH
	(
		(rc.right - rc.left) / 300.0f,
		(rc.bottom - rc.top) / 300.0f,
		-4.0f,
		4.0f
	);

	
	this->cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	// Set Constant Buffer Data
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, this->cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, this->cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertextShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	// Set Vertex Data
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->ib);

	// Draw Cube
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);

}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}




void Cube::release()
{
	vb->release();
	cb->release();
	ib->release();
	
}
