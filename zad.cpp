#include <iostream>
class Date
{
private:
	int Year;
	int Month;
	int Day;
public:
	Date (int year, int month , int day){
		Year = year;
		Month = month;
		Day = day;
	}
	int yback () {
		return Year;
	}
	int mback () {
		return Month;
	}
	int dback () {
		return Day;
	}
};
int main(){
	int month , year , day;
	cin >> year;
	cin >> month;
	cin >> day;
	Date Now(year , month , day);
	cout << Now.yback << " " << Now.mback << " " << Now.dback << endl;
	while(0 == 0){}
	return 0;
}