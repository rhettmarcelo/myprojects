#ifndef OBJSPHERE_H
#define OBJSPHERE_H

#include "objectBase.hpp"

namespace rhettRT {
	class ObjSphere : public ObjectBase { //children class
	public:
		ObjSphere() { //defines a unit sphere at origin

		}

		virtual ~ObjSphere() override { //overriden dtor

		} 

		//computing whether an intersection occurs is by computing a point using the quadratic formula
		virtual bool TestIntersection(const rhettRT::Ray& castRay, qbVector<double>& intPoint, qbVector<double>& localNormal, qbVector<double>& localColor) {
			qbVector<double> vhat = castRay.m_lab;
			vhat.Normalize();

			//'a' is the squared magnitude of the direction of the cast ray.
			//since 'a' is a unit vector, value will always be 1.

			//a = 1.0

			double b{ 2.0 * qbVector<double>::dot(castRay.m_point1, vhat) };
			double c{ qbVector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0 };

			//testing if an intersection occurs
			double intTest = (b * b) - 4.0 * c;

			if (intTest > 0.0) {
				double numSQRT = sqrtf(intTest);
				double t1 = (-b + numSQRT) / 2.0;
				double t2 = (-b - numSQRT) / 2.0;

				//if either t1 or t2 is negative, then at least part of the object
				//is behind the camera therefore will be ignored
				if ((t1 < 0.0) || (t2 < 0.0)) {
					return false;
				}
				else {
					//determines which point of intersection was closest to the camera
					if (t1 < t2) {
						intPoint = castRay.m_point1 + (vhat * t1);
					}
					else {
						intPoint = castRay.m_point1 + (vhat * t2);
					}
				}
				return true;
			}
			else {
				return false;
			}
		}

	private:

	};
}

#endif // !OBJECTSPHERE_H
