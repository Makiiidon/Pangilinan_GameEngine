#pragma once
#include "AGameObject.h"
#include <vector>
#include <unordered_map>

class GameObjectManager
{
public:
	typedef std::vector<AGameObject*> List;
	typedef std::unordered_map<std::string, AGameObject*> HashTable;

	enum PrimitiveType {
		CUBE,
		PLANE,
		SPHERE
	};

	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(std::string name);
	List getAllGameObjects();
	int activeObjects();
	void updateAll();
	void renderAll(int viewWidth, int viewHeight, VertexShader* vs, PixelShader* ps);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(std::string name);
	void setSelectedObject(std::string name);
	void setSelectedObject(AGameObject* gameObject);
	AGameObject* getSelectedObject();

private:
	List gameObjects;
	HashTable hashTable;

};

