/*
 * ExplicitTest.h
 *
 *  Created on: 2021. 9. 17.
 *      Author: dhjeong
 */

#ifndef EXPLICIT_EXPLICITTEST_H_
#define EXPLICIT_EXPLICITTEST_H_

#include <iostream>

class Tmp {
public:
	explicit Tmp(int num) :
			m_num(num) {
		std::cout << "Tmp 생성자 : " << m_num << std::endl;
	}

	void print() {
		std::cout << "Tmp 내부 값 : " << m_num << std::endl;
	}

private:
	int m_num;
};

class ExplicitTest {
public:
	ExplicitTest();
	virtual ~ExplicitTest();

	void test(Tmp tmp) {
		tmp.print();
	}

	void run();
};

#endif /* EXPLICIT_EXPLICITTEST_H_ */
