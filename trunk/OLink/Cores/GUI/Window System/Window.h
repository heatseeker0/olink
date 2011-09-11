//
//  Window.h
//  Application
//
//  Created by Alex Turner on 9/8/11.
//  Copyright 2011 OLink. All rights reserved.
//

#ifndef Window_H
#define Window_H

#include <zenilib.h>
#include "GUIObject.h"
#include "Window System.h"

namespace GUISystem {
	
	class Window : public Zeni::Widget, public Zeni::Widget_Rectangle, public GUIObject
	{
		Window(const Window &);
		Window & operator=(const Window &);
		
	public:
		class Window_Delegate
		{
		public:
			virtual void window_close(Window *window) {};
			virtual void window_resize(Window *window) {};
			virtual void window_minimize(Window *window) {};
			virtual void window_maximize(Window *window) {};
		};
		
		class V_WindowBar
		{
		public:
			virtual void updateWithWindowWith(float windowWidth) = 0;
			virtual void windowMoved(Zeni::Point2f newPositionOfWindow) = 0;
			virtual const float getWindowBarWidth() = 0;
			
			virtual GUIObject* getGUIObject() = 0;
		};
		
		enum State {NORMAL, MINIMIZED, MAXIMIZED};
		
		inline Window(const Zeni::Point2f &UpperLeft, const Zeni::Point2f &Size, Window_Delegate *delegate = NULL, V_WindowBar *windowBar = NULL);
		
		inline const State & getState();
		
		void lendObject(GUIObject &object);
		void unlendObject(GUIObject &object);
		
		virtual void on_mouse_button(const Zeni::Point2i &pos, const bool &down, const int &button);
		virtual void on_mouse_motion(const Zeni::Point2i &pos);
		
		virtual void on_close() {}
		
		virtual void on_resize() {}
		
		virtual void on_minimize() {}
		
		virtual void on_maximize() {}
		
		void renderObject();
		
		void renderAt(Zeni::Point2f UpperLeft);
		
		Zeni::Widget *getWidget() { return this; }
		
		void transform(Zeni::Point2f UpperLeft);
		void moveTo(Zeni::Point2f UpperLeft);
		
		void closeWindow();
		void minimizeWindow();
		void maximizeWindow();
		
	private:
		State m_state;
		
		Window_System windowSystem;
		
		Window_Delegate *delegate;
	};

	class Window_Bar : public Window::V_WindowBar, public GUIObject
	{
	public:
		Window_Bar();
		~Window_Bar();
		
		void updateWithWindowWith(float windowWidth);
		void windowMoved(Zeni::Point2f newPositionOfWindow);
		const float getWindowBarWidth();
		
		GUIObject* getGUIObject() { return this; }
		
		void renderObject();
		void renderAt(Zeni::Point2f UpperLeft);
		Zeni::Widget *getWidget();
	};
}

#endif
