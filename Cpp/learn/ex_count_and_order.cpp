#include<iostream>
#include<set>
#include<map>
#include<string>
using namespace std;

struct Word {
	int times;
	string wd;
};
struct Rule {
	bool operator () (const Word& w1, const Word& w2) const {
		if (w1.times != w2.times)
			return w1.times > w2.times;
		else
			return w1.wd < w2.wd;
	}
};

int main() {
	string s;
	set<Word, Rule> st;
	map<string, int> mp;
	while (cin >> s)
		++mp[s];	//s是mp的关键字，下标查找或创建pair，自增针对pair的second值进行计数；
	for (map<string, int>::iterator i = mp.begin(); i != mp.end(); ++i) {
		//将map mp中逐个元素插入set st中；
		Word tmp;
		tmp.wd = i->first;
		tmp.times = i->second;
		st.insert(tmp);
	}
	for (set<Word, Rule>::iterator i = st.begin(); i != st.end(); ++i)
		// 逐个输出set st中元素；
		cout << i->wd << " " << i->times << endl;
}

/*
输入大量单词，计数，并按顺序输出；
*/