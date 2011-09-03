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
    
    class Button : public GUIObject, public Zeni::Text_Button
    {
    public:
#pragma mark Button Delegate
        class Button_Delegate
        {
        public:
            //See Widget.h/Text_Button for more info about each one.
            virtual void button_hover() {}
            virtual void button_unhover() {}
            
            virtual void button_click() {}
            virtual void button_stray() {}
            virtual void button_unstray() {}
            
            virtual void button_accept() {}
            virtual void button_reject() {}
        };
        
        
#pragma mark Initialization
        Button(std::string title, Zeni::Point2f UpperLeft, Button_Delegate *delegate); //Initialize the button with a Title and a point to draw from
        ~Button(); //Dealloc
        
#pragma mark Getters & Setters
        std::string getTitle(); //Get the title of the button
        void setTitle(std::string title); //Set the title of the button
        
        void setDelegate(Button_Delegate *delegate);
		
#pragma mark movement methods
        
        void transform(Zeni::Point2f UpperLeft); //Move the position by this amount        
        void moveTo(Zeni::Point2f UpperLeft); //Set the object's cords to this
        
#pragma Render methods
        void renderAt(Zeni::Point2f UpperLeft); //Render at the point
		void render();
        
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
        
        Button_Delegate *delegate;
    };
    
}

#endif
