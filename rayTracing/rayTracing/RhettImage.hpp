#ifndef RhettImage_H
#define RhettImage_H

#include <string>
#include <vector>
#include <SDL.h>

class RhettImage {
public:
	RhettImage() { //default ctor
		m_xSize = 0;
		m_ySize = 0;
		m_pTexture = nullptr;
	}

	~RhettImage() { //dtor
		if (m_pTexture != nullptr) {
			SDL_DestroyTexture(m_pTexture);
		}
	}

	void Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer) { //Initializer
		//resizing the image arrays
		m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
		m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
		m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));

		//Stores the dimensions
		m_xSize = xSize;
		m_ySize = ySize;

		//Stores the pointer to the renderer.
		m_pRenderer = pRenderer;

		//Texture initialization
		InitTexture();
	}

	void SetPixel(const int x, const int y, const double red, const double green, const double blue) { //uses color as double precision as... (cont. explanation)
		//sets pixel color a given position
		m_rChannel.at(x).at(y) = red;
		m_gChannel.at(x).at(y) = green;
		m_bChannel.at(x).at(y) = blue;
	}

	void Display() { //handles displaying the pixels
		//allocation of memory to a pixel buffer
		Uint32* tempPixels = new Uint32[m_xSize * m_ySize];

		//clears the buffer as it cycles 
		memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));

		for (int x = 0; x < m_xSize; ++x) {
			for (int y = 0; y < m_ySize; ++y) {
				tempPixels[(y * m_xSize) + x] = ConvertColor(m_rChannel.at(x).at(y), m_gChannel.at(x).at(y), m_bChannel.at(x).at(y));
			}
		}

		//updating the texture with the pixel buffer using SDL
		SDL_UpdateTexture(m_pTexture, nullptr, tempPixels, m_xSize * sizeof(Uint32));

		//deleting the buffer after each update
		delete[] tempPixels;

		//transferring/copying the texture to the renderer
		SDL_Rect srcRect, bounds;
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = m_xSize;
		srcRect.h = m_ySize;
		bounds = srcRect;
		SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
	}

	int GetXSize() {
		return m_xSize;
	}

	int GetYSize() {
		return m_ySize;
	}

private:
	//colors to type Uint32
	Uint32 ConvertColor(const double red, const double green, const double blue) {
		//colors to unsigned ints
		unsigned r = static_cast<unsigned char>(red);
		unsigned g = static_cast<unsigned char>(green);
		unsigned b = static_cast<unsigned char>(blue);

		//directive that shitfs the bits representation according 
		//to the computer's memory architecture endian order (endianness)
		#if SDL_BYTEORDER == SDL_BIG_ENDIAN 
			Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
		#else
			Uint32 pixelColor = (255 << 24) + (r << 16) + (g << 8) + b;
		#endif

		return pixelColor;
	}
	void InitTexture() { //texture initialization
		Uint32 rmask, gmask, bmask, amask;

		//sets the mask color according to the computer's memory architecture endian order (endianness)
		#if SDL_BYTEORDER == SDL_BIG_ENDIAN 
			rmask = 0xff000000;
			gmask = 0x00ff0000;
			bmask = 0x0000ff00;
			amask = 0x000000ff;
		#else
			rmask = 0x000000ff;
			gmask = 0x0000ff00;
			bmask = 0x00ff0000;
			amask = 0xff000000;
		#endif
	
		//deletes any previously created texture
		if (m_pTexture != nullptr) {
			SDL_DestroyTexture(m_pTexture);
		}

		//creates a texture that will store the image, parameter is 32 as there are 32 bits per pixel 
		SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
		m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
		SDL_FreeSurface(tempSurface);
	}

private:
	//Two-Dim arrays to store image data
	std::vector<std::vector<double>> m_rChannel{};
	std::vector<std::vector<double>> m_gChannel{};
	std::vector<std::vector<double>> m_bChannel{};

	//Image dimensions
	int m_xSize{};
	int m_ySize{};

	//SDL methods
	SDL_Renderer* m_pRenderer{};
	SDL_Texture* m_pTexture{};
};

#endif // !RhettImage_H
