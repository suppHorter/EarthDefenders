class NumberGenerator
{
public:	
uint8_t getrndNo();
private: 
uint8_t seed = 42;
};

uint8_t NumberGenerator::getrndNo()
{
	this->seed = (this->seed*11) % 8;
	return this->seed;
}