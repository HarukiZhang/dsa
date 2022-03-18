#define _CRT_SECURE_NO_WARNINGS
#include <list>
#include <iostream>
#include <iomanip>
#include "prototype.h"

class Weapon;
class Warrior;

typedef std::list<Weapon*> Equipment;
typedef std::list<Warrior*> CityField;
constexpr int kWeaponNum = 3;

constexpr int kWarriorsNum = 5;
constexpr int kAttackInit = 0;
constexpr int kMaxWeaponNum = 10;
constexpr int predef_genOrd[2][5] = {
	{3, 0, 1, 2, 4},
	{2, 3, 4, 1, 0}
};
enum TribeField : bool {
	RedTribe = true,
	BluTribe = false
};

class Chronos {
protected:
	static int hourFlow;
	static int minuteFlow;
public:
	static const int& hour;
};
int Chronos::hourFlow = 0;
int Chronos::minuteFlow = 0;
const int& Chronos::hour = Chronos::hourFlow;

class Weapon {
protected:
	static constexpr float kAttBase = 10.0f;
	enum WeaponAttackCoef : int {
		attCoefSword = 2,
		attCoefBomb = 4,
		attCoefArrow = 3
	};
	enum WeaponDurability : int {
		duraSword = 3,
		duraBomb = 1,
		duraArrow = 2
	};

public:
	enum WeaponNames : int {
		sword = 0,
		bomb,
		arrow
	};

public:
	virtual ~Weapon() {};

	virtual int useWeapon(int warrior_attack_) = 0;

	virtual int getDurability() const = 0;

	virtual int getTypeid() const = 0;

	virtual const char* getTypename() const = 0;
};

class Sword : public Weapon {
	int durability = duraSword;

public:
	virtual int useWeapon(int warrior_attack_) {
		return static_cast<int>(warrior_attack_ * attCoefSword / kAttBase);
	}

	virtual int getDurability() const {
		return durability;
	}

	virtual int getTypeid() const { return sword; }

	virtual const char* getTypename() const { return "sword"; }
};
class Bomb : public Weapon {
	int durability = duraBomb;

public:
	virtual int useWeapon(int warrior_attack_) {
		--durability;
		return static_cast<int>(warrior_attack_ * attCoefBomb / kAttBase);
	}

	virtual int getDurability() const {
		return durability;
	}

	virtual int getTypeid() const { return bomb; }

	virtual const char* getTypename() const { return "bomb"; }
};
class Arrow : public Weapon {
	int durability = duraArrow;

public:
	virtual int useWeapon(int warrior_attack_) {
		--durability;
		return static_cast<int>(warrior_attack_ * attCoefArrow / kAttBase);
	}

	virtual int getDurability() const {
		return durability;
	}

	virtual int getTypeid() const { return arrow; }

	virtual const char* getTypename() const { return "arrow"; }
};

class Warrior
{
public:
	enum W_Typeid : int {
		dragon = 0,
		ninja,
		iceman,
		lion,
		wolf
	};
	enum W_AliveStt : bool {
		alive = true,
		died = false
	};
	enum AttackRes : int {
		runOutOfWeapon = 5,
		noDamage = 4,
		bothAlive = 3,
		bothDied = 2,
		killed = 1,
		selfKilled = 0
	};

public:
	virtual ~Warrior() {}

	virtual int getID() const = 0;

	virtual int getHP() const = 0;

	virtual const char* getTypename() const = 0;

	virtual W_Typeid getTypeid() const = 0;

	virtual const char* getTribe() const = 0;

	virtual bool getTribe(bool) const = 0;

	virtual int getLoc() const = 0;

	virtual int getAttack() const = 0;

	virtual int* getWpCounter() = 0;

	virtual Equipment* getEquipment() = 0;

	virtual void reorderEquipment() = 0;

	virtual bool equipmentEmpty() = 0;

	virtual void warriorMove() = 0;

	virtual AttackRes warriorAttack(Warrior* adversary_, Equipment::iterator wpIdx_) = 0;

	virtual bool receiveDamage(int damage_) = 0;

	virtual void printGenSpecial() const = 0;

	virtual void printWarrReport() const = 0;

	virtual int& resetLoc() = 0;

	virtual int getLoyalty() const {
		return 1;
	}

	int takeWeapon(Warrior* adversary_) {
		Equipment* myEquip = this->getEquipment();
		Equipment* adEquip = adversary_->getEquipment();
		int* myWpCounter = this->getWpCounter();
		int* adWpCounter = adversary_->getWpCounter();
		int maxTakeNum = kMaxWeaponNum - myEquip->size();
		if (maxTakeNum == 0 || adEquip->size() == 0) return 0;
		adEquip->sort(Warrior::_takeWp_compare);
		int  takeNum = 0;
		for (auto it = adEquip->begin();
			it != adEquip->end() &&
			takeNum < maxTakeNum;
			++takeNum) {
			int wpid = (*it)->getTypeid();
			myEquip->push_front(*it);
			myWpCounter[wpid]++;
			it = adEquip->erase(it);
			adWpCounter[wpid]--;
		}
		return takeNum;
	}

protected:
	Weapon* _receive_weapon(int weapon_typeid) {
		switch (weapon_typeid) {
		case Weapon::sword: return new Sword; break;
		case Weapon::bomb: return new Bomb; break;
		case Weapon::arrow: return new Arrow; break;
		default: return nullptr; break;
		}
	}

	static bool _weapon_compare(const Weapon* w1, const Weapon* w2) {
		int w1id = w1->getTypeid(), w2id = w2->getTypeid();
		if (w1id != w2id)
			return w1id < w2id;
		return w1->getDurability() < w2->getDurability();
	}

	static bool _takeWp_compare(const Weapon* w1, const Weapon* w2) {
		int w1id = w1->getTypeid(), w2id = w2->getTypeid();
		if (w1id != w2id)
			return w1id < w2id;
		return w1->getDurability() > w2->getDurability();
	}
};

class Dragon : public Warrior
{
private:
	int idN;
	int hp;
	int weaponCounter[kWeaponNum]{};
	int location = 0;
	float morale;
	bool tribe;
	Equipment* equipment;
	static int attack;

public:
	Dragon(bool tribe_, int idN_, int hp_, int mana_resv_)
		: idN(idN_), hp(hp_), tribe(tribe_), equipment(new Equipment) {
		equipment->push_back(_receive_weapon(idN % 3));
		weaponCounter[idN % 3]++;
		morale = static_cast<float>(mana_resv_) / hp;
	}

	virtual ~Dragon() {
		for (auto it = equipment->begin(); it != equipment->end(); ++it)
			delete* it;
		delete equipment;
	}

	virtual int getID() const { return idN; }

	virtual int getHP() const { return hp; }

	virtual const char* getTypename() const { return "dragon"; }

	virtual W_Typeid getTypeid() const { return dragon; }

	virtual const char* getTribe() const {
		if (tribe == RedTribe) return "red";
		return "blue";
	}

	virtual bool getTribe(bool) const {
		return tribe;
	}

	virtual int getLoc() const {
		return location;
	}

	virtual int getAttack() const {
		return attack;
	}

	virtual int* getWpCounter() {
		return weaponCounter;
	}

	virtual Equipment* getEquipment() {
		return equipment;
	}

	virtual void reorderEquipment() {
		equipment->sort(_weapon_compare);
	}

	virtual bool equipmentEmpty() {
		return equipment->empty();
	}

	virtual void warriorMove() {
		if (tribe == RedTribe)
			++location;
		else
			--location;
	}

	virtual AttackRes warriorAttack(Warrior* adversary_, Equipment::iterator wpIdx_) {
		if (equipment->empty())
			return runOutOfWeapon;
		bool flag_self = alive, flag_advs = alive;
		int damage = (*wpIdx_)->useWeapon(attack);
		flag_advs = adversary_->receiveDamage(damage);
		if ((*wpIdx_)->getTypeid() == Weapon::bomb)
			flag_self = receiveDamage(damage / 2);
		if (damage == 0) return noDamage;
		if (flag_self == alive && flag_advs == alive)
			return bothAlive;
		else {
			if (flag_self == alive)
				return killed;
			else if (flag_advs == alive)
				return selfKilled;
			else
				return bothDied;
		}
	}

	virtual bool receiveDamage(int damage_) {
		int dev = hp - damage_;
		if (dev > 0) {
			hp = dev;
			return alive;
		}
		hp = 0;
		return died;
	}

	virtual void printGenSpecial() const {}

	virtual void printWarrReport() const {
		std::cout << std::setw(3) << std::setfill('0') << Chronos::hour;
		std::cout << ":55 " << getTribe() << " " << getTypename() << " " << idN
			<< " has " << weaponCounter[Weapon::sword] << " sword "
			<< weaponCounter[Weapon::bomb] << " bomb " << weaponCounter[Weapon::arrow]
			<< " arrow and " << hp << " elements\n"
			<< std::flush;
	}

	virtual int& resetLoc() { return location; }

	static int& resetAttack() { return attack; }

	void printYell() const {
		std::cout << ":40 " << getTribe() << " dragon " << idN
			<< " yelled in city " << location << "\n" << std::flush;
	}

};

int Dragon::attack = kAttackInit;

class Ninja : public Warrior
{
private:
	int idN;
	int hp;
	int weaponCounter[kWeaponNum]{};
	int location = 0;
	bool tribe;
	Equipment* equipment;
	static int attack;

public:
	Ninja(bool tribe_, int idN_, int hp_)
		: idN(idN_), hp(hp_), tribe(tribe_), equipment(new Equipment) {
		equipment->push_back(_receive_weapon(idN % 3));
		weaponCounter[idN % 3]++;
		equipment->push_back(_receive_weapon((idN + 1) % 3));
		weaponCounter[(idN + 1) % 3]++;
	}

	~Ninja() {
		for (auto it = equipment->begin(); it != equipment->end(); ++it)
			delete* it;
		delete equipment;
	}

	int getID() const { return idN; }

	int getHP() const { return hp; }

	const char* getTypename() const { return "ninja"; }

	Warrior::W_Typeid getTypeid() const { return ninja; }

	const char* getTribe() const {
		if (tribe == RedTribe) return "red";
		return "blue";
	}

	bool getTribe(bool) const {
		return tribe;
	}

	int getLoc() const {
		return location;
	}

	int getAttack() const {
		return attack;
	}

	int* getWpCounter() {
		return weaponCounter;
	}

	Equipment* getEquipment() {
		return equipment;
	}

	void reorderEquipment() {
		equipment->sort(_weapon_compare);
	}

	bool equipmentEmpty() {
		return equipment->empty();
	}

	void warriorMove() {
		if (tribe == RedTribe)
			++location;
		else
			--location;
	}

	Warrior::AttackRes warriorAttack(Warrior* adversary_, Equipment::iterator wpIdx_) {
		if (equipment->empty())
			return runOutOfWeapon;
		bool flag_self = alive, flag_advs = alive;
		int damage = (*wpIdx_)->useWeapon(attack);
		flag_advs = adversary_->receiveDamage(damage);
		if (damage == 0) return noDamage;
		if (flag_self == alive && flag_advs == alive)
			return bothAlive;
		else {
			if (flag_self == alive)
				return killed;
			else if (flag_advs == alive)
				return selfKilled;
			else
				return bothDied;
		}
	}

	bool receiveDamage(int damage_) {
		int dev = hp - damage_;
		if (dev > 0) {
			hp = dev;
			return alive;
		}
		hp = 0;
		return died;
	}

	void printGenSpecial() const {};

	void printWarrReport() const {
		std::cout << std::setw(3) << std::setfill('0') << Chronos::hour;
		std::cout << ":55 " << getTribe() << " " << getTypename() << " " << idN
			<< " has " << weaponCounter[Weapon::sword] << " sword "
			<< weaponCounter[Weapon::bomb] << " bomb " << weaponCounter[Weapon::arrow]
			<< " arrow and " << hp << " elements\n"
			<< std::flush;
	}

	int& resetLoc() { return location; }

	static int& resetAttack() { return attack; }
};

int Ninja::attack = kAttackInit;

class Iceman : public Warrior
{
private:
	int idN;
	int hp;
	int weaponCounter[kWeaponNum]{};
	int location = 0;
	bool tribe;
	Equipment* equipment;
	static int attack;

public:
	Iceman(bool tribe_, int idN_, int hp_)
		: idN(idN_), hp(hp_), tribe(tribe_), equipment(new Equipment) {
		equipment->push_back(_receive_weapon(idN % 3));
		weaponCounter[idN % 3]++;
	}

	~Iceman() {
		for (auto it = equipment->begin(); it != equipment->end(); ++it)
			delete* it;
		delete equipment;
	}

	int getID() const { return idN; }

	int getHP() const { return hp; }

	const char* getTypename() const { return "iceman"; }

	Warrior::W_Typeid getTypeid() const { return iceman; }

	const char* getTribe() const {
		if (tribe == RedTribe) return "red";
		return "blue";
	}

	bool getTribe(bool) const {
		return tribe;
	}

	int getLoc() const {
		return location;
	}

	int getAttack() const {
		return attack;
	}

	int* getWpCounter() {
		return weaponCounter;
	}

	Equipment* getEquipment() {
		return equipment;
	}

	void reorderEquipment() {
		equipment->sort(_weapon_compare);
	}

	bool equipmentEmpty() {
		return equipment->empty();
	}

	void warriorMove() {
		if (tribe == RedTribe)
			++location;
		else
			--location;
		hp -= hp / 10;
	}

	Warrior::AttackRes warriorAttack(Warrior* adversary_, Equipment::iterator wpIdx_) {
		if (equipment->empty())
			return runOutOfWeapon;
		bool flag_self = alive, flag_advs = alive;
		int damage = (*wpIdx_)->useWeapon(attack);
		flag_advs = adversary_->receiveDamage(damage);
		if ((*wpIdx_)->getTypeid() == Weapon::bomb)
			flag_self = receiveDamage(damage / 2);
		if (damage == 0) return noDamage;
		if (flag_self == alive && flag_advs == alive)
			return bothAlive;
		else {
			if (flag_self == alive)
				return killed;
			else if (flag_advs == alive)
				return selfKilled;
			else
				return bothDied;
		}
	}

	bool receiveDamage(int damage_) {
		int dev = hp - damage_;
		if (dev > 0) {
			hp = dev;
			return alive;
		}
		hp = 0;
		return died;
	}

	void printGenSpecial() const {}

	void printWarrReport() const {
		std::cout << std::setw(3) << std::setfill('0') << Chronos::hour;
		std::cout << ":55 " << getTribe() << " " << getTypename() << " " << idN
			<< " has " << weaponCounter[Weapon::sword] << " sword "
			<< weaponCounter[Weapon::bomb] << " bomb " << weaponCounter[Weapon::arrow]
			<< " arrow and " << hp << " elements\n"
			<< std::flush;
	}

	int& resetLoc() { return location; }

	static int& resetAttack() { return attack; }
};

int Iceman::attack = kAttackInit;






class Lion : public Warrior
{
private:
	int idN;
	int hp;
	int weaponCounter[kWeaponNum]{};
	int location = 0;
	int loyalty;
	bool tribe;
	Equipment* equipment;
	static int attack;
	static int loyalDec;

public:
	Lion(bool tribe_, int idN_, int hp_, int mana_resv_)
		: idN(idN_), hp(hp_), loyalty(mana_resv_), tribe(tribe_),
		equipment(new Equipment)
	{
		equipment->push_back(_receive_weapon(idN % 3));
		weaponCounter[idN % 3]++;
	}

	~Lion() {
		for (auto it = equipment->begin(); it != equipment->end(); ++it)
			delete* it;
		delete equipment;
	}

	int getID() const { return idN; }

	int getHP() const { return hp; }

	const char* getTypename() const { return "lion"; }

	Warrior::W_Typeid getTypeid() const { return lion; }

	const char* getTribe() const {
		if (tribe == RedTribe) return "red";
		return "blue";
	}

	bool getTribe(bool) const {
		return tribe;
	}

	int getLoc() const {
		return location;
	}

	int getAttack() const {
		return attack;
	}

	int* getWpCounter() {
		return weaponCounter;
	}

	int getLoyalty() const {
		return loyalty;
	}

	Equipment* getEquipment() {
		return equipment;
	}

	void reorderEquipment() {
		equipment->sort(_weapon_compare);
	}

	bool equipmentEmpty() {
		return equipment->empty();
	}

	void warriorMove() {
		if (tribe == RedTribe)
			++location;
		else
			--location;
		loyalty -= loyalDec;
	}

	Warrior::AttackRes warriorAttack(Warrior* adversary_, Equipment::iterator wpIdx_) {
		if (equipment->empty())
			return runOutOfWeapon;
		bool flag_self = alive, flag_advs = alive;
		int damage = (*wpIdx_)->useWeapon(attack);
		flag_advs = adversary_->receiveDamage(damage);
		if ((*wpIdx_)->getTypeid() == Weapon::bomb)
			flag_self = receiveDamage(damage / 2);
		if (damage == 0) return noDamage;
		if (flag_self == alive && flag_advs == alive)
			return bothAlive;
		else {
			if (flag_self == alive)
				return killed;
			else if (flag_advs == alive)
				return selfKilled;
			else
				return bothDied;
		}
	}

	bool receiveDamage(int damage_) {
		int dev = hp - damage_;
		if (dev > 0) {
			hp = dev;
			return alive;
		}
		hp = 0;
		return died;
	}

	void printGenSpecial() const {
		std::cout << "Its loyalty is " << loyalty << "\n" << std::flush;
	}

	void printWarrReport() const {
		std::cout << std::setw(3) << std::setfill('0') << Chronos::hour;
		std::cout << ":55 " << getTribe() << " " << getTypename() << " " << idN
			<< " has " << weaponCounter[Weapon::sword] << " sword "
			<< weaponCounter[Weapon::bomb] << " bomb " << weaponCounter[Weapon::arrow]
			<< " arrow and " << hp << " elements\n"
			<< std::flush;
	}

	int& resetLoc() { return location; }

	static int& resetAttack() { return attack; }

	static int& resetLoyalDec() { return loyalDec; }
};

int Lion::attack = kAttackInit;
int Lion::loyalDec = NULL;








class Wolf : public Warrior
{
private:
	int idN;
	int hp;
	int weaponCounter[kWeaponNum]{};
	int location = 0;
	bool tribe;
	Equipment* equipment;
	static int attack;

public:
	Wolf(bool tribe_, int idN_, int hp_)
		: idN(idN_), hp(hp_), tribe(tribe_), equipment(new Equipment)
	{ /*wolf receive no equipment at born*/
	}

	~Wolf() {
		for (auto it = equipment->begin(); it != equipment->end(); ++it)
			delete* it;
		delete equipment;
	}

	int getID() const { return idN; }

	int getHP() const { return hp; }

	const char* getTypename() const { return "wolf"; }

	Warrior::W_Typeid getTypeid() const { return wolf; }

	const char* getTribe() const {
		if (tribe == RedTribe) return "red";
		return "blue";
	}

	bool getTribe(bool) const {
		return tribe;
	}

	int getLoc() const {
		return location;
	}

	int getAttack() const {
		return attack;
	}

	int* getWpCounter() {
		return weaponCounter;
	}

	Equipment* getEquipment() {
		return equipment;
	}

	void reorderEquipment() {
		equipment->sort(_weapon_compare);
	}

	bool equipmentEmpty() {
		return equipment->empty();
	}

	void warriorMove() {
		if (tribe == RedTribe)
			++location;
		else
			--location;
	}

	Warrior::AttackRes warriorAttack(Warrior* adversary_, Equipment::iterator wpIdx_) {
		if (equipment->empty())
			return runOutOfWeapon;
		bool flag_self = alive, flag_advs = alive;
		int damage = (*wpIdx_)->useWeapon(attack);
		flag_advs = adversary_->receiveDamage(damage);
		if ((*wpIdx_)->getTypeid() == Weapon::bomb)
			flag_self = receiveDamage(damage / 2);
		if (damage == 0) return noDamage;
		if (flag_self == alive && flag_advs == alive)
			return bothAlive;
		else {
			if (flag_self == alive)
				return killed;
			else if (flag_advs == alive)
				return selfKilled;
			else
				return bothDied;
		}
	}

	bool receiveDamage(int damage_) {
		int dev = hp - damage_;
		if (dev > 0) {
			hp = dev;
			return alive;
		}
		hp = 0;
		return died;
	}

	void printGenSpecial() const {}

	void printWarrReport() const {
		std::cout << std::setw(3) << std::setfill('0') << Chronos::hour;
		std::cout << ":55 " << getTribe() << " " << getTypename() << " " << idN
			<< " has " << weaponCounter[Weapon::sword] << " sword "
			<< weaponCounter[Weapon::bomb] << " bomb " << weaponCounter[Weapon::arrow]
			<< " arrow and " << hp << " elements\n"
			<< std::flush;
	}

	int& resetLoc() { return location; }

	static int& resetAttack() { return attack; }

	void wolfTakeWeapon(Warrior* taked) {
		Equipment* adEquip = taked->getEquipment();
		int* adWpCounter = taked->getWpCounter();
		int maxTakeNum = kMaxWeaponNum - equipment->size();
		if (maxTakeNum == 0 || adEquip->size() == 0) return;
		adEquip->sort(Warrior::_takeWp_compare);
		auto it = adEquip->begin();
		int wpidN = (*it)->getTypeid();
		int  takeNum = 0;
		for (;
			it != adEquip->end() &&
			(*it)->getTypeid() == wpidN &&
			takeNum < maxTakeNum;
			++takeNum) {
			equipment->push_front(*it);
			weaponCounter[wpidN]++;
			it = adEquip->erase(it);
			adWpCounter[wpidN]--;
		}
		const char* wptypename = (*(equipment->begin()))->getTypename();
		std::cout << std::setw(3) << std::setfill('0') << Chronos::hour;
		std::cout << ":35 " << getTribe() << " wolf "
			<< idN << " took " << takeNum << " "
			<< wptypename << " from " << taked->getTribe() << " "
			<< taked->getTypename() << " " << taked->getID()
			<< " in city " << location << "\n" << std::flush;
	}
};

int Wolf::attack = kAttackInit;







class HeadQuarter
{
private:
	int mana;//4
	const int* genOrder;//4
	int idCounter = 1;//4
	int genLog = 0;//4
	bool tribe;//1
	bool stopFlag = true;//1
	static const int* initHPs;

public:
	HeadQuarter(bool tribe_, int mana_, const int* genOrd_)
		: mana(mana_), genOrder(genOrd_), tribe(tribe_)
	{}

	int getMana() { return mana; }

	Warrior* generateWarrior() {
		int idx = _next_idx();
		if (stopFlag && _check_mana_reservoir(idx)) {
			Warrior* ret = _select_warrior_generation(idx);
			_print_GenWarr(ret);
			++idCounter;
			return ret;
		}
		else if (stopFlag) {
			stopFlag = false;
		}
		return nullptr;
	}

	static const int*& resetInitHPs() { return initHPs; }

private:
	const char* _get_tribe() {
		if (tribe) return "red";
		return "blue";
	}

	int _next_idx() {
		return genOrder[(genLog++) % 5];
	}

	bool _check_mana_reservoir(int idx_) {
		int dev = mana - initHPs[idx_];
		if (dev >= 0) {
			mana = dev;
			return true;
		}
		return false;
	}

	Warrior* _select_warrior_generation(int idx_) {
		switch (idx_) {
		case Warrior::dragon:
			return new Dragon{ tribe, idCounter, initHPs[idx_],
							  mana /*different param*/ };
			break;
		case Warrior::ninja:
			return new Ninja{ tribe, idCounter, initHPs[idx_] };
			break;
		case Warrior::iceman:
			return new Iceman{ tribe, idCounter, initHPs[idx_] };
			break;
		case Warrior::lion:
			return new Lion{ tribe, idCounter, initHPs[idx_],
							mana /*different param*/ };
			break;
		case Warrior::wolf:
			return new Wolf{ tribe, idCounter, initHPs[idx_] };
			break;
		default:
			return nullptr;
		}
	}

	void _print_GenWarr(const Warrior* warr_) {
		std::cout << std::setw(3) << std::setfill('0') << Chronos::hour;
		std::cout << ":00 " << _get_tribe() << " " << warr_->getTypename()
			<< " " << idCounter << " born\n" << std::flush;
		warr_->printGenSpecial();
	}

	void _print_GenStop() {
		std::cout << std::setw(3) << std::setfill('0') << Chronos::hour << " ";
		std::cout << _get_tribe() << " headquarter stops making warriors\n"
			<< std::flush;
	}
};

const int* HeadQuarter::initHPs = nullptr;








class BattleField
{
	enum BattleRes : int {
		deuce = 3,
		dualDeath = 2,
		win = 1,
		lose = 0
	};

private:
	int city;
	Warrior* warrRed,
		* warrBlu;

public:
	BattleField(Warrior* w1, Warrior* w2)
		: city(w1->getLoc())
	{
		warrRed = w1->getTribe(true) ? w1 : w2;
		warrBlu = w1->getTribe(true) ? w2 : w1;
	}

	void initiateBattle() {
		if (!_before_battle()) return;

		BattleRes flagBattRes = _battle_loop();

		_after_battle(flagBattRes);
	}

private:
	bool _before_battle() {
		if (warrRed->getHP() == 0 || warrBlu->getHP() == 0) return false;
		warrRed->reorderEquipment();
		warrBlu->reorderEquipment();
		return true;
	}

	BattleRes _battle_loop() {
		Warrior* firstAttacker,
			* secondAttacker;
		bool isCityOdd = city / 2 == (city - 1) / 2 && city > 0;
		firstAttacker = isCityOdd ? warrRed : warrBlu;
		secondAttacker = isCityOdd ? warrBlu : warrRed;

		Equipment* eq1 = firstAttacker->getEquipment();
		Equipment* eq2 = secondAttacker->getEquipment();
		Equipment::iterator eqIt1 = eq1->begin();
		Equipment::iterator eqIt2 = eq2->begin();
		int* wpC1 = firstAttacker->getWpCounter();
		int* wpC2 = secondAttacker->getWpCounter();
		Warrior::AttackRes flag1, flag2;
		int NDCount1 = 0, NDCount2 = 0;
		while (true) {
			if (!eq1->empty()) {
				if (eqIt1 == eq1->end())
					eqIt1 = eq1->begin();
				flag1 = firstAttacker->warriorAttack(secondAttacker, eqIt1);
				if ((*eqIt1)->getDurability() == 0) {
					wpC1[(*eqIt1)->getTypeid()]--;
					eqIt1 = eq1->erase(eqIt1);
				}
				else ++eqIt1;

				if (flag1 >= Warrior::noDamage)
					++NDCount1;
				else if (flag1 <= Warrior::bothDied)
					return _switch_AttackRes(flag1);
			}
			else ++NDCount1;
			if (!eq2->empty()) {
				if (eqIt2 == eq2->end())
					eqIt2 = eq2->begin();
				flag2 = secondAttacker->warriorAttack(firstAttacker, eqIt2);
				if ((*eqIt2)->getDurability() == 0) {
					wpC2[(*eqIt2)->getTypeid()]--;
					eqIt2 = eq2->erase(eqIt2);
				}
				else ++eqIt2;

				if (flag2 >= Warrior::noDamage)
					++NDCount2;
				else if (flag2 <= Warrior::bothDied)
					return _switch_AttackRes(flag2);
			}
			else ++NDCount2;
			if (NDCount1 > kMaxWeaponNum && NDCount2 > kMaxWeaponNum)
				return deuce;
		}
	}

	void _after_battle(BattleRes flag_) {
		if (flag_ < dualDeath) {
			bool isRedDead = warrRed->getHP() == 0;
			Warrior* winner = isRedDead ? warrBlu : warrRed;
			Warrior* looser = isRedDead ? warrRed : warrBlu;

			winner->takeWeapon(looser);
		}
		_print_batt_res(flag_);
		if (flag_ != dualDeath) {
			if (warrRed->getTypeid() == Warrior::dragon && warrRed->getHP() != 0) {
				std::cout << std::setw(3) << std::setfill('0') << Chronos::hour;
				static_cast<Dragon*>(warrRed)->printYell();
			}
			if (warrBlu->getTypeid() == Warrior::dragon && warrBlu->getHP() != 0) {
				std::cout << std::setw(3) << std::setfill('0') << Chronos::hour;
				static_cast<Dragon*>(warrBlu)->printYell();
			}
		}
	}

	void _print_batt_res(BattleRes flag_) {
		switch (flag_) {
			bool isRedDead;
			Warrior* winner, * looser;
		case dualDeath:
			std::cout << std::setw(3) << std::setfill('0') << Chronos::hour;
			std::cout << ":40 both red " << warrRed->getTypename() << " "
				<< warrRed->getID() << " and blue " << warrBlu->getTypename()
				<< " " << warrBlu->getID() << " died in city " << city
				<< "\n" << std::flush;
			break;
		case win: /* win and lose can use same argument*/
		case lose:
			isRedDead = warrRed->getHP() == 0;
			winner = isRedDead ? warrBlu : warrRed;
			looser = isRedDead ? warrRed : warrBlu;
			std::cout << std::setw(3) << std::setfill('0') << Chronos::hour;
			std::cout << ":40 " << winner->getTribe() << " "
				<< winner->getTypename() << " "
				<< winner->getID() << " killed "
				<< looser->getTribe() << " "
				<< looser->getTypename() << " "
				<< looser->getID()
				<< " in city " << city
				<< " remaining " << winner->getHP()
				<< " elements\n" << std::flush;
			break;
		case deuce:
			std::cout << std::setw(3) << std::setfill('0') << Chronos::hour;
			std::cout << ":40 both red " << warrRed->getTypename() << " "
				<< warrRed->getID() << " and blue " << warrBlu->getTypename()
				<< " " << warrBlu->getID() << " were alive in city " << city
				<< "\n" << std::flush;
			break;
		default:
			std::cout << "when printing battle result, error happened: "
				<< flag_ << "\n" << std::flush;
		}
	}

	BattleRes _switch_AttackRes(Warrior::AttackRes attackRes_) {
		switch (attackRes_) {
		case Warrior::bothDied: return dualDeath; break;
		case Warrior::killed: return win; break;
		case Warrior::selfKilled: return lose; break;
		}
	}

};






class WorldMap : public Chronos
{
public:
	enum stopSign : bool {
		timeStop = true,
		timeFlow = false,
		HQtaked = true
	};

private:
	HeadQuarter* HQRed, * HQBlu;
	CityField* cityField;
	static int cityRange;
	static int stopMinu;

public:
	WorldMap(HeadQuarter* HQRed_, HeadQuarter* HQBlu_)
		: HQRed(HQRed_), HQBlu(HQBlu_),
		cityField(new CityField)
	{}

	~WorldMap() {
		for (auto it = cityField->begin(); it != cityField->end(); ++it)
			delete* it;
		delete cityField;
	}

	stopSign newbornEnterCity() {
		Warrior* newbornR = HQRed->generateWarrior();
		if (newbornR != nullptr) {
			newbornR->resetLoc() = 0;
			cityField->push_front(newbornR);
		}
		Warrior* newbornB = HQBlu->generateWarrior();
		if (newbornB != nullptr) {
			newbornB->resetLoc() = cityRange + 1;
			cityField->push_back(newbornB);
		}
		return _check_min(5);
	}

	stopSign lionSpecialFlee() {
		for (auto it = cityField->begin();
			it != cityField->end(); ) {
			if ((*it)->getLoyalty() <= 0) {
				Warrior* fleer = *it;
				std::cout << std::setw(3) << std::setfill('0') << hour;
				std::cout << ":05 " << fleer->getTribe() << " lion "
					<< fleer->getID() << " ran away\n" << std::flush;
				delete* it;
				it = cityField->erase(it);
			}
			else
				++it;
		}
		return _check_min(5);
	}

	stopSign warriorMarch() {
		if (cityField->empty()) return _check_min(5);
		cityField->sort(_compare_warrLoc);
		for (auto it = cityField->begin(); it != cityField->end(); ++it) {
			(*it)->warriorMove();
		}
		cityField->sort(_compare_warrLoc);
		auto itlf = cityField->begin();
		auto itrt = cityField->end();
		Warrior* reacher = nullptr;
		int locTmp = (*itlf)->getLoc();
		if (locTmp == 0 || locTmp > cityRange) {
			reacher = *itlf;
			_warrior_reach_HQ(reacher);
		}
		else
			_print_marchMessage(*itlf);
		if (--itrt != itlf) {
			for (++itlf; itlf != itrt; ++itlf)
				_print_marchMessage(*itlf);
			if ((*itrt)->getLoc() <= cityRange)
				_print_marchMessage(*itrt);
			else {
				reacher = *itrt;
				_warrior_reach_HQ(reacher);
			}
		}
		if (reacher != nullptr) {
			if (stopSign ss = _check_min(5))
				return ss;
			return WorldMap::HQtaked;
		}
		return _check_min(5);
	}

	stopSign wolfSpecialTkWp() {
		if (cityField->empty()) return _check_min(25);
		auto itrt = cityField->begin();
		auto itlf = itrt++;
		for (; itrt != cityField->end(); ++itlf, ++itrt) {
			if ((*itlf)->getLoc() == (*itrt)->getLoc())
				_wolf_take_weapon(*itlf, *itrt);
		}
		return _check_min(25);
	}

	stopSign matchBattle() {
		if (cityField->empty()) return _check_min(5);
		auto itrt = cityField->begin();
		auto itlf = itrt++;
		for (; itrt != cityField->end(); ++itlf, ++itrt) {
			if ((*itlf)->getLoc() == (*itrt)->getLoc()) {
				BattleField battle{ *itlf, *itrt };
				battle.initiateBattle();
			}
		}
		return _check_min(5);
	}

	stopSign hQReport() {
		std::cout << std::setw(3) << std::setfill('0') << hour;
		std::cout << ":50 " << HQRed->getMana()
			<< " elements in red headquarter\n" << std::flush;
		std::cout << std::setw(3) << std::setfill('0') << hour;
		std::cout << ":50 " << HQBlu->getMana()
			<< " elements in blue headquarter\n" << std::flush;
		return _check_min(10);
	}

	stopSign warriorReport() {
		auto it = cityField->begin();
		while (it != cityField->end()) {
			if ((*it)->getHP() == 0) {
				delete* it;
				it = cityField->erase(it);
			}
			else {
				(*it)->printWarrReport();
				++it;
			}
		}
		++Chronos::hourFlow;
		return _check_min(5);
	}

	static void setSekaiClock(int stopTime_) {
		stopMinu = stopTime_;
		Chronos::hourFlow = 0;
		Chronos::minuteFlow = 0;
	}

	static void resetCityRange(int cityRange_) {
		cityRange = cityRange_;
	}

	static int getCityRange() { return WorldMap::cityRange; }

private:
	stopSign _check_min(int minuPlus) {
		if (Chronos::minuteFlow == stopMinu) {
			Chronos::minuteFlow += minuPlus;
			return timeStop;
		}
		Chronos::minuteFlow += minuPlus;
		return timeFlow;
	}

	static bool _compare_warrLoc(const Warrior* w1, const Warrior* w2) {
		int loc1 = w1->getLoc();
		int loc2 = w2->getLoc();
		if (loc1 != loc2)
			return loc1 < loc2;
		return w1->getTribe(true);
	}

	void _print_marchMessage(Warrior* warr_) {
		std::cout << std::setw(3) << std::setfill('0') << hour;
		std::cout << ":10 " << warr_->getTribe() << " "
			<< warr_->getTypename() << " " << warr_->getID()
			<< " marched to city " << warr_->getLoc()
			<< " with " << warr_->getHP() << " elements and force "
			<< warr_->getAttack() << "\n" << std::flush;
	}

	void _warrior_reach_HQ(Warrior* reacher) {
		const char* myTribe = reacher->getTribe();
		const char* adTribe = reacher->getTribe(true) ? "blue" : "red";
		std::cout << std::setw(3) << std::setfill('0') << hour;
		std::cout << ":10 " << myTribe << " " << reacher->getTypename() << " "
			<< reacher->getID() << " reached " << adTribe << " headquarter with "
			<< reacher->getHP() << " elements and force "
			<< reacher->getAttack() << "\n" << std::flush;
		std::cout << std::setw(3) << std::setfill('0') << hour;
		std::cout << ":10 " << adTribe << " headquarter was taken\n" << std::flush;
	}

	void _wolf_take_weapon(Warrior* warr1, Warrior* warr2) {
		int typeid1 = warr1->getTypeid(),
			typeid2 = warr2->getTypeid();
		if (typeid1 != typeid2) {
			if (typeid1 == Warrior::wolf || typeid2 == Warrior::wolf) {
				bool isW1Wolf = typeid1 == Warrior::wolf;
				Wolf* taker = static_cast<Wolf*>(isW1Wolf ? warr1 : warr2);
				Warrior* taked = isW1Wolf ? warr2 : warr1;
				taker->wolfTakeWeapon(taked);
			}
		}
	}
};

int WorldMap::cityRange = NULL;
int WorldMap::stopMinu = NULL;











//------------------------------------ MAIN ------------------------------------------
int main() {
    bool swt_rein = 1;      // whether reopen stdin;
    bool swt_reout = 1;     // whether reopen stdout;
    bool swt_va = 1;        // whether verify answer;
    FILE* rein = nullptr, * reout = nullptr;
    if (swt_rein) rein = freopen("datapub_in.txt", "r", stdin);
    if (swt_reout) reout = freopen("out.txt", "w", stdout);
    LARGE_INTEGER t0, t1;
    QueryPerformanceCounter(&t0);
    //-----------------------------main codes below-----------------------------------
    
	int caseN;
	std::cin >> caseN;
	for (int k = 1; k <= caseN; ++k) {
		std::cout << "Case " << k << ":\n" << std::flush;
		int manaIn, cityN, loyalDecIn, stopTime;
		std::cin >> manaIn >> cityN >> loyalDecIn >> stopTime;
		WorldMap::resetCityRange(cityN);
		Lion::resetLoyalDec() = loyalDecIn;
		int initHPIn[kWarriorsNum];
		for (int& i : initHPIn)
			std::cin >> i;
		HeadQuarter::resetInitHPs() = initHPIn;
		std::cin >> Dragon::resetAttack();
		std::cin >> Ninja::resetAttack();
		std::cin >> Iceman::resetAttack();
		std::cin >> Lion::resetAttack();
		std::cin >> Wolf::resetAttack();
		HeadQuarter HQRed{ RedTribe, manaIn, predef_genOrd[RedTribe] };
		HeadQuarter HQBlu{ BluTribe, manaIn, predef_genOrd[BluTribe] };
		WorldMap::setSekaiClock(stopTime);
		WorldMap myWorld{ &HQRed, &HQBlu };
		while (true) {
			if (myWorld.newbornEnterCity())
				break;
			if (myWorld.lionSpecialFlee())
				break;
			if (myWorld.warriorMarch())
				break;
			if (myWorld.wolfSpecialTkWp())
				break;
			if (myWorld.matchBattle())
				break;
			if (myWorld.hQReport())
				break;
			if (myWorld.warriorReport())
				break;
		}
	}

    //-----------------------------main codes above-----------------------------------
    QueryPerformanceCounter(&t1);
    if (reout) reout = freopen("CON", "a", stdout);
	std::cout << "\n--------------- Main complete. ---------------\n" << std::flush;
    printPerfCounter(t0, t1, "Total  ");
    if (swt_va) verifyAnswer("answer.txt", "out.txt"); // wrong line starts from 1;
    if (rein) fclose(stdin);
    if (reout) fclose(stdout);
    return 0;
}