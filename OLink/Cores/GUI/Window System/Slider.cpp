//
//  Slider.cpp
//  Application
//
//  Created by Alex Turner on 9/4/11.
//  Copyright 2011 OLink. All rights reserved.
//

#include "Slider.h"

namespace GUISystem {
	
#pragma mark Initialization
	Slider::Slider(Zeni::Point2f endpointa, Zeni::Point2f endpointb, float radius, Slider_Delegate *delegate)
	: GUIObject(endpointa, Zeni::Point2f(endpointb.x - endpointa.x, endpointb.y - endpointa.y)),
	internalSlider(endpointa, endpointb, radius, delegate, this)
	{
	}
	
	Slider::~Slider() {}
	
#pragma mark Getters & Setters
	void Slider::setPosition(const float position)
	{
		internalSlider.set_slider_position(position);
	}
	
	void Slider::setDelegate(Slider_Delegate *delegate)
	{
		internalSlider.delegate = delegate;
	}
	
#pragma mark movement methods
	
	void Slider::transform(Zeni::Point2f UpperLeft)
	{
		this->GUIObject::transform(UpperLeft);
		
		float yBottom = this->internalSlider.get_end_point_b().y - this->internalSlider.get_end_point_a().y;
		
		this->internalSlider.set_end_points(UpperLeft, Zeni::Point2f(UpperLeft.x, UpperLeft.y + yBottom));
	}
	
	void Slider::moveTo(Zeni::Point2f UpperLeft)
	{	
		this->GUIObject::moveTo(UpperLeft);
		
		float yBottom = this->internalSlider.get_end_point_b().y - this->internalSlider.get_end_point_a().y;
		
		this->internalSlider.set_end_points(UpperLeft, Zeni::Point2f(UpperLeft.x, UpperLeft.y + yBottom));
	}
	
#pragma mark render methods
	
	void Slider::renderObject()
	{
		this->internalSlider.render();
	}
	
	void Slider::renderAt(Zeni::Point2f UpperLeft)
	{
		Zeni::Point2f previousCoords = this->getCoordinates();
		
		this->moveTo(UpperLeft);
		
		this->internalSlider.render();
		
		this->moveTo(previousCoords);
	}
	
}