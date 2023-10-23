#include "GameObjectManager.h"
#include "Cube.h"
#include "Plane.h"
#include "EngineTime.h"


GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();

}

void GameObjectManager::destroy()
{
	for (AGameObject* obj : gameObjects) {
		obj->release();
	}
	gameObjects.clear();
	hashTable.clear();
	sharedInstance = nullptr;
}

AGameObject* GameObjectManager::findObjectByName(std::string name)
{
	int found = -1;
	int counter = 0;
	while (found != -1) {
		if (gameObjects[counter]->getName() == name)
		{
			found = counter;
			return gameObjects[counter];
		}
		counter++;
	}

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
	float deltaTime = EngineTime::getDeltaTime();
	for (int i = 0; i < gameObjects.size(); i++) 
	{
		gameObjects[i]->update(deltaTime);
	}
}

void GameObjectManager::renderAll(int viewWidth, int viewHeight, VertexShader* vs, PixelShader* ps)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->draw(viewWidth, viewHeight, vs, ps);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	gameObjects.push_back(gameObject);
	hashTable.insert({ gameObject->getName(), gameObject });
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
{
	switch (type)
	{
	case GameObjectManager::CUBE:
	{
		Cube* cube = new Cube("Cube", shaderByteCode, sizeShader);
		gameObjects.push_back(cube);
		hashTable.insert({ cube->getName(), cube });
		break;
	}

	case GameObjectManager::PLANE:
	{
		Plane* plane = new Plane("Plane", shaderByteCode, sizeShader);
		gameObjects.push_back(plane);
		hashTable.insert({ plane->getName(), plane });
		break;
	}

	case GameObjectManager::SPHERE:

		break;

	default:

		break;
	}
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
}

void GameObjectManager::deleteObjectByName(std::string name)
{
	hashTable.erase(name);
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
