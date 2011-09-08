//
//  RadioButton.cpp
//  Application
//
//  Created by Alex Turner on 9/4/11.
//  Copyright 2011 OLink. All rights reserved.
//

#include "RadioButton.h"

namespace GUISystem {
	
	/*void RadioButton_Set::accept(RadioButton &radioButton)
	{
		internalRadioButtonSet.accept(radioButton.getWidget());
	}
	
	void RadioButton_Set::clear()
	{
		internalRadioButtonSet.clear();
	}
		
#pragma mark movement methods
	
	void RadioButton_Set::transform(Zeni::Point2f UpperLeft)
	{
		
	}
	
	void RadioButton_Set::moveTo(Zeni::Point2f UpperLeft)
	{
		
	}
	
#pragma mark render methods
	
	void RadioButton_Set::renderObject()
	{
		
	}
	
	void RadioButton_Set::renderAt(Zeni::Point2f UpperLeft)
	{
		
	}
	
#pragma mark Initialization
	RadioButton::RadioButton(RadioButton_Set &radioButton_Set,
				const Zeni::Point2f &UpperLeft, const Zeni::Point2f &Size,
				RadioButton_Delegate &delegate)
	: GUIObject(UpperLeft),
	internalRadioButton(radioButton_Set,
						  UpperLeft, Size,
						  delegate,
						  this)
	{
		this->Size = Size;
	}
	
	RadioButton::~RadioButton()
	{
	}
	
#pragma mark movement methods
	
	void RadioButton::transform(Zeni::Point2f UpperLeft)
	{
        this->GUIObject::transform(UpperLeft);
		
		this->internalRadioButton.set_upper_left(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x, this->getCoordinates().y + UpperLeft.y));
		this->internalRadioButton.set_lower_right(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x + this->Size.x, this->getCoordinates().y + UpperLeft.y + this->Size.y));
	}
	
	void RadioButton::moveTo(Zeni::Point2f UpperLeft)
	{	
		this->GUIObject::moveTo(UpperLeft);
		
		this->internalRadioButton.set_upper_left(UpperLeft);
		this->internalRadioButton.set_lower_right(Zeni::Point2f(UpperLeft.x + this->Size.x, UpperLeft.y + this->Size.y));
	}
	
#pragma mark Render methods
	void RadioButton::renderAt(Zeni::Point2f UpperLeft)
	{
		Zeni::Point2f previousCoords = this->getCoordinates();
		
        this->moveTo(UpperLeft);
		
		this->internalRadioButton.render();
		
		this->moveTo(previousCoords);
    }
	
	void CheckBox::renderObject()
	{
		this->internalRadioButton.render();
	}*/
}