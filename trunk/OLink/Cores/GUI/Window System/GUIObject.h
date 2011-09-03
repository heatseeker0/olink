//
//  GUIObject.h
//  Zenilib
//
//  Created by Alex Turner on 7/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef GUIOBJECT
#define GUIOBJECT 1

#include "zenilib.h"
#include <string>

namespace GUISystem {
    
    //Base class for all GUI Objects.
    class GUIObject
    {
    public:
#pragma mark Initialization Methods
        GUIObject(Zeni::Point2f coord); //Initialize the object with the coordinates coord
        ~GUIObject();
        
#pragma mark Getters & Setters
        
        Zeni::Point2f getCoordinates(); //Get the coord variable
        void setCoordinates(Zeni::Point2f UpperLeft) __attribute__ ((deprecated)); //Set the coord variable.  You should probably use moveTo for more clarity but it's there as a generic setter
        
        std::string getUID();
        
#pragma mark movement methods
        
        void transform(Zeni::Point2f UpperLeft); //Move the position by this amount        
        void moveTo(Zeni::Point2f UpperLeft); //Set the object's cords to this
        
#pragma mark render methods
        
        virtual void renderObject(); //Every sub class needs to have a render method!
        virtual void renderAt(Zeni::Point2f UpperLeft); //Render method to render at a specific point, used for adjusting if for example the object is in a window		
    private:
        std::string m_uniqueIdentifier; //Unique identifier to identify this object as unique. ( Unix timestamp when object was created + :randomnumber should be unique )
        
        Zeni::Point2f m_coord; //Coord of the object relative to the base cord (not necesarily the actual coord)
    };
}

#endif
