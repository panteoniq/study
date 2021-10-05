/*
 * WeakPtr.cpp
 *
 *  Created on: 2021. 9. 25.
 *      Author: dhjeong
 */

#include <iostream>
#include <boost/make_shared.hpp>
#include "WeakPtr.h"

WeakPtr::WeakPtr() {
}

WeakPtr::~WeakPtr() {
}

void WeakPtr::run() {
	boost::weak_ptr<DataInfo> weakPtr1;
	boost::weak_ptr<DataInfo> weakPtr2;
	{
		boost::shared_ptr<DataInfo> sPtr = boost::make_shared<DataInfo>("Struct", 1, 2);
		weakPtr1 = sPtr;
		weakPtr2 = sPtr;
	}
	std::cout << "weakPtr1 lock after block" << std::endl;
	boost::shared_ptr<DataInfo> sPtr2 = weakPtr1.lock();

	if (sPtr2) {
		std::cout << sPtr2->name << std::endl;
	} else {
		std::cout << "sPtr2 NULL" << std::endl;
	}

//	boost::shared_ptr<DataInfo> sPtr = boost::make_shared<DataInfo>("Struct", 1, 2);
//	std::cout << sPtr->name << std::endl;
//	boost::weak_ptr<DataInfo> weakPtr1 = sPtr;
//	boost::shared_ptr<DataInfo> sPtr2 = weakPtr1.lock();
//	std::cout << sPtr2->name << std::endl;
}

void WeakPtr::inside(boost::shared_ptr<DataInfo> &sharedPtr,
		boost::weak_ptr<DataInfo> weakPtr) {

}
