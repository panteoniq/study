/*
 * Twosum.cpp
 *
 *  Created on: 2021. 9. 7.
 *      Author: dhjeong
 */

#include "Twosum.h"
#include <stdio.h>
#include <vector>
#include <map>
#include <utility>

Twosum::Twosum() {
	// TODO Auto-generated constructor stub

}

Twosum::~Twosum() {
	// TODO Auto-generated destructor stub
}

void Twosum::run() {
	std::vector<int> inputList;
	int target = 0;

	inputList.push_back(11);
	inputList.push_back(13);
	inputList.push_back(2);
	inputList.push_back(7);
	target = 9;
	doTest(inputList, target);
}

void Twosum::doTest(std::vector<int> &inputList, int target) {
	std::map<int, int> inputMap;
	for (unsigned int i = 0; i < inputList.size(); i++) {
		int remain = target - inputList[i];
		if (inputMap.find(remain) != inputMap.end()) {
			printf("[%d %d]\n", inputMap.at(remain), i);
			break;
		}
		inputMap.insert(std::make_pair(inputList[i], i));
	}
}
