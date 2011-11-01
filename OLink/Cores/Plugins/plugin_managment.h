#ifndef _Plugin_Manager_
#define _Plugin_Manager_
#include <zenilib.h>
#include <string>
#include <vector>
#include <cstdarg>
/*
	1) Modify enum TYPES with the specific types of Plugins you want. For example: enum TYPES {NETWORK, GUI, LOGIC }
	2) Use addPlugintype(....) to regist the Plugintypes of step 1.
	3) Use addAllowedFunctions(....) to regist which functions can be called by a Plugin with a specific type
	
	=> Now you can use obj_send(....) to call a specific function from a Plugin.

	See "class PluginManager" for more informations about the parameters of the functions

*/



//What types of plugins are available
enum TYPES {Basic, Advance}; 

// This struct manage "global" functions which can get called through a specific plugin type.
// When we decide us for that solution we could make it faster through implement that as a binary tree 
struct AllowedFunctions {
		std::string name; // name of the function
		void (*function) (void*); // pointer to the function
		AllowedFunctions* next; // next "global" function in a list
};


// Handle the different types of plugins which are defined in enum TYPES
struct PluginTypes {	
	TYPES type;
	AllowedFunctions* allowedfunctions;
	std::string name;
};



class PluginManager {

		public: void addPlugintype(TYPES type, std::string name);
				PluginManager() { plugins.reserve(200);	}
				void addAllowedFunctions(TYPES type, std::string name,  void (*func)(void*));
				void addAllowedFunctions(TYPES type, std::string name,  void (*func[])(void*));
				static PluginManager* getInstance() { static PluginManager manager;  return &manager;	}
				void obj_send(TYPES type, std::string name, void* data);
				~PluginManager();

		private:  std::vector<PluginTypes*> plugins;
				  std::vector<PluginTypes*>::iterator it;

};

#endif