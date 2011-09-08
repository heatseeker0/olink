//
//  RadioButton.h
//  Application
//
//  Created by Alex Turner on 9/4/11.
//  Copyright 2011 OLink. All rights reserved.
//

#include "GUIObject.h"

namespace GUISystem {
	
	/*class RadioButton : public GUIObject
	{
	public:
		class RadioButton_Delegate {
		public:
			virtual void radiobutton_accept(RadioButton *radioButton) = 0;
		};
		
		RadioButton_Delegate &delegate;
		
	private:
		class Internal_RadioButton : public Zeni::Radio_Button
		{
			RadioButton_Delegate &delegate;
			
			RadioButton *radioButton;
		public:
			Internal_RadioButton(RadioButton_Set &radioButton_Set,
								 const Zeni::Point2f &UpperLeft, const Zeni::Point2f &Size,
								 RadioButton_Delegate &newDelegate,
								 RadioButton *radioButton)
			: Zeni::Radio_Button((*radioButton_Set.getRadioButtonSet()), UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y)),
			delegate(newDelegate)
			{
				this->radioButton = radioButton;
			}
			
			void on_accept()
			{
				delegate.radiobutton_accept(radioButton);
			}
		};
		
		Internal_RadioButton internalRadioButton;
		
		Zeni::Point2f Size;
		
	public:
#pragma mark Initialization
		RadioButton(RadioButton_Set &radioButton_Set,
					const Zeni::Point2f &UpperLeft, const Zeni::Point2f &Size,
					RadioButton_Delegate &delegate);
		~RadioButton();
		
#pragma mark Getters & Setters		
		Zeni::Widget *getWidget() { return &internalRadioButton; };
		
#pragma mark movement methods
		
		void transform(Zeni::Point2f UpperLeft); //Move the position by this amount        
        void moveTo(Zeni::Point2f UpperLeft); //Set the object's cords to this
        
#pragma mark render methods
        
        void renderObject(); //Every sub class needs to have a render method!
        void renderAt(Zeni::Point2f UpperLeft); //Render method to render at a specific point, used for adjusting if for example the object is in a window
	};
	
	class RadioButton_Set : public GUIObject
	{
		Zeni::Radio_Button_Set internalRadioButtonSet;
		
	public:
		void accept(RadioButton &radioButton);
		void clear();
		
		Zeni::Widget *getWidget() { return &internalRadioButtonSet; };
		Zeni::Radio_Button_Set* getRadioButtonSet() { return &internalRadioButtonSet; }
		
#pragma mark movement methods
		
		void transform(Zeni::Point2f UpperLeft); //Move the position by this amount        
        void moveTo(Zeni::Point2f UpperLeft); //Set the object's cords to this
        
#pragma mark render methods
        
        void renderObject(); //Every sub class needs to have a render method!
        void renderAt(Zeni::Point2f UpperLeft); //Render method to render at a specific point, used for adjusting if for example the object is in a window
	};*/
	
}