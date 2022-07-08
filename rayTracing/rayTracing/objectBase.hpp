#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "qbLinAlg/qbVector.h"
#include "Ray.hpp"
#include <math.h>

#define EPSILON 1e-21f;

namespace rhettRT {
	class ObjectBase {
	public:
		ObjectBase() {
			
		}

		virtual ~ObjectBase() { //virtual keyword is present as the destructor is intended to be overwritten by any children class

		}

		//object test for intersections
		virtual bool TestIntersection(const Ray& castRay, qbVector<double>& intPoint, qbVector<double>& localNormal, qbVector<double>& localColor) {
			return false;
		}

		//functions to test if two-floating point numbers are close to being equal
		bool closeEnough(const double f1, const double f2) {
			return fabs(f1 - f2) < EPSILON;
		}

		//public color base of the object
		qbVector<double> m_baseColor{ 3 };
	};
}

#endif // !OBJECTBASE_H
