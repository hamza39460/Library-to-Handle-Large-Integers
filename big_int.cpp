#include"big_int.h"
BIG_INT:: BIG_INT()
{
	big_int_msb = NULL;
	big_int_lsb = NULL;
	flag = true;
	size = 0;
}
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
big_int*& BIG_INT:: return_msb()
{
	return big_int_msb;
}
big_int*& BIG_INT:: return_lsb()
{
	return big_int_lsb;
}
int BIG_INT::return_size()
{
	return size;
}
bool BIG_INT::return_flag()
{
	return big_int_msb->flag;
}
void BIG_INT::set_flag(bool x)
{
	big_int_msb->flag = x;
}
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
istream &operator>>(istream  &input, BIG_INT &var) {
	cin.clear();
	if (var.return_msb() != NULL)
	{
		big_int *temp = var.return_msb();
		while (var.return_msb() != NULL)
		{
			var.return_msb() = var.return_msb()->next;
			delete temp;
			temp = var.return_msb();
		}
		var.return_msb() = var.return_lsb() = NULL;

	}
	char a = 0;
	while (a < '0' || a>'9')
	{
		a = getchar();
		if (a == '-')
			break;
	}
	while (a != '\n')
	{
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
ostream &operator<<(ostream  &output, BIG_INT &var)
{
	big_int *temp = var.return_msb();
	if (temp->flag == false&&temp->int_!='0')
	{
		output << "-";
	}
	while (temp != NULL)
	{
		output << temp->int_;
		temp = temp->next;
	}
	return output;
}
bool BIG_INT:: operator==(BIG_INT&var1)
{
	if (big_int_msb->flag != var1.return_msb()->flag)
		return false;
	else if (size != return_size())
		return false;
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
	return true;
}
bool BIG_INT::operator!=(BIG_INT&var1)
{
	if (big_int_msb->flag != var1.return_msb()->flag)
		return true;
	else if (size != return_size())
		return true;
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
	return false;
}
bool BIG_INT::operator>(BIG_INT&var1)
{
	if (big_int_msb->flag == true && var1.return_msb()->flag == false)
		return true;
	else if (big_int_msb->flag == false && var1.return_msb()->flag == true)
		return false;
	else if ((big_int_msb->flag == true && var1.return_msb()->flag == true) && size > var1.return_size())
		return true;
	else if ((big_int_msb->flag == true && var1.return_msb()->flag == true) && size < var1.return_size())
		return false;
	else if ((big_int_msb->flag == false && var1.return_msb()->flag == false) && size < var1.return_size())
		return true;
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
bool BIG_INT::operator<(BIG_INT&var1)
{
	if (big_int_msb->flag == false && var1.return_msb()->flag == true)
		return true;
	else if (big_int_msb->flag == true && var1.return_msb()->flag == false)
		return false;
	else if ((big_int_msb->flag == true && var1.return_msb()->flag == true) && size > var1.return_size())
		return false;
	else if ((big_int_msb->flag == true && var1.return_msb()->flag == true) && size < var1.return_size())
		return true;
	else if ((big_int_msb->flag == false && var1.return_msb()->flag == false) && size < var1.return_size())
		return false;
	else if (big_int_msb->flag == false && var1.return_msb()->flag == false) {
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
bool BIG_INT::operator>=(BIG_INT&var1)
{
	if (this->operator>(var1) == true)
		return true;
	else if (this->operator==(var1) == true)
		return true;
	else
		return false;
}
bool BIG_INT::operator<=(BIG_INT&var1)
{
	if (this->operator<(var1) == true)
		return true;
	else if (this->operator==(var1) == true)
		return true;
	else
		return false;
}
void BIG_INT::operator=(BIG_INT &var1) {
	big_int *temp = big_int_msb;
	big_int *temp2 = var1.return_msb();
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
	while (temp2 != NULL)
	{
		add_digit(temp2->int_);
		temp2 = temp2->next;
	}
	big_int_msb->flag = var1.return_msb()->flag;
}
BIG_INT*& BIG_INT::add(BIG_INT &var1)
{
	/*static */ BIG_INT *result=new BIG_INT;
	big_int *temp1 = big_int_lsb;
	big_int *temp2 = var1.return_lsb();
	int carry = 0;
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
BIG_INT*& BIG_INT::sub(BIG_INT &var1)
{
	bool temp_flag = true;
	big_int *temp1 = NULL;
	big_int *temp2 = NULL;
	BIG_INT *result = new BIG_INT;
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
			
			temp_flag = var1.return_flag();
		}
	int carry = 0;
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
	return result;
}
BIG_INT& BIG_INT::operator+(BIG_INT &var1)
{
	bool temp_flag = true;
	BIG_INT *result = NULL;
	if (big_int_msb->flag == false && var1.return_msb()->flag == true)
	{
		result = sub(var1);
	}
	else if (big_int_msb->flag == true && var1.return_msb()->flag == false)
	{
		result = sub(var1);
	}
	else if (big_int_msb->flag == false && var1.return_msb()->flag == false)
	{
		result = add(var1);
		if (this->operator>(var1) == true)
		{
			temp_flag = big_int_msb->flag;
		}
		else
		{
			temp_flag = var1.return_msb()->flag;
		}
	}
	else if (big_int_msb->flag == true && var1.return_msb()->flag == true)
	{
		result = add(var1);
	}
	result->set_flag(temp_flag);
	return *result;
	
}
BIG_INT& BIG_INT::operator-(BIG_INT &var1)

{
	bool temp_flag = true;
	BIG_INT *result = NULL;
	if (big_int_msb->flag == false && var1.return_msb()->flag == true)
	{
		result = add(var1);
		temp_flag = false;
		result->set_flag(temp_flag);
	}
	else if (big_int_msb->flag == true && var1.return_msb()->flag == false)
	{
		result = add(var1);
		temp_flag = true;
		result->set_flag(temp_flag);
	}
	else if (big_int_msb->flag == false && var1.return_msb()->flag == false)
	{
		var1.set_flag(true);
		result = sub(var1);
		var1.set_flag(false);
		
	}
	else if (big_int_msb->flag == true && var1.return_msb()->flag == true)
	{
		result = sub(var1);
	}
	
	return *result;
}