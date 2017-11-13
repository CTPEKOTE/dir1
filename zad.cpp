//#include <iostream>
//#include <cmath>
using namespace std;
class C
{
private:
	double Re;
	double Im;
public:
	C(){};//pustoi konstruktor
	C(double re){ //konstruktor ot 1
		Re = re;
		Im = 0.0;
	}
	C(double re, double im){//konstruktor ot 2
		Re = re;
		Im = im;
	}
	double abs() const {//modul
		return sqrt((Re * Re) + (Im * Im));
	}
	void operator = (const C &a) {//prisvaivanie
		this -> Re = a.Re;
		this -> Im = a.Im;
		return;
	}
	bool operator == (const C &a) const {//sravnenie complex
		if (a.Re == this -> Re && a.Im == this -> Im){
			return true;
		}
		else return false;
	}
	bool operator == (const double &a) const {//sravnenie compex i double
		if (a == this -> Re && 0 == this -> Im){
			return true;
		}
		else return false;
	}
	bool operator != (const C &a) const {//sravnenie complex
		if (a.Re == this -> Re && a.Im == this -> Im){
			return false;
		}
		else return true;
	}
	bool operator != (const double &a) const {//sravnenie complex i double
		if (a == this -> Re && 0 == this -> Im){
			return false;
		}
		else return true;
	}
	friend bool operator != (const double &a , const C &b);
	friend bool operator == (const double &a , const C &b);
	C operator / (const double &a) const {//delenie complex na real
		C otv = *this;
		otv.Re /= a;
		otv.Im /= a;
		return otv;
	}
	C operator / (const C &a) const {//delenie complex
		C otv = *this;
		double imb = otv.Im, reb = otv.Re;
		otv.Re = reb * a.Re + imb * a.Im;
		otv.Im = imb * a.Re - reb * a.Im;
		otv = otv / (a.Re * a.Re + a.Im * a.Im);
		return otv;
	}
	friend C operator /(const double &a, const C &b);
	C operator * (const C &a) const { //umnojenie dlya complex
		double imb = this ->Im;
		double reb = this -> Re;
		C otv = *this;
		otv.Re *= a.Re;
		otv.Re -= imb * a.Im;
		otv.Im *= a.Re;
		otv.Im += reb * a.Im;
		return otv; 
	}
	C operator * (const double &real) const {//umnojenie dlya complex i double
		C otv = *this;
		otv.Re *= real;
		otv.Im *= real;
		return otv;
	}
	friend C operator * (const double &a, const C &b);
	C operator - (const C &a) const {// vychitanie dlya complex
		C otv = *this;
		otv.Re -= a.Re;
		otv.Im -= a.Im;
		return otv;
	}
	C operator - (const double &a) const {//vychitanie dlya complex i double
		C otv = *this;
		otv.Re -= a;
		return otv;
	}
	friend C operator - (const double &a,const C &b);
	C operator + (const C &a) const { //slojenie dlya complex
		C otv = *this;
		otv.Re += a.Re;
		otv.Im += a.Im;
		return otv;
	}
	C operator + (const double &a) const {//slojenie complex + double
		C otv = *this;
		otv.Re += a;
		return otv;
	}
	friend C operator + (const double &a,const C &b);
	friend ostream& operator<<(ostream &os, const C &dt);
	};
	ostream& operator<<(ostream& os, const C& dt) // print
	{
		os << dt.Re << " " << dt.Im;
		return os;
	}
	C operator + (const double &a , const C &b){//slojenie double + complex
		return ( C(b.Re + a , b.Im));
	}
	C operator - (const double &a, const C &b){//vychitanie dlya double i complex
		return C(a - b.Re , -b.Im);
	}
	C operator * (const double &a, const C &b){//umnojenie dlya double i complex
		return C(b.Re * a, b.Im * a);
	}
	C operator / (const double &a, const C &b){//delenie double na complex
		double imb = b.Im , reb = b.Re , znam = (imb * imb + reb * reb);
		return C(reb * a / znam, -imb * a / znam);
	}
	bool operator == (const double &a , const C &b){//sravnenie double i complex
		if (a == b.Re && 0 == b.Im){
			return true;
		}
		else return false;
	}
	bool operator != (const double &a , const C &b){//sravnenie dpuble i complex
		if (a == b.Re && 0 == b.Im){
			return false;
		}
		else return true;
	}
	/*int main(){
		C a(1.0) , comp , comp1 , comp2;
		const C  d(-2.0,1.0);
		const double  b = -2.0;
		comp = d / d;
		comp1 = d / b;
		comp2 = b / d;
		//if ( d != a)
			cout << a;
		//if ( d != b)
		//	cout << " " << a.abs() << endl;
		//cout << comp << endl << comp1 << endl << comp2;
		return 0;
	}*/
