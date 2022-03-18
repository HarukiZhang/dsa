#include "prototype.h"

#include <cstdlib>
#include <utility>

class MyString
{
	// 在此处补充你的代码
	char* buffer;
	int length;
public:
	MyString() : length(0), buffer(nullptr) {}
	~MyString() { if (buffer) delete[] buffer; }
	MyString(const char* instr) {
		if (instr) {
			length = strlen(instr);
			buffer = new char[length + 4];
			strcpy(buffer, instr);
		}
		else {
			length = 0;
			buffer = nullptr;
		}
	}
	MyString(const MyString& cms_) {
		if (cms_.buffer) {
			length = cms_.length;
			buffer = new char[length + 4];
			strcpy(buffer, cms_.buffer);
		}
		else {
			length = 0;
			buffer = nullptr;
		}
	}
	MyString& operator=(const MyString& cms_) {
		if (cms_.buffer) {
			if (buffer) delete[] buffer;
			buffer = new char[cms_.length + 4];
			strcpy(buffer, cms_.buffer);
		}
		length = cms_.length;
		return *this;
	}
	MyString operator+(const MyString& postcms_) const {
		MyString res;
		if (postcms_.buffer) {
			res.length = length + postcms_.length;
			res.buffer = new char[res.length + 4];
			if (buffer)
				strcpy(res.buffer, buffer);
			strcpy(res.buffer + length, postcms_.buffer);
		}
		return res;
	}
	MyString operator+(const char* poststr_) const {
		MyString res;
		if (poststr_) {
			res.length = length + strlen(poststr_);
			res.buffer = new char[res.length + 4];
			if (buffer)
				strcpy(res.buffer, buffer);
			strcpy(res.buffer + length, poststr_);
		}
		return res;
	}
	friend MyString operator+(const char* antstr_, const MyString& postcms_) {
		MyString res;
		if (antstr_) {
			int ant_len = strlen(antstr_);
			res.length = postcms_.length + ant_len;
			res.buffer = new char[res.length + 4];
			strcpy(res.buffer, antstr_);
			if (postcms_.buffer)
				strcpy(res.buffer + ant_len, postcms_.buffer);
		}
		return res;
	}
	MyString& operator+=(const char* poststr_) {
		if (poststr_) {
			int old_len = length;
			length += strlen(poststr_);
			char* resstr = new char[length + 4];
			if (buffer) {
				strcpy(resstr, buffer);
				delete[] buffer;
			}
			strcpy(resstr + old_len, poststr_);
			buffer = resstr;
		}
		return *this;
	}
	MyString& operator+=(const MyString& postcms_) {
		if (postcms_.buffer) {
			int old_len = length;
			length += postcms_.length;
			char* resstr = new char[length + 4];
			if (buffer) {
				strcpy(resstr, buffer);
				delete[] buffer;
			}
			strcpy(resstr + old_len, postcms_.buffer);
			buffer = resstr;
		}
		return *this;
	}
	bool operator<(const MyString& postcms_) const {
		if (this->buffer && postcms_.buffer) {
			int i = 0;
			for (; *(this->buffer + i) == *(postcms_.buffer + i); ++i);
			return *(this->buffer + i) < *(postcms_.buffer + i);
		}
		else if (!(this->buffer || postcms_.buffer)) return false;
		else return this->buffer == nullptr ? true : false;
	}
	bool operator>(const MyString& postcms_) const {
		if (this->buffer && postcms_.buffer) {
			int i = 0;
			for (; *(this->buffer + i) == *(postcms_.buffer + i); ++i);
			return *(this->buffer + i) > *(postcms_.buffer + i);
		}
		else if (!(this->buffer || postcms_.buffer)) return false;
		else return this->buffer == nullptr ? false : true;
	}
	bool operator==(const MyString& postcms_) const {
		if (this->buffer && postcms_.buffer) {
			for (int i = 0; *(this->buffer + i) || *(postcms_.buffer + i); ++i) {
				if (*(this->buffer + i) != *(postcms_.buffer + i))
					return false;
			}
			return true;
		}
		else if (!(this->buffer || postcms_.buffer)) return true;
		else return false;
	}
	char& operator[](int offset) const {return *(buffer + offset);}
	MyString operator()(int start, int sublen) const {
		MyString subms;
		subms.length = sublen;
		subms.buffer = new char[sublen + 4];
		for (int i = 0; i < sublen; ++i)
			*(subms.buffer + i) = *(buffer + (start + i));
		*(subms.buffer + ++sublen) = 0;
		return subms;
	}
	friend std::ostream& operator<<(std::ostream& out, const MyString& cms_) {
		if (cms_.buffer)
			out << cms_.buffer;
		return out;
	}
	// 在此处补充你的代码
};


int main() {
    bool swt_rein = false;
    bool swt_reout = false;
    bool swt_va = false;
    FILE* rein = nullptr, * reout = nullptr;
    if (swt_rein) rein = freopen("in.txt", "r", stdin);
    if (swt_reout) reout = freopen("out.txt", "w", stdout);
    LARGE_INTEGER t0, t1;
    QueryPerformanceCounter(&t0);
    //-----------------------------main codes below-----------------------------------
    
	MyString testa = "abcd-qrst-abcd- uvw xyz";
	std::cout << testa(5, 10) << std::flush;

    //-----------------------------main codes above-----------------------------------
    QueryPerformanceCounter(&t1);
    if (reout) reout = freopen("CON", "a", stdout);
    printf("\n--------------- Main complete. ---------------\n");
    printPerfCounter(t0, t1, "Total  ");
    if (swt_va) verifyAnswer("E:\\Downloads\\out.txt", "out.txt");
    if (rein) fclose(stdin);
    if (reout) fclose(stdout);
    return 0;
}

/*
*/