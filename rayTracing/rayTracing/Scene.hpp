#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <SDL.h>
#include "RhettImage.hpp"


namespace rhettRT {
	class Scene {
	public:
		Scene() {

		}

		//rendering function
		bool Render(RhettImage& outputImage) {
			//getting the dimensions of the output image
			int xSize{ outputImage.GetXSize() };
			int ySize{ outputImage.GetYSize() };

			//color variation of producing colors
			for (int x = 0; x < xSize; ++x) {
				for (int y = 0; y < ySize; ++y) {
					double red = (static_cast<double>(x) / static_cast<double>(xSize)) * 255;
					double green = (static_cast<double>(y) / static_cast<double>(ySize)) * 255;
					outputImage.SetPixel(x, y, red, green, 127.0); //blue is fixed at 127.0
				}
			}

			return true;
		}

	private:

	};
}

#endif // !SCENE_H
