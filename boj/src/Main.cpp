/*
 * Main.cpp
 *
 *  Created on: 2021. 6. 9.
 *      Author: dhjeong
 */

#include "test/source.cpp"
#include <vector>
#include <string>

int main(void) {
	test test;
	test.run();

	std::vector<std::string> strList;
	strList.push_back("test");
	for (int i=0; i<strList.size(); i++) {

	}
}
