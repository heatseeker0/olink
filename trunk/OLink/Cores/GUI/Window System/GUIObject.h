//
//  GUIObject.h
//  Zenilib
//
//  Created by Alex Turner on 7/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef GUIOBJECT
#define GUIOBJECT 1

#include <zenilib.h>
#include <string>

namespace GUISystem {
    
	class Window_System;
	
    //Base class for all GUI Objects.
    class GUIObject
    {
    public:
#define GUIObject_T 0
		
// Initialization Methods
        GUIObject(Zeni::Point2f coord, Zeni::Point2f Size); //Initialize the object with the coordinates coord
        ~GUIObject();
        
// Getters & Setters
        
        virtual Zeni::Point2f getCoordinates(); //Get the coord variable
#ifndef _WINDOWS
        virtual void setCoordinates(Zeni::Point2f UpperLeft) __attribute__ ((deprecated)); //Set the coord variable.  You should probably use moveTo for more clarity but it's there as a generic setter
#else
		__declspec(deprecated) virtual void setCoordinates(Zeni::Point2f UpperLeft);
#endif

		virtual Zeni::Point2f getSize() { return this->Size; }
		virtual void setSize(Zeni::Point2f Size) { this->Size = Size; }
		
        Zeni::String getUID() const;
		
		virtual void setWindowSystem(Window_System *windowSystem) { this->windowSystem = windowSystem; }
		virtual Window_System *getWindowSystem() { return this->windowSystem; }
		
		virtual int getType() { return GUIObject_T; }
        
// movement methods
        
        virtual void transform(Zeni::Point2f UpperLeft); //Move the position by this amount        
        virtual void moveTo(Zeni::Point2f UpperLeft); //Set the object's cords to this
        
// render methods
        
        virtual void renderObject() = 0; //Every sub class needs to have a render method!
        virtual void renderAt(Zeni::Point2f UpperLeft) = 0; //Render method to render at a specific point, used for adjusting if for example the object is in a window	
		virtual Zeni::Widget *getWidget() = 0;
		
// Comparison Operators
		
		bool operator ==(const GUIObject& b) const; 
		bool operator !=(const GUIObject& b) const;	
		
    private:
        Zeni::String m_uniqueIdentifier; //Unique identifier to identify this object as unique. ( Unix timestamp when object was created + :randomnumber should be unique )
        
        Zeni::Point2f m_coord; //Coord of the object relative to the base cord (not necesarily the actual coord)
		
		Zeni::Point2f Size;
		
		Window_System *windowSystem;
    };
}

#endif
