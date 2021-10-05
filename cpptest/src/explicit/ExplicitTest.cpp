/*
 * ExplicitTest.cpp
 *
 *  Created on: 2021. 9. 17.
 *      Author: dhjeong
 */

#include "ExplicitTest.h"
#include <iostream>

ExplicitTest::ExplicitTest() {
	// TODO Auto-generated constructor stub

}

ExplicitTest::~ExplicitTest() {
	// TODO Auto-generated destructor stub
}


void ExplicitTest::run() {
	int intVal;

//	float floatVal = (float) intVal;
//	float floatVal = float(intVal);

	int first = 5;
	int second = 2;
	float first2 = 5.0;

	float floatVal = first / second;
	float floatVal2 = (float) first / second;
	float floatVal3 = (float) first2 / second;

	std::cout << floatVal << std::endl;
	std::cout << floatVal2 << std::endl;
	std::cout << floatVal3 << std::endl;

//	Tmp tmp1 = Tmp(1);
//	Tmp tmp2 = 10;

	Tmp tmp(10);
	test(tmp);
}
