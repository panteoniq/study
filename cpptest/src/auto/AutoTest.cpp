/*
 * AutoTest.cpp
 *
 *  Created on: 2021. 9. 28.
 *      Author: dhjeong
 */

#include <iostream>

#include "AutoTest.h"

AutoTest::AutoTest() {
}

AutoTest::~AutoTest() {
}


//구조체나 공용체, 클래스도 가능함
class Test {
public:
	int a;
} tt;

//함수포인터나, 함수 자체도 가능함 -> 이러한 함수를 람다 함수라고 함
//함수 포인터 -> 구조체나 클래스의 함수 포인터도 가능
int test2(int a) {
	return a;
}

void AutoTest::run() {
	//변수를 초기화 값으로 사용가능
	int a = 7;
	int b = a; // a의 자료형을 기준으로 설정됨


	//포인터와 참조자를 붙일 수 있음
	auto autoNormal = 1.2;
	auto &autoRef = autoNormal;
	auto *autoPtr = &autoNormal;

	auto autoClass = tt;

//	autoClass testAutoClass;

	autoClass.a = 3;

    auto autoFn = test2;
    std::cout << autoFn(7) << std::endl;

    auto autoFnLambda = []{std::cout << "hello wolrd" << std::endl;};
    autoFnLambda();

    auto autoFnLambda2 = [](int a){return a;};
    std::cout << autoFnLambda2(7) << std::endl;

    auto autoFnLambda3= [&](int a){int c = b+a;return c;};
    std::cout << autoFnLambda3(10) << std::endl;
}

