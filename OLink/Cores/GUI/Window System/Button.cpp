//
//  Button.cpp
//  Zenilib
//
//  Created by Alex Turner on 7/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <zenilib.h>

#include "Button.h"

namespace GUISystem {
	
// Initialization
	
    Button::Button(std::string title, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *newDelegate)
    : GUIObject(UpperLeft, Size)
    {
		this->internalTextImageButton = NULL;
		this->internalImageButton = NULL;
		this->internalTextButton = NULL;
		
		Zeni::String zeniStringTitle(title);
		this->internalTextButton = new Internal_TextButton(zeniStringTitle, UpperLeft, Size, newDelegate, this);
		
        this->title = title;
		
		this->delegate = newDelegate;
		
		setSize(Size);
	}
	
	Button::Button(std::map<std::string, std::string> images, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *newDelegate)
	: GUIObject(UpperLeft, Size)
	{
		this->internalTextImageButton = NULL;
		this->internalImageButton = NULL;
		this->internalTextButton = NULL;
		
		Zeni::String zeniStringTitle("");
		this->internalImageButton = new Internal_TextImageButton(images, zeniStringTitle, UpperLeft, Size, newDelegate, this);
		
        this->images = images;
		
		this->delegate = newDelegate;
		
		setSize(Size);
	}
	
	Button::Button(std::map<std::string, std::string> images, std::string title, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *newDelegate)
	: GUIObject(UpperLeft, Size)
	{
		this->internalTextImageButton = NULL;
		this->internalImageButton = NULL;
		this->internalTextButton = NULL;
		
		Zeni::String zeniStringTitle(title);
		this->internalTextImageButton = new Internal_TextImageButton(images, zeniStringTitle, UpperLeft, Size, newDelegate, this);
		
		this->images = images;
		this->title = title;
		
		this->delegate = newDelegate;
		
		setSize(Size);
	}
	
    Button::~Button()
    {
		if (internalTextButton != NULL)
			delete internalTextButton;
		
		if (internalTextImageButton != NULL)
			delete internalTextImageButton;
		
		if (internalImageButton != NULL)
			delete internalImageButton;
    }
    
// Getters & Setters
	
    std::string Button::getTitle()
    {
		if (internalTextButton == NULL && internalTextImageButton == NULL)
			return "";
		
        return title;
    }
    
    void Button::setTitle(std::string title)
    {
		if (internalTextImageButton == NULL && internalTextButton == NULL)
			return;
		
        this->title = title;
		
		if (internalTextButton != NULL)
			this->internalTextButton->text = Zeni::String(title);
		else
			this->internalTextImageButton->setText(Zeni::String(title));
    }
	
	Zeni::Color* Button::getColors()
	{
		return this->colorsOfTheButton;
	}
	
	std::map<std::string, std::string> Button::getImages()
	{
		if (internalTextButton != NULL)
		{
			std::map<std::string, std::string> map;
			return map;
		}
		
		return images;
	}
	
	void Button::setImages(std::map<std::string, std::string> images)
	{
		if (internalTextButton != NULL)
			return;
		
		this->images = images;
		if (internalImageButton != NULL)
			internalImageButton->setImages(images);
		else
			internalTextImageButton->setImages(images);
	}
    
    void Button::setDelegate(Delegate *delegate)
    {
		this->delegate = delegate;
		
		if (internalTextButton != NULL)
			internalTextButton->delegate = delegate;
		else if (internalTextImageButton != NULL)
			internalTextImageButton->delegate = delegate;
		else
			internalImageButton->delegate = delegate;
    }
	
	Zeni::Widget* Button::getWidget()
	{		
		if (internalTextButton != NULL)
			return internalTextButton;
		else if (internalTextImageButton != NULL)
			return internalTextImageButton;
		else
			return internalImageButton;
	};
	
	void Button::setSize(Zeni::Point2f Size)
	{
		this->GUIObject::setSize(Size);
		
		if (internalTextButton != NULL)
		{
			internalTextButton->set_upper_left(this->getCoordinates());
			internalTextButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
		}
		else if (internalTextImageButton != NULL)
		{
			internalTextImageButton->set_upper_left(this->getCoordinates());
			internalTextImageButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
		}
		else if (internalImageButton != NULL)
		{
			internalImageButton->set_upper_left(this->getCoordinates());
			internalImageButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
		}
	}
	
// Movement methods
	
	void Button::transform(Zeni::Point2f UpperLeft)
	{
        this->GUIObject::transform(UpperLeft);
		
		if (internalTextButton != NULL)
		{
			this->internalTextButton->set_upper_left(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x, this->getCoordinates().y + UpperLeft.y));
			this->internalTextButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x + this->getSize().x, this->getCoordinates().y + UpperLeft.y + this->getSize().y));
		}
		else if (internalTextImageButton != NULL)
		{
			this->internalTextImageButton->set_upper_left(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x, this->getCoordinates().y + UpperLeft.y));
			this->internalTextImageButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x + this->getSize().x, this->getCoordinates().y + UpperLeft.y + this->getSize().y));
		}
		else if (internalImageButton != NULL)
		{
			this->internalImageButton->set_upper_left(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x, this->getCoordinates().y + UpperLeft.y));
			this->internalImageButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x + this->getSize().x, this->getCoordinates().y + UpperLeft.y + this->getSize().y));
		}
	}
	
	void Button::moveTo(Zeni::Point2f UpperLeft)
	{	
		this->GUIObject::moveTo(UpperLeft);
		
		if (internalTextButton != NULL)
		{
			this->internalTextButton->set_upper_left(Zeni::Point2f(this->getCoordinates().x, this->getCoordinates().y));
			this->internalTextButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
		}
		else if (internalTextImageButton != NULL)
		{
			this->internalTextImageButton->set_upper_left(Zeni::Point2f(this->getCoordinates().x, this->getCoordinates().y));
			this->internalTextImageButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
		}
		else if (internalImageButton != NULL)
		{
			this->internalImageButton->set_upper_left(Zeni::Point2f(this->getCoordinates().x, this->getCoordinates().y));
			this->internalImageButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
		}
	}
    
// Render methods
    void Button::renderAt(Zeni::Point2f UpperLeft)
    {
		Zeni::Point2f previousCoords = this->getCoordinates();
		
        this->moveTo(UpperLeft);
		
		if (internalTextButton != NULL)
			this->internalTextButton->render();
		else if (internalTextImageButton != NULL)
			this->internalTextImageButton->render();
		else if (internalImageButton != NULL)
			this->internalImageButton->render();
		
		this->moveTo(previousCoords);
    }
	
	void Button::renderObject()
	{
		if (internalTextButton != NULL)
			this->internalTextButton->render();
		else if (internalTextImageButton != NULL)
			this->internalTextImageButton->render();
		else if (internalImageButton != NULL)
			this->internalImageButton->render();
	}
};
