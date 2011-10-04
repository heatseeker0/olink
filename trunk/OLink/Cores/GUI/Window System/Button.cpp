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
	
    Button::Button(std::string title, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *newDelegate)
    : GUIObject(UpperLeft, Size)
    {
		this->internalTextImageButton = NULL;
		this->internalImageButton = NULL;
		this->internalColorButton = NULL;
		this->internalTextColorButton = NULL;
		this->internalTextButton = NULL;
		
		this->internalTextButton = new Internal_TextButton(title, UpperLeft, Size, newDelegate, this);
		
        this->title = title;
		
		this->delegate = newDelegate;
		
		setSize(Size);
	}
	
	Button::Button(std::map<std::string, std::string> images, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *newDelegate)
	: GUIObject(UpperLeft, Size)
	{
		this->internalTextImageButton = NULL;
		this->internalImageButton = NULL;
		this->internalColorButton = NULL;
		this->internalTextColorButton = NULL;
		this->internalTextButton = NULL;
		
		this->internalImageButton = new Internal_TextImageButton(images, "", UpperLeft, Size, newDelegate, this);
		
        this->images = images;
		
		this->delegate = newDelegate;
		
		setSize(Size);
	}
	
	Button::Button(std::map<std::string, std::string> images, std::string title, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *newDelegate)
	: GUIObject(UpperLeft, Size)
	{
		this->internalTextImageButton = NULL;
		this->internalImageButton = NULL;
		this->internalColorButton = NULL;
		this->internalTextColorButton = NULL;
		this->internalTextButton = NULL;
		
		this->internalTextImageButton = new Internal_TextImageButton(images, title, UpperLeft, Size, newDelegate, this);
		
		this->images = images;
		this->title = title;
		
		this->delegate = newDelegate;
		
		setSize(Size);
	}
	
	Button::Button(std::string title, Zeni::Color colorsOfTheButton[2], Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *newDelegate)
	: GUIObject(UpperLeft, Size)
	{
		this->internalTextImageButton = NULL;
		this->internalImageButton = NULL;
		this->internalColorButton = NULL;
		this->internalTextColorButton = NULL;
		this->internalTextButton = NULL;
		
		this->internalTextColorButton = new Internal_TextColorButton(title, colorsOfTheButton, UpperLeft, Size, newDelegate, this);
		
		this->title = title;
		this->colorsOfTheButton[0] = colorsOfTheButton[0];
		this->colorsOfTheButton[1] = colorsOfTheButton[1];
		this->colorsOfTheButton[2] = colorsOfTheButton[2];
		
		this->delegate = newDelegate;
		
		setSize(Size);
	}
	
	Button::Button(Zeni::Color colorsOfTheButton[2], Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *newDelegate)
	: GUIObject(UpperLeft, Size)
	{
		this->internalTextImageButton = NULL;
		this->internalImageButton = NULL;
		this->internalColorButton = NULL;
		this->internalTextColorButton = NULL;
		this->internalTextButton = NULL;
		
		this->internalColorButton = new Internal_TextColorButton("", colorsOfTheButton, UpperLeft, Size, newDelegate, this);		
		
		this->colorsOfTheButton[0] = colorsOfTheButton[0];
		this->colorsOfTheButton[1] = colorsOfTheButton[1];
		this->colorsOfTheButton[2] = colorsOfTheButton[2];
		
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
		
		if (internalColorButton != NULL)
			delete internalColorButton;
		
		if (internalTextColorButton != NULL)
			delete internalTextColorButton;
    }
    
#pragma mark Getters & Setters
	
    std::string Button::getTitle()
    {
		if (internalTextButton == NULL && internalTextImageButton == NULL && internalTextColorButton == NULL)
			return "";
		
        return title;
    }
    
    void Button::setTitle(std::string title)
    {
		if (internalTextImageButton == NULL && internalTextButton == NULL && internalTextColorButton == NULL)
			return;
		
        this->title = title;
		
		if (internalTextButton != NULL)
			this->internalTextButton->text = Zeni::String(title);
		else if (internalTextImageButton != NULL)
			this->internalTextImageButton->setText(Zeni::String(title));
		else
			this->internalTextColorButton->setText(Zeni::String(title));
    }
	
	Zeni::Color* Button::getColors()
	{
		return this->colorsOfTheButton;
	}
	
	void Button::setColors(Zeni::Color colors[2])
	{
		if (internalTextColorButton == NULL && internalColorButton == NULL)
			return;
		
		this->colorsOfTheButton[0] = colors[0];
		this->colorsOfTheButton[1] = colors[1];
		this->colorsOfTheButton[2] = colors[2];
		
		if (internalTextColorButton != NULL)
			this->internalTextColorButton->setColors(colors);
		else
			this->internalColorButton->setColors(colors);
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
		else if (internalImageButton != NULL)
			return internalImageButton;
		else if (internalTextColorButton != NULL)
			return internalTextColorButton;
		else
			return internalColorButton;
	};
	
#pragma mark Movement methods
	
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
		else if (internalColorButton != NULL)
		{
			this->internalColorButton->set_upper_left(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x, this->getCoordinates().y + UpperLeft.y));
			this->internalColorButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x + this->getSize().x, this->getCoordinates().y + UpperLeft.y + this->getSize().y));
		}
		else if (internalTextColorButton != NULL)
		{
			this->internalTextColorButton->set_upper_left(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x, this->getCoordinates().y + UpperLeft.y));
			this->internalTextColorButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + UpperLeft.x + this->getSize().x, this->getCoordinates().y + UpperLeft.y + this->getSize().y));
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
		else if (internalTextColorButton != NULL)
		{
			this->internalTextColorButton->set_upper_left(Zeni::Point2f(this->getCoordinates().x, this->getCoordinates().y));
			this->internalTextColorButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
		}
		else if (internalColorButton != NULL)
		{
			this->internalColorButton->set_upper_left(Zeni::Point2f(this->getCoordinates().x, this->getCoordinates().y));
			this->internalColorButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
		}
	}
    
#pragma Render methods
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
		else if (internalTextColorButton != NULL)
			this->internalTextColorButton->render();
		else if (internalColorButton != NULL)
			this->internalColorButton->render();
		
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
		else if (internalTextColorButton != NULL)
			this->internalTextColorButton->render();
		else if (internalColorButton != NULL)
			this->internalColorButton->render();
	}
};
