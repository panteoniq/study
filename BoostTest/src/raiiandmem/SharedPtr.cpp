/*
 * SharedPtr.cpp
 *
 *  Created on: 2021. 9. 14.
 *      Author: dhjeong
 */

#include "SharedPtr.h"
#include <iostream>
#include <boost/make_shared.hpp>
#include <string>

SharedPtr::SharedPtr() {
}

SharedPtr::~SharedPtr() {
}

void SharedPtr::run() {
	DataInfo *info = new DataInfo("test", 1234, 644);
//	DataInfo info("test", 1234, 644);
	// no matching function for call to ‘make_shared(DataInfo*&)’
//	boost::shared_ptr<DataInfo> infoPtr = boost::make_shared(info); // -> 이거나 생성자에서 new를 하는 거나... 뭐가 다르지?
	// no matching function for call to ‘make_shared(DataInfo&)’
//	boost::shared_ptr<DataInfo> infoPtr2 = boost::make_shared(*info);
	// conversion from ‘DataInfo*’ to non-scalar type ‘boost::shared_ptr<DataInfo>’ requested
//	boost::shared_ptr<DataInfo> infoPtr3 = info;
//	boost::shared_ptr<DataInfo> infoPtr4(info);
//	std::cout << infoPtr4->name << std::endl;
//	std::cout << infoPtr4->size << std::endl;
//	std::cout << infoPtr4->permission << std::endl << std::endl;

//	boost::shared_ptr<DataInfo> infoPtr5(&info);
//	std::cout << infoPtr5->name << std::endl;
//	std::cout << infoPtr5->size << std::endl;
//	std::cout << infoPtr5->permission << std::endl << std::endl;

//	std::cout << "end" << std::endl;
//
//	boost::shared_ptr<DataInfo> infoPtr2;
//	boost::shared_ptr<DataInfo> infoPtr3;
////
//	{
//		DataInfo info;
//		info.name = "testName2";
//		info.size = 1203;
//		info.permission = 644;
//
//		boost::shared_ptr<DataInfo> infoPtr(new DataInfo());
//		infoPtr2 = boost::make_shared<DataInfo>(info);
//		infoPtr3 = boost::make_shared<DataInfo>("testName3", 1234, 655);
//
//		infoPtr->name = "testName";
//		infoPtr->size = 0;
//		infoPtr->permission = 755;
//
//		info.name = "changed";
//
//		std::cout << infoPtr->name << std::endl;
//		std::cout << infoPtr->size << std::endl;
//		std::cout << infoPtr->permission << std::endl << std::endl;
//
//		std::cout << infoPtr2->name << std::endl;
//		std::cout << infoPtr2->size << std::endl;
//		std::cout << infoPtr2->permission << std::endl << std::endl;
//
//		std::cout << infoPtr3->name << std::endl;
//		std::cout << infoPtr3->size << std::endl;
//		std::cout << infoPtr3->permission << std::endl << std::endl;
//	}
//
//	std::cout << infoPtr2->name << std::endl;
//	std::cout << infoPtr2->size << std::endl;
//	std::cout << infoPtr2->permission << std::endl << std::endl;
//
//	std::cout << infoPtr3->name << std::endl;
//	std::cout << infoPtr3->size << std::endl;
//	std::cout << infoPtr3->permission << std::endl << std::endl;
//
//	boost::shared_ptr<DataInfo> ptr;
//	inside(ptr);
//	std::cout << ptr->name << std::endl;
//	std::cout << "Outside count ---" << std::endl;
//	std::cout << ptr.use_count() << std::endl;
//	boost::shared_ptr<DataInfo> ptr = boost::make_shared<DataInfo>("Struct", 1, 2);
//	std::cout << "ptr ref count(1) : " << ptr.use_count() << std::endl;
//	{
//		// 참조 카운터 1 증가
//		boost::shared_ptr<DataInfo> ptr2 = ptr;
//		std::cout << "ptr ref count(2) : " << ptr.use_count() << std::endl;
//		std::cout << "ptr2 ref count(2) : " << ptr2.use_count() << std::endl;
//	}
//	// 블럭을 빠져나왔으므로 ptr2는 소멸됨
//	std::cout << "ptr ref count(3) : " << ptr.use_count() << std::endl;

	std::shared_ptr<A> pa = std::make_shared<A>();
	std::cout << "pa inside count(1) : " << pa->getCount() << std::endl;
	std::cout << "pa itself count(1) : " << pa.use_count() << std::endl;
	std::shared_ptr<A> pb = std::make_shared<A>();
	std::cout << "pb inside count(1) : " << pb->getCount() << std::endl;
	std::cout << "pb itself count(1) : " << pb.use_count() << std::endl;

	pa->set_other(pb);
	std::cout << "pa count(2) : " << pa->getCount() << std::endl;
	pb->set_other(pa);
	std::cout << "pb count(2) : " << pb->getCount() << std::endl;

//	boost::shared_ptr<DataInfo> ptr = boost::make_shared<DataInfo>("Struct", 1, 2);
//	boost::shared_ptr<DataInfo> ptr2 = ptr;
//	ptr = ptr2;

}

void SharedPtr::inside(boost::shared_ptr<DataInfo> &ptr) {
	DataInfo info("inside", 123456, 123);
//	ptr = boost::make_shared<DataInfo>(info);
//	ptr->name = "outside";

	ptr = boost::make_shared<DataInfo>("Struct", 1, 2);
	ptr->name = "outside";

	boost::shared_ptr<DataInfo> ptr2 = ptr;
	std::cout << ptr2->size << std::endl;
	std::cout << "Inside use count ---" << std::endl;
	std::cout << ptr.use_count() << std::endl;
	std::cout << ptr2.use_count() << std::endl;
	boost::shared_ptr<DataInfo> ptr3;
	std::cout << ptr3.use_count() << std::endl;

	std::cout << "Inside weak count ---" << std::endl;
	boost::shared_ptr<DataInfo> sharedPtr = boost::make_shared<DataInfo>(
			"Struct", 1, 2);
	std::cout << "end" << std::endl;

}
