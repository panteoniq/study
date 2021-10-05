/*
 * Level2.h
 *
 *  Created on: 2021. 9. 9.
 *      Author: dhjeong
 */

#ifndef PROGRAMMERS_HASH_LEVEL2_H_
#define PROGRAMMERS_HASH_LEVEL2_H_

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Level2 {
public:
	Level2();
	virtual ~Level2();

	void run();


	bool solution(vector<string> phone_book) {
		bool answer = true;

		set<string> tmp;

		for (int i = 0; i < phone_book.size(); i++) {
			tmp.insert(phone_book[i]);
		}

		for (int i = 0; i < phone_book.size(); i++) {
					if (tmp.phone_book[i])
		}
//
//		for (int j = i + 1; j < phone_book.size(); j++) {
//						if (phone_book[j].find(phone_book[i]) != string::npos) {
//							answer = false;
//							break;
//						}
//					}
//					if (answer == false) {
//						break;
//					}

		return answer;
	}

};

#endif /* PROGRAMMERS_HASH_LEVEL2_H_ */
