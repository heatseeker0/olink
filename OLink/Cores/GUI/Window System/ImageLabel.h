//
//  ImageLabel.h
//  Application
//
//  Created by Alex Turner on 9/19/11.
//  Copyright 2011 OLink. All rights reserved.
//

#ifndef ImageLabel_H
#define ImageLabel_H 1

#include "zenilib.h"
#include "GUIObject.h"

namespace GUISystem {
	
	class ImageLabel : public GUIObject
	{
	private:
		class Internal_ImageLabel : public Zeni::Widget_Rectangle, public Zeni::Widget
		{
		private:
			Internal_ImageLabel(const Internal_ImageLabel &);
			Internal_ImageLabel & operator=(const Internal_ImageLabel &);
			
			std::string image;
			
			Zeni::Widget_Renderer_Texture *imageRenderer;
			
		public:
			Internal_ImageLabel(std::string image, Zeni::Point2f UpperLeft, Zeni::Point2f Size)
			: Widget_Rectangle(UpperLeft, Zeni::Point2f(UpperLeft.x + Size.x, UpperLeft.y + Size.y))
			{
				this->image = image;
				
				this->imageRenderer = new Zeni::Widget_Renderer_Texture(Zeni::String(image));
				this->give_Renderer(this->imageRenderer);
			}
			
			void setImage(std::string image)
			{
				this->image = image;
				
				imageRenderer->texture = image;
			}
			
			void on_key(const SDL_keysym & /*keysym*/, const bool & /*down*/)
			{}
			
			void on_mouse_button(const Zeni::Point2i &pos, const bool &down, const int &button)
			{}
			
			void on_mouse_motion(const Zeni::Point2i &pos)
			{}
			
			void perform_logic()
			{}
		};
		
		Internal_ImageLabel internalImageLabel;
				
	public:
#define ImageLabel_T 9
		
		ImageLabel(std::string image, Zeni::Point2f UpperLeft, Zeni::Point2f Size);
		~ImageLabel();
		
		void setImage(std::string image);
		
		void transform(Zeni::Point2f UpperLeft); //Move the position by this amount        
        void moveTo(Zeni::Point2f UpperLeft); //Set the object's cords to this
		
		int getType() { return ImageLabel_T; };
        
#pragma Render methods
        void renderAt(Zeni::Point2f UpperLeft); //Render at the point
		void renderObject();
		
		Zeni::Widget* getWidget();
	};
	
};

#endif
