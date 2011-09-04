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

#include <utility>

using namespace GUISystem;
using namespace Zeni;

class GUITestState : public Gamestate_Base, public Button::Button_Delegate
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
	
private:
    GUISystem::Window_System screen;
    Button buttonToAdd;
	TextLabel label;
};

#endif
