#include<iostream>
#include<cstring>
using namespace std;

char left[3][7];
char right[3][7];
char result[3][5];
bool isFake(char c, bool light) {
	for (int i = 0; i < 3; ++i){
		if (result[i][0] == 'e'){
			if (strchr(::left[i], c) || strchr(::right[i], c))
				return false;
		}
		else {
			bool f1 = result[i][0] == 'u' && light;
			bool f2 = result[i][0] == 'd' && !light;
			if (f1 || f2) {
				if (strchr(::right[i], c) == nullptr || strchr(::left[i], c))
					return false;
			}
			else {
				if (strchr(::right[i], c) || strchr(::left[i], c) == nullptr)
					return false;
			}
		}
	}
	return true;
}


int main() {
	for (int i = 0; i < 3; ++i)
		cin >> ::left[i] >> ::right[i] >> ::result[i];
	for (char i = 'A'; i < 'Z'; ++i){
		if (isFake(i, true))
			cout << i << " is the fake and it's lighter.\n" << flush;
		else if (isFake(i, false))
			cout << i << " is the fake and it's heavier.\n" << flush;
	}
}