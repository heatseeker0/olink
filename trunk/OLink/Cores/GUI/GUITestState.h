//
//  TestState.h
//  Zenilib
//
//  Created by Alex Turner on 7/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "zenilib.h"
#include "Window System/Window System.h"

#include "Window System/Button.h"

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
	
	void button_hover();
	void button_unhover();
	
	void button_click();
	void button_stray();
	void button_unstray();
	
	void button_accept();
	void button_reject();
	
private:
    GUISystem::Window_System screen;
    Button *buttonToAdd;
};
