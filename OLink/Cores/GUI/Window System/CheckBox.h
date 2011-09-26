//
//  CheckBox.h
//  Application
//
//  Created by Alex Turner on 9/4/11.
//  Copyright 2011 OLink. All rights reserved.
//

#ifndef CheckBox_H
#define CheckBox_H 1

#include "zenilib.h"

#include "GUIObject.h"

namespace GUISystem {
	
	class CheckBox : public GUIObject
	{
		
	public:
		class CheckBox_Delegate {
		public:
			virtual void checkbox_accept(CheckBox *checkBox) {};
			
			virtual void checkbox_click(CheckBox *checkBox) {};
			
			virtual void checkbox_stray(CheckBox *checkBox) {};
			virtual void checkbox_unstray(CheckBox *checkBox) {};
			
			virtual void checkbox_reject(CheckBox *checkBox) {};
		};
		
	private:
		
		class Internal_CheckBox : public Zeni::Check_Box
		{
			Internal_CheckBox(const Internal_CheckBox &);
			Internal_CheckBox & operator=(const Internal_CheckBox &);
			
			CheckBox_Delegate *delegate;
			
			CheckBox *checkBox;
			
			bool isRadio;
			
		public:
			Internal_CheckBox(const Zeni::Point2f &UpperLeft, const Zeni::Point2f &Size, CheckBox_Delegate *newDelegate, CheckBox *checkBox, bool radioButton = false)
			: Check_Box(UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y)),
			delegate(newDelegate)
			{
				this->checkBox = checkBox;
				this->isRadio = radioButton;
			}
			
			void on_accept() {
				if (!isRadio || (isRadio && !this->is_checked()))
				{
					Check_Box::on_accept();
					this->delegate->checkbox_accept(checkBox);
				}
			}
			
			void on_click() {
				if (!isRadio || (isRadio && !this->is_checked()))
				{
					Check_Box::on_click();
					this->delegate->checkbox_click(checkBox);
				}
			}
			
			void on_unstray() {
				Check_Box::on_unstray();
				this->delegate->checkbox_unstray(checkBox);
			}
			
			void on_reject() {
				Check_Box::on_reject();
				this->delegate->checkbox_reject(checkBox);
			}
			
			void on_stray() {
				Check_Box::on_stray();
				this->delegate->checkbox_stray(checkBox);
			}
		};
		
		CheckBox_Delegate *delegate;
		
		Internal_CheckBox internalCheckBox;
				
	public:
#define CheckBox_T 4
		
#pragma mark Initialization
        CheckBox(Zeni::Point2f UpperLeft, Zeni::Point2f Size, CheckBox_Delegate *delegate, bool radioButton = false); //Initialize the text label with a Title and a point to draw from
        ~CheckBox(); //Dealloc
        
#pragma mark Getters & Setters
        bool isChecked(); //Is the check box checked?
		void setChecked(bool checked);
		
		int getType() { return CheckBox_T; };
		
#pragma mark movement methods
        
        void transform(Zeni::Point2f UpperLeft); //Move the position by this amount        
        void moveTo(Zeni::Point2f UpperLeft); //Set the object's cords to this
        
#pragma Render methods
        void renderAt(Zeni::Point2f UpperLeft); //Render at the point
		void renderObject();
		
		Zeni::Widget* getWidget();
	};
	
}

#endif
