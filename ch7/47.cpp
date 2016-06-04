// https://gist.github.com/taeguk/f80fddabaa48877e80a0600722d566a0
#include <iostream>

// 특성정보에 대한 tag들.
struct walk_ability_tag {};
struct jump_ability_tag {};
struct fly_ability_tag {};
struct run_ability_tag :public walk_ability_tag {};
struct ground_ability_tag :public run_ability_tag, public jump_ability_tag {};
struct all_ability_tag :public ground_ability_tag, public fly_ability_tag {};

// 특성정보 클래스 템플릿.
// 특성정보 클래스는 관례에 따라 항상 구조체로 구현한다.
template <class T>
struct ability_traits {
	typedef typename T::ability_category ability_category;
};

// 특성정보에 따라 호출될 함수가 컴파일 타임에 결정된다.
template <class T>
void move(T& obj) {
	move(obj, typename ability_traits<T>::ability_category());
}

// 특성정보에 따른 함수들의 오버로딩.
template <class T>
void move(T&, walk_ability_tag) { std::cout << "move by walking." << std::endl; }
template <class T>
void move(T&, jump_ability_tag) { std::cout << "move by jumping." << std::endl; }
template <class T>
void move(T&, fly_ability_tag) { std::cout << "move by flying." << std::endl; }
template <class T>
void move(T&, run_ability_tag) { std::cout << "move by running." << std::endl; }
template <class T>
void move(T&, ground_ability_tag) { std::cout << "move through ground." << std::endl; }
template <class T>
void move(T&, all_ability_tag) { std::cout << "move by all methods." << std::endl; }

// 특성정보를 지원하는 클래스들.
class Walker {
public:
	typedef walk_ability_tag ability_category;
};
class Jumper {
public:
	typedef jump_ability_tag ability_category;
};
class Flyer {
public:
	typedef fly_ability_tag ability_category;
};
class Runner {
public:
	typedef run_ability_tag ability_category;
};
class GroundMan {
public:
	typedef ground_ability_tag ability_category;
};
class Master {
public:
	typedef all_ability_tag ability_category;
};

int main() {
	Walker walker;
	Jumper jumper;
	Flyer flyer;
	Runner runner;
	GroundMan groundMan;
	Master master;

	move(walker);
	move(jumper);
	move(flyer);
	move(runner);
	move(groundMan);
	move(master);

	/* 실행결과
	move by walking.
	move by jumping.
	move by flying.
	move by running.
	move through ground.
	move by all methods.
	*/

	return 0;
}