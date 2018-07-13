#include "RenderManager.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

RenderManager & RenderManager::get()
{
	static RenderManager* instance = NULL;
	if (instance == NULL)
	{
		instance = new RenderManager();
	}
	_ASSERT(instance);
	return *instance;
}

void RenderManager::startUp()
{
	//Any necessary initialization goes here
}

void RenderManager::shutDown()
{
}

void RenderManager::render()
{
	for (int i = 0; i < m_renderableObjs.size(); i++)
	{
		m_renderableObjs.at(i)->render();
	}
}

void RenderManager::addRenderableObj(RenderableObject * renderableObj)
{
	m_renderableObjs.push_back(renderableObj);
}

void RenderManager::clear()
{
	m_renderableObjs.clear();
}

