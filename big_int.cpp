#include"big_int.h"
/*
this is constructor.
it initialize the MSB and lsb to null
Flag to true
and size to 0
*/
BIG_INT:: BIG_INT()
{
	big_int_msb = NULL;
	big_int_lsb = NULL;
	flag = true;
	size = 0;
}
/*
Destructor
deletes the entire number
*/
BIG_INT::~BIG_INT()
{
	if (big_int_msb == NULL)
		delete big_int_msb;
	else {
		big_int *temp = big_int_msb;
		while (big_int_msb != NULL)
		{
			big_int_msb = big_int_msb->next;
			delete temp;
			temp = big_int_msb;
		}
	}
	big_int_msb = big_int_lsb = NULL;
}
/* returns msb pointer*/
big_int* BIG_INT:: return_msb()
{
	return big_int_msb;
}
/*returns lsb pointer*/
big_int* BIG_INT:: return_lsb()
{
	return big_int_lsb;
}

/* returns msb pointer*/
big_int*& BIG_INT::return_msb_ref()
{
	return big_int_msb;
}
/*returns lsb pointer*/
big_int*& BIG_INT::return_lsb_ref()
{
	return big_int_lsb;
}
/*returns size*/
int BIG_INT::return_size()
{
	return size;
}
/*returns flag*/
bool BIG_INT::return_flag()
{
	return big_int_msb->flag;
}
/*set flag*/
void BIG_INT::set_flag(bool x)
{
	big_int_msb->flag = x;
	//flag = x;
}
/*add digit to number
if char isnt minus sign then adds the digit to number
else set flag to minus
*/
void BIG_INT::add_digit(char a)
{
	if (a != '-')
	{
		big_int *curr = new big_int;
		curr->int_ = a;
		curr->flag = flag;
		flag = true;
		if (big_int_msb == NULL)
		{
			big_int_msb = curr;
			big_int_lsb = big_int_msb;
			curr = NULL;
		}
		else
		{
			curr->pre = big_int_lsb;
			big_int_lsb->next = curr;
			curr = NULL;
			big_int_lsb = big_int_lsb->next;
		}
		size++;
	}
	else
		flag = false;
}
void BIG_INT::add_for_arthematic(char a)
{
	big_int *curr = new big_int;
	curr->int_ = a;
	if (big_int_msb == NULL)
	{
		big_int_msb = curr;
		big_int_lsb = big_int_msb;
		curr = NULL;
	}
	else
	{
		curr->next = big_int_msb;
		big_int_msb = curr;
		curr = NULL;
	}
	size++;
}
/*>> operator overloaded for input*/
istream &operator>>(istream  &input, BIG_INT &var) {
	input.clear(); // clears the input stream
	/* checks the msb if its not null 
	then we have to delete the already existing number first */
	if (var.return_msb() != NULL) 
	{
		// deleting the existing nummber
		big_int *temp = var.return_msb();
		while (var.return_msb() != NULL)
		{
			var.return_msb_ref() = var.return_msb()->next;
			delete temp;
			temp = var.return_msb();
		}
		var.return_msb_ref() = var.return_lsb_ref() = NULL;
	}
	char a = 0;
	while (a < '0' || a > '9')
	{
		// checks for minus sign 
		// incase number is negative
		a = getchar();
		if (a == '-')
			break;
	}
	while (a != '\n')
	{
		// add digits to number if found newline char breaks
		var.add_digit(a);
		a = 0;
		while (a < '0' || a>'9')
		{
			a = getchar();
			if (a == '\n')
				break;
		}
	}
	return input;
}
/*<< operator overloaded for output*/
ostream &operator<<(ostream  &output, BIG_INT &var)
{
	// check if flag is false
	// false means number is negative so outputs the negative sign first
	big_int *temp = var.return_msb();
	if (temp->flag == false)
	{
		output << "-";
	}
	// output the number
	while (temp != NULL)
	{
		output << temp->int_;
		temp = temp->next;
	}
	return output;
}
/*== operator overloaded for checking equality of two numbers*/
bool BIG_INT:: operator==(BIG_INT &var1)
{
	// checks if both numbers are negative or positive 
	// if numbers have opposite sign then returns false
	if (big_int_msb->flag != var1.return_msb()->flag)
		return false;
	// checks the size of both numbers
	// if both arent equal returns false
	else if (size != return_size())
		return false;
	// if both have same size and sign the checks further
	// checks the corresponding digits if any digit is not equal then returns false
	else {
		big_int*temp1 = big_int_msb;
		big_int*temp2 = var1.return_msb();
		while (temp1 != NULL && temp2 != NULL)
		{
			if (temp1->int_ != temp2->int_)
				return false;
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
	}
	// return true means all three conditions for checking equality has been completed
	// and numbers are equal
	return true;
}
/*!= operator overloaded for checking Inequality of two numbers*/
bool BIG_INT::operator!=(BIG_INT &var1)
{
	// checks if both numbers are negative or positive 
	// if numbers have equal sign then returns true
	if (big_int_msb->flag != var1.return_msb()->flag)
		return true;
	// checks the size of both numbers
	// if both arent equal returns true
	else if (size != return_size())
		return true;
	// if both have same size and sign the checks further
	// checks the corresponding digits if any digit is not equal then returns true
	else {
		big_int*temp1 = big_int_msb;
		big_int*temp2 = var1.return_msb();
		while (temp1 != NULL && temp2 != NULL)
		{
			if (temp1->int_ != temp2->int_)
				return true;
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
	}
	// return false means all three conditions for checking equality has been completed
	// and numbers are not equal
	return false; 
}
/*> operator overloaded for checking if first Number is greater*/
bool BIG_INT::operator>(BIG_INT &var1)
{
	// checking if first number is positive and second is negative then return true
	if (big_int_msb->flag == true && var1.return_msb()->flag == false)
		return true;
	// checking if first number is negative and second is positive then return false
	else if (big_int_msb->flag == false && var1.return_msb()->flag == true)
		return false;
	// checking if both have same sign i.e +ve
	// and if size of first number is greater than size of second number then
	// return true
	else if ((big_int_msb->flag == true && var1.return_msb()->flag == true) && size > var1.return_size())
		return true;
	// checking if both have same sign i.e +ve
	// and if size of first number is lesser than size of second number then
	// return false
	else if ((big_int_msb->flag == true && var1.return_msb()->flag == true) && size < var1.return_size())
		return false;
	// checking if both have same sign i.e -ve
	// and if size of first number is lesser than size of second number then
	// return false
	else if ((big_int_msb->flag == false && var1.return_msb()->flag == false) && size < var1.return_size())
		return true;
	// checking if both have same sign i.e -ve
	// and if size of first number is greater than size of second number then
	// return false
	else if ((big_int_msb->flag == false && var1.return_msb()->flag == false) && size > var1.return_size())
		return false;
	// if both numbers have same sign i.e -ve
	// and both have same sign
	// then check corresponding digits
	// if digit of first number is lesser than then return true
	else if (big_int_msb->flag == false && var1.return_msb()->flag == false && size == var1.return_size()) {
		big_int*temp1 = big_int_msb;
		big_int*temp2 = var1.return_msb();
		while (temp1 != NULL && temp2 != NULL)
		{
			if (temp1->int_ < temp2->int_)
				return true;
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		return false;
	}
	// if both numbers have same sign i.e +ve
	// and both have same sign
	// then check corresponding digits
	// if digit of first number is greater than then return true
	else {
		big_int*temp1 = big_int_msb;
		big_int*temp2 = var1.return_msb();
		bool x = true;
		while (temp1 != NULL && temp2 != NULL)
		{
			if (temp1->int_ > temp2->int_)
				return true;
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		return false;
	}
}
/*< operator overloaded for checking if first Number is lesser*/
bool BIG_INT::operator<(BIG_INT &var1)
{
	// checking if first number is -ve and second is +ve then return true
	if (big_int_msb->flag == false && var1.return_msb()->flag == true)
		return true;
	// checking if first number is positive and second is negative then return false
	else if (big_int_msb->flag == true && var1.return_msb()->flag == false)
		return false;
	// checking if both numbers have same sign i.e +ve
	// and size of first number is greater than second number 
	// then return false
	else if ((big_int_msb->flag == true && var1.return_msb()->flag == true) && size > var1.return_size())
		return false;
	// checking if both numbers have same sign i.e +ve
	// and size of first number is less than second number 
	// then return true
	else if ((big_int_msb->flag == true && var1.return_msb()->flag == true) && size < var1.return_size())
		return true;
	// checking if both numbers have same sign i.e -ve
	// and size of first number is greater than second number 
	// then return false
	else if ((big_int_msb->flag == false && var1.return_msb()->flag == false) && size < var1.return_size())
		return false;
	// if both have same sign i.e -ve
	// and same size
	// then checks the corresponding digits
	// if digit of first number is greater than second
	// then returns true
	else if (big_int_msb->flag == false && var1.return_msb()->flag == false&& size == var1.return_size()) {
		big_int*temp1 = big_int_msb;
		big_int*temp2 = var1.return_msb();
		while (temp1 != NULL && temp2 != NULL)
		{
			if (temp1->int_ > temp2->int_)
				return true;
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		return false;
	}
	// if both have same sign i.e +ve
	// and same size
	// then checks the corresponding digits
	// if digit of first number is lesser than second
	// then returns true
	else {
		big_int*temp1 = big_int_msb;
		big_int*temp2 = var1.return_msb();
		while (temp1 != NULL && temp2 != NULL)
		{
			if (temp1->int_ < temp2->int_)
				return true;
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		return false;
	}

}
/*>= operator overloaded for checking if first Number is greater or equal */
bool BIG_INT::operator>=(BIG_INT &var1)
{
	// calls > overloaded function
	// calls == overloaded function
	// returns true if any one gets true
	if (this->operator>(var1) == true||this->operator==(var1)==true)
		return true;
	else
		return false;
}
/*<= operator overloaded for checking if first Number is lesser or equal */
bool BIG_INT::operator<=(BIG_INT &var1)
{
	// calls > overloaded function
	// calls == overloaded function
	// returns true if any one gets true
	if (this->operator<(var1) == true|| this->operator==(var1) == true)
		return true;
	else
		return false;
}
/*= operator overloaded to assigning second number to first number*/
void BIG_INT::operator=(BIG_INT &var1) {
	big_int *temp = big_int_msb;
	big_int *temp2 = var1.return_msb_ref();
	// if there's already a number in first number it deletes the number
	if (big_int_msb != NULL)
	{
		big_int *temp = big_int_msb;
		while (temp != NULL)
		{
			big_int_msb=big_int_msb->next;
			delete temp;
			temp = big_int_msb;
		}
		big_int_msb = big_int_lsb = NULL;
	}
	// copies the second numbet to first number
	while (temp2 != NULL)
	{
		add_digit(temp2->int_);
		temp2 = temp2->next;
	}
	big_int_msb->flag = var1.return_msb_ref()->flag;
}
/*add function to add two number and returns the result of addition*/
BIG_INT*& BIG_INT::add(BIG_INT &var1)
{
	BIG_INT *result=new BIG_INT; 
	big_int *temp1 = big_int_lsb;
	big_int *temp2 = var1.return_lsb();
	int carry = 0; 
	// adding the corresponding digits
	while (temp1 != NULL && temp2 != NULL)
	{
		int n1 = temp1->int_ - 48;
		int n2 = temp2->int_ - 48;
		int r = n1 + n2 + carry;
		carry = r / 10;
		r = r % 10;
		result->add_for_arthematic(r + 48);
		temp1 = temp1->pre;
		temp2 = temp2->pre;
	}
	// adding remaining elements from number 1
	while (temp1 == NULL && temp2 != NULL)
	{
		int n1 = 0;
		int n2 = temp2->int_ - 48;
		int r = n1 + n2 + carry;
		carry = r / 10;
		r = r % 10;
		result->add_for_arthematic(r + 48);
		temp2 = temp2->pre;
	}
	// adding the remaining elements from number two
	while (temp1 != NULL && temp2 == NULL)
	{
		int n1 = 0;
		int n2 = temp1->int_ - 48;
		int r = n1 + n2 + carry;
		carry = r / 10;
		r = r % 10;
		result->add_for_arthematic(r + 48);
		temp1 = temp1->pre;
	}
	if (carry != 0)
		result->add_for_arthematic(carry + 48);
	return result;
}
/*add function to sub two numbers and returns the result of subtraction*/
BIG_INT*& BIG_INT::sub(BIG_INT &var1)
{
	bool temp_flag = true;
	big_int *temp1 = NULL;
	big_int *temp2 = NULL;
	BIG_INT *result = new BIG_INT;
	//  assigning the sign of greater number to result
		if (this->operator>(var1) == true || (size > var1.return_size()))
		{
				temp1 = big_int_lsb;
				temp2 = var1.return_lsb();
				temp_flag = return_flag();
		}
		else
		{

			temp1 = var1.return_lsb();
			temp2 = big_int_lsb;
			temp_flag = false;
		}
	int carry = 0;
	// subtracting the lesser number from greater number
	while (temp1 != NULL && temp2 != NULL)
	{
		int n1 = temp1->int_ - 48;
		int n2 = temp2->int_ - 48;

		int r = 0;

		if (n2 > n1)
		{
			big_int *temp3 = temp1->pre;
			while (n2 > n1)
			{
				temp3->int_ -= 1;
				temp3 = temp3->pre;
				n1 = 10 + n1;
			}
		}
		r = n1 - n2;
		r = r - carry;
		carry = r / 10;
		r = r % 10;
		result->add_for_arthematic(r + 48);
		temp1 = temp1->pre;
		temp2 = temp2->pre;
	}
	// remaining digits to result
	while (temp1 == NULL && temp2 != NULL)
	{
		int n1 = 0;
		int n2 = temp2->int_ - 48;
		int r = n2 - n1 - carry;
		carry = r / 10;
		r = r % 10;
		result->add_for_arthematic(r + 48);
		temp2 = temp2->pre;
	}
	while (temp1 != NULL && temp2 == NULL)
	{
		int n1 = 0;
		int n2 = temp1->int_ - 48;
		int r = n2 - n1 - carry;
		carry = r / 10;
		r = r % 10;
		result->add_for_arthematic(r + 48);
		temp1 = temp1->pre;
	}
	if (carry != 0)
		result->add_for_arthematic(carry + 48);
	result->set_flag(temp_flag);
	this; var1;
	return result;
}
/*+ operator overloaded to add two numbers*/
BIG_INT& BIG_INT::operator+(BIG_INT &var)
{
	BIG_INT var1;
	var1.operator=(*this);
	BIG_INT var2;
	var2.operator=(var);
	bool temp_flag = true;
	BIG_INT *result = NULL;
	// check if one number is negative and other is positive than sub the number
	if (var1.big_int_msb->flag == false && var2.return_msb()->flag == true)
	{
		result = var1.sub(var2);
	}
	else if (var1.big_int_msb->flag == true && var2.return_msb()->flag == false)
	{
		result = var1.sub(var2);
	}
	// if both numbers are -ve than add both numbers and assign the sign of greater number to temp_flag
	else if (var1.big_int_msb->flag == false && var2.return_msb()->flag == false)
	{
		result = var1.add(var2);
		if (this->operator>(var2) == true)
		{
			temp_flag = var1.big_int_msb->flag;
		}
		else
		{
			temp_flag = var2.return_msb()->flag;
		}
	}
	else if (var1.big_int_msb->flag == true && var2.return_msb()->flag == true)
	{
		result = var1.add(var2);
	}
	// seting flag of result to temp_flag
	result->set_flag(temp_flag);
	return *result;
	
}
/*- operator overloaded to sub two numbers*/
BIG_INT& BIG_INT::operator-(BIG_INT &var)
{
	BIG_INT var1;
	var1.operator=(*this);
	BIG_INT var2;
	var2.operator=(var);
	bool temp_flag = true;
	BIG_INT *result = NULL;
	// if first number is +ve and other is -ve then adds both number and assign the sign of  greater number to  result
	if (var1.big_int_msb->flag == true && var2.return_msb()->flag == false)
	{
		result = var1.add(var2);
		if(var1.operator>(var2)==true)
			temp_flag = var1.return_flag();
		else
			temp_flag = var2.return_flag();
		result->set_flag(temp_flag);
	}
	// if first number is -ve and other is +ve then adds both number and assign the -ve sign to result
	else if (var1.big_int_msb->flag == false && var2.return_msb()->flag == true)
	{
		result = var1.add(var2);
		temp_flag = false;
		result->set_flag(temp_flag);
	}
	// if both have -ve sign then add the both numbers  and set sign of result negative
	else if (var1.big_int_msb->flag == false && var2.return_msb()->flag == false)
	{
		result = var1.add(var2);
		result->set_flag(false);
	}
	// if both have +ve sign then simply subtract the numbers
	else if (var1.big_int_msb->flag == true && var2.return_msb()->flag == true)
	{
		result = var1.sub(var2);
	}
	return *result;
}
