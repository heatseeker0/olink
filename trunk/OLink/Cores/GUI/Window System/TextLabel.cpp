//
//  TextLabel.cpp
//  Application
//
//  Created by Alex Turner on 9/4/11.
//  Copyright 2011 OLink. All rights reserved.
//

#include "TextLabel.h"

namespace GUISystem {
	
#pragma mark Initialization
	TextLabel::TextLabel(std::string title, Zeni::Point2f UpperLeft, Zeni::Point2f Size)
	: GUIObject(UpperLeft),
	internalTextBox(title, UpperLeft, Size)
	{
		this->Size = Size;
	}
	
	TextLabel::~TextLabel()
	{
		
	}
	
#pragma mark Getters & Setters
	std::string TextLabel::getTitle()
	{
		return title;
	}
	
	void TextLabel::setTitle(std::string title)
	{
		internalTextBox.set_text(Zeni::String(title));
		this->title = title;
	}
	
#pragma mark movement methods
	
	void TextLabel::transform(Zeni::Point2f UpperLeft)
	{
		this->GUIObject::transform(UpperLeft);
		
		this->internalTextBox.set_upper_left(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x, this->getCoordinates().y + UpperLeft.y));
		this->internalTextBox.set_lower_right(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x + this->Size.x, this->getCoordinates().y + UpperLeft.y + this->Size.y));
	}
	
	void TextLabel::moveTo(Zeni::Point2f UpperLeft)
	{
		this->GUIObject::moveTo(UpperLeft);
		
		this->internalTextBox.set_upper_left(UpperLeft);
		this->internalTextBox.set_lower_right(Zeni::Point2f(UpperLeft.x + this->Size.x, UpperLeft.y + this->Size.y));
	}
	
#pragma Render methods
	void TextLabel::renderAt(Zeni::Point2f UpperLeft)
	{
		Zeni::Point2f previousCoords = this->getCoordinates();
		
		this->moveTo(UpperLeft);
		
		this->internalTextBox.render();
		
		this->moveTo(previousCoords);
	}
	
	void TextLabel::renderObject()
	{
		this->internalTextBox.render();
	}
	
	Zeni::Widget* TextLabel::getWidget()
	{
		return &internalTextBox;
	}
	
}
