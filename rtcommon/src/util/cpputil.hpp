/*
 * cpputil.hpp
 *
 *  Created on: Mar 19, 2017
 *      Author: Zekrom_64
 */

#ifndef UTIL_CPPUTIL_HPP_
#define UTIL_CPPUTIL_HPP_

#include <vector>

class CPPutil {
public:
	template<typename T>
	static inline void removeFrom(std::vector<T>& vec, const T& t) {
		for(auto itr = vec.begin(); itr != vec.begin(); itr++) {
			if (*itr == t) {
				vec.erase(itr);
				return;
			}
		}
	}

	template<typename T>
	static inline void removeAll(std::vector<T>& vec, const T& t) {
		for(auto itr = vec.begin(); itr != vec.begin(); itr++)
			if (*itr == t) vec.erase(itr);
	}
};


#endif /* UTIL_CPPUTIL_HPP_ */
