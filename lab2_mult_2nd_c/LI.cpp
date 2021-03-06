﻿#include "stdafx.h"
#include "LI.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

LI::LI(string number)
{
	for (int i = 0; i<number.size(); ++i) {
		char digit = number[i];
		if (48 <= digit&&digit <= 57) {
			value.push_back(digit - '0');
		}
		else { std::cout << "not a number"; 
}
}
	reverse(value.begin(), value.end()); //to store it vice versa 
}

LI::LI(LI & b):value(b.value)
{
}

LI::LI(long int input) {
	set_value(input);
	//reverse(value.begin(), value.end());
}

LI::LI(int length, int def_val): value(length, 0)
{
}


//LI::LI(int length):value(length, 0)
//{
//}

LI::LI():value(0,0)
{
}

void LI:: set_value(long int input) {
	value.push_back(input % this->Base);
	int temp = input / this->Base;
	if (temp == 0) return;
	set_value(temp);
}

void LI::out() {
	reverse(value.begin(), value.end());
	for (auto elem : value)
		cout << elem;
	cout << endl;
	reverse(value.begin(), value.end());
} 

LI  LI::operator+( LI & b)
{

	int n = max(this->value.size(), b.value.size());
	this->add_zeros(n - this->value.size());
	b.add_zeros(n - b.value.size());
	LI sum(n + 1, 0);
	for (int i = 0; i < n; ++i) {
		sum.value[i] += (value[i] + b.value[i]) % Base;
		sum.value[i + 1] = (value[i] + b.value[i]) / Base;

	}
	this->erase_zeros();
	b.erase_zeros();
	sum.erase_zeros();
	return sum;
}





/*
LI LI::operator-(LI & b)
{
	if (this->value.size() < b.value.size() || ((this->value.size() == b.value.size()) && (this->compare_digits(b)))) { 
		LI sub (*this);
		return (b-sub); }
	int n = max(this->value.size(), b.value.size());
	this->add_zeros(n - this->value.size());
	b.add_zeros(n - b.value.size());
	LI sub(n + 1, 0);
	for (int i = 0; i < n; ++i) {
		if (value[i]>=b.value[i])
			sub.value[i] = (value[i] - b.value[i]) % Base;
		else {
			value[i + 1] -= 1%Base; //WHAT TO DO IF THE BASE != 10
			sub.value[i] = (Base + value[i] - b.value[i])%Base;

		}
	

	}
	this->erase_zeros();
	b.erase_zeros();
	sub.erase_zeros();
	return sub;
}

*/

LI  LI::substraction(LI & b)
{
	LI a_copy = (*this);
	int n = max(a_copy.value.size(), b.value.size());
	a_copy.add_zeros(n - a_copy.value.size());
	b.add_zeros(n - b.value.size());
	LI sub(n + 1, 0);
	for (int i = 0; i < n; ++i) {
		if (a_copy.value[i] >= b.value[i])
			sub.value[i] = (a_copy.value[i] - b.value[i]) % Base;
		else {
			a_copy.value[i + 1] -= 1 % Base; //WHAT TO DO IF THE BASE != 10
			sub.value[i] = (Base + a_copy.value[i] - b.value[i]) % Base;

		}


	}
	b.erase_zeros();
	sub.erase_zeros();
	return sub;
}


bool LI::less(LI &b) {

	if ((this->value.size() < b.value.size())) return true;
	if ((this->value.size() > b.value.size())) return false;
	for (int i = this->value.size() - 1; i >= 0; i--) {
		if (this->value[i] < b.value[i])  return  true;
		else { if (this->value[i] > b.value[i])  return  false; }
	}
	return false;


	
}

LI LI::operator-(LI & b)
{
	if (less(b)){
		return b.substraction(*this);
	}
	return this->substraction(b);
}


LI LI::operator=(LI & b)
{
	this->value = b.value;
	return LI();
}


void LI::expand_cur(LI & cur,LI & a, LI & b, int & count_expand)
{
	if (cur.less(b)) {
		count_expand++;
		if  (((int)a.value.size() - (int)b.value.size() - count_expand)>=0) {
			reverse(cur.value.begin(), cur.value.end());
			cur.value.push_back(a.value[a.value.size() - b.value.size() - count_expand]);
			reverse(cur.value.begin(), cur.value.end());
		}
	}
}

int LI::find_multiplier(LI & cur, LI & b)
{
	LI num(1);
	LI one(1);
	while (!cur.less(num*b)) {
		num = num + one;
	}
	num = num - one;
	int res = num.value[0];

	return res;
}

LI LI::operator/(LI & b)
{
	int l_a = value.size();
	int l_b = b.value.size();
	vector <int> div_vec;
	if (l_a < l_b) return LI(0);
	if (*this == b) return LI(1);
	if ((l_a == 1) && (l_b == 1)) {
		div_vec.push_back(find_multiplier(*this, b));
		LI div(div_vec);
		return div;

	}


	LI mul;
	LI cur(value[l_a - l_b]);
	int count_expand = 0;


	if (l_a ==l_b) {
		div_vec.push_back(find_multiplier(*this, b));
	}



	
	if ((l_a - l_b) != value.size() - 1) {
		for (int i = 1; i < l_b; i++) 
			cur.value.push_back(value[l_a - l_b + i]);
	}
	while ((l_b + count_expand)<value.size()) {
	expand_cur(cur, *this, b, count_expand);
	div_vec.push_back(find_multiplier(cur, b));
	mul = b*LI(find_multiplier(cur, b));
	cur = cur - mul;
	if (cur == LI(vector<int>(1, 0)))  cur.value.pop_back(); 
}
	LI div(div_vec);
	return div;

}

LI::LI(vector<int> input) {
	reverse(input.begin(), input.end());
	this->value = input;
}

bool LI::operator == (LI & b) {
	if (value.size() != b.value.size()) return false;
	else {
		for (int i = 0; i < value.size(); ++i) {
			if (value[i] != b.value[i]) return false;
		}
	}
	return true;
}



LI  LI::operator*(LI & b)
{

	int l_a = value.size();

	int l_b = b.value.size();

	LI mul(l_a + l_b, 0);

	this->value.push_back(0);

	int remember = 0;

	for (int j = 0; j < l_b; ++j) {

		for (int i = 0; i<l_a + 1; ++i) {



			mul.value[i + j] += (remember + value[i] * b.value[j]);



			remember = mul.value[i + j] / Base;

			mul.value[i + j] %= Base;



		}

	}

	mul.erase_zeros();
	this->erase_zeros();
	b.erase_zeros();
	return mul;
}
 
void LI::add_zeros(int add)
{
	while (add--)
		value.push_back(0);
}

void LI::erase_zeros()
{
	if (this->value.begin() != this->value.end()) {
		while (this->value.back() == 0&&this->value.size()!=1) {
			this->value.pop_back();
		}
	}
}

LI LI::ordinary_mul(LI & b)
{
	int l_a = value.size();

	int l_b = b.value.size();

	LI mul(l_a + l_b, 0);

	this->value.push_back(0);

	int remember = 0;

	for (int j = 0; j < l_b; ++j) {

		for (int i = 0; i<l_a + 1; ++i) {


			mul.value[i + j] += (remember + value[i] * b.value[j]);


			remember = mul.value[i + j] / Base;

			mul.value[i + j] %= Base;

		}

	}

	
	mul.erase_zeros();
	this->erase_zeros();
	b.erase_zeros();

	return mul;
}

LI LI::Karatsuba_mul(LI & b)
{

	int n = max(this->value.size(), b.value.size());
	if (n == 1) return this->ordinary_mul(b);
	if (n % 2)n += 1; //is odd, makes it even
	this->add_zeros(n - this->value.size());
	b.add_zeros(n - b.value.size());
	LI a_left(n/2, 0);
	a_left.left_half(*this);
	LI a_right(n/2, 0);
	a_right.right_half(*this);
	LI b_left(n/2 , 0);
	b_left.left_half(b);
	LI b_right(n/2 , 0);
	b_right.right_half(b);
	LI  Prod_1(n/2 , 0);
	Prod_1=	a_left.Karatsuba_mul(b_left);
	LI Prod_2(n/2 , 0);
	Prod_2 = a_right.Karatsuba_mul(b_right);
	LI sum_1 = a_left + a_right;
	LI sum_2 = b_left + b_right;
	LI Prod_3(n / 2 + 1, 0);
		Prod_3= sum_1.Karatsuba_mul(sum_2);
	LI ten_in_n = pow(10, n); //10^n
	LI ten_in_n_over_2 = pow(10, n / 2); //10^(n/2)
	LI res(2*n, 0);
	res	= Prod_1.ordinary_mul(ten_in_n) + ten_in_n_over_2.ordinary_mul(Prod_3-Prod_1-Prod_2)+Prod_2;
	return res;	
}

void LI::right_half(LI & from)
{
	int n = from.value.size();
	for (int i = 0; i < n / 2; ++i)
		this->value[i] = from.value[i];
}

int LI::find_power_of_2(int&odd_component) {
	int s=0;
	LI two(2);
	LI a(*this);
	string odd = "";
	while ((a.value[0] % 2) == 0) {
		a = a / two;
		s++;
	}

	odd_component = a.LI_to_int();
	return s;
}


int LI::LI_to_int() {
	int res = 0;
	string tmp = "";
	LI a(*this);
	int j = this->value.size();
	for (int i = 0; i < j; ++i) {
		int num = a.value.back();
		a.value.pop_back();
		tmp += to_string(num);
	}
	res = stoi(tmp);
	return res;
}

int LI::sufficient_loop_num() {
	LI a(*this);
	int num = a.LI_to_int();
	return static_cast<int>((log(num) / log(2))+10);
}



LI LI::power(int k) {
	LI a(*this);
	if (k == 0) return LI(1);
	LI tmp(*this);
	for (int i = 0; i < k-1; ++i) {
		tmp = tmp*a;
	}
	return tmp;
}

random_device rand_dev;
mt19937 generator(rand_dev());

bool LI::Rabin_Miller()
{
	int odd_component = 0;


	LI sth = *this - LI("1");

	int s = sth.find_power_of_2(odd_component);

	int k = this->sufficient_loop_num();

	int n_1 = sth.LI_to_int();


	uniform_int_distribution<int> distribution(2, (n_1 - 1));

	if ((value.size() == 1) && (value[0] == 2)) return true;
	else if (value[0] % 2 == 0) return false;
	else {
		for (int i = 0; i < k; ++i) {
			int a = distribution(generator);
			LI a_(a);
			a_ = a_.power(odd_component);
			LI x = 0;
			if (a_.less(*this))  x=a_;
			else {
				LI tmp1 = a_ / (*this);
				x = a_ - tmp1*(*this); }
			if ((x == LI(1)) || (x == sth)) continue;
			else {
				for (int j = 0; j <( s - 1); ++j) {
					x = x*x;
					if (x.less(*this)) LI x = x;
					else { 
						LI tmp = x / (*this);
						x = x - tmp*(*this); 
					}
					if (x == LI(1)) return false;
					else if (x == sth) goto label;
				}
				return false;
			}

		label:;
		}
		return true;
		//n-1=2^s*b, b- odd
	}
}

void LI::left_half(LI & from)
{
	int n = from.value.size();
	int j = 0;
	for (int i = n / 2; i < n; ++i) {
		this->value[j] = from.value[i];
		j++;
	}
}
