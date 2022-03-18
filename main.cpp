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

using ThreeSticks = std::vector<Stick>;

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
	{
		Stick a{5}; Stick b; Stick c;
		ThreeSticks  hanoi{a, b, c};
		size_t id{0};
		EXPECT((hanoi.at(id).d_pcs.at(3) == 4));
		id = 2;
		EXPECT((hanoi.at(id).d_pcs.size() == 0));
	}
	{
		Stick a{3}; Stick b; Stick c;
		ThreeSticks  hanoi{a, b, c};
		EXPECT((hanoi.at(0).d_pcs == {3,2,1}));
		movePiece(0, 1);
		EXPECT((hanoi.at(0).d_pcs == {3, 2}));
		EXPECT((hanoi.at(0).d_pcs == {1}));
	}
	return 0;
}
