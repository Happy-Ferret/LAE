//==================================================================
// Copyright 2002, softSurfer (www.softsurfer.com)
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from it's use.
// Users of this code must verify correctness for their application.
//==================================================================

#include "point.h"
#include "vector.h"

namespace LAE {
//==================================================================
// Point Class Methods
//==================================================================

//------------------------------------------------------------------
// Constructors (add more as needed)
//------------------------------------------------------------------

// n-dim Point
Point::Point( int n, int a[] ) {
	x = y = z = 0;
	err = Enot;
	switch( dimn = n ) {
	case 3:
		z = a[2];
	case 2:
		y = a[1];
	case 1:
		x = a[0];
		break;
	default:
		err = Edim;
	}
}

Point::Point( int n, double a[] ) {
	x = y = z = 0.0;
	err = Enot;
	switch( dimn = n ) {
	case 3:
		z = a[2];
	case 2:
		y = a[1];
	case 1:
		x = a[0];
		break;
	default:
		err = Edim;
	}
}

//------------------------------------------------------------------
// IO streams
//------------------------------------------------------------------

// Read input Point format: "(%f)", "(%f, %f)", or "(%f, %f, %f)"
istream& operator>>( istream& input, Point& P ) {
	char c;
	input >> c;                // skip '('
	input >> P.x;
	input >> c;
	if( c == ')' ) {
		P.setdim( 1 );     // 1D coord
		return input;
	}
	// else                    // skip ','
	input >> P.y;
	input >> c;
	if( c == ')' ) {
		P.setdim( 2 );     // 2D coord
		return input;
	}
	// else                    // skip ','
	input >> P.z;
	P.setdim( 3 );             // 3D coord
	input >> c;                // skip ')'
	return input;
}

// Write output Point in format: "(%f)", "(%f, %f)", or "(%f, %f, %f)"
ostream& operator<<( ostream& output, Point P ) {
	switch( P.dim() ) {
	case 1:
		output << "(" << P.x << ")";
		break;
	case 2:
		output << "(" << P.x << ", " << P.y << ")";
		break;
	case 3:
		output << "(" << P.x << ", " << P.y << ", " << P.z << ")";
		break;
	default:
		output << "Error: P.dim = " << P.dim();
	}
	return output;
}

//------------------------------------------------------------------
// Assign (set) dimension
//------------------------------------------------------------------

int Point::setdim( int n ) {
	switch( n ) {
	case 1:
		y = 0;
	case 2:
		z = 0;
	case 3:
		return dimn = n;
	default:                      // out of range value
		err = Edim;           // just flag the error
		return 0;
	}
}

//------------------------------------------------------------------
// Comparison (note: dimension must compare)
//------------------------------------------------------------------

int Point::operator==( const Point& Q ) const {
	if( dimn != Q.dim() ) {
		return 0;
	}
	switch( dimn ) {
	case 1:
		return ( x == Q.x );
	case 2:
		return ( x == Q.x && y == Q.y );
	case 3:
	default:
		return ( x == Q.x && y == Q.y && z == Q.z );
	}
}

int Point::operator!=( const Point& Q ) const {
	if( dimn != Q.dim() ) {
		return true;
	}
	switch( dimn ) {
	case 1:
		return ( x != Q.x );
	case 2:
		return ( x != Q.x || y != Q.y );
	case 3:
	default:
		return ( x != Q.x || y != Q.y || z != Q.z );
	}
}

//------------------------------------------------------------------
// Point Vector Operations
//------------------------------------------------------------------

//Vector Point::operator-( const Point& Q ) const {   // Vector diff of Points
//	Vector v;
//	v.x = x - Q.x;
//	v.y = y - Q.y;
//	v.z = z - Q.z;
//	v.dimn = max( dimn, Q.dim() );
//	return v;
//}

Point Point::operator+( const Vector& v ) const {    // +ve translation
	Point P;
	P.x = x + v.x;
	P.y = y + v.y;
	P.z = z + v.z;
	P.dimn = max( dimn, v.dim() );
	return P;
}

Point Point::operator-( const Vector& v ) const {    // -ve translation
	Point P;
	P.x = x - v.x;
	P.y = y - v.y;
	P.z = z - v.z;
	P.dimn = max( dimn, v.dim() );
	return P;
}

Point& Point::operator+=( const Vector& v ) {     // +ve translation
	x += v.x;
	y += v.y;
	z += v.z;
	dimn = max( dimn, v.dim() );
	return *this;
}

Point& Point::operator-=( const Vector& v ) {     // -ve translation
	x -= v.x;
	y -= v.y;
	z -= v.z;
	dimn = max( dimn, v.dim() );
	return *this;
}

//------------------------------------------------------------------
// Point Scalar Operations (convenient but often illegal)
//        are not valid for points in general,
//        unless they are 'affine' as coeffs of
//        a sum in which all the coeffs add to 1,
//        such as: the sum (a*P + b*Q) with (a+b == 1).
//        The programmer must enforce this (if they want to).
//------------------------------------------------------------------

Point operator*( int c, const Point& Q ) {
	Point P;
	P.x = c * Q.x;
	P.y = c * Q.y;
	P.z = c * Q.z;
	P.dimn = Q.dim();
	return P;
}

Point operator*( double c, const Point& Q ) {
	Point P;
	P.x = c * Q.x;
	P.y = c * Q.y;
	P.z = c * Q.z;
	P.dimn = Q.dim();
	return P;
}

Point operator*( const Point& Q, int c ) {
	Point P;
	P.x = c * Q.x;
	P.y = c * Q.y;
	P.z = c * Q.z;
	P.dimn = Q.dim();
	return P;
}

Point operator*( const Point& Q, double c ) {
	Point P;
	P.x = c * Q.x;
	P.y = c * Q.y;
	P.z = c * Q.z;
	P.dimn = Q.dim();
	return P;
}

Point operator/( const Point& Q, int c ) {
	Point P;
	P.x = Q.x / c;
	P.y = Q.y / c;
	P.z = Q.z / c;
	P.dimn = Q.dim();
	return P;
}

Point operator/( const Point& Q, double c ) {
	Point P;
	P.x = Q.x / c;
	P.y = Q.y / c;
	P.z = Q.z / c;
	P.dimn = Q.dim();
	return P;
}

//------------------------------------------------------------------
// Point Addition (also convenient but often illegal)
//    is not valid unless part of an affine sum.
//    The programmer must enforce this (if they want to).
//------------------------------------------------------------------

Point operator+( const Point& Q, const Point& R ) {
	Point P;
	P.x = Q.x + R.x;
	P.y = Q.y + R.y;
	P.z = Q.z + R.z;
	P.dimn = max( Q.dim(), R.dim() );
	return P;
}

//------------------------------------------------------------------
// Affine Sums
// Returns weighted sum, even when not affine, but...
// Tests if coeffs add to 1.  If not, sets: err = Esum.
//------------------------------------------------------------------

Point asum( int n, int c[], const Point Q[] ) {
	int        maxd = 0;
	int        cs = 0;
	Point      P;

	for( int i = 0; i < n; i++ ) {
		cs += c[i];
		if( Q[i].dim() > maxd ) {
			maxd = Q[i].dim();
		}
	}
	if( cs != 1 ) {              // not an affine sum
		P.err = Esum;    // flag error, but compute sum anyway
	}

	for( int i = 0; i < n; i++ ) {
		P.x += c[i] * Q[i].x;
		P.y += c[i] * Q[i].y;
		P.z += c[i] * Q[i].z;
	}
	P.dimn = maxd;
	return P;
}

Point asum( int n, double c[], const Point Q[] ) {
	int        maxd = 0;
	double     cs = 0.0;
	Point      P;

	for( int i = 0; i < n; i++ ) {
		cs += c[i];
		if( Q[i].dim() > maxd ) {
			maxd = Q[i].dim();
		}
	}
	if( cs != 1 ) {              // not an affine sum
		P.err = Esum;    // flag error, but compute sum anyway
	}

	for( int i = 0; i < n; i++ ) {
		P.x += c[i] * Q[i].x;
		P.y += c[i] * Q[i].y;
		P.z += c[i] * Q[i].z;
	}
	P.dimn = maxd;
	return P;
}

//------------------------------------------------------------------
// Distance between Points
//------------------------------------------------------------------

double d( const Point& P, const Point& Q ) {     // Euclidean distance
	double dx = P.x - Q.x;
	double dy = P.y - Q.y;
	double dz = P.z - Q.z;
	return sqrt( dx * dx + dy * dy + dz * dz );
}

double d2( const Point& P, const Point& Q ) {    // squared distance (more efficient)
	double dx = P.x - Q.x;
	double dy = P.y - Q.y;
	double dz = P.z - Q.z;
	return ( dx * dx + dy * dy + dz * dz );
}

//------------------------------------------------------------------
// Sidedness of a Point wrt a directed line P1->P2
//        - makes sense in 2D only
//------------------------------------------------------------------

double Point::isLeft( const Point& P1, const Point& P2 ) {
	if( dimn != 2 || P1.dim() != 2 || P2.dim() != 2 ) {
		err = Edim;        // flag error, but compute anyway
	}
	return ( ( P1.x - x ) * ( P2.y - y ) - ( P2.x - x ) * ( P1.y - y ) );
}

//------------------------------------------------------------------
// Error Routines
//------------------------------------------------------------------

const char* Point::errstr() const {            // return error string
	switch( err ) {
	case Enot:
		return "no error";
	case Edim:
		return "error: invalid dimension for operation";
	case Esum:
		return "error: Point sum is not affine";
	default:
		return "error: unknown err value";
	}
}

std::ostream& operator<<( std::ostream& str, const Point& p ) {
	str << p.x << "," << p.y;
	if( p.dimn == 3 ) {
		str << "," << p.z;
	}
	return str;
}

}
