//
//  Window System.h
//  Zenilib
//
//  Created by Alex Turner on 7/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef WINDOW_SYSTEM_H
#define WINDOW_SYSTEM_H 1

#include <zenilib.h>
#include "GUIObject.h"
#include <vector>

namespace GUISystem {
    
    typedef struct {
        std::vector<GUIObject*> objects;
        
        //Used for clamping a context to a portion of a screen like in a window within the main window (screen)
        Zeni::Point2f UpperLeft;
        Zeni::Point2f LowerRight;
    } Context; //Context struct
    
    //Window system which is used to render objects on the screen
    class Window_System
    {
    public:
// Initialization Methods
        Window_System(std::pair<Zeni::Point2f, Zeni::Point2f> screen); //Initialize the system
        ~Window_System(); //Dealloc the system
        
// Context Methods
        
        void setCurrentContextToSelf(); //Short hand for calling setCurrentContext(getContext())
        void setCurrentContext(Context* newContext); //Set the current context to the given one
        
        static Context* getCurrentContext(); //Get the current context (being used to render)
        Context* getContext(); //Get this instance of the window system's context
		
		void createNewCurrentContext();
        
// GUIObject Methods
        
        void addObject(GUIObject *object); //Add an object to this instance of the window system's context (whether that is the current one or not) context
        void removeObject(GUIObject *object); //Remove an object by its unique internal ID
        
        void addObject(Context *contextToAddTo, GUIObject *object); //Add an object to the context contextToAddTo
        void removeObject(Context *contextToRemoveFrom, GUIObject *object); //Remove an object from the context contextToRemoveFrom
		
		void moveObjectToForeground(GUIObject *object);
        
// Render Methods
        
        void renderObject(GUIObject *object); //Render just the single given object
        
        void renderAllObjects(); //Render all objects in the current context
        void render(); //Short hand for calling renderAllObjects
        
        void renderContext(Context* contextToRender); //Render a context on the screen
		
		static void renderCurrentContext();
        
// Widget Methods
		
		void on_key(const SDL_KeyboardEvent &event);
		void on_mouse_button(const SDL_MouseButtonEvent &event);
		void on_mouse_motion(const SDL_MouseMotionEvent &event);
		void perform_logic();
        
    private:
        static Context *currentContext; //Global current context which is used to render the screen
        
        Context *m_Context; //Context localized to an instance of a window system
                
        Zeni::Projector2D m_projector;
		
		std::pair<Zeni::Point2f, Zeni::Point2f> screenSize;
		
		bool isWidgetBusy;
		Zeni::Widget *busyWidget;
    };
    
}

#endif
