//
//  CheckBox.cpp
//  Application
//
//  Created by Alex Turner on 9/4/11.
//  Copyright 2011 OLink. All rights reserved.
//

#include "CheckBox.h"

namespace GUISystem {
	
#pragma mark Initialization
	CheckBox::CheckBox(Zeni::Point2f UpperLeft, Zeni::Point2f Size, CheckBox_Delegate &newDelegate, bool radioButton)
	: GUIObject(UpperLeft),
	internalCheckBox(UpperLeft, Size, newDelegate, this, radioButton),
	delegate(newDelegate)
	{
		this->Size = Size;
	}
	
	CheckBox::~CheckBox() {}
	
#pragma mark Getters & Setters
	bool CheckBox::isChecked()
	{
		return internalCheckBox.is_checked();
	}
	
	void CheckBox::setChecked(bool checked)
	{
		internalCheckBox.set_checked(checked);
	}
	
#pragma mark movement methods
	
	void CheckBox::transform(Zeni::Point2f UpperLeft)
	{
        this->GUIObject::transform(UpperLeft);
		
		this->internalCheckBox.set_upper_left(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x, this->getCoordinates().y + UpperLeft.y));
		this->internalCheckBox.set_lower_right(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x + this->Size.x, this->getCoordinates().y + UpperLeft.y + this->Size.y));
	}
	
	void CheckBox::moveTo(Zeni::Point2f UpperLeft)
	{	
		this->GUIObject::moveTo(UpperLeft);
		
		this->internalCheckBox.set_upper_left(UpperLeft);
		this->internalCheckBox.set_lower_right(Zeni::Point2f(UpperLeft.x + this->Size.x, UpperLeft.y + this->Size.y));
	}
	
#pragma Render methods
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
