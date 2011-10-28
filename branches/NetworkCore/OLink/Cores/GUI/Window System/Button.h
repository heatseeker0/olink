//
//  Button.h
//  Zenilib
//
//  Created by Alex Turner on 7/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef BUTTON_H
#define BUTTON_H 1

#include <zenilib.h>
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
			virtual void button_hover(Button *) {};
			virtual void button_unhover(Button *) {};
			
			virtual void button_click(Button *) {};
			virtual void button_stray(Button *) {};
			virtual void button_unstray(Button *) {};
			
			virtual void button_accept(Button *) {};
			virtual void button_reject(Button *) {};
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
			
			Internal_TextButton(Zeni::String title, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *newDelegate, Button *button)
			: Text_Button(UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y), "DefaultFont", title)
			{
				this->delegate = newDelegate;
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
			
			Internal_TextImageButton(std::map<std::string, std::string> images, Zeni::String text, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *newDelegate, Button *button)
			: delegate(newDelegate),
			Widget_Button(UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y))
			{
				this->button = button;
				this->images = images;
				
				//We never will delete this because it's already deleted by another class and if we delete it again we'll get a bad access there
				textureRenderer = new Zeni::Widget_Renderer_Texture((images.find(BaseImage) != images.end() ? Zeni::String(images[BaseImage]) : Zeni::String("")));
				textRenderer = new Zeni::Widget_Renderer_Text(Zeni::String("DefaultFont"), text, Zeni::Color(1.0f, 1.0f, 1.0f, 1.0f));
				
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
        
// Initialization
        Button(std::string title, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *delegate); //Initialize the button with a Title and a point to draw from
		Button(std::map<std::string, std::string> images, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *delegate); //Initialize the button with images and a point to draw from
		Button(std::map<std::string, std::string> images, std::string title, Zeni::Point2f UpperLeft, Zeni::Point2f Size, Delegate *delegate); //Initialize the button with images and a title and a point to draw from
        ~Button(); //Dealloc
        
// Getters & Setters
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
			else
				return NONE;
		}
		
		int getType() { return Button_T; };
		
		void setSize(Zeni::Point2f Size);
		
		Zeni::Point2f getSize() { return this->GUIObject::getSize(); }
		
// movement methods
        
        void transform(Zeni::Point2f UpperLeft); //Move the position by this amount        
        void moveTo(Zeni::Point2f UpperLeft); //Set the object's cords to this
        
// Render methods
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
