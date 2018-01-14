#define big_int_h
#ifndef big_int
#include <iostream>
using namespace std;
struct big_int {
	char int_ = '0';
	bool flag = true; //  false for negative and true for positive
	big_int *next = NULL;
	big_int *pre = NULL;
};
class BIG_INT {

	
	big_int *big_int_msb;
	big_int *big_int_lsb;
	bool flag;
	int size;
	
public:
	BIG_INT();
	~BIG_INT();
	big_int *&return_msb();
	big_int *&return_lsb();
	int return_size();
	bool return_flag();
	void set_flag(bool x);
	void add_digit(char a);
	void add_for_arthematic(char a);
	friend istream &operator>>(istream  &input, BIG_INT &var);
	friend ostream &operator<<(ostream  &output, BIG_INT &var);
	bool operator==(BIG_INT&var1);
	bool operator!=(BIG_INT&var1);
	bool operator>(BIG_INT&var1);
	bool operator<(BIG_INT&var1);
	bool operator>=(BIG_INT&var1);
	bool operator<=(BIG_INT&var1);
	void operator=(BIG_INT&var1);
	BIG_INT *&add(BIG_INT &var1);
	BIG_INT *&sub(BIG_INT &var1);
	BIG_INT &operator+(BIG_INT &var1);
	BIG_INT &operator-(BIG_INT &var1);
};
#endif