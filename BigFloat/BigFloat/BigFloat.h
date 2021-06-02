#pragma once

#include <iostream>
#include <deque>
#include <cmath>
#include <sstream>
#include <vector>

class BigFloat
{
public:
	BigFloat();
	BigFloat(const std::string& m_number);
	BigFloat(const int m_number);
	BigFloat(const double m_number);

	static BigFloat GCD(BigFloat& a, BigFloat& b);
	BigFloat& operator=(int Num);
	BigFloat& operator=(double Num);
	BigFloat& operator=(const std::string& strNum);
	BigFloat operator+(const BigFloat& other) const;
	BigFloat operator- (const BigFloat& other) const;
	BigFloat operator*(const BigFloat& other) const;
	BigFloat operator/(const BigFloat& other) const;
	BigFloat operator%(const BigFloat& other) const;
	BigFloat operator++(int);
	BigFloat operator--(int);
	bool operator== (const BigFloat& right) const;
	bool operator!= (const BigFloat& right) const;
	bool operator> (const BigFloat& right) const;
	bool operator>= (const BigFloat& right) const;
	bool operator< (const BigFloat& right) const;
	bool operator<= (const BigFloat& right) const;

	friend std::ostream& operator<<(std::ostream& out, const BigFloat& right);
	std::string ToString() const;
	void SetPrecision(int prec);
	static std::string PeriodicToCommon(const std::string& str);
	static std::string CommonToPeriodic(BigFloat a, BigFloat b);
	BigFloat Abs() const;
	BigFloat Floor() const;


private:
	void LeadTrim();
	void TrailTrim();
	inline int Decimals() const { return m_decimals; };
	inline int Ints() const { return m_number.size() - m_decimals; };
	inline int MemorySize() const { return sizeof(*this) + m_number.size() * sizeof(char); };
	std::string Exp() const;

	inline static int CharToInt(const char& val) { return (val - '0'); };
	inline static char IntToChar(const int& val) { return (val + '0'); };
	static int CompareNum(const BigFloat& left, const BigFloat& right);
	static BigFloat Sum(const BigFloat& left, const BigFloat& right);
	static BigFloat Subtract(const BigFloat& left, const BigFloat& right);
	static BigFloat Multiply(const BigFloat& left, const BigFloat& right);

private:
	char m_sign;
	std::deque<char> m_number;
	int m_decimals;
};

