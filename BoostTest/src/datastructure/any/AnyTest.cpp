/*
 * AnyTest.cpp
 *
 *  Created on: 2021. 8. 30.
 *      Author: dhjeong
 */

#include "AnyTest.h"
#include <boost/any.hpp>
#include <iostream>
#include <vector>

AnyTest::AnyTest() {
	// TODO Auto-generated constructor stub

}

AnyTest::~AnyTest() {
	// TODO Auto-generated destructor stub
}

void AnyTest::run() {
//	std::vector<boost::any> some_values;
//	some_values.push_back(10);
//	const char *c_str = "hello there!";
//	some_values.push_back(c_str);
//	some_values.push_back(std::string("Wow!"));
//
//	std::string &s = boost::any_cast<std::string&>(some_values.back());
//	s += " That is great!\n";
//
//	std::cout << "type name = " << some_values.front().type().name()
//			<< std::endl;
//
//	std::cout << s;

	try {
		int intVal = 333;
		std::string stringVal = "Hello World!";

		boost::any anyString(stringVal);
		boost::any anyInt(intVal);

		std::string strConv1 = boost::any_cast<std::string>(anyString);
		std::string *strConv2 = boost::any_cast<std::string>(&anyString);
		std::string *unsafeStrConv = boost::unsafe_any_cast<std::string>(&anyString);

		// unsafe_any_case의 매개변수는 무조건 포인터 변수여야 한다
//		short shortConv1 = boost::unsafe_any_cast<short>(anyInt);
		short *shortConv2 = boost::unsafe_any_cast<short>(&anyInt);
		short *shortConv3 = boost::unsafe_any_cast<short>(&anyInt);
		std::string *strConv3 = boost::unsafe_any_cast<std::string>(&anyInt);
		std::cout << "strConv4" << strConv3->c_str() << std::endl;
		// cannot convert ‘int*’ to ‘short int*’ in initialization
//		short *errShortConv = boost::any_cast<int>(&anyInt);
		// 본래 자료형과 변환할 자료형이 다른 경우 NULL을 반환한다
		short *errShortConv = boost::any_cast<short>(&anyInt);
		int intConv1 = boost::any_cast<int>(anyInt);
		int *intConv2 = boost::any_cast<int>(&anyInt);

//		std::cout << "type name = " << variable.type().name() << std::endl;
		std::cout << "strConv1 : " << strConv1.c_str() << std::endl;
		std::cout << "strConv2 : " << strConv2->c_str() << std::endl;
		std::cout << "intConv1 : " << intConv1 << std::endl;
		std::cout << "intConv2 : " << intConv2 << std::endl;

//		std::cout << "shortConv1 : " << shortConv1 << std::endl;
		std::cout << "shortConv2 : " << *shortConv2 << std::endl;
		std::cout << "shortConv3 : " << *shortConv3 << std::endl;
		if (errShortConv == NULL) {
			std::cout << "errShortConv IS NULL" << std::endl;
		} else {
			std::cout << "errShortConv : " << *errShortConv << std::endl;
		}

	} catch (boost::bad_any_cast &t) {
		std::cout << "error : " <<  t.what() << std::endl;
	}

}
