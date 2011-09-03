//
//  GUIObject.cpp
//  Zenilib
//
//  Created by Alex Turner on 7/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "GUIObject.h"

#include <time.h>
#include <string>
#include <sstream>

namespace GUISystem {
    
#pragma mark Initialization Methods

    GUIObject::GUIObject(Zeni::Point2f coord) //Initialize the object with the coordinates coord
    : m_coord(coord)
    {
        using namespace std;
        //Get the current time since the epoch and then make it a string
        
        //Create the string stream to be used for the transformation from time_t (long) to string
        stringstream stream;
        
        //Construct the holder for the time
        time_t currentTime;
        //Set the holder
        time( &currentTime );
        //Add it to the string stream
        stream << currentTime;
        
        //Create the unique ID and set it to the string
        string uniqueID = stream.str();
        //Add a colon which preceeds the random number
        uniqueID += ":";
        
        //Flush the stream to clear the contents before we use it again
        stream.flush();
        
        //Set the seed for the random generator
        srand( int(time( NULL )) );
        //Add a random number to the stream
        stream << rand() % RAND_MAX;
        
        //Add that random number to the unique identifier to compelte it
        uniqueID += stream.str();
        
        //Set the member variable to our newly generated ID
        m_uniqueIdentifier = uniqueID;
    }
    
    GUIObject::~GUIObject()
    {
        //No pointers = no dealloc necesary from our view
    }
    
#pragma mark Getters & Setters
    
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
    
    std::string GUIObject::getUID()
    {
        return m_uniqueIdentifier;
    }
    
#pragma mark movement methods

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
    
#pragma mark render methods
    
    void GUIObject::renderObject()
    {
        //Do nothing, nothing to do
    }
    
    void GUIObject::renderAt(Zeni::Point2f coord)
    {
        //Do nothing, nothing to do
    }
}
