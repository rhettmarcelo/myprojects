#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <SDL.h>
#include "RhettImage.hpp"
#include "camera.hpp"
#include "objSphere.hpp"


namespace rhettRT {
	class Scene {
	public:
		Scene() { //configuring the camera, where it is set 10 units away from the scene
			m_camera.SetPosition(qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}});
			m_camera.SetLookAt(qbVector<double>{ std::vector<double>{0.0, 0.0, 0.0} });
			m_camera.SetUp(qbVector<double>{ std::vector<double>{0.0, 0.0, 1.0} });
			m_camera.SetHorzSize(0.25);
			m_camera.SetAspect(16.0 / 9.0);
			m_camera.UpdateCameraGeometry();
		}

		//rendering function
		bool Render(RhettImage& outputImage) {
			//getting the dimensions of the output image
			int xSize{ outputImage.GetXSize() };
			int ySize{ outputImage.GetYSize() };

			//color variation of producing colors, commented out for future use
			//for (int x = 0; x < xSize; ++x) {
			//	for (int y = 0; y < ySize; ++y) {
			//		double red = (static_cast<double>(x) / static_cast<double>(xSize)) * 255;
			//		double green = (static_cast<double>(y) / static_cast<double>(ySize)) * 255;
			//		outputImage.SetPixel(x, y, red, green, 127.0); //blue is fixed at 127.0
			//	}
			//}

			//Looping over every pixel in the image (July 3)
			Ray cameraRay;
			qbVector<double> intPoint{ 3 };
			qbVector<double> localNormal{ 3 };
			qbVector<double> localColor{ 3 };
			double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
			double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
			double minDist = 1e6;
			double maxDist = 0.0;
			
			for (int x = 0; x < xSize; ++x) {
				for (int y = 0; y < ySize; ++y) {
					//Normalizing x and y
					double normX = (static_cast<double>(x) * xFact) - 1.0;
					double normY = (static_cast<double>(y) * yFact) - 1.0;

					//generating the ray for this particular pixel
					m_camera.generateRay(normX, normY, cameraRay);

					//Tests the valid intersection
					bool validInt = m_testSphere.TestIntersection(cameraRay, intPoint, localNormal, localColor);

					//if validInt becomes true, change pixel to red
					if (validInt) {
						//outputImage.SetPixel(x, y, 255.0, 0.0, 0.0);

						//computes the distance between the camera and the point of intersection
						double dist = (intPoint - cameraRay.m_point1).norm();
						if (dist > maxDist)
							maxDist = dist;

						if (dist < minDist)
							minDist = dist;

						//outputImage.SetPixel(x, y, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
						outputImage.SetPixel(x, y, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 255.0 - ((dist - 9.0) / 0.94605) * 255.0);
					}
					else { //or black
						outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
					}
				}
			}

			std::cout << "Minimum distance: " << minDist << '\n';
			std::cout << "Maximum distance: " << maxDist << '\n';
			return true;
		}

	private:
		//adding camera and sphere objects (July 3)
		Camera m_camera;
		ObjSphere m_testSphere;
	};
}

#endif // !SCENE_H
