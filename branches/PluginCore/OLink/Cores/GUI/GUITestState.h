//
//  TestState.h
//  Zenilib
//
//  Created by Alex Turner on 7/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GUITestState_H
#define GUITestState_H

#include <zenilib.h>
#include "Window System/Window System.h"
#include "Window System/Button.h"
#include "Window System/TextLabel.h"
#include "Window System/CheckBox.h"
#include "Window System/Slider.h"
#include "Window System/RadioButton.h"
#include "Window System/Window.h"
#include "Window System/ImageLabel.h"

#include <utility>

using namespace GUISystem;
using namespace Zeni;

class GUITestState : public Gamestate_Base, public Button::Delegate, public CheckBox::CheckBox_Delegate, public GUISystem::Slider::Slider_Delegate, public GUISystem::RadioButton::RadioButton_Delegate, public GUISystem::Window::Window_Delegate
{
public:
    GUITestState();
    ~GUITestState();
	
    void render();
	void on_mouse_button(const SDL_MouseButtonEvent &event);
	void on_mouse_motion(const SDL_MouseMotionEvent &event);
	void on_key(const SDL_KeyboardEvent &event);
	void perform_logic();
	
// Button Delegate Methods
	void button_accept(Button *whichButton);
	
// CheckBox Delegate Methods
	
	void checkbox_accept(CheckBox *checkBox);
	
// Slider Delegate Methods
	
	void slider_slide(GUISystem::Slider *slider);
	void slider_accept(GUISystem::Slider *slider);
	
// RadioButton Delegate Methods
	
	void radiobutton_accept(RadioButton *radioButton);
	
// Window Delegate Methods
	
	void window_close(GUISystem::Window *window);

private:
    GUISystem::Window_System screen;
    GUISystem::Button buttonToAdd;
	GUISystem::Button *imageButtonToAdd;
	GUISystem::Button *imageButtonToAddBig;
	GUISystem::Button *textImageButtonToAdd;
	GUISystem::TextLabel label;
	GUISystem::CheckBox checkBox;
	GUISystem::Slider slider;
	GUISystem::RadioButton_Set radioSet;
	GUISystem::RadioButton radio1;
	GUISystem::RadioButton radio2;
	GUISystem::Window window;
	GUISystem::Window textureWindow;
	GUISystem::ImageLabel imageLabel;
};

#endif
