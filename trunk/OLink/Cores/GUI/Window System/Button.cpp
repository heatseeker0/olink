//
//  Button.cpp
//  Zenilib
//
//  Created by Alex Turner on 7/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Widget.h"

#include "Button.h"

namespace GUISystem {

#pragma mark Initialization

    Button::Button(std::string title, Zeni::Point2f UpperLeft)
    : GUIObject(UpperLeft),
	internalButton(title, UpperLeft, this)
    {
		delegate = NULL;
		
		std::cout << "buttonToAdd-ThisPointer:" << this << std::endl;
        this->title = title;
    }
    
    Button::~Button()
    {
        
    }
    
#pragma mark Getters & Setters

    std::string Button::getTitle()
    {
        return title;
    }
    
    void Button::setTitle(std::string title)
    {
        this->title = title;
		this->internalButton.text = Zeni::String(title);
    }
    
    void Button::setDelegate(Button_Delegate *delegate)
    {
		std::cout << "Delegate(GUITestState):" << delegate << std::endl;
        if (delegate)
			this->delegate = delegate;
		else
			delegate = NULL;
    }
	
#pragma mark Movement methods
	
	void Button::transform(Zeni::Point2f UpperLeft)
	{
        this->GUIObject::transform(UpperLeft);
	
		this->internalButton.set_upper_left(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x, this->getCoordinates().y + UpperLeft.y));
		this->internalButton.set_lower_right(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x + 100.0f, this->getCoordinates().y + UpperLeft.y + 50.0f));
	}
	
	void Button::moveTo(Zeni::Point2f UpperLeft)
	{	
		this->GUIObject::moveTo(UpperLeft);
		
		this->internalButton.set_upper_left(UpperLeft);
		this->internalButton.set_lower_right(Zeni::Point2f(UpperLeft.x + 100.0f, UpperLeft.y + 50.0f));
	}
    
#pragma Render methods
    void Button::renderAt(Zeni::Point2f UpperLeft)
    {
		Zeni::Point2f previousCoords = this->getCoordinates();
		
        this->moveTo(UpperLeft);
		
		this->internalButton.render();
		
		this->moveTo(previousCoords);
    }
	
	void Button::renderObject()
	{
		this->internalButton.render();
	}
};
