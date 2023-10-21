#include "GUIHandler.h"
GUIHandler* GUIHandler::sharedInstance = nullptr;

GUIHandler::GUIHandler()
{
}

GUIHandler::~GUIHandler()
{
}

bool GUIHandler::init(ID3D11Device *device, ID3D11DeviceContext *device_context)
{


	return true;
}

void GUIHandler::onUpdateStart()
{
}

void GUIHandler::onUpdateEnd()
{
}

bool GUIHandler::release()
{
	return false;
}

GUIHandler* GUIHandler::get()
{
	return nullptr;
}
