#include <iostream>
#include <cmath>
using namespace std;
class C
{
public:
	double Re;
	double Im;
public:
	C(double r = 0, double i = 0)
            : Re(r), Im(i) {}

	double abs() const {//modul
		return sqrt((Re * Re) + (Im * Im));
	}
	C& operator= (const C &a) {//prisvaivanie
		Re = a.Re;
		Im = a.Im;
		return *this;
	}
	bool operator== (const C &a) const {//sravnenie complex
		if (a.Re == Re && a.Im == Im){
			return true;
		}
		else return false;
	}
	bool operator== (const double &a) const {//sravnenie compex i double
		if (a ==  Re && 0 == Im){
			return true;
		}
		else return false;
	}
	bool operator!= (const C &a) const {//sravnenie complex
		if (a.Re == Re && a.Im == Im){
			return false;
		}
		else return true;
	}
	bool operator!= (const double &a) const {//sravnenie complex i double
		if (a == Re && 0 == Im){
			return false;
		}
		else return true;
	}
	friend bool operator!= (const double &a , const C &b);
	friend bool operator== (const double &a , const C &b);
	C operator/ (const double &a) const {//delenie complex na real
		double re = Re,im = Im;
		re /= a;
		im /= a;
		return C(re,im);
	}
	C operator/ (const C &a) const {//delenie complex
		double re = Re,im = Im;
		double imb = im, reb = re;
		re = reb * a.Re + imb * a.Im;
		im = imb * a.Re - reb * a.Im;
		//otv = otv / (a.Re * a.Re + a.Im * a.Im);
		return C(re/a.abs()/a.abs() , im /a.abs()/a.abs());
	}
	friend C operator/(const double &a, const C &b);
	C operator* (const C &a) const { //umnojenie dlya complex
		double imb = Im;
		double reb = Re;
		double re = Re,im = Im;
		re *= a.Re;
		re -= imb * a.Im;
		im *= a.Re;
		im += reb * a.Im;
		return C(re,im); 
	}
	C operator* (const double &real) const {//umnojenie dlya complex i double
		double re = Re,im = Im;
		re *= real;
		im *= real;
		return C(re,im);
	}
	friend C operator* (const double &a, const C &b);
	C operator- (const C &a) const {// vychitanie dlya complex
		double re = Re,im = Im;
		re -= a.Re;
		im -= a.Im;
		return C(re,im);
	}
	C operator- (const double &a) const {//vychitanie dlya complex i double
		double re = Re,im = Im;
		re -= a;
		return C(re,im);
	}
	friend C operator- (const double &a,const C &b);
	/*C operator+ (const C &a) const { //slojenie dlya complex
		double re = Re,im = Im;
		re += a.Re;
		im += a.Im;
		return C(re,im);
	}
	C operator+ (const double &a) const {//slojenie complex + double
		double re = Re,im = Im;
		re += a;
		return C(re , im);
	}
	friend C operator+ (const double &a,const C &b);
	friend ostream& operator<<( ostream &os, const C &dt);*/
	};
	ostream& operator<<(ostream& os, const C& dt) // print
	{
		os << dt.Re << " " << dt.Im;
		return os;
	}
	/*C operator+ (const double &a , const C &b){//slojenie double + complex
		return ( C(b.Re + a , b.Im));
	}*/
	C operator- (const double &a, const C &b){//vychitanie dlya double i complex
		return C(a - b.Re , -b.Im);
	}
	C operator* (const double &a, const C &b){//umnojenie dlya double i complex
		return C(b.Re * a, b.Im * a);
	}
	C operator/ (const double &a, const C &b){//delenie double na complex
		double imb = b.Im , reb = b.Re , znam = (imb * imb + reb * reb);
		return C(reb * a / znam, -imb * a / znam);
	}
	bool operator== (const double &a , const C &b){//sravnenie double i complex
		if (a == b.Re && 0 == b.Im){
			return true;
		}
		else return false;
	}
	bool operator!= (const double &a , const C &b){//sravnenie dpuble i complex
		if (a == b.Re && 0 == b.Im){
			return false;
		}
		else return true;
	}
	/*int main(){
		C a(1.0) , comp , comp1 , comp2;
		const C  d(-2.0,1.0);
		const double  b = -2.0;
		comp = d + d;
		comp1 = d + b;
		comp2 = b + d;
		//if ( d != a)
			//cout << a;
		//if ( d != b)
		//	cout << " " << a.abs() << endl;
		cout << comp << endl << comp1 << endl << comp2;
	return 0;
	}*/