//
//  TestState.h
//  Zenilib
//
//  Created by Alex Turner on 7/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "zenilib.h"
#include "Window System.h"

#include "Button.h"

#include <utility>

using namespace GUISystem;
using namespace Zeni;

class TestState : public Gamestate_Base, public Button::Button_Delegate
{
public:
    TestState()
    : buttonToAdd("test", Zeni::Point2f(0.0f, 00.0f), this),
	screen(Zeni::Point2f(get_Window().get_width(), get_Window().get_height()))
    {
        screen.addObject(buttonToAdd);
		
		screen.setCurrentContextToSelf();
    }
    
    void render()
    {
		Video &vr = get_Video();
		Window &window = get_Window();
		
		vr.set_2d(std::pair<Zeni::Point2f, Zeni::Point2f>(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(window.get_width(), window.get_height())), true);
		
        screen.render();
    }
    
private:
    GUISystem::Window_System screen;
    Button buttonToAdd;
};
