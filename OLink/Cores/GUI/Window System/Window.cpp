//
//  Window.cpp
//  Application
//
//  Created by Alex Turner on 9/8/11.
//  Copyright 2011 OLink. All rights reserved.
//

#include "Window.h"

namespace GUISystem {
	
	inline Window::Window(const Zeni::Point2f &UpperLeft, const Zeni::Point2f &Size, Window_Delegate *delegate, V_WindowBar *windowBar)
	: GUIObject(UpperLeft),
	Widget_Rectangle(UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y)),
	windowSystem(std::pair<Zeni::Point2f, Zeni::Point2f>(Zeni::Point2f(UpperLeft.x, UpperLeft.y), Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y)))
	{
		m_state = NORMAL;
		
		this->delegate = delegate;
		
		if (windowBar == NULL)
		{
			windowBar = new Window_Bar();
			windowSystem.addObject(windowBar->getGUIObject());
		}
		else
			windowSystem.addObject(windowBar->getGUIObject());
	}
	
	inline const Window::State & Window::getState()
	{
		return m_state;
	}
	
	void Window::lendObject(GUIObject &object)
	{
		windowSystem.addObject(&object);
	}
	
	void Window::unlendObject(GUIObject &object)
	{
		windowSystem.removeObject(&object);
	}
	
	void Window::on_mouse_button(const Zeni::Point2i &pos, const bool &down, const int &button)
	{
		
	}
	
	void Window::on_mouse_motion(const Zeni::Point2i &pos)
	{
		
	}
	
	void Window::renderObject()
	{
		this->render();
	}
	
	void Window::renderAt(Zeni::Point2f UpperLeft)
	{
		
	}
		
	void Window::transform(Zeni::Point2f UpperLeft)
	{
		
	}
	
	void Window::moveTo(Zeni::Point2f UpperLeft)
	{
		
	}
	
	Window_Bar::Window_Bar()
	: GUIObject(Zeni::Point2f(0.0f, 0.0f))
	{
		
	}
	
	Window_Bar::~Window_Bar()
	{
		
	}
	
	void Window_Bar::updateWithWindowWith(float windowWidth)
	{
		
	}
	
	void Window_Bar::windowMoved(Zeni::Point2f newPositionOfWindow)
	{
		
	}
	
	const float Window_Bar::getWindowBarWidth()
	{
		
	}
	
	void Window_Bar::renderObject()
	{
		
	}
	
	void Window_Bar::renderAt(Zeni::Point2f UpperLeft)
	{
		
	}
}
