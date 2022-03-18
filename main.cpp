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
	~Hanoi() { for(size_t i = 0; i < 3; ++i) delete getStick(i);};
	std::vector<Stick*> d_sticks{3};
	Stick* getStick(size_t i) {return d_sticks.at(i);}
	void movePiece(size_t src, size_t dest) {
		getStick(dest)->d_pcs.push_back(getStick(src)->d_pcs.back());
		getStick(src)->d_pcs.pop_back();
	}
	void play(size_t src, size_t dest, size_t free, size_t pcs) {
		if (pcs == 1) {
			movePiece(src, dest);
			return;
		}
		play(src, free, dest, pcs - 1);
		movePiece(src, dest);
		play(free, dest, src, pcs - 1);
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
		EXPECT((hanoi.getStick(id)->d_pcs.at(0) == 5));
		id = 2;
		EXPECT((hanoi.getStick(id)->d_pcs.size() == 0));
	}
	{
		Hanoi  hanoi{2};
		EXPECT((hanoi.getStick(0)->d_pcs == std::vector<int>{2,1}));
		hanoi.movePiece(0, 1);
		EXPECT((hanoi.getStick(0)->d_pcs == std::vector<int>{2}));
		EXPECT((hanoi.getStick(1)->d_pcs == std::vector<int>{1}));
	}
	{
		Hanoi  hanoi{5};
		EXPECT((hanoi.getStick(0)->d_pcs == std::vector<int>{5,4,3,2,1}));
		EXPECT((hanoi.getStick(2)->d_pcs.size() == 0));
		hanoi.play(0, 2, 1, 5);
		EXPECT((hanoi.getStick(0)->d_pcs.size() == 0));
		EXPECT((hanoi.getStick(2)->d_pcs == std::vector<int>{5,4,3,2,1}));
	}
	return 0;
}
