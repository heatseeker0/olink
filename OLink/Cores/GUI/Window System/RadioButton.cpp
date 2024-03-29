//
//  RadioButton.cpp
//  Application
//
//  Created by Alex Turner on 9/4/11.
//  Copyright 2011 OLink. All rights reserved.
//

#include <zenilib.h>

#include "RadioButton.h"

namespace GUISystem {
	
	RadioButton_Set::RadioButton_Set()
	: GUIObject(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(0.0f, 0.0f))
	{
	}
	
	RadioButton_Set::~RadioButton_Set()
	{
	}
	
	void RadioButton_Set::accept(RadioButton &radioButton)
	{
		for (std::vector<RadioButton *>::iterator it = radioButtons.begin();it != radioButtons.end();it++)
		{
			if ((*it) != &radioButton)
			{
				(*it)->setChecked(false);
			}
		}
	}
	
	void RadioButton_Set::clear()
	{
		radioButtons.clear();
	}
	
	void RadioButton_Set::lendRadioButton(RadioButton &radioButton)
	{
		bool found = false;
		
		for (std::vector<RadioButton *>::iterator it = radioButtons.begin();it != radioButtons.end();it++)
		{
			if ((*it) == &radioButton)
				found = true;
		}
		
		if (!found)
			radioButtons.push_back(&radioButton);
	}
	
	void RadioButton_Set::unlendRadioButton(RadioButton &radioButton)
	{
		for (std::vector<RadioButton *>::iterator it = radioButtons.begin();it != radioButtons.end();it++)
		{
			if ((*it) == &radioButton)
				radioButtons.erase(it);
		}
	}
	
// render methods
	
	void RadioButton_Set::renderObject()
	{
	}
	
	void RadioButton_Set::renderAt(Zeni::Point2f )
	{
	}
	
// Widget methods
	
	void RadioButton_Set::on_mouse_button(const Zeni::Point2i &, const bool &, const int &) {}
	void RadioButton_Set::on_mouse_motion(const Zeni::Point2i &) {}
	
// Initialization
	RadioButton::RadioButton(RadioButton_Set &newRadioButton_Set,
				const Zeni::Point2f &UpperLeft, const Zeni::Point2f &Size,
				RadioButton_Delegate *newDelegate)
	: CheckBox(UpperLeft, Size, this, true),
	radioButton_Set(newRadioButton_Set)
	{
		newRadioButton_Set.lendRadioButton(*this);
		this->delegate = newDelegate;
	}
	
	RadioButton::~RadioButton()
	{
	}
	
// CheckBox Delegate methods
	
	void RadioButton::checkbox_accept(CheckBox *)
	{
		radioButton_Set.accept(*this);
		
		this->delegate->radiobutton_accept(this);
	}
	
	void RadioButton::checkbox_click(CheckBox *) {}
	
	void RadioButton::checkbox_stray(CheckBox *) {}
	void RadioButton::checkbox_unstray(CheckBox *) {}
	
	void RadioButton::checkbox_reject(CheckBox *) {}
}