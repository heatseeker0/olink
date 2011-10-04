//
//  Button.h
//  Zenilib
//
//  Created by Alex Turner on 7/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef BUTTON_H
#define BUTTON_H 1

#include "zenilib.h"
#include "GUIObject.h"
#include <string.h>
#include <map>

namespace GUISystem {
	
    class Button : public GUIObject
    {
	public:
		class Delegate
		{
		public:
			//See Widget.h/Text_Button for more info about each one.
			virtual void button_hover(Button *whichButton) {};
			virtual void button_unhover(Button *whichButton) {};
			
			virtual void button_click(Button *whichButton) {};
			virtual void button_stray(Button *whichButton) {};
			virtual void button_unstray(Button *whichButton) {};
			
			virtual void button_accept(Button *whichButton) {};
			virtual void button_reject(Button *whichButton) {};
		};
		
	private:
#define BaseImage "BaseImage"
#define ClickedImage "ClickedImage"
#define HoverImage "HoverImage"
		
		class Internal_TextButton : public Zeni::Text_Button {
			Internal_TextButton(const Internal_TextButton &);
			Internal_TextButton & operator=(const Internal_TextButton &);
			
			Button *button;
			
		public:
			Delegate *delegate;
			
			Internal_TextButton(std::string title, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *newDelegate, Button *button)
			: Text_Button(UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y), "DefaultFont", Zeni::String(title)),
			delegate(newDelegate)
			{
				this->button = button;
			}
			
			void on_hover() {
				this->delegate->button_hover(button);
			}
			
			void on_unhover() {
				this->delegate->button_unhover(button);
			}
			
			void on_click() {
				this->delegate->button_click(button);
			}
			
			void on_stray() {
				this->delegate->button_stray(button);
			}
			
			void on_unstray() {
				this->delegate->button_unstray(button);
			}
			
			void on_accept() {
				this->delegate->button_accept(button);
			}
			
			void on_reject() {
				this->delegate->button_reject(button);
			}
		};
		
		class Internal_TextColorButton : public Zeni::Widget_Button, public Zeni::Widget_Renderer_Text {
			Internal_TextColorButton(const Internal_TextColorButton &);
			Internal_TextColorButton & operator=(const Internal_TextColorButton &);
			
			Button *button;

			Zeni::Widget_Renderer_Tricolor *renderer;
						
			Zeni::Color colorsOfTheButton[2];
			
			Delegate *delegate;
			
		public:
			Internal_TextColorButton(std::string text, Zeni::Color colorsOfTheButton[2], Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *newDelegate, Button *button)
			: Widget_Button(UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y)),
			Widget_Renderer_Text(Zeni::String("DefaultFont"), Zeni::String(text), Zeni::Color())
			{
				this->button = button;
								
				this->renderer = new Zeni::Widget_Renderer_Tricolor(colorsOfTheButton[0], colorsOfTheButton[2], colorsOfTheButton[1],
																	Zeni::Color(), Zeni::Color(), Zeni::Color());
				this->Widget_Button::give_Renderer(this->renderer);
				
				this->delegate = newDelegate;
			}
			
			void on_mouse_button(const Zeni::Point2i &pos, const bool &down, const int &button)
			{
				this->Widget_Button::on_mouse_button(pos, down, button);
			}
			
			void on_mouse_motion(const Zeni::Point2i &pos)
			{
				this->Widget_Button::on_mouse_motion(pos);
			}
			
			void perform_logic()
			{
				this->Widget_Button::perform_logic();
			}
			
			void setColors(Zeni::Color colors[2])
			{
				this->renderer->bg_normal = colors[0];
				this->renderer->bg_clicked = colors[2];
				this->renderer->bg_hovered_strayed = colors[1];
				
				this->colorsOfTheButton[0] = colors[0];
				this->colorsOfTheButton[2] = colors[2];
				this->colorsOfTheButton[1] = colors[1];
			}
			
			void setText(Zeni::String title) { this->text = Zeni::String(title); } 
			
			void on_hover() {				
				this->delegate->button_hover(button);
			}
			
			void on_unhover() {								
				this->delegate->button_unhover(button);
			}
			
			void on_click() {					
				this->delegate->button_click(button);
			}
			
			void on_stray() {								
				this->delegate->button_stray(button);
			}
			
			void on_unstray() {						
				this->delegate->button_unstray(button);
			}
			
			void on_accept() {					
				this->delegate->button_accept(button);
			}
			
			void on_reject() {					
				this->delegate->button_reject(button);
			}
		};
		
		class Internal_TextImageButton : public Zeni::Widget_Button {
			Internal_TextImageButton(const Internal_TextImageButton &);
			Internal_TextImageButton & operator=(const Internal_TextImageButton &);
			
			Button *button;
			
			std::map<std::string, std::string> images;
			
			class Internal_TextureTextRenderer : public Zeni::Widget_Render_Function
			{
			private:
				
				Zeni::Widget_Renderer_Text *textRenderer;
				Zeni::Widget_Renderer_Texture *textureRenderer;
				
			public:
				inline Internal_TextureTextRenderer(Zeni::Widget_Renderer_Text *pointerTextRenderer, Zeni::Widget_Renderer_Texture *pointerTextureRenderer)
				{
					textRenderer = pointerTextRenderer;
					textureRenderer = pointerTextureRenderer;
				}
				
				~Internal_TextureTextRenderer()
				{
					delete textureRenderer;
					delete textRenderer;
				}
				
				/// rect must be of type Widget_Button and Widget_Renderer_Text
				virtual void render_to(const Widget &widget)
				{
					if (textureRenderer != NULL)
						textureRenderer->render_to(widget);
					
					if (textRenderer != NULL)
						textRenderer->render_to(widget);
				}
				
				virtual Internal_TextureTextRenderer * get_duplicate() const
				{
					return new Internal_TextureTextRenderer(textRenderer, textureRenderer);
				}
				
				void setTexture(Zeni::String texture)
				{
					if (textureRenderer != NULL)
						textureRenderer->texture = texture;
				}
			};
			
			Zeni::Widget_Renderer_Text *textRenderer;
			Zeni::Widget_Renderer_Texture *textureRenderer;
			
			Internal_TextureTextRenderer *textureTextRenderer;
			
		public:
			Delegate *delegate;
			
			Internal_TextImageButton(std::map<std::string, std::string> images, std::string text, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *newDelegate, Button *button)
			: delegate(newDelegate),
			Widget_Button(UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y))
			{
				this->button = button;
				this->images = images;
				
				//We never will delete this because it's already deleted by another class and if we delete it again we'll get a bad access there
				textureRenderer = new Zeni::Widget_Renderer_Texture((images.find(BaseImage) != images.end() ? Zeni::String(images[BaseImage]) : Zeni::String("")));
				textRenderer = new Zeni::Widget_Renderer_Text(Zeni::String("DefaultFont"), Zeni::String(text), Zeni::Color(1.0f, 1.0f, 1.0f, 1.0f));
				
				textureTextRenderer = new Internal_TextureTextRenderer(textRenderer, textureRenderer);
				
				this->give_Renderer(textureTextRenderer);
			}
						
			~Internal_TextImageButton()
			{
			}
			
			void setText(Zeni::String title) { this->textRenderer->text = title; } 
			
			void setImages(std::map<std::string, std::string> images) { this->images = images; }
			
			void on_hover() {
				if (images.find(HoverImage) != images.end())
					this->textureRenderer->texture = Zeni::String(images[HoverImage]);
				else
					this->textureRenderer->texture = (images.find(BaseImage) != images.end() ? Zeni::String(images[BaseImage]) : Zeni::String(""));
				
				this->delegate->button_hover(button);
			}
			
			void on_unhover() {
				this->textureRenderer->texture = (images.find(BaseImage) != images.end() ? Zeni::String(images[BaseImage]) : Zeni::String(""));
				
				this->delegate->button_unhover(button);
			}
			
			void on_click() {
				if (images.find(ClickedImage) != images.end())
					this->textureRenderer->texture =  Zeni::String(images[ClickedImage]);
				else
					this->textureRenderer->texture = (images.find(BaseImage) != images.end() ? Zeni::String(images[BaseImage]) : Zeni::String(""));
				
				this->delegate->button_click(button);
			}
			
			void on_stray() {
				this->textureRenderer->texture = (images.find(BaseImage) != images.end() ? Zeni::String(images[BaseImage]) : Zeni::String(""));
				
				this->delegate->button_stray(button);
			}
			
			void on_unstray() {
				if (images.find(ClickedImage) != images.end())
					this->textureRenderer->texture =  Zeni::String(images[ClickedImage]);
				else
					this->textureRenderer->texture = (images.find(BaseImage) != images.end() ? Zeni::String(images[BaseImage]) : Zeni::String(""));
				
				this->delegate->button_unstray(button);
			}
			
			void on_accept() {
				this->textureRenderer->texture = (images.find(BaseImage) != images.end() ? Zeni::String(images[BaseImage]) : Zeni::String(""));
				
				this->delegate->button_accept(button);
			}
			
			void on_reject() {
				this->textureRenderer->texture = (images.find(BaseImage) != images.end() ? Zeni::String(images[BaseImage]) : Zeni::String(""));
				
				this->delegate->button_reject(button);
			}
		};
		
		Internal_TextButton *internalTextButton;
		Internal_TextImageButton *internalTextImageButton;
		Internal_TextImageButton *internalImageButton;
		Internal_TextColorButton *internalColorButton;
		Internal_TextColorButton *internalTextColorButton;
		
	public:
#define Button_T 5
		
		typedef enum {
			NONE,
			TextButton,
			TextImageButton,
			ImageButton,
			ColorButton,
			TextColorButton
		} ButtonType;
        
#pragma mark Initialization
        Button(std::string title, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *delegate); //Initialize the button with a Title and a point to draw from
		Button(std::string title, Zeni::Color colorsOfTheButton[2], Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *delegate);
		Button(Zeni::Color colorsOfTheButton[2], Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *delegate);
		Button(std::map<std::string, std::string> images, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *delegate); //Initialize the button with images and a point to draw from
		Button(std::map<std::string, std::string> images, std::string title, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *delegate); //Initialize the button with images and a title and a point to draw from
        ~Button(); //Dealloc
        
#pragma mark Getters & Setters
        std::string getTitle(); //Get the title of the button
        void setTitle(std::string title); //Set the title of the button
		
		std::map<std::string, std::string> getImages(); //Get the title of the button
        void setImages(std::map<std::string, std::string> images); //Set the title of the button
		
		Zeni::Color* getColors();
		void setColors(Zeni::Color colors[2]);
        
        void setDelegate(Delegate *delegate);
		
		Zeni::Widget *getWidget();
		
		ButtonType getButtonType()
		{
			if (internalTextButton != NULL)
				return TextButton;
			else if (internalTextImageButton != NULL)
				return TextImageButton;
			else if (internalImageButton != NULL)
				return ImageButton;
			else if (internalColorButton != NULL)
				return ColorButton;
			else if (internalTextColorButton != NULL)
				return TextColorButton;
			else
				return NONE;
		}
		
		int getType() { return Button_T; };
		
		void setSize(Zeni::Point2f Size)
		{
			this->GUIObject::setSize(Size);
			
			if (internalTextButton != NULL)
			{
				internalTextButton->set_upper_left(this->getCoordinates());
				internalTextButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
			}
			else if (internalTextImageButton != NULL)
			{
				internalTextImageButton->set_upper_left(this->getCoordinates());
				internalTextImageButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
			}
			else if (internalImageButton != NULL)
			{
				internalImageButton->set_upper_left(this->getCoordinates());
				internalImageButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
			}
			else if (internalColorButton != NULL)
			{
				internalColorButton->set_upper_left(this->getCoordinates());
				internalColorButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
			}
			else if (internalTextColorButton != NULL)
			{
				internalTextColorButton->set_upper_left(this->getCoordinates());
				internalTextColorButton->set_lower_right(Zeni::Point2f(this->getCoordinates().x + this->getSize().x, this->getCoordinates().y + this->getSize().y));
			}
		}
		
		Zeni::Point2f getSize() { return this->GUIObject::getSize(); }
		
#pragma mark movement methods
        
        void transform(Zeni::Point2f UpperLeft); //Move the position by this amount        
        void moveTo(Zeni::Point2f UpperLeft); //Set the object's cords to this
        
#pragma Render methods
        void renderAt(Zeni::Point2f UpperLeft); //Render at the point
		void renderObject();
		
    private:
        std::string title; //Title of the button
		std::map<std::string, std::string> images; //Images of the button
		
		Zeni::Color colorsOfTheButton[2];
        
        Delegate *delegate;
	};
}

#endif
