//
//  Slider.h
//  Application
//
//  Created by Alex Turner on 9/4/11.
//  Copyright 2011 OLink. All rights reserved.
//

#include "zenilib.h"
#include "GUIObject.h"

namespace GUISystem {
	
	class Slider : public GUIObject
	{
	public:
		class Slider_Delegate
		{
		public:
			virtual void slider_slide(GUISystem::Slider *slider) {};
			virtual void slider_accept(GUISystem::Slider *slider) {};
		};
		
	private:
		
		class Internal_Slider : public Zeni::Slider
		{
			GUISystem::Slider *slider;
		public:
			Slider_Delegate *delegate;
			
			Internal_Slider(Zeni::Point2f endpointa, Zeni::Point2f endpointb, float radius, Slider_Delegate *newDelegate, GUISystem::Slider *newSlider)
			: Zeni::Slider(endpointa, endpointb, radius)
			{
				this->slider = newSlider;
				this->delegate = newDelegate;
			}
			
			void on_accept()
			{
				Slider::on_accept();
				this->delegate->slider_accept(this->slider);
			}
			
			void on_slide()
			{
				Slider::on_slide();
				this->delegate->slider_slide(this->slider);
			}
		};
		
		Internal_Slider internalSlider;
		
	public:
#define Slider_T 1
		
#pragma mark Initialization
        Slider(Zeni::Point2f endpointa, Zeni::Point2f endpointb, float radius, Slider_Delegate *delegate); //Initialize the button with a Title and a point to draw from
        ~Slider(); //Dealloc
        
#pragma mark Getters & Setters
        void setPosition(const float position);
        
        void setDelegate(Slider_Delegate *delegate);
		
		Zeni::Widget *getWidget() { return &internalSlider; };

		int getType() { return Slider_T; }
		
#pragma mark movement methods
		
		void transform(Zeni::Point2f UpperLeft); //Move the position by this amount        
        void moveTo(Zeni::Point2f UpperLeft); //Set the object's cords to this
        
#pragma mark render methods
        
        void renderObject(); //Every sub class needs to have a render method!
        void renderAt(Zeni::Point2f UpperLeft); //Render method to render at a specific point, used for adjusting if for example the object is in a window	
	};
	
}