
#include <iostream>
#include <string>
#include <cstdio>
#include"Date.hpp"
using namespace std;

Date::Date()
{
	m_year=0;
	m_month=0;
	m_day=0;
}
Date::Date(int t_year, int t_month, int t_day)
{
    m_year=t_year;
    m_month=t_month;
    m_day=t_day;
}

Date::Date(const std::string &dateString)
{
    int t_year,t_month,t_day;
    if (dateString[4]!='-'||dateString[7]!='-'||dateString.size()!=10)
    {
    	m_year=0;
    	m_month=0;
    	m_day=0;
    	return;
    }
    m_year=stol(dateString.substr(0,4));
    m_month=stol(dateString.substr(5,2));
    m_day=stol(dateString.substr(8,2));
}
int Date::getYear(void) const
{
    return m_year;
}
int Date::getMonth(void) const
{
    return m_month;
}
int Date::getDay(void) const
{
    return m_day;
}
void Date::setYear(const int t_year)
{
    m_year=t_year;
}
void Date::setMonth(const int t_month)
{
    m_month=t_month;
}
void Date::setDay(const int t_day)
{
    m_day=t_day;
}
Date Date::stringToDate(const std::string &t_dateString)
{
    int t_year,t_month,t_day;
    if (t_dateString[4]!='-'||t_dateString[7]!='-'||t_dateString.size()!=10)
    {
    	return Date();
    }
    else
    {
    	t_year=stol(t_dateString.substr(0,4));
	    t_month=stol(t_dateString.substr(5,2));
	    t_day=stol(t_dateString.substr(8,2));
        Date temp(t_year,t_month,t_day);
	    if(Date::isValid(temp))
        {
            cout<<Date::dateToString(temp)<<endl;
	    	return temp;
        }
	    else
        {
            cout<<"Invalid Date"<<endl;
	    	return Date();
        }
    }
}
bool Date::isValid(const Date &t_date)
{
	if ((t_date.getYear()<1000)||(t_date.getYear()>9999))
    {
		return false;
    }
	else if ((t_date.getMonth()<1)||(t_date.getMonth()>12))
    {
		return false;
    }
	int date[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if ((t_date.getYear()%400==0)||
		((t_date.getYear()%4==0)&&(t_date.getYear()%100!=0)))
		date[2]=29;
	if ((t_date.getDay()<1)||(date[t_date.getMonth()]<t_date.getDay()))
		return false;
	return true;
}
std::string Date::dateToString(const Date &t_date)
{
	if (isValid(t_date))
	{
		string temp=to_string(t_date.getYear());
		temp+="-";
		if (t_date.getMonth()<10)
		{
			temp+="0";
			temp+=to_string(t_date.getMonth());
		}
		else
		{
			temp+=to_string(t_date.getMonth());
		}
		temp+="-";
		if (t_date.getDay()<10)
		{
			temp+="0";
			temp+=to_string(t_date.getDay());
		}
		else
		{
			temp+=to_string(t_date.getDay());
		}
		return temp;
	}
	else
		return "0000-00-00";
}
Date &Date::operator=(const Date &t_date)
{
	m_year=(t_date.getYear());
	m_month=(t_date.getMonth());
	m_day=(t_date.getDay());
	return *this;
}
bool Date::operator==(const Date &t_date) const
{
	if (m_year==t_date.getYear()&&
		m_month==t_date.getMonth()&&
		m_day==t_date.getDay())
	{
		return true;
	}
	return false;
}
bool Date::operator>(const Date &t_date) const
{
	if (m_year>t_date.getYear())
	{
		return true;
	}
	if (m_year<t_date.getYear())
	{
		return false;
	}
	if (m_month>t_date.getMonth())
	{
		return true;
	}
	if (m_month<t_date.getMonth())
	{
		return false;
	}
	if (m_day>t_date.getDay())
	{
		return true;
	}
	if (m_day<t_date.getDay())
	{
		return false;
	}
	return true;
}
bool Date::operator<(const Date &t_date) const
{
	if (*this>t_date||*this==t_date)
	{
		return false;
	}
	return true;
}
bool Date::operator>=(const Date &t_date) const
{
	if (*this>t_date||*this==t_date)
	{
		return true;
	}
	return false;
}
bool Date::operator<=(const Date &t_date) const
{
	if (*this<t_date||*this==t_date)
	{
		return true;
	}
	return false;
}
