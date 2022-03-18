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
ħ������������Ǻ�ħ����˾�����������ħ����˾�������˾�֮�����������е����ɳ��С�
��˾���City 1��City 2��������City n����˾�

������˾�����������ʿ����ʿһ���� dragon ��ninja��iceman��lion��wolf
���֡�ÿ����ʿ���б�š�����ֵ�����������������ԡ� 0        1      2      3 4

˫������ʿ��Ŷ��Ǵ�1��ʼ���㡣�췽��������ĵ�n����ʿ����ž���n��ͬ����������������ĵ�n����ʿ�����Ҳ��n��

��ʿ�ڸս�����ʱ����һ������ֵ��

��ÿ�����㣬˫����˾��и���һ����ʿ������

�췽˾�����iceman��lion��wolf��ninja��dragon��˳��ѭ��������ʿ�� {2,3,4,1,0}

����˾�����lion��dragon��ninja��iceman��wolf��˳��ѭ��������ʿ�� {3,0,1,2,4}

������ʿ��Ҫ����Ԫ��

����һ����ʼ����ֵΪm����ʿ��˾��е�����Ԫ��Ҫ����m����

���˾��е�����Ԫ����������ĳ����˳��Ӧ���������ʿ����ô˾�����ͼ������һ�������������ʿ�����������ˣ���˾�ֹͣ������ʿ��

����һ��ʱ�䣬��˫��˾��ĳ�ʼ����Ԫ��Ŀ��Ҫ���㽫��0��0�ֿ�ʼ��˫��˾�ֹͣ������ʿΪֹ�������¼���˳�������
һ���������¼������Ӧ������������£�

1) ��ʿ����
��������� 004 blue lion 5 born with strength 5,2 lion in red headquarter
��ʾ��4���������Ϊ5����ħlion��ʿ������������ʱ����ֵΪ5����������ħ˾��ﹲ��2��lion��ʿ��
��Ϊ������������ǵ��ʵĸ�����ʽ��ע�⣬ÿ�����һ���µ���ʿ����Ҫ�����ʱ˾��ﹲ�ж��ٸ�������ʿ��

2) ˾�ֹͣ������ʿ
��������� 010 red headquarter stops making warriors
��ʾ��10�������췽˾�ֹͣ������ʿ


����
��һ����һ�������������������������

ÿ��������ݹ����С�

��һ�У�һ������M���京��Ϊ�� ÿ��˾�һ��ʼ����M������Ԫ( 1 <= M <= 10000)��

�ڶ��У���������������� dragon ��ninja��iceman��lion��wolf
�ĳ�ʼ����ֵ�����Ƕ�����0С�ڵ���10000�� ���
��ÿ��������ݣ�Ҫ�������0ʱ0�ֿ�ʼ����˫��˾���ֹͣ������ʿΪֹ�������¼���
��ÿ��������ݣ��������"Case:n" n�ǲ������ݵı�ţ���1��ʼ ��
��������ǡ����˳��͸�ʽ��������¼���ÿ���¼������¼�������ʱ�俪ͷ��ʱ����СʱΪ��λ������λ��

��������
1
20
3 4 5 6 7
�������
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