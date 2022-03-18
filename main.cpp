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
#ifdef DBG
	void display() {
		std::cout << '|';
		for(auto i = d_pcs.begin(); i != d_pcs.end(); ++i) {
			std::cout << *i;
		}
		std::cout << std::endl;
	}
#endif
};

struct Hanoi {
	Hanoi(size_t startPiecesNum) : d_sticks{new Stick(startPiecesNum), new Stick, new Stick} {};
	~Hanoi() { for(size_t i = 0; i < 3; ++i) delete d_sticks.at(i);};
	std::vector<Stick*> d_sticks{3};
	std::vector<int>& getStick(size_t i) {return d_sticks.at(i)->d_pcs;}
	void movePiece(size_t src, size_t dest) {
		getStick(dest).push_back(getStick(src).back());
		getStick(src).pop_back();
#ifdef DBG
		display();
#endif
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
#ifdef DBG
	void display() {
		for(size_t i = 0; i < 3; ++i) {
			d_sticks.at(i)->display();
		}
		std::cout << "---------------" << std::endl;
	}
#endif
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
		EXPECT((hanoi.getStick(id) == std::vector<int>{5,4,3,2,1}));
		id = 2;
		EXPECT((hanoi.getStick(id).size() == 0));
	}
	{
		Hanoi  hanoi{2};
		EXPECT((hanoi.getStick(0) == std::vector<int>{2,1}));
		EXPECT((hanoi.getStick(0).size() == 2));
		hanoi.movePiece(0, 1);
		EXPECT((hanoi.getStick(0).size() == 1));
		EXPECT((hanoi.getStick(1).size() == 1));
		EXPECT((hanoi.getStick(0) == std::vector<int>{2}));
		EXPECT((hanoi.getStick(1) == std::vector<int>{1}));
	}
	{
		Hanoi  hanoi{5};
		EXPECT((hanoi.getStick(0) == std::vector<int>{5,4,3,2,1}));
		EXPECT((hanoi.getStick(2).size() == 0));
#ifdef DBG
		hanoi.display();
#endif
		hanoi.play(0, 2, 1, 5);
		EXPECT((hanoi.getStick(0).size() == 0));
		EXPECT((hanoi.getStick(2) == std::vector<int>{5,4,3,2,1}));
	}
	return 0;
}
