//
//  Window System.cpp
//  Zenilib
//
//  Created by Alex Turner on 7/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Window System.h"

#include <iostream>

namespace GUISystem {
	
	Context *Window_System::currentContext;
    
#pragma mark Initialization Methods
    Window_System::Window_System(std::pair<Zeni::Point2f, Zeni::Point2f> screen)
    {
		this->screenSize = screen;
		
        if (currentContext == NULL)
			this->createNewCurrentContext();
		else
			m_Context = new Context;
		
		m_Context->UpperLeft = screen.first;
		m_Context->LowerRight = screen.second;
		
		busyWidget = 0;
		isWidgetBusy = false;
    }
    
    Window_System::~Window_System()
    {
		if (currentContext == m_Context)
			currentContext = NULL;
		
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
		newCurrentContext->LowerRight.x = screenSize.second.x;
		newCurrentContext->LowerRight.y = screenSize.second.y;
		
		Window_System::currentContext = newCurrentContext;
		
		m_Context = newCurrentContext;
	}
    
#pragma mark GUIObject Methods
    
    void Window_System::addObject(GUIObject *object)
    {
		for (int i = 0;i < m_Context->objects.size();i++)
        {
            if (m_Context->objects[i]->getUID() == object->getUID())
				return;
		}
		
        m_Context->objects.push_back(object);
		object->setWindowSystem(this);
	}
    
    void Window_System::removeObject(GUIObject *object)
    {
        for (int i = 0;i < m_Context->objects.size();i++)
        {
            if (m_Context->objects[i]->getUID() == object->getUID())
            {
                m_Context->objects.erase(m_Context->objects.begin()+i);
				
				break;
            }
        }
    }
    
    void Window_System::addObject(Context *contextToAddTo, GUIObject *object)
    {
		for (int i = 0;i < contextToAddTo->objects.size();i++)
        {
            if (contextToAddTo->objects[i]->getUID() == object->getUID())
				return;
		}
		
        contextToAddTo->objects.push_back(object);
		object->setWindowSystem(this);
    }
    
    void Window_System::removeObject(Context *contextToRemoveFrom, GUIObject *object)
    {
        for (int i = 0;i < contextToRemoveFrom->objects.size();i++)
        {
            if (contextToRemoveFrom->objects[i]->getUID() == object->getUID())
            {
                contextToRemoveFrom->objects.erase(contextToRemoveFrom->objects.begin()+i);
                break;
            }
        }
    }
	
	void Window_System::moveObjectToForeground(GUIObject *object)
	{
		this->removeObject(object);
		this->addObject(object);
	}
    
#pragma mark Render Methods
    
    void Window_System::renderObject(GUIObject *object)
    {
		object->renderObject();
	}
    
    void Window_System::renderAllObjects()
    {
		Context *oldCurrentContext = getCurrentContext();
		
		setCurrentContextToSelf();
		
		Zeni::get_Video().set_2d_view(std::make_pair(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(Window_System::currentContext->LowerRight.x - Window_System::currentContext->UpperLeft.x, Window_System::currentContext->LowerRight.y - Window_System::currentContext->UpperLeft.y)),
									  std::make_pair(Window_System::currentContext->UpperLeft, Window_System::currentContext->LowerRight));
		
        for (int i = 0;i < Window_System::currentContext->objects.size();i++)
            renderObject(Window_System::currentContext->objects[i]);
		
		setCurrentContext(oldCurrentContext);
		
		Zeni::get_Video().set_2d_view(std::make_pair(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(Window_System::currentContext->LowerRight.x - Window_System::currentContext->UpperLeft.x, Window_System::currentContext->LowerRight.y - Window_System::currentContext->UpperLeft.y)),
									  std::make_pair(Window_System::currentContext->UpperLeft, Window_System::currentContext->LowerRight));
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
		
		Zeni::get_Video().set_2d_view(std::make_pair(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(800.0f, 600.0f)),
									  std::make_pair(Window_System::currentContext->UpperLeft, Window_System::currentContext->LowerRight));
		
        for (int i = 0;i < contextToRender->objects.size();i++)
            renderObject(contextToRender->objects[i]);
		
		Window_System::currentContext = oldContext;
		
		Zeni::get_Video().set_2d_view(std::make_pair(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(800.0f, 600.0f)),
									  std::make_pair(Window_System::currentContext->UpperLeft, Window_System::currentContext->LowerRight));
    }
	
	void Window_System::renderCurrentContext()
	{
		if (Window_System::currentContext == NULL)
			return;
		
		Zeni::get_Video().set_2d_view(std::make_pair(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(800.0f, 600.0f)),
									  std::make_pair(Window_System::currentContext->UpperLeft, Window_System::currentContext->LowerRight));
		
        for (int i = 0;i < Window_System::currentContext->objects.size();i++)
			Window_System::currentContext->objects[i]->renderObject();
	}
	
#pragma mark Widget Methods
	
	void Window_System::on_key(const SDL_KeyboardEvent &event)
	{
		Context *oldCurrentContext = getCurrentContext();
		
		setCurrentContextToSelf();
		
		if(busyWidget) {
			busyWidget->on_key(event.keysym, event.type == SDL_KEYDOWN);

			if(!busyWidget->is_busy()) {
				busyWidget = 0;
				isWidgetBusy = false;
			}
		}
		else {
			//std::sort(m_widgets.begin(), m_widgets.end(), &widget_layer_less);
			
			for(std::vector<GUIObject *>::iterator it = currentContext->objects.begin(); it != currentContext->objects.end(); ++it) {
				(*it)->getWidget()->on_key(event.keysym, event.type == SDL_KEYDOWN);
				
				if(!busyWidget && (*it)->getWidget()->is_busy()) {
					busyWidget = (*it)->getWidget();
					isWidgetBusy = true;
				}
			}
		}
		
		setCurrentContext(oldCurrentContext);
	}
	
	void Window_System::on_mouse_button(const SDL_MouseButtonEvent &event)
	{
		Context *oldCurrentContext = getCurrentContext();
		
		setCurrentContextToSelf();
		
		using namespace Zeni;
				
		const Point2f projected = m_projector.unproject(Point2f(float(event.x), float(event.y)));
		
		if(busyWidget) {
			busyWidget->on_mouse_button(Point2i(int(projected.x), int(projected.y)), event.type == SDL_MOUSEBUTTONDOWN, event.button);
			
			if(!busyWidget->is_busy()) {
				busyWidget = 0;
				isWidgetBusy = false;
			}
		}
		else {
			bool alreadySentToObject = false;
			for(std::vector<GUIObject *>::iterator it = currentContext->objects.begin(); it != currentContext->objects.end(); ++it) {				
				if ((projected.x > (*it)->getCoordinates().x && projected.x < (*it)->getCoordinates().x + (*it)->getSize().x) &&
					(projected.y > (*it)->getCoordinates().y && projected.y < (*it)->getCoordinates().y + (*it)->getSize().y))
				{
					alreadySentToObject = true;
				}
				
				(*it)->getWidget()->on_mouse_button(Point2i(int(projected.x), int(projected.y)), event.type == SDL_MOUSEBUTTONDOWN, event.button);
				
				if(!busyWidget && (*it)->getWidget()->is_busy()) {
					busyWidget = (*it)->getWidget();
					isWidgetBusy = true;
				}
				
				if (alreadySentToObject)
					break;
			}
		}
		
		setCurrentContext(oldCurrentContext);
	}
	
	void Window_System::on_mouse_motion(const SDL_MouseMotionEvent &event)
	{
		Context *oldCurrentContext = getCurrentContext();
		
		setCurrentContextToSelf();
		
		if(busyWidget) {
			busyWidget->on_mouse_motion(Zeni::Point2i(event.x, event.y));
			
			if(!busyWidget->is_busy()) {
				busyWidget = 0;
				isWidgetBusy = false;
			}
		}
		else {
			for(std::vector<GUIObject *>::iterator it = currentContext->objects.begin(); it != currentContext->objects.end(); ++it) {	
				Zeni::Point2i motion(event.x, event.y);
				(*it)->getWidget()->on_mouse_motion(motion);
				
				if(!busyWidget && (*it)->getWidget()->is_busy()) {
					busyWidget = (*it)->getWidget();
					isWidgetBusy = true;
				}
			}
		}
		
		setCurrentContext(oldCurrentContext);
	}
	
	void Window_System::perform_logic()
	{
		Context *oldCurrentContext = getCurrentContext();
		
		setCurrentContextToSelf();
		
		m_projector = Zeni::Projector2D(std::pair<Zeni::Point2f, Zeni::Point2f>(Zeni::Point2f(0.0f, 0.0f), screenSize.second), Zeni::get_Video().get_viewport());
		
		for(std::vector<GUIObject *>::iterator it = currentContext->objects.begin(); it != currentContext->objects.end(); ++it)
			(*it)->getWidget()->perform_logic();
		
		setCurrentContext(oldCurrentContext);
	}
}
