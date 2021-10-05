/*
 * Twosum.h
 *
 *  Created on: 2021. 9. 7.
 *      Author: dhjeong
 */

#ifndef TWOSUM_TWOSUM_H_
#define TWOSUM_TWOSUM_H_

#include <vector>

class Twosum {
public:
	Twosum();
	virtual ~Twosum();

	void run();

private:
	void doTest(std::vector<int>& inputList, int target);
};

#endif /* TWOSUM_TWOSUM_H_ */
