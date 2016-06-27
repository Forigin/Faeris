/*************************************************************************/
/*  FsScene.cc                                                           */
/*************************************************************************/
/* Copyright (C) 2012-2014 nosiclin@foxmail.com                          */
/* Copyright (C) 2014-2015 www.fsource.cn                                */
/*                                                                       */
/* http://www.fsource.cn                                                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/


#include "stage/FsScene.h"
#include "stage/layer/FsLayer.h"
#include "support/util/FsSlowArray.h"
#include "stage/layer/FsColorLayer.h"



NS_FS_BEGIN

Scene* Scene::create()
{
	Scene* ret=new Scene;
	return ret;
}

/* layer operation */
void Scene::push(Layer* layer)
{
	if(layer->getScene())
	{
		FS_TRACE_WARN("layer is already owned by scene");
		return ;
	}
	m_layers->push(layer);

	layer->setScene(this);
}

void Scene::pop()
{
	int size=m_layers->size();
	if(size==0)
	{
		FS_TRACE_WARN("No Layer to pop");
		return;
	}
	Layer* ret=(Layer*)m_layers->get(size-1);
	if( ret==m_touchFocusLayer )
	{
		m_touchFocusLayer=NULL;
	}

	ret->setScene(NULL);
	m_layers->pop();
}

void Scene::insert(int pos,Layer* layer)
{
	if(layer->getScene())
	{
		FS_TRACE_WARN("layer is already owned by scene");
		return ;
	}
	m_layers->insert(pos,layer);
	layer->setScene(this);
}
void Scene::replace(int pos,Layer* layer)
{
	Layer*  ret=(Layer*)m_layers->get(pos);
	if(ret==NULL)
	{
		FS_TRACE_WARN("Index(%d) Layer Out Of Range",pos);
		return; 
	}

	if(ret==m_touchFocusLayer)
	{
		m_touchFocusLayer=NULL;
	}

	ret->setScene(NULL);
	m_layers->set(pos,layer);
}

void Scene::remove(Layer* layer)
{
	if(layer->getScene()!=this)
	{
		FS_TRACE_WARN("Layer is not owned by scene");
		return;
	}

	if(layer==m_touchFocusLayer)
	{
		m_touchFocusLayer=NULL;
	}

	layer->setScene(NULL);
	m_layers->remove(layer);
}

Layer* Scene::top()
{
	return (Layer*)m_layers->top();
}

int Scene::layerNu()
{
	return m_layers->size();
}

Layer* Scene::getLayer(int index)
{
	return (Layer*)m_layers->get(index);
}

int Scene::getLayerIndex(Layer* layer)
{
	int layer_nu=m_layers->size();
	Layer* cur=NULL;

	for(int i=0;i<layer_nu;i++)
	{
		cur=(Layer*)m_layers->get(i);
		if(cur==layer)
		{
			return i;
		}
	}
	return -1;
}

void Scene::clear()
{
	int layer_nu=m_layers->size();
	for(int i=layer_nu-1;i>=0;i--)
	{
		Layer* layer=(Layer*)m_layers->get(i);
		layer->setScene(NULL);
	}
	m_layers->clear();
	m_touchFocusLayer=NULL;
}

void Scene::setTouchEnabled(bool enabled)
{
	m_touchEnabled=enabled;
}

bool Scene::getTouchEnabled()
{
	return m_touchEnabled;
}


void Scene::setTouchesEnabled(bool enabled)
{
	m_touchesEnabled=enabled;
}

bool Scene::getTouchesEnabled()
{
	return m_touchesEnabled;
}





void Scene::setFadeEnabled(bool fade)
{
	m_fadeEnabled=fade;
}
bool Scene::getFadeEnabled()
{
	return m_fadeEnabled;
}


void Scene::setFadeColor(Color c)
{
	m_fadeColor=c;
}


/* event */

void Scene::enter()
{
	/* do nothing */
}
void Scene::exit()
{
	/* do nothing */
}
void Scene::update(float dt)
{
	updateAnimation(dt);
	updateLayers(dt);
}


void Scene::updateLayers(float dt)
{
	m_layers->lock();
	int layer_nu=m_layers->size();
	for(int i=layer_nu-1;i>=0;i--)
	{
		Layer* layer=(Layer*)m_layers->get(i);
		if(layer->getVisible())
		{
			FS_OBJECT_LAMBDA_CALL(layer,onUpdate,update,dt);
		}
	}
	m_layers->unlock();
	m_layers->flush();
}

void Scene::draw(RenderDevice* render)
{
	m_layers->lock();
	int layer_nu=m_layers->size();
	for(int i=0;i<layer_nu;i++)
	{
		Layer* layer=(Layer*)m_layers->get(i);
		if(layer->getVisible())
		{
			FS_OBJECT_LAMBDA_CALL(layer,onDraw,draw,render);
		}
	}
	m_layers->unlock();
	m_layers->flush();


	if(m_fadeEnabled)
	{
		m_fadeLayer->setColor(m_fadeColor);
		m_fadeLayer->draw(render);
	}

}
void Scene::touchBegin(float x,float y)
{
	m_touchFocusLayer=NULL;
	m_layers->lock();
	int layer_nu=m_layers->size();
	for(int i=layer_nu-1;i>=0;i--)
	{
		bool handle=false;
		Layer* layer=(Layer*)m_layers->get(i);
		if((layer->getScene()==this)&&layer->touchEnabled()&&layer->getVisible())
		{
			handle=FS_OBJECT_LAMBDA_CALL(layer,onTouchBegin,touchBegin,x,y);
		}
		if(handle)
		{
			if(layer->getScene()==this)
			{
				m_touchFocusLayer=layer;
			}
			break;
		}
	}

	m_layers->unlock();
	m_layers->flush();
}

void Scene::touchMove(float x,float y)
{
	m_layers->lock();
	if(m_touchFocusLayer&&m_touchFocusLayer->touchEnabled()&&m_touchFocusLayer->getVisible())
	{
		FS_OBJECT_LAMBDA_CALL(m_touchFocusLayer,onTouchMove,touchMove,x,y);
	}
	m_layers->unlock();
	m_layers->flush();

}

void Scene::touchEnd(float x,float y)
{
	m_layers->lock();
	if(m_touchFocusLayer&&m_touchFocusLayer->touchEnabled()&&m_touchFocusLayer->getVisible())
	{
		FS_OBJECT_LAMBDA_CALL(m_touchFocusLayer,onTouchEnd,touchEnd,x,y);
	}
	m_touchFocusLayer=NULL;
	m_layers->unlock();
	m_layers->flush();
}

void Scene::touchesBegin(TouchEvent* event)
{
	m_layers->lock();
	int layer_nu=m_layers->size();
	for(int i=layer_nu-1;i>=0;i--)
	{
		bool handle=false;
		Layer* layer=(Layer*)m_layers->get(i);
		if(layer->getTouchesEnabled()&&layer->getVisible())
		{
			handle=FS_OBJECT_LAMBDA_CALL(layer,onTouchesBegin,touchesBegin,event);
		}
		if(handle)
		{
			break;
		}
	}
	m_layers->unlock();
	m_layers->flush();
}

void Scene::touchesPointerDown(TouchEvent* event)
{
	m_layers->lock();
	int layer_nu=m_layers->size();
	for(int i=layer_nu-1;i>=0;i--)
	{
		bool handle=false;
		Layer* layer=(Layer*)m_layers->get(i);
		if(layer->getTouchesEnabled()&&layer->getVisible())
		{
			handle=FS_OBJECT_LAMBDA_CALL(layer,onTouchesPointerDown,touchesPointerDown,event);
		}
		if(handle)
		{
			break;
		}
	}
	m_layers->unlock();
	m_layers->flush();
}
void Scene::touchesMove(TouchEvent* event)
{
	m_layers->lock();
	int layer_nu=m_layers->size();
	for(int i=layer_nu-1;i>=0;i--)
	{
		bool handle=false;
		Layer* layer=(Layer*)m_layers->get(i);
		if(layer->getTouchesEnabled()&&layer->getVisible())
		{
			handle=FS_OBJECT_LAMBDA_CALL(layer,onTouchesMove,touchesMove,event);
		}
		if(handle)
		{
			break;
		}
	}
	m_layers->unlock();
	m_layers->flush();
}

void Scene::touchesPointerUp(TouchEvent* event)
{
	m_layers->lock();
	int layer_nu=m_layers->size();
	for(int i=layer_nu-1;i>=0;i--)
	{
		bool handle=false;
		Layer* layer=(Layer*)m_layers->get(i);
		if(layer->getTouchesEnabled()&&layer->getVisible())
		{
			handle=FS_OBJECT_LAMBDA_CALL(layer,onTouchesPointerUp,touchesPointerUp,event);
		}
		if(handle)
		{
			break;
		}
	}
	m_layers->unlock();
	m_layers->flush();
}

void Scene::touchesEnd(TouchEvent* event)
{
	m_layers->lock();
	int layer_nu=m_layers->size();
	for(int i=layer_nu-1;i>=0;i--)
	{
		bool handle=false;
		Layer* layer=(Layer*)m_layers->get(i);
		if(layer->getTouchesEnabled()&&layer->getVisible())
		{
			handle=FS_OBJECT_LAMBDA_CALL(layer,onTouchesEnd,touchesEnd,event);
		}
		if(handle)
		{
			break;
		}
	}
	m_layers->unlock();
	m_layers->flush();
}



void Scene::keypadEvent(int type,int keycode)
{
}

void Scene::inputTextEvent(const char* text,int length)
{
}




const char* Scene::className()
{
	return FS_SCENE_CLASS_NAME;
}

Scene::Scene()
{
	init();
}
Scene::~Scene()
{
	destruct();
}

void Scene::init()
{
	m_layers=FsSlowArray::create();
	FS_NO_REF_DESTROY(m_layers);

	m_fadeColor=Color4f(1.0f,1.0f,1.0f,0.5f);

	m_fadeEnabled=false;
	m_fadeLayer=ColorLayer::create(m_fadeColor);
	FS_NO_REF_DESTROY(m_fadeLayer);


	m_touchFocusLayer=NULL;

	m_touchEnabled=true;
	m_touchesEnabled=true;


	onEnter=nullptr;
	onExit=nullptr;

	onUpdate=nullptr;
	onDraw=nullptr;

	onTouchBegin=nullptr;
	onTouchMove=nullptr;
	onTouchEnd=nullptr;

	onTouchesBegin=nullptr;
	onTouchesPointerDown=nullptr;
	onTouchesMove=nullptr;
	onTouchesPointerUp=nullptr;
	onTouchesEnd=nullptr;

	onKeypadEvent=nullptr;

}




void Scene::destruct()
{
	FS_DESTROY(m_layers);
	FS_DESTROY(m_fadeLayer);
}


NS_FS_END





