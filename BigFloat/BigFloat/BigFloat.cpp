#include "BigFloat.h"

int BigFloat::CompareNum(const BigFloat& left, const BigFloat& right)
{
	if ((left.m_number.size() - left.m_decimals) > (right.m_number.size() - right.m_decimals))
		return 1;
	else if ((left.m_number.size() - left.m_decimals) < (right.m_number.size() - right.m_decimals))
		return 2;

	if (left.m_decimals > right.m_decimals)
	{
		BigFloat tmp;
		tmp = right;
		while (left.m_decimals > tmp.m_decimals)
		{
			tmp.m_decimals++;
			tmp.m_number.push_front('0');
		}

		for (int i = left.m_number.size() - 1; i >= 0; i--)
		{
			if (left.m_number[i] > tmp.m_number[i])
				return 1;
			else if (left.m_number[i] < tmp.m_number[i])
				return 2;
		}
		return 0;
	}
	else if (left.m_decimals < right.m_decimals)
	{
		BigFloat tmp;
		tmp = left;
		while (tmp.m_decimals < right.m_decimals)
		{
			tmp.m_decimals++;
			tmp.m_number.push_front('0');
		}

		for (int i = tmp.m_number.size() - 1; i >= 0; i--)
		{
			if (tmp.m_number[i] > right.m_number[i])
				return 1;
			else if (tmp.m_number[i] < right.m_number[i])
				return 2;
		}
		return 0;
	}
	else
	{
		for (int i = left.m_number.size() - 1; i >= 0; i--)
		{
			if (left.m_number[i] > right.m_number[i])
				return 1;
			else if (left.m_number[i] < right.m_number[i])
				return 2;
		}
		return 0;
	}
};

BigFloat BigFloat::Sum(const BigFloat& left, const BigFloat& right)
{
	BigFloat tmp;
	int carry = 0;
	int loopsize = (left.m_number.size() > right.m_number.size()) ? left.m_number.size() : right.m_number.size();

	for (int i = 0; i < loopsize; ++i)
	{
		int val1, val2;
		val1 = (i > left.m_number.size() - 1) ? 0 : CharToInt(left.m_number[i]);
		val2 = (i > right.m_number.size() - 1) ? 0 : CharToInt(right.m_number[i]);

		int aus = val1 + val2 + carry;

		carry = 0;
		if (aus > 9)
		{
			carry = 1;
			aus = aus - 10;
		}

		tmp.m_number.push_back(IntToChar(aus));
	}
	if (carry != 0)
		tmp.m_number.push_back(IntToChar(carry));

	return tmp;
};

BigFloat BigFloat::Subtract(const BigFloat& left, const BigFloat& right)
{
	BigFloat tmp;
	int carry = 0;
	int aus;

	for (int i = 0; i < left.m_number.size(); ++i)
	{
		int val1, val2;
		val1 = CharToInt(left.m_number[i]);
		val2 = (i > right.m_number.size() - 1) ? 0 : CharToInt(right.m_number[i]);

		val1 -= carry;

		if (val1 < val2)
		{
			aus = 10 + val1 - val2;
			carry = 1;
		}
		else
		{
			aus = val1 - val2;
			carry = 0;
		}

		tmp.m_number.push_back(IntToChar(aus));
	}

	return tmp;
};


BigFloat BigFloat::Multiply(const BigFloat& left, const BigFloat& right)
{
	BigFloat ris;
	BigFloat tmp;
	ris.m_number.push_back('0');
	int carry = 0;

	for (int i = 0; i < right.m_number.size(); ++i)
	{
		for (int k = 0; k < i; ++k)
		{
			tmp.m_number.push_front('0');
		}

		for (int j = 0; j < left.m_number.size(); ++j)
		{
			int aus = CharToInt(right.m_number[i]) * CharToInt(left.m_number[j]) + carry;
			carry = 0;
			if (aus > 9)
			{
				while (aus > 9)
				{
					carry++;
					aus -= 10;
				}
			}
			tmp.m_number.push_back(IntToChar(aus));
		}

		if (carry != 0)
			tmp.m_number.push_back(IntToChar(carry));
		carry = 0;

		ris = Sum(ris, tmp);
		tmp.m_number.clear();
	}

	return ris;
};


BigFloat BigFloat::GCD(BigFloat& a, BigFloat& b)
{
	while (a != b) {
		if (b > a) {
			BigFloat c = b;
			b = a;
			a = c;
		}
		while (a > b) a = a - b;
	}
	return(a);
}

BigFloat BigFloat::Abs() const
{
	auto res = BigFloat(*this);
	res.m_sign = '+';
	return res;
}

BigFloat BigFloat::Floor() const
{

	auto res = BigFloat(*this);
	for (auto i = res.m_decimals - 1; i >= 0; i--)
	{
		res.m_number[i] = '0';
	}
	return res;
}

std::string BigFloat::PeriodicToCommon(const std::string& str)
{
	std::stringstream ss;
	std::stringstream per;
	bool periodic = false;
	for (auto i = 0; i < str.size(); i++)
	{
		if (str[i] == '+')
		{
			ss << '+';
		}
		else if (str[i] == '-')
		{
			ss << '-';
		}
		if (str[i] == '(')
		{
			periodic = true;
		}
		else if (str[i] == ')')
		{
			break;
		}
		if (isdigit(str[i]) || str[i] == '.')
		{
			if (!periodic)
			{
				ss << str[i];
			}
			else {
				per << str[i];
			}
		}
	}
	if (periodic)
	{
		auto count = 20 / per.str().size();
		if (count == 0)
			count++;
		for (auto i = 0; i < count; i++)
			ss << per.str();
	}
	return ss.str();
}

std::string BigFloat::CommonToPeriodic(BigFloat a, BigFloat b)
{
	std::string whole = (a / b).Floor().ToString();

	a = a % b;
	std::string frac;

	std::vector<BigFloat> remainders;
	do
	{
		remainders.push_back(a);

		a = a * BigFloat(10);

		frac += (a / b).Floor().ToString();

		a = a % b;
		if (a == BigFloat(0))
			break;

		auto r = std::find(remainders.begin(), remainders.end(), a);
		if (r != remainders.end())
		{
			size_t p = r - remainders.begin();
			frac.insert(p, 1, '(');
			frac += ')';
			break;
		}

	} while (true);

	return whole + "." + frac;
}

BigFloat& BigFloat::operator=(int Num)
{
	*this = std::to_string(Num);
	return *this;
};

BigFloat& BigFloat::operator=(double Num)
{
	*this = std::to_string(Num);
	return *this;
};


BigFloat& BigFloat::operator=(const std::string& strNum)
{
	m_number.clear();
	m_decimals = 0;
	m_sign = '\0';

	int count = 0;
	if (strNum[count] == '+')
	{
		m_sign = '+';
		count++;
	}
	else if (strNum[count] == '-')
	{
		m_sign = '-';
		count++;
	}
	else if (isdigit(strNum[count]))
		m_sign = '+';
	else
	{
		return *this;
	}

	bool start_dec = false;
	while (strNum[count] != '\0')
	{
		if (!start_dec)
			if (strNum[count] == '.')
			{
				if (m_number.empty())
				{
					m_sign = '\0';
					return *this;
				}
				start_dec = true;
				count++;
			}

		if (isdigit(strNum[count]))
		{
			m_number.push_front(strNum[count]);
			count++;
			if (start_dec)
				m_decimals++;
		}
		else
		{
			m_sign = '\0';
			m_number.clear();
			m_decimals = 0;
			return *this;
		}
	}
	this->LeadTrim();
	return *this;
};

BigFloat::BigFloat(const std::string& m_number)
{
	*this = PeriodicToCommon(m_number);
}

BigFloat::BigFloat(const int m_number)
{
	*this = m_number;
}

BigFloat::BigFloat(const double m_number)
{
	*this = m_number;
}

BigFloat::BigFloat()
{
	m_sign = '\0';
	m_decimals = 0;
}

BigFloat BigFloat::operator+ (const BigFloat& other) const
{
	BigFloat tmp;
	BigFloat left, right;
	left = *this;
	right = other;

	if (left.m_decimals > right.m_decimals)
		while (left.m_decimals > right.m_decimals)
		{
			right.m_decimals++;
			right.m_number.push_front('0');
		}
	else if (left.m_decimals < right.m_decimals)
		while (left.m_decimals < right.m_decimals)
		{
			left.m_decimals++;
			left.m_number.push_front('0');
		}

	if ((left.m_sign == '+') && (right.m_sign == '-'))
	{
		int check = BigFloat::CompareNum(left, right);
		if (check == 0)
		{
			tmp = 0;
			return tmp;
		}
		if (check == 1)
		{
			tmp = BigFloat::Subtract(left, right);
			tmp.m_sign = '+';
			tmp.m_decimals = left.m_decimals;
			tmp.LeadTrim();
			return tmp;
		}
		if (check == 2)
		{
			tmp = BigFloat::Subtract(right, left);
			tmp.m_sign = '-';
			tmp.m_decimals = left.m_decimals;
			tmp.LeadTrim();
			return tmp;
		}
	}
	if ((left.m_sign == '-') && (right.m_sign == '+'))
	{
		int check = BigFloat::CompareNum(left, right);
		if (check == 0)
		{
			tmp = 0;
			return tmp;
		}
		if (check == 1)
		{
			tmp = BigFloat::Subtract(left, right);
			tmp.m_sign = '-';
			tmp.m_decimals = left.m_decimals;
			tmp.LeadTrim();
			return tmp;
		}
		if (check == 2)
		{
			tmp = BigFloat::Subtract(right, left);
			tmp.m_sign = '+';
			tmp.m_decimals = left.m_decimals;
			tmp.LeadTrim();
			return tmp;
		}
	}

	if ((left.m_sign == '+') && (right.m_sign == '+'))
	{
		tmp = BigFloat::Sum(left, right);
		tmp.m_sign = '+';
		tmp.m_decimals = left.m_decimals;
		return tmp;
	}
	if ((left.m_sign == '-') && (right.m_sign == '-'))
	{
		tmp = BigFloat::Sum(left, right);
		tmp.m_sign = '-';
		tmp.m_decimals = left.m_decimals;
		return tmp;
	}
};

BigFloat BigFloat::operator- (const BigFloat& other) const
{
	BigFloat tmp;

	BigFloat left, right;
	left = *this;
	right = other;

	if (left.m_decimals > right.m_decimals)
		while (left.m_decimals > right.m_decimals)
		{
			right.m_decimals++;
			right.m_number.push_front('0');
		}
	else if (left.m_decimals < right.m_decimals)
		while (left.m_decimals < right.m_decimals)
		{
			left.m_decimals++;
			left.m_number.push_front('0');
		}

	if ((left.m_sign == '+') && (right.m_sign == '-'))
	{
		tmp = BigFloat::Sum(left, right);
		tmp.m_sign = '+';
		tmp.m_decimals = left.m_decimals;
		return tmp;
	}
	if ((left.m_sign == '-') && (right.m_sign == '+'))
	{
		tmp = BigFloat::Sum(left, right);
		tmp.m_sign = '-';
		tmp.m_decimals = left.m_decimals;
		return tmp;
	}

	if ((left.m_sign == '+') && (right.m_sign == '+'))
	{
		int check = BigFloat::CompareNum(left, right);
		if (check == 0)
		{
			tmp = 0;
			return tmp;
		}
		if (check == 1)
		{
			tmp = BigFloat::Subtract(left, right);
			tmp.m_sign = '+';
			tmp.m_decimals = left.m_decimals;
			tmp.LeadTrim();
			return tmp;
		}
		if (check == 2)
		{
			tmp = BigFloat::Subtract(right, left);
			tmp.m_sign = '-';
			tmp.m_decimals = left.m_decimals;
			tmp.LeadTrim();
			return tmp;
		}
	}

	if ((left.m_sign == '-') && (right.m_sign == '-'))
	{
		int check = BigFloat::CompareNum(left, right);
		if (check == 0)
		{
			tmp = 0;
			return tmp;
		}
		if (check == 1)
		{
			tmp = BigFloat::Subtract(left, right);
			tmp.m_sign = '-';
			tmp.m_decimals = left.m_decimals;
			tmp.LeadTrim();
			return tmp;
		}
		if (check == 2)
		{
			tmp = BigFloat::Subtract(right, left);
			tmp.m_sign = '+';
			tmp.m_decimals = left.m_decimals;
			tmp.LeadTrim();
			return tmp;
		}
	}
};

BigFloat BigFloat::operator*(const BigFloat& other) const
{
	BigFloat tmp;

	tmp = BigFloat::Multiply(*this, other);
	if (((other.m_sign == '-') && (this->m_sign == '-')) || ((other.m_sign == '+') && (this->m_sign == '+')))
		tmp.m_sign = '+';
	else
		tmp.m_sign = '-';

	tmp.m_decimals = other.m_decimals + this->m_decimals;
	tmp.LeadTrim();

	return tmp;
};

BigFloat BigFloat::operator/(const BigFloat& other) const
{
	BigFloat tmp;

	BigFloat Q, R, D, N, zero;
	zero = 0;

	if (other == zero)
	{
		return tmp;
	}

	N = (*this > zero) ? (*this) : (*this * (-1));
	D = (other > zero) ? (other) : (other * (-1));
	R.m_sign = '+';

	while ((N.m_decimals != 0) || (D.m_decimals != 0))
	{
		if (N.m_decimals == 0)
			N.m_number.push_front('0');
		else
			N.m_decimals--;

		if (D.m_decimals == 0)
			D.m_number.push_front('0');
		else
			D.m_decimals--;
	}
	N.LeadTrim();
	D.LeadTrim();

	int div_precision = (this->m_decimals > other.m_decimals) ? (this->m_decimals) : (other.m_decimals);
	for (int i = 0; i < div_precision; i++)
		N.m_number.push_front('0');

	int check = BigFloat::CompareNum(N, D);

	if (check == 0)
	{
		tmp.m_number.push_front('1');
	}
	if (check == 2)
	{
		return zero;
	}
	else
	{
		while (!N.m_number.empty())
		{
			R.m_number.push_front(*(N.m_number.rbegin()));
			N.m_number.pop_back();

			bool is_zero = true;
			std::deque<char>::const_iterator zero_iter = R.m_number.begin();
			for (; zero_iter != R.m_number.end(); ++zero_iter)
				if (*zero_iter != '0')
					is_zero = false;

			if ((R >= D) && (!is_zero))
			{
				int Q_sub = 0;
				int min = 0;
				int max = 9;

				while (R >= D)
				{
					int avg = max - min;
					int mod_avg = avg / 2;
					avg = (avg - mod_avg * 2) ? (mod_avg + 1) : (mod_avg);

					int div_check = BigFloat::CompareNum(R, D * avg);

					if (div_check == 2)
					{
						max = avg;
					}
					else
					{
						Q_sub = Q_sub + avg;
						R = R - D * avg;

						max = 9;
					}
				}

				Q.m_number.push_front(BigFloat::IntToChar(Q_sub));

				bool is_zero = true;
				std::deque<char>::const_iterator zero_iter = R.m_number.begin();
				for (; zero_iter != R.m_number.end(); ++zero_iter)
					if (*zero_iter != '0')
						is_zero = false;
				if (is_zero)
					R.m_number.clear();

			}
			else
			{
				Q.m_number.push_front('0');
			}
		}
		tmp = Q;
	}

	if (((this->m_sign == '-') && (other.m_sign == '-')) || ((this->m_sign == '+') && (other.m_sign == '+')))
		tmp.m_sign = '+';
	else
		tmp.m_sign = '-';

	tmp.m_decimals = div_precision;
	tmp.LeadTrim();

	return tmp;
};

BigFloat BigFloat::operator%(const BigFloat& other) const
{
	BigFloat tmp;

	if ((this->m_decimals != 0) || (other.m_decimals != 0))
	{
		return tmp;
	}

	BigFloat Q, R, D, N, zero, ret;
	zero = 0;

	if (other == zero)
	{
		return tmp;
	}

	N = (*this > zero) ? (*this) : (*this * (-1));
	D = (other > zero) ? (other) : (other * (-1));
	R.m_sign = '+';

	int check = BigFloat::CompareNum(N, D);

	if (check == 0)
	{
		return zero;
	}
	if (check == 2)
	{
		return *this;
	}
	else
	{
		while (!N.m_number.empty())
		{
			R.m_number.push_front(*(N.m_number.rbegin()));
			N.m_number.pop_back();

			bool is_zero = true;
			std::deque<char>::const_iterator zero_iter = R.m_number.begin();
			for (; zero_iter != R.m_number.end(); ++zero_iter)
				if (*zero_iter != '0')
					is_zero = false;

			if ((R >= D) && (!is_zero))
			{
				int Q_sub = 0;
				int min = 0;
				int max = 9;

				while (R >= D)
				{
					int avg = max - min;
					int mod_avg = avg / 2;
					avg = (avg - mod_avg * 2) ? (mod_avg + 1) : (mod_avg);

					int div_check = BigFloat::CompareNum(R, D * avg);

					if (div_check == 2)
					{
						max = avg;
					}
					else
					{
						Q_sub = Q_sub + avg;
						R = R - D * avg;

						max = 9;
					}
				}

				Q.m_number.push_front(BigFloat::IntToChar(Q_sub));
				ret = R;

				bool is_zero = true;
				std::deque<char>::const_iterator zero_iter = R.m_number.begin();
				for (; zero_iter != R.m_number.end(); ++zero_iter)
					if (*zero_iter != '0')
						is_zero = false;
				if (is_zero)
					R.m_number.clear();
			}
			else
			{
				ret = R;
				Q.m_number.push_front('0');
			}
		}

		Q.LeadTrim();
		ret.LeadTrim();
		tmp = ret;
	}

	if (((this->m_sign == '-') && (other.m_sign == '-')) || ((this->m_sign == '+') && (other.m_sign == '+')))
		tmp.m_sign = '+';
	else
		tmp.m_sign = '-';

	if (!BigFloat::CompareNum(tmp, zero))
		tmp.m_sign = '+';

	return tmp;
};

BigFloat BigFloat::operator++(int)
{
	*this = *this + 1;
	return *this;
}

BigFloat BigFloat::operator--(int)
{
	*this = *this - 1;
	return *this;
}

bool BigFloat::operator== (const BigFloat& right) const
{
	int check = CompareNum(*this, right);
	if ((check == 0) && (m_sign == right.m_sign))
		return true;
	return false;
};

bool BigFloat::operator!= (const BigFloat& right) const
{
	return !(*this == right);
};

bool BigFloat::operator> (const BigFloat& right) const
{
	if (((m_sign == '+') && (right.m_sign == '+')))
	{
		int check = CompareNum(*this, right);
		if (check == 1)
			return true;
		return false;
	}
	if (((m_sign == '-') && (right.m_sign == '-')))
	{
		int check = CompareNum(*this, right);
		if (check == 2)
			return true;
		return false;
	}
	if (((m_sign == '-') && (right.m_sign == '+')))
		return false;
	if (((m_sign == '+') && (right.m_sign == '-')))
		return true;
};

bool BigFloat::operator>= (const BigFloat& right) const
{
	return !(*this < right);
};

bool BigFloat::operator< (const BigFloat& right) const
{
	if (((m_sign == '+') && (right.m_sign == '+')))
	{
		int check = CompareNum(*this, right);
		if (check == 2)
			return true;
		return false;
	}
	if (((m_sign == '-') && (right.m_sign == '-')))
	{
		int check = CompareNum(*this, right);
		if (check == 1)
			return true;
		return false;
	}
	if (((m_sign == '-') && (right.m_sign == '+')))
		return true;
	if (((m_sign == '+') && (right.m_sign == '-')))
		return false;
};

bool BigFloat::operator<= (const BigFloat& right) const
{
	return !(*this > right);
};

std::ostream& operator<<(std::ostream& out, const BigFloat& right)
{
	if(right.m_sign == -1)
	out << "-";
	for (int i = right.m_number.size() - 1; i >= 0; --i)
	{
		out << right.m_number[i];
		if ((i == right.m_decimals) && (i != 0))
			out << '.';
	}
	return out;

};  
std::string BigFloat::ToString() const
{
	std::string var;
	std::stringstream ss;
	if (m_sign == '-')
	{
		ss << m_sign;
	}
	for (int i = m_number.size() - 1; i >= 0; i--)
	{
		ss << m_number[i];
		if ((i == m_decimals) && (i != 0))
			ss << ".";
	}
	ss >> var;
	return var;
};

void BigFloat::SetPrecision(int prec)
{
	if (this->m_decimals < prec)
	{
		while (this->m_decimals < prec)
		{
			this->m_decimals++;
			this->m_number.push_front('0');
		}
	}
	else if (this->m_decimals > prec)
	{
		char last;
		while (this->m_decimals > prec)
		{
			last = m_number[0];
			this->m_decimals--;
			this->m_number.pop_front();
		}
		if (CharToInt(last) >= 5)
		{
			if (prec == 0)
				(*this)++;
			else
			{
				std::stringstream ss;
				ss << "0.";
				for (int i = 1; i < prec; i++)
					ss << "0";
				ss << "1";
				BigFloat aus(ss.str());
				*this = *this + aus;
			}
		}
	}
};

void BigFloat::LeadTrim()
{
	for (int i = m_number.size() - 1; i > m_decimals; --i)
	{
		if (m_number[i] == '0')
			m_number.pop_back();
		else
			break;
	}
};

void BigFloat::TrailTrim()
{
	while ((m_number[0] == '0') && (m_decimals > 0))
	{
		m_number.pop_front();
		m_decimals--;
	}
};

std::string BigFloat::Exp() const
{
	std::stringstream out;

	int check = BigFloat::CompareNum(*this, BigFloat(1));
	if (check == 0)
	{
		out << m_sign;
		out << "1e+0";
	}
	if (check == 1)
	{
		out << m_sign;
		int i = m_number.size() - 1;
		out << m_number[i];
		i--;
		if (i > 0)
		{
			out << '.';
			for (; (i >= (int)m_number.size() - 6) && (i >= 0); --i)
			{
				out << m_number[i];
			}
		}
		out << "e+" << Ints() - 1;
	}
	if (check == 2)
	{
		int exp = 0;
		int count = m_number.size() - 1;
		while (m_number[count] == '0' && count > 0)
		{
			count--;
			exp++;
		}
		if (count == 0)
			if (m_number[count] == '0')
				out << "+0";
			else
				out << m_sign << m_number[count] << "e-" << exp;
		else
		{
			out << m_sign << m_number[count] << '.';
			for (int i = count - 1; (i >= (int)count - 5) && (i >= 0); --i)
			{
				out << m_number[i];
			}
			out << "e-" << exp;
		}
	}
	return out.str();
};
