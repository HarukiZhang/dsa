#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<iomanip>
#include<string>

constexpr int kWarriorsNum = 5;

constexpr bool kRedP = true;
constexpr bool kBluP = false;

constexpr int kAttackPending = 0;

constexpr int genOrd[2][5] = { {2, 3, 4, 1, 0},
							  {3, 0, 1, 2, 4} };  // red = [0], blue = [1];

class Warrior {
protected:
	bool party; // red party = true; blue party = false;
	int idN;
	int hp;
	int attack; // pending value

public:
	Warrior() : party(true), idN(-1), hp(0), attack(kAttackPending) {}
	virtual ~Warrior() {} //necessary?
	inline int getHP() {
		return hp;
	}
	inline int getID() {
		return idN;
	}
	// getParty used for printing;
	inline const char* getParty(bool party_) {
		if (party_) return "red";
		else return "blue";
	}
	// pure virtual function for each derived type to get themselves' subtype
	virtual inline const char* getSubtype() = 0;
};

class Dragon : public Warrior {
protected:
	/*stdHP should be able to be reset by input info in runtime;
	and stdHP should be protected from easy external reset*/
	static int stdHP;

public:
	Dragon(bool party_, int idN_)
	{
		party = party_;
		idN = idN_;
		hp = stdHP;
		attack = kAttackPending;
	}
	virtual inline const char* getSubtype() {
		return "dragon";
	}
	inline static const int getStdHP() {
		return stdHP;
	}
	inline static int& resetStdHP() {
		return stdHP;
	}
};
class Ninja : public Warrior {
protected:
	static int stdHP;

public:
	Ninja(bool party_, int idN_)
	{
		party = party_;
		idN = idN_;
		hp = stdHP;
		attack = kAttackPending;
	}
	virtual inline const char* getSubtype() {
		return "ninja";
	}
	inline static const int getStdHP() {
		return stdHP;
	}
	inline static int& resetStdHP() {
		return stdHP;
	}
};
class Iceman : public Warrior {
protected:
	static int stdHP;

public:
	Iceman(bool party_, int idN_)
	{
		party = party_;
		idN = idN_;
		hp = stdHP;
		attack = kAttackPending;
	}
	virtual inline const char* getSubtype() {
		return "iceman";
	}
	inline static const int getStdHP() {
		return stdHP;
	}
	inline static int& resetStdHP() {
		return stdHP;
	}
};
class Lion : public Warrior {
protected:
	static int stdHP;

public:
	Lion(bool party_, int idN_)
	{
		party = party_;
		idN = idN_;
		hp = stdHP;
		attack = kAttackPending;
	}
	virtual inline const char* getSubtype() {
		return "lion";
	}
	inline static const int getStdHP() {
		return stdHP;
	}
	inline static int& resetStdHP() {
		return stdHP;
	}
};
class Wolf : public Warrior {
protected:
	static int stdHP;

public:
	Wolf(bool party_, int idN_)
	{
		party = party_;
		idN = idN_;
		hp = stdHP;
		attack = kAttackPending;
	}
	virtual inline const char* getSubtype() {
		return "wolf";
	}
	inline static const int getStdHP() {
		return stdHP;
	}
	inline static int& resetStdHP() {
		return stdHP;
	}
};

int Dragon::stdHP = -1;
int Ninja::stdHP = -1;
int Iceman::stdHP = -1;
int Lion::stdHP = -1;
int Wolf::stdHP = -1;

class HeadQuarter {
	// standard_generation_Sequences = {"dragon", "ninja", "iceman", "lion", "wolf"};
public:
	static const int* stdHPs;

private:
	bool party; // red party = true; blue party = false;
	int mana;
	const int* generationOrder; //pre-defined genOrd that should be iterated by index
	
	int warriorIdCount = 1; // used to uniformly assign ID number to each warrior
	int troops[kWarriorsNum]{ 0 };  // record the number of warrior in each subtype
	int timeCounter = 0;
	int genLog = 0; // used in _next_idx() {return genLog % 5}
	int genIdx = 0; // the index of warrior's subtype that is under operation at the moment
	bool stopFlag = true; // used for controlling to print stop message only once;

public:
	HeadQuarter(bool party_, int mana_, const int* genOrd_) :
		party(party_), mana(mana_), generationOrder(genOrd_)
	{}
	
	~HeadQuarter() {}

	bool generateWarrior() {
		if (stopFlag && _check_mana_reservoir()) {
			std::cout << std::setw(3) << std::setfill('0') << timeCounter++ << " ";
			std::string _subtype;
			switch (genIdx) {
			case 0:
				_subtype = "dragon";
				break;
			case 1:
				_subtype = "ninja";
				break;
			case 2:
				_subtype = "iceman";
				break;
			case 3: 
				_subtype = "lion";
				break;
			case 4: 
				_subtype = "wolf";
				break;
			}
			troops[genIdx]++;
			_print_GenWarr(_subtype, warriorIdCount++, _get_warriors_stdHP());
			return true;
		}
		else if (stopFlag) {
			std::cout << std::setw(3) << std::setfill('0') << timeCounter++ << " ";
			_print_GenStop(); //if no more mana for generation of any Warrior, directly call printGenStop();
			stopFlag = false;
		}
		return false;
	}

private:
	const char* _get_party(bool party_) {
		if (party_) return "red";
		return "blue";
	}
	
	int _next_idx() {
		return (genLog++) % 5;
	}

	bool _check_mana_reservoir() //idx generator cannot pass over, so mana has to be change inside func
	{
		for (int i = 0; i < kWarriorsNum; ++i) {
			genIdx = generationOrder[_next_idx()];
			int dev = mana - _get_warriors_stdHP();
			if (dev >= 0) {
				mana = dev;
				return true;
			}
		}
		return false;
	}

	int _get_warriors_stdHP(bool)
	{
		switch (genIdx) {
		case 0:	return Dragon::getStdHP(); break;
		case 1: return Ninja::getStdHP(); break;
		case 2: return Iceman::getStdHP(); break;
		case 3: return Lion::getStdHP(); break;
		case 4: return Wolf::getStdHP(); break;
		default: return -1;
		}
	}

	void _print_GenWarr(Warrior* warr_) {
		std::cout << _get_party(party) << " "
			<< warr_->getSubtype() << " "
			<< warr_->getID()
			<< " born with strength "
			<< warr_->getHP() << ","
			<< troops[genIdx] << " "
			<< warr_->getSubtype() << " in "
			<< _get_party(party) << " headquarter"
			<< std::flush;
	}

	void _print_GenStop() {
		const char* p = _get_party(party);
		std::cout << p
			<< " headquarter stops making warriors\n"
			<< std::flush;
	}

	void _print_GenWarr(std::string subtype_, int idn_, int hp_) {
		const char* p = _get_party(party);
		std::cout << p << " "
			<< subtype_ << " "
			<< idn_
			<< " born with strength "
			<< hp_ << ","
			<< troops[genIdx] << " "
			<< subtype_ << " in "
			<< p << " headquarter\n"
			<< std::flush;
	}

	int _get_warriors_stdHP() {
		return stdHPs[genIdx];
	}
};

const int* HeadQuarter::stdHPs = nullptr;


int main() {

	int caseNum;
	std::cin >> caseNum;

	for (int i = 0; i < caseNum; ++i) {

		int mana_in;
		std::cin >> mana_in;

		int _stdHPs[kWarriorsNum];
		for (int i = 0; i < kWarriorsNum; ++i) {
			std::cin >> _stdHPs[i];
		}

		HeadQuarter::stdHPs = _stdHPs;

		HeadQuarter HQRed{ kRedP, mana_in, genOrd[0] };
		HeadQuarter HQBlu{ kBluP, mana_in, genOrd[1] };

		bool flagRed = true, flagBlu = true;
		while (flagRed || flagBlu) {
			flagRed = HQRed.generateWarrior();
			flagBlu = HQBlu.generateWarrior();
		}
	}

}

/*
各种武士应该使用独立的print函数来进行出生状态的输出，先尝试写在constructor里，还有编号的计数器；
如果不好控制constructor的调用，就单独写print函数，和控制编号计数器的static函数；


魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市。
红司令部，City 1，City 2，……，City n，蓝司令部

两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编号、生命值、攻击力这三种属性。

双方的武士编号都是从1开始计算。红方制造出来的第n个武士，编号就是n。同样，蓝方制造出来的第n个武士，编号也是n。

武士在刚降生的时候有一个生命值。

在每个整点，双方的司令部中各有一个武士降生。

红方司令部按照iceman、lion、wolf、ninja、dragon的顺序循环制造武士。

蓝方司令部按照lion、dragon、ninja、iceman、wolf的顺序循环制造武士。

制造武士需要生命元。

制造一个初始生命值为m的武士，司令部中的生命元就要减少m个。

如果司令部中的生命元不足以制造某个按顺序应该制造的武士，那么司令部就试图制造下一个。如果所有武士都不能制造了，则司令部停止制造武士。

给定一个时间，和双方司令部的初始生命元数目，要求你将从0点0分开始到双方司令部停止制造武士为止的所有事件按顺序输出。
一共有两种事件，其对应的输出样例如下：

1) 武士降生
输出样例： 004 blue lion 5 born with strength 5,2 lion in red headquarter
表示在4点整，编号为5的蓝魔lion武士降生，它降生时生命值为5，降生后蓝魔司令部里共有2个lion武士。
（为简单起见，不考虑单词的复数形式）注意，每制造出一个新的武士，都要输出此时司令部里共有多少个该种武士。

2) 司令部停止制造武士
输出样例： 010 red headquarter stops making warriors
表示在10点整，红方司令部停止制造武士


输入
第一行是一个整数，代表测试数据组数。

每组测试数据共两行。

第一行：一个整数M。其含义为， 每个司令部一开始都有M个生命元( 1 <= M <= 10000)。

第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000。
输出
对每组测试数据，要求输出从0时0分开始，到双方司令部都停止制造武士为止的所有事件。
对每组测试数据，首先输出"Case:n" n是测试数据的编号，从1开始 。
接下来按恰当的顺序和格式输出所有事件。每个事件都以事件发生的时间开头，时间以小时为单位，有三位。

样例输入
1
20
3 4 5 6 7
样例输出
Case:1
000 red iceman 1 born with strength 5,1 iceman in red headquarter
000 blue lion 1 born with strength 6,1 lion in blue headquarter
001 red lion 2 born with strength 6,1 lion in red headquarter
001 blue dragon 2 born with strength 3,1 dragon in blue headquarter
002 red wolf 3 born with strength 7,1 wolf in red headquarter
002 blue ninja 3 born with strength 4,1 ninja in blue headquarter
003 red headquarter stops making warriors
003 blue iceman 4 born with strength 5,1 iceman in blue headquarter
004 blue headquarter stops making warriors

*/