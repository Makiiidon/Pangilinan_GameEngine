#include "Quad.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"

Quad::Quad(std::string name, void* shaderByteCode, size_t sizeShader) : AGameObject(name)
{

	vertex vertex_list[] = {
		// Front
		{Vector3D( -0.5f, -0.5f,  0.0f ),     Vector3D(0, 0, 0),   Vector3D(0, 0, 0)}, // POS1 - Lower Left
		{Vector3D( -0.5f,  0.5f,  0.0f ),     Vector3D(1, 1, 0),   Vector3D(1, 1, 0)}, // POS2 - Upper Left
		{Vector3D(  0.5f,  0.5f,  0.0f ),     Vector3D(0, 0, 1),   Vector3D(0, 0, 1)}, // POS3 - Lower Right
		{Vector3D(  0.5f, -0.5f,  0.0f ),     Vector3D(1, 1, 1),   Vector3D(1, 1, 1)}, // POS4 - Upper Right
	};
	// Create a vertex buffer
	vb = GraphicsEngine::get()->createVertexBuffer();

	constant cc;
	cc.m_angle = 0;

	cb = GraphicsEngine::get()->createConstantBuffer();
	cb->load(&cc, sizeof(constant));
}

Quad::~Quad()
{
}

void Quad::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	transform.setIdentity();
	transform.setScale(localScale);
	cc.m_world *= transform;

	transform.setIdentity();
	transform.setTranslation(localPosition);
	cc.m_world *= transform;

	transform.setIdentity();
	transform.setRotationX(localRotation.m_x);
	cc.m_world *= transform;

	transform.setIdentity();
	transform.setRotationY(localRotation.m_y);
	cc.m_world *= transform;

	transform.setIdentity();
	transform.setRotationZ(localRotation.m_z);
	cc.m_world *= transform;

	ticks += this->deltaTime;
	//Using a diagonal sine wave (sinx + x) makes the time move from fast to slow and vice versa
	//cc.m_angle = m_delta_time + ((sin(m_delta_time / 10.0f) + (m_delta_time / 10.0f))) * 100.0f;
	cc.m_angle += ticks * speed;


}

void Quad::draw(RECT rc, VertexShader* vertexShader, PixelShader* pixelShader)
{
	cc.m_view.setIdentity();
	cc.m_projection.setOrthoLH
	(
		rc.right - rc.left / 400.0f,
		rc.bottom - rc.top / 400.0f,
		-4.0f,
		4.0f
	);

	// Set Constant Buffer Data
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertextShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	// Set Vertex Data
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vb);

	// Draw Quad
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStip(vb->getSizeVertexList(), 0);
}

void Quad::setAnimSpeed(float speed)
{
}


void Quad::release()
{
	vb->release();
	cb->release();
}
