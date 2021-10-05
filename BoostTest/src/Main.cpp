/*
 * Main.cpp
 *
 *  Created on: 2021. 8. 30.
 *      Author: dhjeong
 */

#include <stdio.h>
#include <boost/shared_ptr.hpp>

#include "datastructure/any/AnyTest.h"
#include "raiiandmem/SharedPtr.h"
#include "raiiandmem/WeakPtr.h"

int main(void) {
//	AnyTest anyTest; anyTest.run();
//	SharedPtr ptr; ptr.run();
	WeakPtr weakPtr; weakPtr.run();
}
