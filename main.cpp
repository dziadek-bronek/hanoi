// clear; g++ -Wall -Werror -DDBG main.cpp && ./a.out
// clear; g++ -Wall -Werror main.cpp && ./a.out

#include<string>
#include<vector>
#include<iostream>

#define EXPECT(A) {std::cout << (std::string)((A) ? "PASSED" : "\t\tFAILED") + ": " << #A << std::endl;}
struct Stick {
	Stick() = default;
	Stick(size_t startPieces) {
		for(size_t i = startPieces; i >= 1; --i) {
			d_pcs.push_back(i);
		}
	};
	std::vector<int> d_pcs{};
};

struct Hanoi {
	Hanoi(size_t startPiecesNum) : d_sticks{new Stick(startPiecesNum), new Stick, new Stick} {};
	~Hanoi() { for(size_t i = 0; i < 3; ++i) delete d_sticks.at(i);};
	std::vector<Stick*> d_sticks{3};
	void movePiece(size_t src, size_t dest) {
		d_sticks.at(dest)->d_pcs.push_back(d_sticks.at(src)->d_pcs.back());
		d_sticks.at(src)->d_pcs.pop_back();
	}

};

int main() {
	{
		Stick stick;
		EXPECT((stick.d_pcs.size() == 0));
	}
	{
		Stick stick{5};
		EXPECT((stick.d_pcs.size() == 5));
		EXPECT((stick.d_pcs.at(3) == 2));
	}
	{
		Hanoi  hanoi{5};
		size_t id{0};
		EXPECT((hanoi.d_sticks.at(id)->d_pcs.at(0) == 5));
		id = 2;
		EXPECT((hanoi.d_sticks.at(id)->d_pcs.size() == 0));
	}
	{
		Hanoi  hanoi{2};
		EXPECT((hanoi.d_sticks.at(0)->d_pcs == std::vector<int>{2,1}));
		hanoi.movePiece(0, 1);
		EXPECT((hanoi.d_sticks.at(0)->d_pcs == std::vector<int>{2}));
		EXPECT((hanoi.d_sticks.at(1)->d_pcs == std::vector<int>{1}));
	}
	{
		Hanoi  hanoi{5};
		EXPECT((hanoi.d_sticks.at(0)->d_pcs == std::vector<int>{5,4,3,2,1}));
		EXPECT((hanoi.d_sticks.at(2)->d_pcs.size() == 0));
		hanoi.play(0, 2, 1, 5);
		EXPECT((hanoi.d_sticks.at(0)->d_pcs.size() == 0));
		EXPECT((hanoi.d_sticks.at(2)->d_pcs == std::vector<int>{5,4,3,2,1}));
	}
	return 0;
}
