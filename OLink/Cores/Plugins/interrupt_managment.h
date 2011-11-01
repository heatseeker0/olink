#ifndef _InteruptManagement_
#define _InteruptManagement_
#include <map>
#include <iostream>

/*
	1) Modify enum IRQS to give a specific function name a specific IRQ number. E.g  enum IRQS {  Close = 0x0, DRAW = 0x1};
	2) Use sr_regist(int int_num, isr func) to assign an IRQ number a specific functions
	
	=> Now a Plugin can use void interrupt(int num, void* data) to call a global function
*/
//Stores the specific functions and there IRQ number.
enum IRQS { TEST = 0x0, DRAW = 0x1};

typedef void (*isr)(void*);

class InterruptManager {
	public: void isr_regist(int int_num, isr func);
			void interrupt(int num, void* data);

			static InterruptManager* getInstance() { static InterruptManager iteruptmanager; return &iteruptmanager; } 
	
	private: std::map<int,isr> is_routines; 

};

#endif