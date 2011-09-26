//
//  TestState.cpp
//  Zenilib
//
//  Created by Alex Turner on 7/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "GUITestState.h"

#include "Window System/Button.h"

#include <sstream>

#include <utility>

GUITestState::GUITestState()
: screen(std::pair<Zeni::Point2f, Zeni::Point2f>(Zeni::Point2f(0.0f, 0.0f) , Zeni::Point2f(Zeni::get_Video().get_render_target_size()))),
buttonToAdd("Click me!", Zeni::Point2f(50.0f, 10.0f), Zeni::Point2f(100.0f, 50.0f), this),
label("I am a test label", Zeni::Point2f(175.0f, 10.0f), Zeni::Point2f(150.0f, 50.0f)),
checkBox(Zeni::Point2f(350.0f, 10.0f), Zeni::Point2f(50.0f, 50.0f), this),
slider(Zeni::Point2f(425.0f, 10.0f), Zeni::Point2f(425.0f, 110.0f), 15.0f, this),
radioSet(),
radio1(radioSet, Zeni::Point2f(500.0f, 10.0f), Zeni::Point2f(50.0f, 50.0f), this),
radio2(radioSet, Zeni::Point2f(500.0f, 85.0f), Zeni::Point2f(50.0f, 50.0f), this),
window(Zeni::Point2f(575.0f, 10.0f), Zeni::Point2f(100.0f, 100.0f), Zeni::Color(), this),
textureWindow(Zeni::Point2f(575.0f, 135.0f), Zeni::Point2f(100.0f, 100.0f), Zeni::String("BaseImageDemo"), this),
imageLabel("ClickedImageDemo", Zeni::Point2f(175.0f, 85.0f), Zeni::Point2f(50.0f, 50.0f))
{
	screen.addObject(&buttonToAdd);
	screen.addObject(&label);
	screen.addObject(&checkBox);
	screen.addObject(&slider);
	screen.addObject(&radioSet);
	screen.addObject(&radio1);
	screen.addObject(&radio2);
	screen.addObject(&imageLabel);
	
	imageButtonToAdd = NULL;
	
	std::map<std::string, std::string> map;
	map.insert(std::make_pair(BaseImage, "BaseImageDemo"));
	map.insert(std::make_pair(HoverImage, "HoverImageDemo"));
	map.insert(std::make_pair(ClickedImage, "ClickedImageDemo"));
	
	imageButtonToAdd = new Button(map, Zeni::Point2f(50.0f, 85.0f), Zeni::Point2f(50.0f, 50.0f), this);
	
	screen.addObject(imageButtonToAdd);

	textImageButtonToAdd = new Button(map, "Test!", Zeni::Point2f(50.0f, 160.0f), Zeni::Point2f(50.0f, 50.0f), this);
	
	screen.addObject(textImageButtonToAdd);
	
	Zeni::Color colors[2];
	colors[0] = Zeni::get_Colors()["blue"];
	colors[1] = Zeni::get_Colors()["cyan"];
	colors[2] = Zeni::get_Colors()["red"];
	
	Zeni::Color textColors[2];
	textColors[0] = Zeni::get_Colors()["blue"];
	textColors[1] = Zeni::get_Colors()["cyan"];
	textColors[2] = Zeni::get_Colors()["red"];
	
	colorButtonToAdd = new Button(colors, Zeni::Point2f(50.0f, 235.0f), Zeni::Point2f(50.0f, 50.0f), this);
	screen.addObject(colorButtonToAdd);
	
	//textColorButtonToAdd = new Button("Test!", textColors, Zeni::Point2f(50.0f, 310.0f), Zeni::Point2f(50.0f, 50.0f), this);
	//screen.addObject(textColorButtonToAdd);
			
	//GUISystem::Window *testwindow = new GUISystem::Window(Zeni::Point2f(575.0f, 10.0f), Zeni::Point2f(100.0f, 100.0f), Zeni::Color(), this);
	
	//window.lendObject(testwindow);
	
	//screen.addObject(&window);
	
	//screen.addObject(&textureWindow);
	
	screen.setCurrentContextToSelf();
}

GUITestState::~GUITestState()
{
	if (imageButtonToAdd != NULL)
		delete imageButtonToAdd;
	
	if (textImageButtonToAdd != NULL)
		delete textImageButtonToAdd;
	
	if (colorButtonToAdd != NULL)
		delete colorButtonToAdd;
	
	if (textColorButtonToAdd != NULL)
		delete textColorButtonToAdd;
}

void GUITestState::render()
{
	Video &vr = get_Video();
	Zeni::Window &window = get_Window();
	
	vr.set_2d(std::pair<Zeni::Point2f, Zeni::Point2f>(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(window.get_width(), window.get_height())), true);
		
	screen.render();
}

void GUITestState::button_accept(Button *whichButton)
{
	if (whichButton->getUID() != buttonToAdd.getUID())
		return;
	
	static int clicks = 0;
	
	clicks++;
	
	std::stringstream ss;
	ss << clicks;
	
	buttonToAdd.setTitle(ss.str());
}

void GUITestState::checkbox_accept(CheckBox *checkBox)
{
	
}

void GUITestState::slider_slide(GUISystem::Slider *slider)
{
	
}

void GUITestState::slider_accept(GUISystem::Slider *slider)
{
	
}

void GUITestState::radiobutton_accept(RadioButton *radioButton)
{
	
}

void GUITestState::window_close(GUISystem::Window *window)
{
	this->screen.removeObject(window);
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
