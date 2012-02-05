//
//  NetworkCore.h
//  Application
//
//  Created by Alex Turner on 2/4/12.
//  Copyright (c) 2012 OLink. All rights reserved.
//

#ifndef NetworkCore_H
#define NetworkCore_H

#include <string>

//Used for sending entire classes and objects.  A class must inherit from this and implement these methods
class NetworkObject
{
public:
	NetworkObject();
	~NetworkObject();
	
	//Convert the class into something.  XML might be cleanest.  Zenilib has built in XML support
	virtual std::string convertToString();
	//Convert a string into the class.  Return the class as a void*
	virtual void* convertFromString(std::string);
	
	/*
	 Example NetworkObject string:
	 
	 <?xml version="1.0" encoding="UTF-8" ?>
	 <NetworkObject>
		<OriginalType>Example</OriginalType>
	 </NetworkObject>
	 <OLink>
		<Version>1.0.0</Version>
		<BuildNumber>14SBJ</BuildNumber>
		<CompatibleVersionMinimum>14SBJ</CompatibleVersionMinimum> //Only Compatible with this build
	 </Olink>
	 <Example>
		<ExampleFieldInClass>ExampleString</ExampleFieldInClass>
	 </Example>
	 
	 Example Message string (To Compare to NetworkObject above):
	 
	 <?xml version="1.0" encoding="UTF-8" ?>
	 <OLink>
	 <Version>1.0.0</Version>
	 <BuildNumber>14SBJ</BuildNumber>
	 <CompatibleVersionMinimum>14SBJ</CompatibleVersionMinimum> //Only Compatible with this build
	 </Olink>
	 <Message>
		<MessageContents>Blah</MessageContents>
	 </Message>
	 
	 These are very similar but different as you can tell.
	 */
}

//Server Class
class NetworkServer
{
	typedef void (*clientAcceptCallback)(long sessionIdent);
	typedef void (*clientLogoffCallback)(long sessionIdent);
	
	typedef void (*clientMessageCallback)(long sessionIdent, std::string message);
	typedef void (*clientNetworkObjectCallback)(long sessionIdent, std::string networkObjectAsString);
	
	typedef void (*serverErrorCallback)(int errno, std::string humanReadable);
	
	clientAcceptCallback acceptCallback;
	clientLogoffCallback logoffCallback;
	clientMessageCallback messageCallback;
	clientNetworkObjectCallback networkObjectCallback;
	serverErrorCallback errorCallback;
	
	int socket;
	
public:
	//Initialize a Server
	//If master is false, it will wait for a request for linking
	NetworkServer(short port = 25432, int maxConnections = -1, bool master = true);
	~NetworkServer();
	
	//Function Callbacks
	void setClientAcceptFunction(clientAcceptCallback callback);
	void setClientLogoffFunction(clientLogoffCallback callback);
	
	void setClientDidSendMessageFunction(clientMessageCallback callback);
	void setClientNetworkObjectFunction(clientNetworkObjectCallback callback);
	
	void setServerErrorFunction(serverErrorCallback callback);
	
	//Utilities
	//Send a message to a client
	void sendToClient(long sessionIdent, std::string message);
	void sendNetworkObjectToClient(long sessionIdent, NetworkObject objectToSend);
	//Disconnect a client
	void disconnectClient(long sessionIdent);
	//Split resources over multiple servers
	//By default will prefer to be the master server.  Returns true if it is still the master server
	bool linkServer(std::string IPAddress, short port);
}

//Network Class
class NetworkClient
{
	typedef void (*serverConnectedCallback)(void);
	typedef void (*serverShutdownCallback)(void);
	
	typedef void (*serverMessageCallback)(std::string message);
	typedef void (*serverNetworkObjectCallback)(std::string networkObjectAsString);
	
	typedef void (*clientErrorCallback)(int errno, std::string humanReadable);
	
	serverConnectedCallback connectedCallback;
	serverShutdownCallback shutdownCallback;
	
	serverMessageCallback messageCallback;
	serverNetworkObjectCallback networkObjectCallback;
	
	clientErrorCallback errorCallback;
	
	int socket;
	
public:
	//Initialize the client
	NetworkClient(std::string IPAddress, short port);
	~NetworkClient();
	
	//Connect to the server
	bool connectToServer();
	
	//Function callbacks
	void setServerConnectedFunction(serverConnectedCallback callback);
	void setServerShutdownFunction(serverShutdownCallback callback);
	
	void setServerMessageFunction(serverMessageCallback callback);
	void setServerNetworkObjectFunction(serverNetworkObjectCallback callback);
	
	void setClientErrorFunction(clientErrorCallback callback);
	
	//Utilities
	//Send a message to the server
	void sendToServer(std::string message);
	void sendNetworkObjectToServer(NetworkObject objectToSend);
	//Disconnect from the server
	void disconnect();
} 

#endif
