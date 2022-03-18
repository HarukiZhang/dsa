#include <iostream>
#include <iomanip>

using namespace std;

constexpr int kWarriorsNum = 5;
constexpr char ordered_warriors_name[5][7] = {"dragon", "ninja", "iceman", "lion", "wolf"};
constexpr int genOrd[2][5] = {{2, 3, 4, 1, 0},
                              {3, 0, 1, 2, 4}};  // red = [0], blue = [1];

constexpr bool kRedP = false;
constexpr bool kBluP = true;

int timeCounter, ordered_initial_HPs[5], troop1, subtroops1[5], troop2, subtroops2[5];

const char* selectParty(bool party) {
  if (party) return "blue ";
  return "red ";
}

void printInfo(bool party_, const int& index_) {
  const int* _genOrd = party_ ? genOrd[1] : genOrd[0];
  int* _troop = party_ ? &troop2 : &troop1;
  int* _subtr = party_ ? subtroops2 : subtroops1;

  ++_subtr[index_];
  ++(*_troop);

  cout << setw(3) << setfill('0') << timeCounter << " ";
  cout << selectParty(party_) << ordered_warriors_name[_genOrd[index_]] << " " << *_troop
       << " born with strength " << ordered_initial_HPs[_genOrd[index_]] << ","
       << _subtr[index_] << " " << ordered_warriors_name[_genOrd[index_]] << " in "
       << selectParty(party_) << "headquarter" << endl;
}

void printStop(bool party_) {
  cout << setw(3) << setfill('0') << timeCounter << " ";
  cout << selectParty(party_) << "headquarter stops making warriors\n" << flush;
}

int genRed(bool reset) {
  static int s;
  if (reset) return s = 0;
  return (s++) % kWarriorsNum;
}

int genBlu(bool reset) {
  static int s;
  if (reset) return s = 0;
  return (s++) % kWarriorsNum;
}

bool check_mana_reservoir(bool party_, const int mana_, int& index_,
                          const int* genOrd_, int (*gen)(bool)) {
  for (int i = 0; i < kWarriorsNum; ++i) {
    index_ = gen(0);
    int dev = mana_ - ordered_initial_HPs[genOrd_[index_]];
    if (dev >= 0) return true;
  }
  return false;
}

bool generateWarriors(bool party_, int& mana_, int& index_, bool flag_,
             int (*gen)(bool)) {
  const int kSel = party_ ? 1 : 0;
  if (check_mana_reservoir(party_, mana_, index_, genOrd[kSel], gen)) {
    mana_ -= ordered_initial_HPs[genOrd[kSel][index_]];
    printInfo(party_, index_);
    return true;
  } else if (flag_) {
    printStop(party_);
    flag_ = false;
  }
  return flag_;
}

int main() {
  int caseNum;
  cin >> caseNum;

  for (int cn = 1; cn <= caseNum; ++cn) {
    int mana1;
    cin >> mana1;

    for (int i = 0; i < kWarriorsNum; ++i) cin >> ordered_initial_HPs[i];

    int mana2 = mana1;  // reset mana reservoir
    timeCounter = 0;            // reset time counter

    troop1 = 0;  // reset each troop and subtroop counter;
    troop2 = 0;
    for (int i = 0; i < kWarriorsNum; ++i) {
      *(subtroops1 + i) = 0;
      *(subtroops2 + i) = 0;
    }

    genRed(1);  // resest the subscript generator
    genBlu(1);

    cout << "Case:" << cn << endl;

    bool flag1 = true, flag2 = true;
    while (flag1 || flag2) {
      int idx1, idx2;
      // red
      flag1 = generateWarriors(kRedP, mana1, idx1, flag1, genRed);

      // blue
      flag2 = generateWarriors(kBluP, mana2, idx2, flag2, genBlu);

      // time increment
      ++timeCounter;
    }
  }
  return 0;
}

/*
004 blue lion 5 born with strength 5,2 lion in red headquarter
魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市。
红司令部，City 1，City 2，……，City n，蓝司令部

两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf
五种。每种武士都有编号、生命值、攻击力这三种属性。 0        1      2      3 4

双方的武士编号都是从1开始计算。红方制造出来的第n个武士，编号就是n。同样，蓝方制造出来的第n个武士，编号也是n。

武士在刚降生的时候有一个生命值。

在每个整点，双方的司令部中各有一个武士降生。

红方司令部按照iceman、lion、wolf、ninja、dragon的顺序循环制造武士。 {2,3,4,1,0}

蓝方司令部按照lion、dragon、ninja、iceman、wolf的顺序循环制造武士。 {3,0,1,2,4}

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

第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf
的初始生命值。它们都大于0小于等于10000。 输出
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