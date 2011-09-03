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

    Button::Button(std::string title, Zeni::Point2f UpperLeft, Button_Delegate *delegate)
    : GUIObject(UpperLeft),
	Text_Button(UpperLeft, Zeni::Point2f(UpperLeft.x + 100.0f, UpperLeft.y + 50.0f), "DefaultFont", Zeni::String(title))
    {
        this->title = title;
		
		this->delegate = delegate;
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
    }
    
    void Button::setDelegate(Button_Delegate *delegate)
    {
        this->delegate = delegate;
    }
	
#pragma mark Movement methods
	
	void Button::transform(Zeni::Point2f UpperLeft)
	{
        this->GUIObject::transform(UpperLeft);
	
		this->set_upper_left(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x, this->getCoordinates().y + UpperLeft.y));
		this->set_lower_right(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x + 100.0f, this->getCoordinates().y + UpperLeft.y + 50.0f));
	}
	
	void Button::moveTo(Zeni::Point2f UpperLeft)
	{	
		this->GUIObject::moveTo(UpperLeft);
		
		this->set_upper_left(UpperLeft);
		this->set_lower_right(Zeni::Point2f(UpperLeft.x + 100.0f, UpperLeft.y + 50.0f));
	}
    
#pragma Render methods
    void Button::renderAt(Zeni::Point2f UpperLeft)
    {
		Zeni::Point2f previousCoords = this->getCoordinates();
		
        this->moveTo(UpperLeft);
		
		this->Button::render();
		
		this->moveTo(previousCoords);
    }
	
	void Button::render()
	{
		this->Text_Button::render();
	}
	
#pragma mark Text_Button methods
    void Button::on_hover()
    {
		if (delegate == NULL)
			return;
		
        delegate->button_hover();
    }
    
    void Button::on_unhover()
    {
		if (delegate == NULL)
			return;
		
        delegate->button_unhover();
    }
    
    void Button::on_click()
    {
		if (delegate == NULL)
			return;
		
        delegate->button_click();
    }
    
    void Button::on_stray()
    {
		if (delegate == NULL)
			return;
		
        delegate->button_stray();
    }
    
    void Button::on_unstray()
    {
		if (delegate == NULL)
			return;
		
        delegate->button_unstray();
    }
    
    void Button::on_accept()
    {
		if (delegate == NULL)
			return;
		
        delegate->button_accept();
    }
    
    void Button::on_reject()
    {
		if (delegate == NULL)
			return;
		
        delegate->button_reject();
    }
};
