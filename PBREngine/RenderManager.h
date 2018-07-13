#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "RenderableObject.h"

class RenderManager
{
	std::vector<RenderableObject *> m_renderableObjs;

public:
	RenderManager();
	~RenderManager();

	//Initialization of manager
	void startUp();

	//Termination of manager
	void shutDown();

	//Get the singleton instance
	static RenderManager& get();

	//Render the objects
	void render();
	void writeOBJ(std::string objFile);

	//Add a renderable object
	void addRenderableObj(RenderableObject * renderableObj);

	//Remove all renderable objects
	void clear();
};

#endif
