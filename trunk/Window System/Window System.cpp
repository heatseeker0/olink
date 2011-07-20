//
//  Window System.cpp
//  Zenilib
//
//  Created by Alex Turner on 7/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Window System.h"

namespace GUISystem {
    
#pragma mark Initialization Methods
    Window_System::Window_System()
    {
        m_Context = new Context;
    }
    
    Window_System::~Window_System()
    {
        delete m_Context;
    }
    
#pragma mark Context Methods
    
    void Window_System::setCurrentContextToSelf()
    {
        currentContext = m_Context;
    }
    
    void Window_System::setCurrentContext(Context* newContext)
    {
        currentContext = newContext;
    }
    
    Context* Window_System::getCurrentContext()
    {
        return currentContext;
    }
    
    Context* Window_System::getContext()
    {
        return m_Context;
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
        object.render();
    }
    
    void Window_System::renderAllObjects()
    {
        for (int i = 0;i < currentContext->objects.size();i++)
            renderObject(currentContext->objects[i]);
    }
    
    void Window_System::render()
    {
        renderAllObjects();
    }
    
    void Window_System::renderContext(Context* contextToRender)
    {
        for (int i = 0;i < contextToRender->objects.size();i++)
            renderObject(contextToRender->objects[i]);
    }
}
