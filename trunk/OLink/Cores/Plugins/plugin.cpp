//Plugin header
#include "plugin.h"

#if defined _WIN32 || defined _WIN64
	#include <Windows.h>
#else
	//dlopen header
	#include <dlfcn.h>
#endif
//cout
#include <iostream>

//Initiliaze a plugin
Plugin::Plugin(std::string pluginToLoad)
{
    //Use the standard namespace
    using namespace std;
    
    //Set our defaults
    defaultCommand = "";
    defaultParse = "";
    invalid = false;
    
    //Create the handle
	#if defined _WIN32 || defined _WIN64
		handle = LoadLibrary(pluginToLoad.c_str());
	#else	
		handle = dlopen(pluginToLoad.c_str(), RTLD_NOW);    
	#endif
    //Check if we have a handle
    if (!handle)
    {
        //We don't
        //Set invalid to true
        invalid = true;
        
        //Output this
		#if defined _WIN32
			cerr << "Unable to open plugin '" << pluginToLoad << "'.  The error was '" << GetLastError() << "'" << endl;
		#else
			cerr << "Unable to open plugin '" << pluginToLoad << "'.  The error was '" << dlerror() << "'" << endl;
		#endif
	}
    
    //Load our symbols
	#if defined _WIN32 || defined _WIN64
		void *voidCreator = GetProcAddress(handle, "createPlugin");
		DWORD dlsym_error = GetLastError();
	#else
		void *voidCreator = dlsym(handle, "createPlugin");
		const char* dlsym_error = dlerror();
    #endif
	if (dlsym_error)
    {
        cerr << "Unable to load the createPlugin symbol: '" << dlsym_error << "'" << endl;
        invalid = true;
    }
	
	union { CreatePlugin func; void* obj; } aliasCreator;
	aliasCreator.obj = voidCreator;
	creator = aliasCreator.func;
	#if defined _WIN32 || defined _WIN64
		void *voidDestroyer = GetProcAddress(handle, "destroyPlugin");
		dlsym_error = GetLastError();	
	#else
		void *voidDestroyer = dlsym(handle, "destroyPlugin");
		dlsym_error = dlerror();
	#endif
    
	if (dlsym_error)
    {
        cerr << "Unable to load the destroyPlugin symbol: '" << dlsym_error << "'" << endl;
        invalid = true;
    }
    
	union { DestroyPlugin func; void* obj; } aliasDestroyer;
	aliasDestroyer.obj = voidDestroyer;
	destroyer = aliasDestroyer.func;
	
    //Create an instance of our class
    plugin = creator();
	cout << "Plugin Command:" << plugin->getCommandName() << endl;
	plugin->setSender(PluginManager::getInstance());
	plugin->setType(Basic);

	plugin->setInterruptHandler(InterruptManager::getInstance());
	plugin->setMessageHandler(MessageDeque::getInstance() );

	vector<std::string> params;
	params.push_back("AUTH");
	
	cout << "Plugin parse of default parse:" << plugin->parseCommand("new.evilzone.org", "NOTICE", params, "*** Looking up your hostname...") << endl;

}

Plugin::~Plugin()
{
    destroyer(plugin);
	#if defined _WIN32 || defined _WIN64
		FreeLibrary(handle);
	#else
		dlclose(handle);
	#endif
}

std::string Plugin::getCommandName()
{
    return plugin->getCommandName();
}

std::string Plugin::parseCommand(std::string prefix, std::string command, std::vector<std::string> params, std::string trail)
{
    return plugin->parseCommand(prefix, command, params, trail);
}

std::vector<std::string> Plugin::getDisplayableCommands()
{
	return plugin->getDisplayableCommands();
}


