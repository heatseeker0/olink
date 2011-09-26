//
//  TextLabel.h
//  Application
//
//  Created by Alex Turner on 9/4/11.
//  Copyright 2011 OLink. All rights reserved.
//

#ifndef TextLabel_H
#define TextLabel_H 1

#include "zenilib.h"

#include "GUIObject.h"

namespace GUISystem {

	class TextLabel : public GUIObject
	{
		class Internal_Text_Box : public Zeni::Text_Box {
			Internal_Text_Box(const Internal_Text_Box &);
			Internal_Text_Box & operator=(const Internal_Text_Box &);
			
		public:
			Internal_Text_Box(const std::string &title, Zeni::Point2f UpperLeft, Zeni::Point2f Size)
			: Text_Box(UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y), Zeni::String("DefaultFont"), Zeni::String(title), Zeni::get_Colors()["DefaultTextLabelColor"])
			{
				give_BG_Renderer(new Zeni::Widget_Renderer_Color(Zeni::Color(0.0f, 0.0f, 0.0f, 0.0f)));
			}
		};
		
		Internal_Text_Box internalTextBox;
		
		std::string title;
				
	public:
#define TextLabel_T 6
		
#pragma mark Initialization
        TextLabel(std::string title, Zeni::Point2f UpperLeft, Zeni::Point2f Size); //Initialize the text label with a Title and a point to draw from
        ~TextLabel(); //Dealloc
        
#pragma mark Getters & Setters
        std::string getTitle(); //Get the title of the text label
        void setTitle(std::string title); //Set the title of the text label
		
		int getType() { return TextLabel_T; };
		
#pragma mark movement methods
        
        void transform(Zeni::Point2f UpperLeft); //Move the position by this amount        
        void moveTo(Zeni::Point2f UpperLeft); //Set the object's cords to this
        
#pragma Render methods
        void renderAt(Zeni::Point2f UpperLeft); //Render at the point
		void renderObject();
		
		Zeni::Widget* getWidget();
	};
	
}

#endif