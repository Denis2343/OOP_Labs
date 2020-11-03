#ifndef tritset_H
#define tritset_H

#include <iostream>
#include <vector>
#include <unordered_map>

enum Trit { False, Unknown, True };

class TritSet {
private:
	std::vector<int> uint_;
	size_t lastIndex_;
public:
	TritSet(size_t size) {
		uint_ = std::vector<int>(size, Unknown);
	}

	TritSet(const TritSet& other) {
		this->lastIndex_ = other.lastIndex_;
		this->uint_.assign(other.uint_.begin(), other.uint_.end());
	}

	TritSet& operator [](const size_t index) {
		lastIndex_ = index;
		return *this;
	}

	TritSet& operator =(int value) {
		if (lastIndex_ >= uint_.size() && (value == True || value == False)) {
			int i = uint_.size() - 1;
			while (i != lastIndex_ - 1) {
				uint_.push_back(Unknown);
				i++;
			}
			uint_.push_back(value);
		}
		else if (lastIndex_ <= uint_.size())
			uint_.at(lastIndex_) = value;
		return *this;
	}

	bool operator ==(int value) {
		if (lastIndex_ >= uint_.size() && value == Unknown)
			return true;
		else if (lastIndex_ >= uint_.size() && value != Unknown)
			return false;
		else if (uint_.at(lastIndex_) == value)
			return true;
		else
			return false;

	}

	void shrink() {
		int i = 0;
		for (int it = uint_.size() - 1; uint_.at(it) == Unknown; it--)
			i++;
		if (i != 0)
			uint_.erase(uint_.end() - i, uint_.end());
	}

	size_t cardinality(Trit value) {
		size_t count = 0;
		for (std::vector<int>::iterator it = uint_.begin(); it != uint_.end(); it++)
			if (*it == value)
				count++;
		return count;
	}

	std::unordered_map<Trit, int> cardinality() {
		std::unordered_map<Trit, int> map;
		map[True] = 0;
		map[False] = 0;
		map[Unknown] = 0;

		for (std::vector<int>::iterator it = uint_.begin(); it != uint_.end(); it++)
			map[(Trit)*it]++;

		return map;
	}

	void trim(size_t lastIndex) {
		uint_.erase(uint_.begin() + lastIndex, uint_.end());
	}

	size_t length() {
		std::vector<int>::iterator it = uint_.begin();
		size_t index = 0;
		while (*it != Unknown) {
			it++;
			index++;
		}
		return index;
	}

	size_t capacity() {
		return uint_.size();
	}

	friend TritSet operator &(TritSet& set1, TritSet& set2);
	friend TritSet operator |(TritSet& set1, TritSet& set2);
	friend TritSet& operator !(TritSet& set1);
	friend std::ostream& operator <<(std::ostream& out, const TritSet& tritSet);
};

TritSet operator &(TritSet& set1, TritSet& set2);
TritSet operator |(TritSet& set1, TritSet& set2);
TritSet& operator !(TritSet& set1);
std::ostream& operator <<(std::ostream& out, const TritSet& tritSet);

#endif
