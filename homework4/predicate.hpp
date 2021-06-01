#pragma once
#include <iterator>
#include <vector>
using namespace std;
template <typename T, typename predicateFcn_>
bool allOf(T iterBegin, T iterEnd, predicateFcn_ predicateFcn) {
	for (; iterBegin != iterEnd; iterBegin++)
		if (!predicateFcn(*iterBegin))
			return 0;
	return 1;
}
template <typename T, typename predicateFcn_>
bool anyOf(T iterBegin, T iterEnd, predicateFcn_ predicateFcn) {
	for (; iterBegin != iterEnd; iterBegin++)
		if (predicateFcn(*iterBegin))
			return 1;

	return 0;
}
template <typename T, typename predicateFcn_>
bool noneOf(T iterBegin, T iterEnd, predicateFcn_ predicateFcn) {
	for (; iterBegin != iterEnd; iterBegin++)
		if (predicateFcn(*iterBegin))
			return 0;

	return 1;
}
template <typename T, typename predicateFcn_>
bool oneOf(T iterBegin, T iterEnd, predicateFcn_ predicateFcn) {
	int counter = 0;
	for (; iterBegin != iterEnd; iterBegin++)
		if (predicateFcn(*iterBegin))
			counter++;

	if (counter == 1)
		return 1;
	else
		return 0;
}
template <typename T, typename comprasionFcn_ = less<> >
bool isSorted(T iterBegin, T iterEnd, const comprasionFcn_& comprasionFcn = less<>()) {
	for (; iterBegin != iterEnd - 1; iterBegin++)
		if (!comprasionFcn(*iterBegin, *(iterBegin + 1)))
			return 0;

	return 1;
}
template <typename T, typename predicateFcn_>
bool isPartitioned(T iterBegin, T iterEnd, predicateFcn_ predicateFcn) {
	bool foundFirst = 0;
	for (; iterBegin != iterEnd; iterBegin++) {
		if (foundFirst) {
			if (predicateFcn(*iterBegin))
				return 0;
		}
		else {
			if (!predicateFcn(*iterBegin))
				foundFirst = 1;
		}
	}
	return 1;
}
template<typename T>
T findNot(T iterBegin, T iterEnd, int adjusted) {
	for (; iterBegin != iterEnd; iterBegin++)
		if (*iterBegin != adjusted)
			return iterBegin;

	return iterEnd;
}
template <typename T>
T findBackward(T iterBegin, T iterEnd, int adjusted) {
	T returnIter = iterEnd;
	for (; iterBegin != iterEnd; iterBegin++)
		if (*iterBegin == adjusted)
			returnIter = iterBegin;

	return returnIter;
}
template<typename T, typename predicateFcn_>
bool isPalindrome(T iterBegin, T iterEnd, predicateFcn_ predicateFcn) {
	T leftIter = iterBegin;
	T rightIter = --iterEnd;
	while (leftIter != rightIter && rightIter != iterBegin) {
		if (!predicateFcn(*leftIter, *rightIter))
			return 0;
		leftIter++;
		rightIter--;
	}
	return 1;
}