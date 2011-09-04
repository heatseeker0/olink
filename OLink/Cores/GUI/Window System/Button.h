//
//  Button.h
//  Zenilib
//
//  Created by Alex Turner on 7/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef BUTTON_H
#define BUTTON_H

#include "zenilib.h"
#include "GUIObject.h"
#include <string.h>

namespace GUISystem {
	
    class Button : public GUIObject
    {
    public:
#pragma mark Button Delegate
        class Button_Delegate
        {
        public:
            //See Widget.h/Text_Button for more info about each one.
            virtual void button_hover(Button *whichButton) = 0;
            virtual void button_unhover(Button *whichButton) = 0;
            
            virtual void button_click(Button *whichButton) = 0;
            virtual void button_stray(Button *whichButton) = 0;
            virtual void button_unstray(Button *whichButton) = 0;
            
            virtual void button_accept(Button *whichButton) = 0;
            virtual void button_reject(Button *whichButton) = 0;
        };
        
		class Internal_Button : public Zeni::Text_Button {
			Internal_Button(const Internal_Button &);
			Internal_Button & operator=(const Internal_Button &);
			
			Button *delegate;
			
		public:
			Internal_Button(std::string title, Zeni::Point2f UpperLeft, Button *delegate)
			: Text_Button(UpperLeft, Zeni::Point2f(UpperLeft.x + 100.0f, UpperLeft.y + 50.0f),
						  "DefaultFont", Zeni::String(title))
			{
				this->delegate = delegate;
			}
			
			void on_accept() {
				this->delegate->on_accept();
			}
		};
		
		Internal_Button internalButton;
        
#pragma mark Initialization
        Button(std::string title, Zeni::Point2f UpperLeft, Button_Delegate &delegate); //Initialize the button with a Title and a point to draw from
        ~Button(); //Dealloc
        
#pragma mark Getters & Setters
        std::string getTitle(); //Get the title of the button
        void setTitle(std::string title); //Set the title of the button
        
        void setDelegate(Button_Delegate &delegate);
		
		Zeni::Widget *getWidget() { return &internalButton; };
		
#pragma mark movement methods
        
        void transform(Zeni::Point2f UpperLeft); //Move the position by this amount        
        void moveTo(Zeni::Point2f UpperLeft); //Set the object's cords to this
        
#pragma Render methods
        void renderAt(Zeni::Point2f UpperLeft); //Render at the point
		void renderObject();
        
#pragma Text_Button methods		
        void on_hover();
		
		void on_unhover();
		
		void on_click();
		
		void on_stray();
		
		void on_unstray();
		
		void on_accept();
		
		void on_reject();
		
    private:
        std::string title; //Title of the button
        
        Button_Delegate &delegate;
    };
    
}

#endif
