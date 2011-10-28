//
//  RadioButton.h
//  Application
//
//  Created by Alex Turner on 9/4/11.
//  Copyright 2011 OLink. All rights reserved.
//

#include "CheckBox.h"

#include <vector>

namespace GUISystem {
	
	class RadioButton;
	
	class RadioButton_Set : public GUIObject, public Zeni::Widget
	{
		std::vector<RadioButton *> radioButtons;
		
	public:
#define RadioButton_Set_T 2
		
		RadioButton_Set();
		~RadioButton_Set();
		
		void accept(RadioButton &radioButton);
		void clear();
		
		void lendRadioButton(RadioButton &radioButton);
		void unlendRadioButton(RadioButton &radioButton);
		
		Zeni::Widget *getWidget() { return this; };
		
		int getType() { return RadioButton_Set_T; };
        
// render methods
        
        void renderObject(); //Every sub class needs to have a render method!
        void renderAt(Zeni::Point2f UpperLeft); //Render method to render at a specific point, used for adjusting if for example the object is in a window
		
// Widget methods
		
		void on_mouse_button(const Zeni::Point2i &pos, const bool &down, const int &button);
		void on_mouse_motion(const Zeni::Point2i &pos);
	};
	
	class RadioButton : public CheckBox, public CheckBox::CheckBox_Delegate
	{
	public:
		class RadioButton_Delegate {
		public:
			virtual void radiobutton_accept(RadioButton *) {};
		};
		
		RadioButton_Delegate *delegate;
		RadioButton_Set &radioButton_Set;
		
	public:
#define RadioButton_T 3
		
// Initialization
		RadioButton(RadioButton_Set &radioButton_Set,
					const Zeni::Point2f &UpperLeft, const Zeni::Point2f &Size,
					RadioButton_Delegate *delegate);
		~RadioButton();
		
// CheckBox Delegate methods
		
		void checkbox_accept(CheckBox *checkBox);
		
		void checkbox_click(CheckBox *checkBox);
		
		void checkbox_stray(CheckBox *checkBox);
		void checkbox_unstray(CheckBox *checkBox);
		
		void checkbox_reject(CheckBox *checkBox);
		
		int getType() { return RadioButton_T; };
	};
}