/*
** D
*/

#include <cstdio>

const int DAY_OF_MONTH[] = {
	0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

class Date
{
public:
	Date()
	{
		// WARNING: This is illegal!
		_year = _month = _day = 0;
		_isLeap = false;
	}

	Date(int year, int month, int day)
	{
		Init(year, month, day);
	}

	// Assume that it is always legal.
	void Init(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;

		_CheckLeap();
	}

	void Read()
	{
		scanf("%4d", &_year);
		scanf("%2d", &_month);
		scanf("%2d", &_day);

		_CheckLeap();
	}

	bool IsLeap() { return _isLeap; }

	void Convert(int* arr)
	{
		int date = _year;
		date = date * 100 + _month;
		date = date * 100 + _day;

		for (int i = 0; i < 8; i++)
		{
			arr[i] = date % 10;
			date /= 10;
		}
	}

	Date& operator=(Date& date)
	{
		_year = date._year;
		_month = date._month;
		_day = date._day;
		_isLeap = date._isLeap;

		return *this;
	}

	bool operator==(Date& date)
	{
		return ((_day == date._day) && \
			(_month == date._month) && \
			(_year == date._year));
	};

	bool operator!=(Date& date)
	{
		return !operator==(date);
	};

	Date& operator++()
	{
		int days = DAY_OF_MONTH[_month];
		if (_isLeap && _month == 2)
			days++;

		_day++;
		if (_day > days)
		{
			_day = 1;
			_month++;
			if (_month > 12)
			{
				_month = 1;
				_year++;
				_CheckLeap();
			}
		}

		return *this;
	};

private:
	bool _CheckLeap()
	{
		if (_year % 100 == 0)
			_isLeap = (_year % 400 == 0) ? true : false;
		else
			_isLeap = (_year % 4 == 0) ? true : false;

		return _isLeap;
	}

	int _year;
	int _month;
	int _day;
	bool _isLeap;
};

bool IsGoodDate(int* date);
int main()
{
	int arr[12];
	int cnt;
	Date begin;
	Date end;

	begin.Read();
	end.Read();
	++end;

	cnt = 0;
	for (Date date = begin; date != end; ++date)
	{
		date.Convert(arr);
		if (IsGoodDate(arr))
			cnt++;
	}

	printf("%d\n", cnt);

	return 0;
}

bool IsGoodDate(int* date)
{
	int left, right;

	// Condition 1: (\/)
	left = 7;
	while ((left > 0) && (date[left] >= date[left - 1]))
		left--;
	right = 0;
	while ((right < 7) && (date[right] >= date[right + 1]))
		right++;
	if (left <= right)
		return true;

	// Condition 2: (/\)
	left = 7;
	while ((left > 0) && (date[left] <= date[left - 1]))
		left--;
	right = 0;
	while ((right < 7) && (date[right] <= date[right + 1]))
		right++;
	if (left <= right)
		return true;

	return false;
}
