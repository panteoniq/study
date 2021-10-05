/*
 * SharedPtr.h
 *
 *  Created on: 2021. 9. 14.
 *      Author: dhjeong
 */

#ifndef RAIIANDMEM_SHAREDPTR_H_
#define RAIIANDMEM_SHAREDPTR_H_

#include <iostream>
#include <boost/shared_ptr.hpp>
#include "struct.h"

class SharedPtr {
public:
	SharedPtr();
	virtual ~SharedPtr();

	void run();
	void inside(boost::shared_ptr<DataInfo> &ptr);
};

#endif /* RAIIANDMEM_SHAREDPTR_H_ */
