#ifndef CAPP_H
#define CAPP_H
#include <SDL.h>
#include "RhettImage.hpp"


class CApp {
public:
	CApp() { //The default constructor
		isRunning = true;
		pWindow = nullptr;
		pRenderer = nullptr;
	}

	int OnExecute() {
		SDL_Event event{};
		if (OnInit() == false) {
			return -1;
		}

		while (isRunning) {
			while (SDL_PollEvent(&event) != 0) {
				OnEvent(&event);
			}
			OnLoop();
			OnRender();
		}
	}

	bool OnInit() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { //SDL_Init returns a negative value when it fails to initialize
			return false;
		}

		//Parameters 2560 and 1440 represent my current monitor resolution
		pWindow = SDL_CreateWindow("Rhett's Ray Tracer!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, xResolution, yResolution, SDL_WINDOW_SHOWN);
		if (pWindow != nullptr) {
			pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

			//initializing the rhettImage;
			m_image.Initialize(xResolution, yResolution, pRenderer);

			//creating color variations
			for (int x = 0; x < xResolution; ++x) {
				for (int y = 0; y < yResolution; ++y) {
					double red = (static_cast<double>(x) / static_cast<double>(xResolution)) * 255;
					double green = (static_cast<double>(y) / static_cast<double>(yResolution)) * 255;
					m_image.SetPixel(x, y, red, green, 127.0); //blue is fixed at 120.0
				}
			}
		}
		else {
			return false;
		}

		return true;
	}

	void OnEvent(SDL_Event* event) {
		if (event->type == SDL_QUIT) {
			isRunning == false;
		}
	}

	void OnLoop() {

	}

	void OnRender() {//Sets the background color
		SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255); //White
		SDL_RenderClear(pRenderer);
		
		//display image
		m_image.Display();

		SDL_RenderPresent(pRenderer); //Show the result
	}

	void OnExit() { //Our "destructor" to clean things up
		SDL_DestroyRenderer(pRenderer);
		SDL_DestroyWindow(pWindow);
		pWindow = nullptr;
		SDL_Quit();
	}

private:
	//an instance of rhettImage to store the image
	RhettImage m_image;

	static constexpr int xResolution{ 2560 };
	static constexpr int yResolution{ 1440 };
	bool isRunning{};
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;
};

#endif // !CAPP_H
