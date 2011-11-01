 

//#include "stdafx.h"
#include "message_loop.h"
#include <iostream>


#if defined _WIN32 || defined _WIN64
	#include <Windows.h>	
#else
	#include <pthread.h>
#endif

int id;
HANDLE thread;
#if defined _WIN32 || defined _WIN64
DWORD WINAPI messageloop(LPVOID lpParam ) {

	MessageDeque* m = static_cast<MessageDeque*>(lpParam);
	std::map<std::string, GlobalFunction> flookup;

	while(true) {
		if(m->getsize() != 0) {
			m->getMap(flookup);
			Message temp = m->pop();
			if(flookup.find(temp.message) != flookup.end())
				flookup[temp.message](temp.data);			
		}
	}
}
#else
void messageloop(void* lpParam ) {
	MessageDeque* m = static_cast<MessageDeque*>(lpParam);
	std::map<std::string, GlobalFunction> flookup;
	while(true) {
		if(m->getsize() != 0) {
			m->getMap(flookup);
			Message temp = m->pop();
			if(flookup.find(temp.message) != flookup.end())
				flookup[temp.message](temp.data);			
		}
	}
}
#endif

//This function starts the thread
bool initMessageThread() {
	DWORD temp;
	MessageDeque* messages = MessageDeque::getInstance();
	#if defined _WIN32 || defined _WIN64
		thread = CreateThread(NULL,0,messageloop,messages,0,&temp);
	#else
		pthread_t t1;
		if(pthread_create(&t1, NULL, (void *)&messageloop, (void *)messages) != 0)
			return false;		
	#endif
	id = temp;
	if(thread == NULL)
		return false;
	return true;
}

//Removes a Message from the MessageDeque
Message MessageDeque::pop() {
	Message temp;
	if(size > 0) {	
		size--;
		temp = first->data;
		//To clean up the Heap
		Node* tempNode = first;
		first = first->next;		
		delete tempNode;
		return temp;
	}
	return temp;
}


//This function adds a Message to the MessageDeque
// Message m => Message which should be added
void MessageDeque::push(Message m){
	Node *temp = new Node();
	size++;
	if(size == 1) {
		last = temp;
		first = temp;
		temp->data = m;
		return;
	}
	last->next = temp;
	temp->data = m;
	last = temp;
}

//Return the Size of the Deque
inline int MessageDeque::getsize() {
	return size;
}

//This function add a pointer to a function which can get called through a plugin to a map
// std::string message => The name of the function
// GlobalFunction func => Pointer to the function
void MessageDeque::regist_function(std::string message, GlobalFunction func) {
	if(function_lookup.find(message) == function_lookup.end())
		function_lookup[message] = func;
}

//Removes a function from the Map
//std::string message => Name of the function 
void MessageDeque::delete_function(std::string message) {
	if(function_lookup.find(message) != function_lookup.end())
		function_lookup.erase(message);

}

void global1(void *data) {
	std::cout <<"I ma here!";
}