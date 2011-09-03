//
//  TestState.cpp
//  Zenilib
//
//  Created by Alex Turner on 7/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "GUITestState.h"

GUITestState::GUITestState()
: buttonToAdd("test", Zeni::Point2f(0.0f, 00.0f), this),
screen(Zeni::Point2f(get_Window().get_width(), get_Window().get_height()))
{
	screen.addObject(buttonToAdd);
	
	screen.setCurrentContextToSelf();
}

void GUITestState::render()
{
	Video &vr = get_Video();
	Window &window = get_Window();
	
	vr.set_2d(std::pair<Zeni::Point2f, Zeni::Point2f>(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(window.get_width(), window.get_height())), true);
	
	screen.render();
}
