#include "tritset.h"

TritSet operator &(TritSet& set1, TritSet& set2) {
	TritSet set3(set1.uint_.size() > set2.uint_.size() ? set1.uint_.size() : set2.uint_.size()); //Create Tritset for result with set1's size or set2's size, which bigger

	for (size_t i = 0; i < set3.uint_.size(); i++) {
		if (set1.uint_.size() - 1 < i)
			set3.uint_.at(i) = set2.uint_.at(i);
		else if (set2.uint_.size() - 1 < i)
			set3.uint_.at(i) = set1.uint_.at(i);
		else if (set1.uint_.at(i) == False || set2.uint_.at(i) == False)
			set3.uint_.at(i) = False;
		else if (set1.uint_.at(i) == True && set2.uint_.at(i) == True)
			set3.uint_.at(i) = True;
		else
			set3.uint_.at(i) = Unknown;
	}

	return set3;
}

TritSet operator |(TritSet& set1, TritSet& set2) {
	TritSet set3(set1.uint_.size() > set2.uint_.size() ? set1.uint_.size() : set2.uint_.size()); //Create Tritset for result with set1's size or set2's size, which bigger

	for (size_t i = 0; i < set3.uint_.size(); i++) {
		if (set1.uint_.size() - 1 < i)
			set3.uint_.at(i) = set2.uint_.at(i);
		else if (set2.uint_.size() - 1 < i)
			set3.uint_.at(i) = set1.uint_.at(i);
		else if (set1.uint_.at(i) == False && set2.uint_.at(i) == False)
			set3.uint_.at(i) = False;
		else if (set1.uint_.at(i) == True || set2.uint_.at(i) == True)
			set3.uint_.at(i) = True;
		else
			set3.uint_.at(i) = Unknown;
	}

	return set3;
}

TritSet& operator !(TritSet& set1) {
	for (size_t i = 0; i < set1.uint_.size(); i++) {
		if (set1.uint_.at(i) == False)
			set1.uint_.at(i) = True;
		else if (set1.uint_.at(i) == True)
			set1.uint_.at(i) = False;
	}

	return set1;
}

std::ostream& operator <<(std::ostream& out, const TritSet& tritSet) {
	out << tritSet.uint_.at(tritSet.lastIndex_);

	return out;
}