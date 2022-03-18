// clear; g++ -Wall -Werror -DDBG main.cpp && ./a.out
// clear; g++ -Wall -Werror main.cpp && ./a.out

#include<string>
#include<vector>
#include<iostream>

#define EXPECT(A) {std::cout << (std::string)((A) ? "PASSED" : "\t\tFAILED") + ": " << #A << std::endl;}
struct Stick {
	Stick() = default;
	Stick(size_t startPieces) {
		for(size_t i = 1; i <= startPieces; ++i) {
			d_pcs.push_back(i);
		}
	};
	std::vector<int> d_pcs{};
};

int main() {
	{
		Stick stick;
		EXPECT((stick.d_pcs.size() == 0));
	}
	{
		Stick stick{5};
		EXPECT((stick.d_pcs.size() == 5));
		EXPECT((stick.d_pcs.at(3) == 4));
	}
	return 0;
}
