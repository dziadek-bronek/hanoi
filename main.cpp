// clear; g++ -Wall -Werror -DDBG main.cpp && ./a.out
// clear; g++ -Wall -Werror main.cpp && ./a.out

#include<string>
#include<vector>
#include<iostream>

#define EXPECT(A) {std::cout << (std::string)((A) ? "PASSED" : "\t\tFAILED") + ": " << #A << std::endl;}
struct Stick {
	Stick() {};
	std::vector<int> d_pcs{};
};

int main() {
	{
		Stick stick;
		EXPECT((stick.d_pcs.size() == 0));
	}
	return 0;
}
