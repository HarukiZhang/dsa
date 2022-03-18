#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <Windows.h>


class FibonacciGenerator {
public:
	FibonacciGenerator() : a(0), b(0), c(0), state(0) {}
	int generate() {
		switch (state) {
		case 0:
			for (a = 0, b = 1; ; c = a + b) {
				state = 1;
				return c;
		case 1:;
			}
		}
	}
private:
	int a, b, c;
	int state;
};

int function1(void) {
	static int i, state = 0;
	switch (state) {
	case 0: /* start of function */
		for (i = 0; i < 2; i++) {
			state = 1; /* so we will come back to "case 1" */
			return i;
	case 1:; /* resume control straight after the return */
		}
	}
}

class SSI {
	unsigned char ssint;
public:
	SSI() : ssint(NULL) {}
	SSI(int l) : ssint(static_cast<unsigned char>(l)) {}
	SSI(SSI& l) : ssint(l.ssint) {}
	operator int() const { return static_cast<int>(ssint); }
	SSI& operator=(int l) {
		ssint = l;
		return *this;
	}
	SSI& operator=(SSI& l) {
		ssint = l.ssint;
		return *this;
	}
	SSI& operator++() {
		ssint += '\1';
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& os, SSI& l) {
		os << static_cast<int>(l.ssint);
		return os;
	}
};


//class AbstractWarrior {
//public:
//	virtual ~AbstractWarrior() {}
//	virtual int getID() const = 0;
//	virtual SSI getHP() const = 0;
//	virtual SSI getAtt() const = 0;
//};
//class WarriorW : public AbstractWarrior {
//private:
//	Equipment* equip;                           // 4  4
//	Equipment::iterator* wpIdx = &(equip->begin()); // 4 4
//	int idN;                                    // 4  4
//	SSI wpCt[5]{};                              // 5  1
//	SSI hp;                                     // 1  1
//	SSI loc = '\0';                             // 1  1
//	bool tribe;                                 // 1  1
//
//protected:
//	WarriorW(int id, int h, int a, int lc, bool t) : idN(id), hp(h), att(a), loc(lc), tribe(t) {}
//	virtual ~WarriorW() {}
//	int getID() const override { return idN; }
//	SSI getHP() const override { return hp; }
//
//	template<typename DervWarr>
//	SSI getAtt() const override { static_cast<DervWarr*>(this)->getAtt(); }
//};
//class DragonD : public WarriorW {
//	float morale;
//
//	static SSI att;
//
//public:
//	DragonD(int id, int h, int a, float m) : WarriorW{ id, h, a }, morale(m) {}
//	SSI getAtt() const { return att; }
//};
//class LionL : public WarriorW {
//	int loyalty;
//public:
//	LionL(int id, int h, int a, int loy) : WarriorW{ id, h, a }, loyalty(loy) {}
//};






int main() {

}

