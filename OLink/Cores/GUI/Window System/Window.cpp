//
//  Window.cpp
//  Application
//
//  Created by Alex Turner on 9/8/11.
//  Copyright 2011 OLink. All rights reserved.
//

#include <zenilib.h>

#include "Window.h"

namespace GUISystem {
	
// Window Class

	Window::Window(const Zeni::Point2f &UpperLeft, const Zeni::Point2f &Size, Zeni::Color color, Window_Delegate *delegate, V_WindowBar *windowBar)
	: GUIObject(UpperLeft, Size),
	Widget_Rectangle(UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y)),
	windowSystem(std::make_pair(UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y)))
	{
		createdWindowBar = false;
		
		if (windowBar == NULL)
		{
			this->windowBar = new Window_Bar();
			createdWindowBar = true;
		}
		else
			this->windowBar = windowBar;
		
		this->colorRenderer = new Zeni::Widget_Renderer_Color(color);
		this->give_Renderer(colorRenderer);
		
		this->OriginalSize = Size;
		
		this->windowBar->windowMoved(this->getCoordinates());
		this->windowBar->updateWithWindowWith(this->getSize().x);
		this->windowBar->setDelegate(this);
		this->windowBar->getGUIObject()->setWindowSystem(this->getWindowSystem());
		
		this->resizingWindow = false;
		
		this->delegate = delegate;
	}
	
	Window::Window(const Zeni::Point2f &UpperLeft, const Zeni::Point2f &Size, Zeni::String texture, Window_Delegate *delegate, V_WindowBar *windowBar)
	: GUIObject(UpperLeft, Size),
	Widget_Rectangle(UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y)),
	windowSystem(std::make_pair(UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y)))
	{
		createdWindowBar = false;
		
		if (windowBar == NULL)
		{
			this->windowBar = new Window_Bar();
			createdWindowBar = true;
		}
		else
			this->windowBar = windowBar;
		
		this->textureRenderer = new Zeni::Widget_Renderer_Texture(texture);
		this->give_Renderer(textureRenderer);
		
		this->OriginalSize = Size;
		
		this->windowBar->windowMoved(this->getCoordinates());
		this->windowBar->updateWithWindowWith(this->getSize().x);
		this->windowBar->setDelegate(this);
		this->windowBar->getGUIObject()->setWindowSystem(this->getWindowSystem());
		
		this->resizingWindow = false;
		
		this->delegate = delegate;
	}
	
	void Window::setWindowSystem(Window_System *windowSystem)
	{
		this->GUIObject::setWindowSystem(windowSystem);
		this->windowBar->getGUIObject()->setWindowSystem(this->getWindowSystem());
	}
	
	Window::~Window()
	{
		if (createdWindowBar)
			delete windowBar;
	}
	
	inline const Window::State & Window::getState()
	{
		return m_state;
	}
	
	void Window::lendObject(GUIObject *object)
	{
		if (object->getType() == Window_T)
		{
			std::cerr << "Error! Cannot add window to another window!" << std::endl;
			
			assert("Error caught in OLink!");
			
			return;
		}
		
		windowSystem.addObject(object);
	}
	
	void Window::unlendObject(GUIObject *object)
	{
		windowSystem.removeObject(object);
	}
	
	void Window::on_mouse_button(const Zeni::Point2i &pos, const bool &down, const int &button)
	{
		if ((pos.x < (this->windowSystem.getContext()->LowerRight.x + 5) && pos.x > (this->windowSystem.getContext()->UpperLeft.x - 5)) &&
			(pos.y < (this->windowSystem.getContext()->LowerRight.y + 5) && pos.y > (this->windowSystem.getContext()->UpperLeft.y - 5)))
		{
			this->getWindowSystem()->moveObjectToForeground(this);
		}
		
		if ((((pos.x < (this->windowSystem.getContext()->LowerRight.x + 5) && pos.x > (this->windowSystem.getContext()->LowerRight.x - 5)) ||
			 (pos.x < (this->windowSystem.getContext()->UpperLeft.x + 5) && pos.x > (this->windowSystem.getContext()->UpperLeft.x - 5))) &&
			((pos.y < (this->windowSystem.getContext()->UpperLeft.y + 5) && pos.y > (this->windowSystem.getContext()->UpperLeft.y - 5)) ||
			 (pos.y > (this->windowSystem.getContext()->LowerRight.y - 5) && pos.y < (this->windowSystem.getContext()->LowerRight.y + 5)))) &&
			down == true && resizingWindow == false)
		{
			resizingWindow = true;
			
			return;
		}
		else if (down == false && resizingWindow == true)
		{
			resizeToPoint(Zeni::Point2f(pos));
			
			resizingWindow = false;
						
			return;
		}
		
		windowBar->getGUIObject()->getWidget()->on_mouse_button(pos, down, button);
		
		SDL_MouseButtonEvent event;
		event.x = pos.x - windowSystem.getContext()->UpperLeft.x;
		event.y = pos.y - windowSystem.getContext()->UpperLeft.y;
		event.type = (down ? SDL_MOUSEBUTTONDOWN : SDL_MOUSEBUTTONUP);
		event.button = button;
		
		windowSystem.on_mouse_button(event);
	}
	
	void Window::on_mouse_motion(const Zeni::Point2i &pos)
	{
		if (resizingWindow)
		{
			resizeToPoint(Zeni::Point2f(pos));
			
			return;
		}
		
		windowBar->getGUIObject()->getWidget()->on_mouse_motion(pos);
		
		SDL_MouseMotionEvent event;
		event.x = pos.x - windowSystem.getContext()->UpperLeft.x;
		event.y = pos.y - windowSystem.getContext()->UpperLeft.y;
		
		windowSystem.on_mouse_motion(event);
	}
	
	void Window::perform_logic()
	{
		windowSystem.perform_logic();
		
		windowBar->getGUIObject()->getWidget()->perform_logic();
	}
	
	void Window::on_key(const SDL_keysym &keysym, const bool &down)
	{
		SDL_KeyboardEvent event;
		event.keysym = keysym;
		event.type = (down ? SDL_KEYDOWN : SDL_KEYUP);
		windowSystem.on_key(event);
		
		windowBar->getGUIObject()->getWidget()->on_key(keysym, down);
	}
	
	void Window::renderObject()
	{
		if (this->m_state != MINIMIZED && this->m_state != CLOSED)
		{
			this->render();
			
			windowSystem.renderAllObjects();
		}
		
		if (this->m_state != CLOSED)
			windowBar->getGUIObject()->renderObject();
	}
	
	void Window::renderAt(Zeni::Point2f UpperLeft)
	{
		Zeni::Point2f oldPosition = this->getCoordinates();
		this->moveTo(UpperLeft);
		
		this->renderObject();
		
		this->moveTo(oldPosition);
	}
	
	void Window::transform(Zeni::Point2f UpperLeft)
	{
		this->GUIObject::transform(UpperLeft);
		
		this->set_upper_left(this->getCoordinates());
		this->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
		
		Context* windowSystemContext = this->windowSystem.getContext();
		
		windowSystemContext->UpperLeft += UpperLeft;
		windowSystemContext->LowerRight += UpperLeft;
		
		this->windowBar->windowMoved(this->getCoordinates());
	}
	
	void Window::moveTo(Zeni::Point2f UpperLeft)
	{
		this->GUIObject::moveTo(UpperLeft);
		
		this->set_upper_left(this->getCoordinates());
		this->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
		
		Context* windowSystemContext = this->windowSystem.getContext();
		
		windowSystemContext->UpperLeft = this->getCoordinates();
		windowSystemContext->LowerRight = Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y);
		
		this->windowBar->windowMoved(this->getCoordinates());
	}
	
	void Window::closeWindow()
	{
		m_state = CLOSED;
		
		this->on_close();
		
		if (this->delegate != NULL)
			this->delegate->window_close(this);
	}
	
	void Window::minimizeWindow()
	{
		if (m_state != MINIMIZED)
		{
			m_state = MINIMIZED;
			
			this->on_minimize();
			
			if (this->delegate != NULL)
				this->delegate->window_minimize(this);
		}
		else if (m_state == MINIMIZED)
		{
			m_state = NORMAL;
			
			this->on_unminimize();
			
			if (this->delegate != NULL)
				this->delegate->window_unminimize(this);
		}
	}
	
	void Window::maximizeWindow()
	{
		if (m_state != MAXIMIZED)
		{
			m_state = MAXIMIZED;
			
			this->on_maximize();
			
			if (this->delegate != NULL)
				this->delegate->window_maximize(this);
			
			Context* windowSystemContext = this->windowSystem.getContext();
			
			this->OldUpperLeft = windowSystemContext->UpperLeft;
			this->OldSize = this->getSize();
			
			this->setSize(Zeni::Point2f(Zeni::get_Video().get_render_target_size()));
			
			this->moveTo(Zeni::Point2f(0.0f, 0.0f));
			
			this->windowBar->updateWithWindowWith(this->getSize().x);
		}
		else if (m_state == MAXIMIZED)
		{
			m_state = NORMAL;
			
			this->on_unmaximize();
			
			if (this->delegate != NULL)
				this->delegate->window_unmaximize(this);
			
			this->setSize(this->OldSize);
			
			this->moveTo(this->OldUpperLeft);
			
			this->windowBar->updateWithWindowWith(this->getSize().x);
		}
	}
	
	void Window::resizeToPoint(Zeni::Point2f resizeToPoint)
	{
		Zeni::Point2f sizeToResizeTo(resizeToPoint.x - this->getCoordinates().x, resizeToPoint.y - this->getCoordinates().y);
		
		if (sizeToResizeTo.x < OriginalSize.x)
			sizeToResizeTo.x = OriginalSize.x;
		
		if (sizeToResizeTo.y < OriginalSize.y)
			sizeToResizeTo.y = OriginalSize.y;
		
		Context* windowSystemContext = this->windowSystem.getContext();
		
		windowSystemContext->LowerRight.x = this->getCoordinates().x + sizeToResizeTo.x;
		windowSystemContext->LowerRight.y = this->getCoordinates().y + sizeToResizeTo.y;
		
		this->set_lower_right(windowSystemContext->LowerRight);
		this->setSize(sizeToResizeTo);
		
		this->windowBar->updateWithWindowWith(sizeToResizeTo.x);
	}
	
	Zeni::Widget* Window::getWidget()
	{
		return this;
	}
	
// Window_Bar class
	
	Window_Bar::Window_Bar()
	: GUIObject(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(0.0f, 0.0f)),
	Size(0.0f, 10.0f),
	Widget_Rectangle(Zeni::Point2f(0.0f, 0.0f), Size)
	{
		this->colorRenderer = new Zeni::Widget_Renderer_Color(Zeni::get_Colors()["blue"]);
		this->give_Renderer(colorRenderer);
		
		this->movingWindow = false;
		
		this->grabbedPositionFromOrigin = Zeni::Point2f(0.0f, 0.0f);
		
		Zeni::Color colorsOfTheButtons[3];
		colorsOfTheButtons[0] = Zeni::get_Colors()["black"];
		colorsOfTheButtons[1] = Zeni::get_Colors()["white"];
		colorsOfTheButtons[2] = Zeni::get_Colors()["red"];
		
		closeButton = new Button("", Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(8.0f, 8.0f), this);
		minimizeButton = new Button("", Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(8.0f, 8.0f), this);
		maximizeButton = new Button("", Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(8.0f, 8.0f), this);
		
		maximizedWindowJustNow = false;
	}
	
	Window_Bar::~Window_Bar()
	{
		delete closeButton;
		delete minimizeButton;
		delete maximizeButton;
	}
	
	void Window_Bar::updateWithWindowWith(float windowWidth)
	{
		this->Size.x = windowWidth;
		
		this->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->Size.x, this->getCoordinates().y + this->Size.y));
		
		this->closeButton->moveTo(Zeni::Point2f(this->getCoordinates().x + this->Size.x - 10.0f, this->getCoordinates().y + 1.0f));
		this->minimizeButton->moveTo(Zeni::Point2f(this->getCoordinates().x + this->Size.x - 20.0f, this->getCoordinates().y + 1.0f));
		this->maximizeButton->moveTo(Zeni::Point2f(this->getCoordinates().x + this->Size.x - 30.0f, this->getCoordinates().y + 1.0f));
	}
	
	void Window_Bar::windowMoved(Zeni::Point2f newPositionOfWindow)
	{
		this->GUIObject::moveTo(newPositionOfWindow);

		this->set_upper_left(this->getCoordinates());
		this->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->Size.x, this->getCoordinates().y + this->Size.y));
		
		this->closeButton->moveTo(Zeni::Point2f(this->getCoordinates().x + this->Size.x - 10.0f, this->getCoordinates().y + 1.0f));
		this->minimizeButton->moveTo(Zeni::Point2f(this->getCoordinates().x + this->Size.x - 20.0f, this->getCoordinates().y + 1.0f));
		this->maximizeButton->moveTo(Zeni::Point2f(this->getCoordinates().x + this->Size.x - 30.0f, this->getCoordinates().y + 1.0f));
	}
	
	const float Window_Bar::getWindowBarHeight()
	{
		return this->Size.y;
	}
	
	void Window_Bar::setDelegate(GUISystem::Window *window)
	{
		this->windowDelegate = window;
	}
	
	void Window_Bar::renderObject()
	{
		this->render();
		
		this->closeButton->renderObject();
		this->minimizeButton->renderObject();
		this->maximizeButton->renderObject();
	}
	
	void Window_Bar::renderAt(Zeni::Point2f UpperLeft)
	{
		Zeni::Point2f OldCoords = this->getCoordinates();
		
		this->windowMoved(UpperLeft);
		
		this->renderObject();
		
		this->windowMoved(OldCoords);
	}
	
	void Window_Bar::on_mouse_button(const Zeni::Point2i &pos, const bool &down, const int &button)
	{
		closeButton->getWidget()->on_mouse_button(pos, down, button);
		minimizeButton->getWidget()->on_mouse_button(pos, down, button);
		maximizeButton->getWidget()->on_mouse_button(pos, down, button);
				
		if (this->windowDelegate == NULL)
			return;
		
		if (((pos.x <= (this->getCoordinates().x + this->Size.x)) &&
			(pos.x >= (this->getCoordinates().x)) &&
			((pos.y <= (this->getCoordinates().y + this->Size.y)) &&
			(pos.y >= (this->getCoordinates().y)))) && 
			down == true && movingWindow == false)
		{
			movingWindow = true;
			
			this->grabbedPositionFromOrigin = Zeni::Point2f(this->getCoordinates().x - pos.x, this->getCoordinates().y - pos.y);
		}
		else if (movingWindow == true && down == false)
		{
			movingWindow = false;
			
			if (!maximizedWindowJustNow)
				this->windowDelegate->moveTo(Zeni::Point2f(pos.x + this->grabbedPositionFromOrigin.x, pos.y + this->grabbedPositionFromOrigin.y));
			else
				maximizedWindowJustNow = false;
		}
	}
	
	void Window_Bar::on_mouse_motion(const Zeni::Point2i &pos)
	{
		closeButton->getWidget()->on_mouse_motion(pos);
		minimizeButton->getWidget()->on_mouse_motion(pos);
		maximizeButton->getWidget()->on_mouse_motion(pos);
		
		if (this->windowDelegate == NULL)
			return;
		
		if (movingWindow == true)
		{
			Zeni::Point2f positionToMoveTo(pos.x + this->grabbedPositionFromOrigin.x, pos.y + this->grabbedPositionFromOrigin.y);
			this->windowDelegate->moveTo(positionToMoveTo);
		}
	}
	
	void Window_Bar::perform_logic()
	{
		closeButton->getWidget()->perform_logic();
		minimizeButton->getWidget()->perform_logic();
		maximizeButton->getWidget()->perform_logic();
	}
	
	void Window_Bar::button_accept(Button *whichButton)
	{
		if (whichButton == closeButton)
			this->windowDelegate->closeWindow();
		else if (whichButton == minimizeButton)
			this->windowDelegate->minimizeWindow();
		else if (whichButton == maximizeButton)
		{
			this->windowDelegate->maximizeWindow();
			maximizedWindowJustNow = true;
		}
	}
	
	Zeni::Widget* Window_Bar::getWidget()
	{
		return this;
	}
}
