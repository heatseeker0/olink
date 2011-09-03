//
//  Window System.cpp
//  Zenilib
//
//  Created by Alex Turner on 7/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Window System.h"

namespace GUISystem {
	
	Context *Window_System::currentContext;
    
#pragma mark Initialization Methods
    Window_System::Window_System(Zeni::Point2f screen)
    {
		this->screenSize = screen;
		
        if (currentContext == NULL)
			this->createNewCurrentContext();
		else
			m_Context = new Context;
    }
    
    Window_System::~Window_System()
    {
        delete m_Context;
    }
    
#pragma mark Context Methods
    
    void Window_System::setCurrentContextToSelf()
    {
        Window_System::currentContext = m_Context;
    }
    
    void Window_System::setCurrentContext(Context* newContext)
    {
        Window_System::currentContext = newContext;
    }
    
    Context* Window_System::getCurrentContext()
    {
        return Window_System::currentContext;
    }
    
    Context* Window_System::getContext()
    {
        return m_Context;
    }
	
	void Window_System::createNewCurrentContext()
	{
		Context* newCurrentContext = new Context;
		newCurrentContext->UpperLeft.x = 0.0f;
		newCurrentContext->UpperLeft.y = 0.0f;
		newCurrentContext->LowerRight.x = screenSize.x;
		newCurrentContext->LowerRight.y = screenSize.y;
		
		Window_System::currentContext = newCurrentContext;
		
		m_Context = newCurrentContext;
	}
    
#pragma mark GUIObject Methods
    
    void Window_System::addObject(GUIObject object)
    {
        m_Context->objects.push_back(object); 
	}
    
    void Window_System::removeObject(GUIObject object)
    {
        for (int i = 0;i < m_Context->objects.size();i++)
        {
            if (m_Context->objects[i].getUID() == object.getUID())
            {
                m_Context->objects.erase(m_Context->objects.begin()+i);
				
				break;
            }
        }
    }
    
    void Window_System::addObject(Context *contextToAddTo, GUIObject object)
    {
        contextToAddTo->objects.push_back(object); 
    }
    
    void Window_System::removeObject(Context *contextToRemoveFrom, GUIObject object)
    {
        for (int i = 0;i < contextToRemoveFrom->objects.size();i++)
        {
            if (contextToRemoveFrom->objects[i].getUID() == object.getUID())
            {
                contextToRemoveFrom->objects.erase(contextToRemoveFrom->objects.begin()+i);
                break;
            }
        }
    }
    
#pragma mark Render Methods
    
    void Window_System::renderObject(GUIObject object)
    {
		Zeni::Point2f cords = object.getCoordinates();
		
		Zeni::Point2f toMoveBy(0.0f, 0.0f);
		
		if (currentContext != NULL)
			toMoveBy = currentContext->LowerRight;
				
        object.renderAt(Zeni::Point2f(cords.x + toMoveBy.x, cords.y + toMoveBy.y));
	}
    
    void Window_System::renderAllObjects()
    {
		if (currentContext == NULL)
			return;
		
        for (int i = 0;i < Window_System::currentContext->objects.size();i++)
            renderObject(Window_System::currentContext->objects[i]);
    }
    
    void Window_System::render()
    {
        renderAllObjects();
		//Could also just do renderContext(Window_System::currentContext);
    }
    
    void Window_System::renderContext(Context* contextToRender)
    {
		Context *oldContext = Window_System::currentContext;
		Window_System::currentContext = contextToRender;
		
        for (int i = 0;i < contextToRender->objects.size();i++)
            renderObject(contextToRender->objects[i]);
		
		Window_System::currentContext = oldContext;
    }
}
