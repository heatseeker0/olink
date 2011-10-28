//
//  GUIObject.cpp
//  Zenilib
//
//  Created by Alex Turner on 7/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <zenilib.h>

#include "GUIObject.h"

#include <time.h>
#include <string>
#include <sstream>

namespace GUISystem {
    
// Initialization Methods

    GUIObject::GUIObject(Zeni::Point2f coord, Zeni::Point2f Size) //Initialize the object with the coordinates coord
    : m_coord(coord)
    {
        using namespace std;
        //Get the current time since the epoch and then make it a string
        
        static long long objectID = 0;
		
		stringstream ss;
		
		ss << ++objectID;
        
        //Set the member variable to our newly generated ID
        m_uniqueIdentifier = ss.str();
		
		windowSystem = NULL;
		
		this->Size = Size;
	}
    
    GUIObject::~GUIObject()
    {
        //No pointers = no dealloc necesary from our view
    }
    
// Getters & Setters
    
    Zeni::Point2f GUIObject::getCoordinates()
    {
        //Return our member variable coord
        return m_coord;
    }
    
    void GUIObject::setCoordinates(Zeni::Point2f newCoords)
    {
        //Set our member variable to the new coord
        m_coord = newCoords;
    }
    
    std::string GUIObject::getUID() const
    {
        return m_uniqueIdentifier;
    }
    
// movement methods

    void GUIObject::transform(Zeni::Point2f coordToMoveBy)
    {
        //Transform the current coords by the new ones, as in add to our current values
        m_coord.x += coordToMoveBy.x;
        m_coord.y += coordToMoveBy.y;
    }
    
    void GUIObject::moveTo(Zeni::Point2f coordToMoveTo)
    {
        //Set our coords to these to move us TO a point
        m_coord = coordToMoveTo;
    }
	
// Comparison Operators
	
	bool GUIObject::operator ==(const GUIObject& b) const
	{
		return (this->getUID() == b.getUID());
	}
	
	bool GUIObject::operator !=(const GUIObject& b) const
	{
		return !(*this == b);
	}
}
