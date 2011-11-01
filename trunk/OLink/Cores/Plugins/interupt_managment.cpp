//#include "stdafx.h"
#include <zenilib.h>
#include "interrupt_managment.h"

void InterruptManager::isr_regist(int int_num, isr func) {
	is_routines[int_num] = func;
}


void InterruptManager::interrupt(int num, void* data){
		isr func = is_routines[num];
		if(is_routines.find(num)==is_routines.end()) {
			std::cerr <<"Error: Interrupt " << num << " was not found"<<std::endl;
			return;
		}
		func(data);
}




