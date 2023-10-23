#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

GameObjectManager* GameObjectManager::getInstance()
{
	return nullptr;
}

void GameObjectManager::initialize()
{
}

void GameObjectManager::destroy()
{
}

AGameObject* GameObjectManager::findObjectByName(std::string name)
{
	return nullptr;
}

GameObjectManager::List GameObjectManager::getAllGameObjects()
{
	return gameObjects;
}

int GameObjectManager::activeObjects()
{
	return gameObjects.size();
}

void GameObjectManager::updateAll()
{
}

void GameObjectManager::renderAll(int viewWidth, int viewHeight, VertexShader* vs, PixelShader* ps)
{
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
{
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
}

void GameObjectManager::deleteObjectByName(std::string name)
{
}

void GameObjectManager::setSelectedObject(std::string name)
{
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject)
{
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return nullptr;
}
