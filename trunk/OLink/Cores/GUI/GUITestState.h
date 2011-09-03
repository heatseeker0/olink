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
    
    void render();
	
private:
    GUISystem::Window_System screen;
    Button buttonToAdd;
};
