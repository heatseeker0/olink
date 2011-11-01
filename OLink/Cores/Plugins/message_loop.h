#ifndef _Message_Loop_
#define _Message_Loop_
#include <string>
#include <map>
#include <Windows.h>

/*
	1) Call initMessageThread() to start the Thread, who checks if a new Message was send
	2) Use the method void MessageDeque::regist_function(std::string message, GlobalFunction func) to regist a new function and to give it a name as a key. 
	   E.g: regist_function("Send_String",&Send_String);
	
	=> Now a plugin can push a new Message ( void MessageDeque::push(Message m)). The Message is a struct, which contains the function name and some additional informations

*/

enum PLUGINTYPES {Basic1, Advance1}; 

typedef void (*GlobalFunction) (void*);

struct Message {
	std::string message; //Function name
	PLUGINTYPES type; // The type of the plugin
	void* data; //Datas which should be passed to the function
};

class Node {
private: Node* next;
		 Message data;
		 friend class MessageDeque;
};

//Handles the messages which were pushed and did not get executed yet. It also holds a map which stores functions which can be called through a plugin and it's name
class MessageDeque {
	public: void push(Message m);
			inline int getsize(); 
			Message pop(); 
			MessageDeque() { size =0; };
			static MessageDeque* getInstance() { static MessageDeque m; return &m; } 
			void regist_function(std::string message, GlobalFunction func);
			void delete_function(std::string message);
			void getMap(std::map<std::string, GlobalFunction>& a) { a=function_lookup; };

	private: int size;
			 Node* last;
			 Node* first;
			 std::map<std::string, GlobalFunction> function_lookup;
			 

};

extern int id;
extern bool initMessageThread();
extern void global1(void* data);



#endif