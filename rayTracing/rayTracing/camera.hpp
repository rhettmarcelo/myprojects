#ifndef CAMERA_H
#define CAMERA_H

#include "qbLinAlg/qbVector.h"
#include "Ray.hpp"
#include <math.h>

namespace rhettRT {
	class Camera {
	public:
		Camera() {
			m_cameraPosition = qbVector<double>{ std::vector<double> {0.0, -10.0, 0.0} }; //-10 represents the camera having 10 units further away than the screen plane
			m_cameraLookAt = qbVector<double>{ std::vector<double>{0.0, 0.0, 0.0} };
			m_cameraUp = qbVector<double>{ std::vector<double>{0.0, 0.0, 1.0} }; //looking up
			m_cameraLength = 1.0;
			m_cameraHorzSize = 1.0;
			m_cameraAspectRatio = 1.0;
		}

		//setting camera parameters
		void SetPosition(const qbVector<double>& newPosition) {
			m_cameraPosition = newPosition;
		}
		void SetLookAt(const qbVector<double>& newLookAt) {
			m_cameraLookAt = newLookAt;
		}
		void SetUp(const qbVector<double>& upVector) {
			m_cameraUp = upVector;
		}
		void SetLength(double newLength) {
			m_cameraLength = newLength;
		}
		void SetHorzSize(double newSize) {
			m_cameraHorzSize = newSize;
		}
		void SetAspect(double newAspect) {
			m_cameraAspectRatio = newAspect;
		}

		//returning camera parameters
		qbVector<double> GetPosition() {
			return m_cameraPosition;
		}
		qbVector<double> GetLookAt() {
			return m_cameraLookAt;
		}
		qbVector<double> GetUp() {
			return m_cameraUp;
		}
		qbVector<double> GetU() { //U and V are vector points in the screen plane
			return m_projectionScreenU;
		} 
		qbVector<double> GetV() {
			return m_projectionScreenV;
		}
		qbVector<double> GetScreenCenter() {
			return m_projectionScreenCenter;
		}
		double GetLength() {
			return m_cameraLength;
		}
		double GetHorzSize() {
			return m_cameraHorzSize;
		}
		double GetAspect() {
			return m_cameraAspectRatio;
		}

		//Ray generation function
		Ray generateRay(float proScreenX, float proScreenY) {
			//computes the location of the screen point in world coordinates, at U and V
			qbVector<double> screenWorldPart1 = m_projectionScreenCenter + (m_projectionScreenU * proScreenX);
			qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);

			//Uses this point that utilizes the camera position to compute the ray
			return Ray(m_cameraPosition, screenWorldCoordinate);
		}

		//Camera geometry updater
		void UpdateCameraGeometry() {
			//computes the vector from the camera position to the LookAt position
			m_alignmentVector = m_cameraLookAt - m_cameraPosition;
			m_alignmentVector.Normalize();

			//computing the U and V vectors
			m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
			m_projectionScreenU.Normalize();
			m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
			m_projectionScreenV.Normalize();

			//computing the position of the center point of the scene
			m_projectionScreenCenter = m_cameraPosition + (m_cameraLength * m_alignmentVector);

			//modifiying U and V vectors to match the size and aspect ratio
			m_projectionScreenU = m_projectionScreenU * m_cameraHorzSize;
			m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSize / m_cameraAspectRatio);
		}

	private:
		qbVector<double> m_cameraPosition{ 3 };
		qbVector<double> m_cameraLookAt{ 3 };
		qbVector<double> m_cameraUp{ 3 };
		double m_cameraLength{};
		double m_cameraHorzSize{};
		double m_cameraAspectRatio{};

		qbVector<double> m_alignmentVector{ 3 }; //principal axes of the camera
		qbVector<double> m_projectionScreenU{ 3 };
		qbVector<double> m_projectionScreenV{ 3 };
		qbVector<double> m_projectionScreenCenter{ 3 };
	};
}


#endif // !CAMERA_H
