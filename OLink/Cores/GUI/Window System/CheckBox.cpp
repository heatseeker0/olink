//
//  CheckBox.cpp
//  Application
//
//  Created by Alex Turner on 9/4/11.
//  Copyright 2011 OLink. All rights reserved.
//

#include <zenilib.h>

#include "CheckBox.h"

namespace GUISystem {
	
// Initialization
	CheckBox::CheckBox(Zeni::Point2f UpperLeft, Zeni::Point2f Size, CheckBox_Delegate *newDelegate, bool radioButton)
	: GUIObject(UpperLeft, Size),
	internalCheckBox(UpperLeft, Size, newDelegate, this, radioButton)
	{
		this->delegate = newDelegate;
	}
	
	CheckBox::~CheckBox() {}
	
// Getters & Setters
	bool CheckBox::isChecked()
	{
		return internalCheckBox.is_checked();
	}
	
	void CheckBox::setChecked(bool checked)
	{
		internalCheckBox.set_checked(checked);
	}
	
// movement methods
	
	void CheckBox::transform(Zeni::Point2f UpperLeft)
	{
        this->GUIObject::transform(UpperLeft);
		
		this->internalCheckBox.set_upper_left(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x, this->getCoordinates().y + UpperLeft.y));
		this->internalCheckBox.set_lower_right(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x + this->getSize().x, this->getCoordinates().y + UpperLeft.y + this->getSize().y));
	}
	
	void CheckBox::moveTo(Zeni::Point2f UpperLeft)
	{	
		this->GUIObject::moveTo(UpperLeft);
		
		this->internalCheckBox.set_upper_left(UpperLeft);
		this->internalCheckBox.set_lower_right(Zeni::Point2f(UpperLeft.x + this->getSize().x, UpperLeft.y + this->getSize().y));
	}
	
// Render methods
	void CheckBox::renderAt(Zeni::Point2f UpperLeft)
	{
		Zeni::Point2f previousCoords = this->getCoordinates();
		
        this->moveTo(UpperLeft);
		
		this->internalCheckBox.render();
		
		this->moveTo(previousCoords);
    }
	
	void CheckBox::renderObject()
	{
		this->internalCheckBox.render();
	}
	
	Zeni::Widget* CheckBox::getWidget()
	{
		return &internalCheckBox;
	}
}
