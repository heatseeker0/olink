//
//  ImageLabel.cpp
//  Application
//
//  Created by Alex Turner on 9/19/11.
//  Copyright 2011 OLink. All rights reserved.
//

#include <zenilib.h>

#include "ImageLabel.h"

namespace GUISystem {
	
	ImageLabel::ImageLabel(std::string image, Zeni::Point2f UpperLeft, Zeni::Point2f Size)
	: GUIObject(UpperLeft, Size),
	internalImageLabel(image, UpperLeft, Size)
	{
	}
	
	ImageLabel::~ImageLabel()
	{
	}
	
	void ImageLabel::setImage(std::string image)
	{
		this->internalImageLabel.setImage(image);
	}
	
	void ImageLabel::transform(Zeni::Point2f UpperLeft)
	{
		this->GUIObject::transform(UpperLeft);
		
		this->internalImageLabel.set_upper_left(this->getCoordinates());
		this->internalImageLabel.set_upper_left(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
	}
	
	void ImageLabel::moveTo(Zeni::Point2f UpperLeft)
	{
		this->GUIObject::moveTo(UpperLeft);
		
		this->internalImageLabel.set_upper_left(UpperLeft);
		this->internalImageLabel.set_lower_right(Zeni::Point2f(UpperLeft.x + this->getSize().x, UpperLeft.y + this->getSize().y));
	}
	
// Render methods
	void ImageLabel::renderAt(Zeni::Point2f UpperLeft)
	{
		Zeni::Point2f OldUpperLeft = this->getCoordinates();
		this->moveTo(UpperLeft);
		
		this->renderObject();
		
		this->moveTo(OldUpperLeft);
	}
	
	void ImageLabel::renderObject()
	{
		this->internalImageLabel.render();
	}
	
	Zeni::Widget* ImageLabel::getWidget()
	{
		return &internalImageLabel;
	}
	
};
