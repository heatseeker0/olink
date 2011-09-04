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
	
    Button::Button(std::string title, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Button_Delegate &newDelegate)
    : GUIObject(UpperLeft),
	delegate(newDelegate),
	internalButton(title, UpperLeft, Size, this)
    {
        this->title = title;
		
		this->Size = Size;
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
    
    void Button::setDelegate(Button_Delegate &delegate)
    {
		this->delegate = delegate;
    }
	
#pragma mark Movement methods
	
	void Button::transform(Zeni::Point2f UpperLeft)
	{
        this->GUIObject::transform(UpperLeft);
		
		this->internalButton.set_upper_left(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x, this->getCoordinates().y + UpperLeft.y));
		this->internalButton.set_lower_right(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x + this->Size.x, this->getCoordinates().y + UpperLeft.y + this->Size.y));
	}
	
	void Button::moveTo(Zeni::Point2f UpperLeft)
	{	
		this->GUIObject::moveTo(UpperLeft);
		
		this->internalButton.set_upper_left(UpperLeft);
		this->internalButton.set_lower_right(Zeni::Point2f(UpperLeft.x + this->Size.x, UpperLeft.y + this->Size.y));
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
	
	void Button::on_hover()
	{
		this->delegate.button_hover(this);
	}
	
	void Button::on_unhover()
	{
		this->delegate.button_unhover(this);
	}
	
	void Button::on_click()
	{
		this->delegate.button_click(this);
	}
	
	void Button::on_stray()
	{
		this->delegate.button_stray(this);
	}
	
	void Button::on_unstray()
	{
		this->delegate.button_unstray(this);
	}
	
	void Button::on_accept()
	{
		this->delegate.button_accept(this);
	}
	
	void Button::on_reject()
	{
		this->delegate.button_reject(this);
	}
};
