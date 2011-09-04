//
//  TestState.cpp
//  Zenilib
//
//  Created by Alex Turner on 7/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "GUITestState.h"

GUITestState::GUITestState()
: screen(Zeni::Point2f(get_Window().get_width(), get_Window().get_height()))
{
	std::cout << "GUITestState:" << this << std::endl;
	buttonToAdd = new Button("Test", Zeni::Point2f(100.0f, 100.0f));
	std::cout << "buttonToAdd:" << buttonToAdd << std::endl;
	buttonToAdd->setDelegate(this);
	screen.addObject(buttonToAdd);
	
	screen.setCurrentContextToSelf();
}

GUITestState::~GUITestState()
{
	delete buttonToAdd;
}

void GUITestState::render()
{
	Video &vr = get_Video();
	Window &window = get_Window();
	
	vr.set_2d(std::pair<Zeni::Point2f, Zeni::Point2f>(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(window.get_width(), window.get_height())), true);
	
	screen.render();
}

void GUITestState::button_hover()
{
	//Do nothing
}

void GUITestState::button_unhover()
{
	//Do nothing
}

void GUITestState::button_click()
{
	buttonToAdd->setTitle("Clicked!");
}

void GUITestState::button_stray()
{
	//Do nothing
}

void GUITestState::button_unstray()
{
	//Do nothing
}

void GUITestState::button_accept()
{
	//Do nothing
}

void GUITestState::button_reject()
{
	//Do nothing
}

void GUITestState::on_mouse_button(const SDL_MouseButtonEvent &event)
{
	screen.on_mouse_button(event);
}

void GUITestState::on_mouse_motion(const SDL_MouseMotionEvent &event)
{
	screen.on_mouse_motion(event);
}

void GUITestState::on_key(const SDL_KeyboardEvent &event)
{
	screen.on_key(event);
}

void GUITestState::perform_logic()
{
	screen.perform_logic();
}
