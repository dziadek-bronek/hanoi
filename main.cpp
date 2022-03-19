// clear; g++ -Wall -Werror -DDISPLAY_STICKS main.cpp && ./a.out
// clear; g++ -Wall -Werror main.cpp && ./a.out

#include<string>
#include<vector>
#include<iostream>

#define EXPECT(A) {std::cout << (std::string)((A) ? "PASSED" : "\t\tFAILED") + ": " << #A << std::endl;}

struct Stick : std::vector<int> {
	Stick() = default;
	Stick(size_t startPiecesNum) {
		for(size_t i = startPiecesNum; i >= 1; --i) {
			push_back(i);
		}
	};
#ifdef DISPLAY_STICKS
	void display() {
		std::cout << '|';
		for(auto i = begin(); i != end(); ++i) {
			std::cout << *i;
		}
		std::cout << std::endl;
	}
#endif
};

struct Hanoi {
	Hanoi(size_t startPiecesNum) : d_sticks{new Stick(startPiecesNum), new Stick, new Stick} {};
	~Hanoi() { for(size_t i = 0; i < 3; ++i) delete d_sticks.at(i);};
	std::vector<int>& getStick(size_t i) {return *(d_sticks.at(i));}
	void movePiece(size_t src, size_t dest) {
		getStick(dest).push_back(getStick(src).back());
		getStick(src).pop_back();
#ifdef DISPLAY_STICKS
		display();
#endif
	}
	void solve(size_t src, size_t dest, size_t free, size_t pcs) {
		if (pcs == 1) {
			movePiece(src, dest);
			return;
		}
		solve(src, free, dest, pcs - 1);
		movePiece(src, dest);
		solve(free, dest, src, pcs - 1);
	}
#ifdef DISPLAY_STICKS
	void display() {
		for(size_t i = 0; i < 3; ++i) {
			d_sticks.at(i)->display();
		}
		std::cout << "---------------" << std::endl;
	}
#endif
	private:
	std::vector<Stick*> d_sticks{};
};

int main() {
	{
		Stick stick;
		EXPECT((stick.size() == 0));
	}
	{
		Stick stick(5);
		EXPECT((stick.size() == 5));
		EXPECT((stick.at(3) == 2));
	}
	{
		Hanoi hanoi(5);
#ifdef DISPLAY_STICKS
		hanoi.display();
#endif
		EXPECT((hanoi.getStick(0) == Stick(5)));
		EXPECT((hanoi.getStick(2).size() == 0));
	}
	{
		Hanoi hanoi{2};
#ifdef DISPLAY_STICKS
		hanoi.display();
#endif
		EXPECT((hanoi.getStick(0) == Stick(2)));
		EXPECT((hanoi.getStick(0).size() == 2));
		hanoi.movePiece(0, 1);
		EXPECT((hanoi.getStick(0).size() == 1));
		EXPECT((hanoi.getStick(1).size() == 1));
		EXPECT((hanoi.getStick(0).at(0) == 2));
		EXPECT((hanoi.getStick(1).at(0) == 1));
	}
	{
		Hanoi hanoi(5);
#ifdef DISPLAY_STICKS
		hanoi.display();
#endif
		EXPECT((hanoi.getStick(0) == Stick(5)));
		EXPECT((hanoi.getStick(2).size() == 0));
		hanoi.solve(0, 2, 1, 5);
		EXPECT((hanoi.getStick(0).size() == 0));
		EXPECT((hanoi.getStick(2) == Stick(5)));
	}
	{
		Hanoi hanoi(5);
#ifdef DISPLAY_STICKS
		hanoi.display();
#endif
		hanoi.movePiece(0, 1);
		hanoi.movePiece(0, 1);
		EXPECT((hanoi.getStick(1).size() == 1));
	}
	return 0;
}
