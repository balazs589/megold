#ifndef SIMPLE_COMPLEX_H
#define SIMPLE_COMPLEX_H

#include <string>
#include <iostream>
#include <math.h>

namespace scomplex
{
	class COMPLEX
	{
		friend std::ostream& operator<<(std::ostream &o, const COMPLEX & c);  //
	public:
		COMPLEX() :re(0),im(0) {}
		COMPLEX(double r, double i=0) : re(r),im(i) {}
		COMPLEX(const COMPLEX &c) : re(c.re), im(c.im) {}

		const double Re() { return re; }
		const double Im() { return im; }

		//unaris operatorok

		const COMPLEX operator-() { return COMPLEX(-re, -im); }
		const COMPLEX operator+() { return *this; }
		const bool operator!() { return (re == 0 && im == 0); };

		//binaris operatorok

		friend const COMPLEX operator+(const COMPLEX &zl, const COMPLEX &zr);
		friend const COMPLEX operator-(const COMPLEX &zl, const COMPLEX &zr);
		friend const COMPLEX operator*(const COMPLEX &zl, const COMPLEX &zr);
		friend const COMPLEX operator/(const COMPLEX &zl, const COMPLEX &zr);

		//lvalue-t ado operatorok

		friend COMPLEX &operator+=(COMPLEX &zl, const COMPLEX &zr);
		friend COMPLEX &operator-=(COMPLEX &zl, const COMPLEX &zr);
		friend COMPLEX &operator*=(COMPLEX &zl, const COMPLEX &zr);
		friend COMPLEX &operator/=(COMPLEX &zl, const COMPLEX &zr);

		//ertekadas

		COMPLEX &operator=(const COMPLEX &z) { re = z.re; im = z.im; return *this; }

		//logikai operatorok

		bool operator==(const COMPLEX &z) { return re == z.re && im == z.im; }
		bool operator!=(const COMPLEX &z) { return re != z.re || im != z.im; }

		//segedfuggvvenyek

		double abs2() { return re*re + im* im; }
		double abs() { return sqrt(abs2()); }
/**********************************************************************************/		
// 2 db sajat fuggveny:		
		static double AbszolutErtek(const COMPLEX& z);
		static COMPLEX NegyzetGyok(const COMPLEX& z);
/**********************************************************************************/		

	private:
		double re,im;
	};

	inline const COMPLEX operator+(const COMPLEX &zl, const COMPLEX &z)
	{ return COMPLEX(zl.re+z.re, zl.im+z.im); }

	inline const COMPLEX operator-(const COMPLEX &zl, const COMPLEX &z)
	{ return COMPLEX(zl.re-z.re, zl.im-z.im); }

	inline const COMPLEX operator*(const COMPLEX &zl, const COMPLEX &z)
	{ return COMPLEX(zl.re*z.re - zl.im*z.im, zl.im*z.re+zl.re*z.im); }

	inline const COMPLEX operator/(const COMPLEX &zl, const COMPLEX &z)
	{
		double d = (z.re*z.re+ z.im*z.im);

		if(!d)
			throw "osztas 0-val";

		else
			d=1/d;

		return operator*(zl, COMPLEX(z.re*d, -z.im*d));
	}

	inline COMPLEX &operator+=(COMPLEX &zl, const COMPLEX &z)
	{ zl.re += z.re; zl.im += z.im; return zl; }

	inline COMPLEX &operator-=(COMPLEX &zl, const COMPLEX &z)
	{ zl.re -= z.re; zl.im -= z.im; return zl; }

	inline COMPLEX &operator*=(COMPLEX &zl, const COMPLEX &z)
	{ zl.re = zl.re*z.re - zl.im*z.im; zl.im = zl.im*z.re + zl.re*z.im; return zl; }

	inline COMPLEX &operator/=(COMPLEX &zl, const COMPLEX &z)
	{
		double d = (z.re*z.re+ z.im*z.im);
		if(!d)
			throw "osztas 0-val";
		else
			d=1/d;
		return operator*=(zl, COMPLEX(z.re*d, -z.im*d));
	}

inline std::ostream& operator<<(std::ostream &o, const COMPLEX & c)

{
	o << "(" << c.re << (c.im < 0 ? "" : "+") << c.im << "i)";
	return o;
}

//end of namespace scomplex
}
#endif