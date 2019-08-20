#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H


#include <iostream>
using namespace std;

// TODO: SEED AUS EPROM!

class RandomNumberGenerator {
private:
	int seed = 0;
public:
	RandomNumberGenerator() {}

	void setSeed(int seed) {
		this->seed = seed;
	}

	int getSeed() {
		
		return this->seed;
	}

	int getRandomNumber(int range) {
		this->seed = (this->seed * 8) % 11;
		return this->seed % range;
	}
};

#endif
