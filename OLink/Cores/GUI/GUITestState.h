//
//  TestState.h
//  Zenilib
//
//  Created by Alex Turner on 7/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GUITestState_H
#define GUITestState_H

#include "zenilib.h"
#include "Window System/Window System.h"
#include "Window System/Button.h"
#include "Window System/TextLabel.h"
#include "Window System/CheckBox.h"
#include "Window System/Slider.h"

#include <utility>

using namespace GUISystem;
using namespace Zeni;

class GUITestState : public Gamestate_Base, public Button::Button_Delegate, public CheckBox::CheckBox_Delegate, public GUISystem::Slider::Slider_Delegate
{
public:
    GUITestState();
    ~GUITestState();
	
    void render();
	void on_mouse_button(const SDL_MouseButtonEvent &event);
	void on_mouse_motion(const SDL_MouseMotionEvent &event);
	void on_key(const SDL_KeyboardEvent &event);
	void perform_logic();
	
#pragma mark Button Delegate Methods
	
	void button_hover(Button *whichButton);
	void button_unhover(Button *whichButton);
	
	void button_click(Button *whichButton);
	void button_stray(Button *whichButton);
	void button_unstray(Button *whichButton);
	
	void button_accept(Button *whichButton);
	void button_reject(Button *whichButton);
	
#pragma mark CheckBox Delegate Methods
	
	void checkbox_accept(CheckBox *checkBox);
	
	void checkbox_click(CheckBox *checkBox);
	
	void checkbox_stray(CheckBox *checkBox);
	void checkbox_unstray(CheckBox *checkBox);
	
	void checkbox_reject(CheckBox *checkBox);
	
#pragma mark Slider Delegate Methods
	
	void slider_slide(GUISystem::Slider *slider);
	void slider_accept(GUISystem::Slider *slider);
	
private:
    GUISystem::Window_System screen;
    GUISystem::Button buttonToAdd;
	GUISystem::TextLabel label;
	GUISystem::CheckBox checkBox;
	GUISystem::Slider slider;
};

#endif
