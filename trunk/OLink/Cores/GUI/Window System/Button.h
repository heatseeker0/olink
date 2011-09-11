//
//  Button.h
//  Zenilib
//
//  Created by Alex Turner on 7/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef BUTTON_H
#define BUTTON_H 1

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
            virtual void button_hover(Button *whichButton) {};
            virtual void button_unhover(Button *whichButton) {};
            
            virtual void button_click(Button *whichButton) {};
            virtual void button_stray(Button *whichButton) {};
            virtual void button_unstray(Button *whichButton) {};
            
            virtual void button_accept(Button *whichButton) {};
            virtual void button_reject(Button *whichButton) {};
        };
        
	private:
		
		class Internal_Button : public Zeni::Text_Button {
			Internal_Button(const Internal_Button &);
			Internal_Button & operator=(const Internal_Button &);
			
			Button *button;
			
		public:
			Button_Delegate &delegate;
			
			Internal_Button(std::string title, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Button_Delegate &newDelegate, Button *button)
			: Text_Button(UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y),
						  "DefaultFont", Zeni::String(title)),
			delegate(newDelegate)
			{
				this->button = button;
			}
			
			void on_hover() {
				this->delegate.button_hover(button);
			}
			
			void on_unhover() {
				this->delegate.button_unhover(button);
			}
			
			void on_click() {
				this->delegate.button_click(button);
			}
			
			void on_stray() {
				this->delegate.button_stray(button);
			}
			
			void on_unstray() {
				this->delegate.button_unstray(button);
			}
			
			void on_accept() {
				this->delegate.button_accept(button);
			}
			
			void on_reject() {
				this->delegate.button_reject(button);
			}
		};
		
		Internal_Button internalButton;
		
	public:
        
#pragma mark Initialization
        Button(std::string title, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Button_Delegate &delegate); //Initialize the button with a Title and a point to draw from
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
		
    private:
        std::string title; //Title of the button
        
        Button_Delegate &delegate;
		
		Zeni::Point2f Size;
    };
    
}

#endif
