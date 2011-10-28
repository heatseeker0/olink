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
#include "Button.h"

namespace GUISystem {
	
	class Window : public Zeni::Widget, public Zeni::Widget_Rectangle, public GUIObject
	{
		Window(const Window &);
		Window & operator=(const Window &);
		
	public:
#define Window_T 7
		
		class Window_Delegate
		{
		public:
			virtual void window_close(Window *) {};
			virtual void window_resize(Window *) {};
			virtual void window_minimize(Window *) {};
			virtual void window_maximize(Window *) {};
			virtual void window_unminimize(Window *) {};
			virtual void window_unmaximize(Window *) {};
		};
		
		class V_WindowBar
		{
		public:
			virtual void updateWithWindowWith(float windowWidth) = 0;
			virtual void windowMoved(Zeni::Point2f newPositionOfWindow) = 0;
			virtual const float getWindowBarHeight() = 0;
			virtual void setDelegate(GUISystem::Window *window) = 0;
			
			virtual GUIObject* getGUIObject() = 0;
		};
		
		enum State {NORMAL, MINIMIZED, MAXIMIZED, CLOSED};
		
		Window(const Zeni::Point2f &UpperLeft, const Zeni::Point2f &Size, Zeni::Color color = Zeni::Color(), Window_Delegate *delegate = NULL, V_WindowBar *windowBar = NULL);
		Window(const Zeni::Point2f &UpperLeft, const Zeni::Point2f &Size, Zeni::String texture, Window_Delegate *delegate = NULL, V_WindowBar *windowBar = NULL);
		
		~Window();
		
		const State & getState();
		
		void lendObject(GUIObject *object);
		void unlendObject(GUIObject *object);
		
		virtual void on_mouse_button(const Zeni::Point2i &pos, const bool &down, const int &button);
		virtual void on_mouse_motion(const Zeni::Point2i &pos);
		virtual void perform_logic();
		virtual void on_key(const SDL_keysym &keysym, const bool &down);
		
		virtual void on_close() {}
		
		virtual void on_resize() {}
		
		virtual void on_minimize() {}
		
		virtual void on_maximize() {}
		
		virtual void on_unminimize() {}
		
		virtual void on_unmaximize() {}
		
		void renderObject();
		
		void renderAt(Zeni::Point2f UpperLeft);
		
		Zeni::Widget *getWidget();
		
		void transform(Zeni::Point2f UpperLeft);
		void moveTo(Zeni::Point2f UpperLeft);
		
		void closeWindow();
		void minimizeWindow();
		void maximizeWindow();
		
		void resizeToPoint(Zeni::Point2f resizeToPoint);
		
		int getType() { return Window_T; };
		
		void setWindowSystem(Window_System *windowSystem);
		
	private:
		State m_state;
		
		Window_System windowSystem;
		
		Window_Delegate *delegate;
		
		Zeni::Widget_Renderer_Texture *textureRenderer;
		Zeni::Widget_Renderer_Color *colorRenderer;
		
		V_WindowBar *windowBar;
		bool createdWindowBar;
				
		bool resizingWindow;
		
// Resize/Maximize Stuff
		Zeni::Point2f OriginalSize;
		
		Zeni::Point2f OldUpperLeft;
		Zeni::Point2f OldSize;
	};

	class Window_Bar : public Window::V_WindowBar, public GUIObject, public Zeni::Widget_Rectangle, public Zeni::Widget, public Button::Delegate
	{
		Button *closeButton;
		Button *minimizeButton;
		Button *maximizeButton;
		
		Zeni::Widget_Renderer_Color *colorRenderer;
		
		Zeni::Point2f Size;
		
		bool movingWindow;
		bool maximizedWindowJustNow;
		
		GUISystem::Window *windowDelegate;
		
		Zeni::Point2f grabbedPositionFromOrigin;
		
	public:
#define WindowBar_T 8
		
		Window_Bar();
		~Window_Bar();
		
		void updateWithWindowWith(float windowWidth);
		void windowMoved(Zeni::Point2f newPositionOfWindow);
		const float getWindowBarHeight();
		
		void setDelegate(GUISystem::Window *window);
		
		void on_mouse_button(const Zeni::Point2i &pos, const bool &down, const int &button);
		void on_mouse_motion(const Zeni::Point2i &pos);
		void perform_logic();
		
		GUIObject* getGUIObject() { return this; }
		
		void renderObject();
		void renderAt(Zeni::Point2f UpperLeft);
		Zeni::Widget *getWidget();
		
		void button_accept(Button *whichButton);
		
		int getType() { return WindowBar_T; };
	};
}

#endif
