/**************************************************************************
 * exception.h                                                            * 
 * Copyright (C) 2014 Joshua <gnu.crazier@gmail.com>                      *
 **************************************************************************/

#pragma once

#include "zobject.h"
#include <setjmp.h>
#include <stdbool.h>

/**
 * \brief throw an exception.
 * \param instance exception instance.
 * \example throw(zNewInstance("base_exception", "some bad thing happen");
 */
#define throw(instance)	__throw(instance)

/** rethrow an exception. */
#define rethrow() 						\
do {								\
	__pop_jmp_point();					\
	__throw(__get_cur_error());				\
} while(0)

/**
 * \brief try block.
 * \example
 * 	try {
 * 		throw(zNewInstance("base_exception", "error happened"));
 * 	} catch(ins, "base_exception) {
 * 		do_something(ins);
 * 	} otherwise {
 * 		do_anotherthing();
 * 		rethrow();
 * 	} finally {
 * 		finnaly_thing();
 * 	}
 */
#define try if(!setjmp(__push_jmp_point()))

#define catch(instance, class_name)				\
    else if(zGetInstance(__get_cur_error(), class_name)) {	\
	struct ZObjInstance *instance = __get_cur_error();
	
#define otherwise } else {

#define finally } __pop_jmp_point();

/**
 * \note the fellow functions, include __push_jmp_point, __pop_jmp_point,
 * 	 __get_cur_error, __throw, are used by micro, and they should never 
 * 	 be used directly by user!!!
 */
void * __push_jmp_point(void);
void __pop_jmp_point(void);
struct ZObjInstance *__get_cur_error(void);
void __throw(struct ZObjInstance *);

/**
 * \brief Init exception system.
 * \param thread_identifer 
 *        The fuction given to exception system, so that 
 * 	  the system can identify diffrent thread. This if for thread safe, 
 * 	  if you use single thread, you can pass NULL.
 * \example exceptionInit(pthread_self);
 */ 
void exceptionInit(unsigned long (*thread_identifier)(void));
