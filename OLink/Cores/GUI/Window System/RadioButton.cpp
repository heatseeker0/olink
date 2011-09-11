//
//  RadioButton.cpp
//  Application
//
//  Created by Alex Turner on 9/4/11.
//  Copyright 2011 OLink. All rights reserved.
//

#include "RadioButton.h"

namespace GUISystem {
	
	RadioButton_Set::RadioButton_Set()
	: GUIObject(Zeni::Point2f(0.0f, 0.0f))
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
	
#pragma mark render methods
	
	void RadioButton_Set::renderObject()
	{
	}
	
	void RadioButton_Set::renderAt(Zeni::Point2f UpperLeft)
	{
	}
	
#pragma mark Widget methods
	
	void RadioButton_Set::on_mouse_button(const Zeni::Point2i &pos, const bool &down, const int &button) {}
	void RadioButton_Set::on_mouse_motion(const Zeni::Point2i &pos) {}
	
#pragma mark Initialization
	RadioButton::RadioButton(RadioButton_Set &newRadioButton_Set,
				const Zeni::Point2f &UpperLeft, const Zeni::Point2f &Size,
				RadioButton_Delegate &newDelegate)
	: CheckBox::CheckBox(UpperLeft, Size, *this, true),
	delegate(newDelegate),
	radioButton_Set(newRadioButton_Set)
	{
		newRadioButton_Set.lendRadioButton(*this);
	}
	
	RadioButton::~RadioButton()
	{
	}
	
#pragma mark CheckBox Delegate methods
	
	void RadioButton::checkbox_accept(CheckBox *checkBox)
	{
		radioButton_Set.accept(*this);
		
		this->delegate.radiobutton_accept(this);
	}
	
	void RadioButton::checkbox_click(CheckBox *checkBox) {}
	
	void RadioButton::checkbox_stray(CheckBox *checkBox) {}
	void RadioButton::checkbox_unstray(CheckBox *checkBox) {}
	
	void RadioButton::checkbox_reject(CheckBox *checkBox) {}
}