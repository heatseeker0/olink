//#include "stdafx.h"
#include <zenilib.h>
#include "plugin_managment.h"

//This routine will add a new Plugintype 
//	TYPES type => the type of the plugin. TYPES is defined in plugin_managment.h
//	std::string name => the name of the plugin type
void PluginManager::addPlugintype(TYPES type, std::string name) {
	PluginTypes* temp = new PluginTypes;
	temp->type= type;
	temp->name = name;
	temp->allowedfunctions = NULL;
	for(it=plugins.begin(); it < plugins.end(); it++){
		if((*it)->type == type){
			temp->allowedfunctions =(*it)->allowedfunctions;
			break;	
		}
	}

	plugins.push_back(temp);
}

//This routine will add to a specific Plugintype a new "Gloablfunction"
//	TYPES type => the type of the plugin. TYPES is defined in plugin_managment.h
//	std::string name => is the name of the fuction
//  void (*func)(void*)) => points to the specific function
void PluginManager::addAllowedFunctions(TYPES type,std::string name, void (*func)(void*)) {
	AllowedFunctions* temp = NULL;
	for(it=plugins.begin(); it < plugins.end(); it++){
		if((*it)->type == type){
			temp = (*it)->allowedfunctions;
			break;
		}		
	}
	if(temp != NULL){
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = new AllowedFunctions;
		temp = temp->next;
		temp->name = name;
		temp->next= NULL;
	}
	else{
		temp = new AllowedFunctions;
		temp->next= NULL;
		temp->function= func;
		temp->name= name;
		for(it=plugins.begin(); it < plugins.end(); it++)
			if((*it)->type == type)
				(*it)->allowedfunctions = temp;							
	}

}

//This routine decide which "global" function should be called
//   TYPES type => type of the plugin, which want to call a registed method
//	 std::string name => name of the function to call
//   void* data => that pointer will get passed to the "global" function
void PluginManager::obj_send(TYPES type, std::string name, void* data){
	AllowedFunctions* temp = NULL;

	void (*tempfunction) ( void* ); 
	for(it=plugins.begin(); it < plugins.end(); it++){
		if((*it)->type==type){
			temp = (*it)->allowedfunctions;
			break;
		}
	}
	if(temp == NULL) return;

	while(temp->name != name) {
		if(temp->next == NULL) return;
			temp = temp->next;
	}

	tempfunction = temp->function;
	(*tempfunction)(data);
}



PluginManager::~PluginManager() {
	AllowedFunctions* temp = NULL;
	AllowedFunctions* temp2 = NULL;
	std::vector<TYPES> done;
	for(it=plugins.begin(); it < plugins.end(); it++){
		if((*it)->type) continue;
		temp = (*it)->allowedfunctions;
		while(temp != NULL) {
			temp2 = temp->next;
			delete temp;
			temp = temp2;
		}
		done.push_back((*it)->type);
	}	
}