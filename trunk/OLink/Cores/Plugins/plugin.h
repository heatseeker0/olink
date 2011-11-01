#ifndef PLUGIN_H
#define PLUGIN_H


/* Plugin must include:
 VirtualPlugin *createPlugin();
 void destroyPlugin(VirtualPlugin *);
 
 and then the class they return must be a valid VirtualPlugin
 */

#if defined _WIN32 || defined _WIN64
	#include <Windows.h>
#endif
//Include string for std::string
#include <string>
//Include vector for st::vector
#include <vector>

#include "C:\Users\USER\documents\visual studio 2010\Projects\ircBase\ircBase\plugin_managment.h"
#include "C:\Users\USER\documents\visual studio 2010\Projects\ircBase\ircBase\interrupt_managment.h"
#include "C:\Users\USER\documents\visual studio 2010\Projects\ircBase\ircBase\message_loop.h"

//Class used for the plugin
class VirtualPlugin
{
		
public: PluginManager* GlobalFunctions; //We need a object of the type PluginManager to call obj_send
		TYPES type; // That var hold what type that plugin is
		
		InterruptManager* InteruptHandler;
		MessageDeque* messages;

public:
    virtual std::string parseCommand(std::string prefix, std::string command, std::vector<std::string> params, std::string trail) { return ""; }
    virtual std::string getCommandName() { return ""; }
	virtual std::vector<std::string> getDisplayableCommands() { std::vector<std::string> vec; return vec; }
	void setSender(PluginManager* GlobalFunctions) { this->GlobalFunctions = GlobalFunctions;}
	void setType(TYPES type){ this->type = type;}
	void setInterruptHandler(InterruptManager* temp) { InteruptHandler = temp; }
	void setMessageHandler(MessageDeque* temp) { messages = temp; }
};

//Plugin type defs
typedef VirtualPlugin* (*CreatePlugin)();
typedef void (*DestroyPlugin)(VirtualPlugin *);

//Plugin class
class Plugin
{
public:
    //Initialize a plugin with the path (relativeo or absolute) of the plugin to load
    Plugin(std::string pluginToLoad);
    //Dealloc method
    ~Plugin();
    
    //Get the command name the plugin supports
    //Returns "-1" if you must call it each time a command is called (multiple commands for example)
    std::string getCommandName();
    //Parse a command (returns "" if it doesn't handle the command)
    std::string parseCommand(std::string prefix, std::string command, std::vector<std::string> params, std::string trail);
    
	std::vector<std::string> getDisplayableCommands();
	
	
    bool invalid;
    
private:
    //Used if this is an invalid plugin
    std::string defaultCommand;
    std::string defaultParse;
    
    //Handle for the plugin


	#if defined _WIN32
		HINSTANCE handle;
	#else 
		void *handle;
	#endif
	
    //Plugin class
    VirtualPlugin *plugin;
    
    CreatePlugin creator;
    DestroyPlugin destroyer;
};

#endif
