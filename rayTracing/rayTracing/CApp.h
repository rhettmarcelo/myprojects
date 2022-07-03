#ifndef CAPP_H
#define CAPP_H
#include <SDL.h>
#include "RhettImage.hpp"
#include "Scene.hpp"
#include "camera.hpp"
#include "qbLinAlg/qbVector.h"


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

			//adding from Ray and Camera classes, for testing
			rhettRT::Camera testCamera;
			testCamera.SetPosition(qbVector<double>(std::vector<double>{0.0, 0.0, 0.0}));
			testCamera.SetLookAt(qbVector<double>(std::vector<double>{0.0, 2.0, 0.0}));
			testCamera.SetUp(qbVector<double>(std::vector<double>{0.0, 0.0, 1.0}));
			testCamera.SetLength(1.0);
			testCamera.SetHorzSize(1.0);
			testCamera.SetAspect(1.0);
			testCamera.UpdateCameraGeometry();

			//Gets the screen center and U/V vectors and display
			auto screenCenter = testCamera.GetScreenCenter();
			auto screenU = testCamera.GetU();
			auto screenV = testCamera.GetV();

			//to display at console
			std::cout << "Camera screen center: " << '\n';
			PrintVector(screenCenter);
			std::cout << "Camera U vector: " << '\n';
			PrintVector(screenU);
			std::cout << "Camera V vector: " << '\n';
			PrintVector(screenV);

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
		
		//rendering the scene
		m_scene.Render(m_image);

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
	//an instance of rhettImage and scene to store the image
	RhettImage m_image;
	rhettRT::Scene m_scene;

	static constexpr int xResolution{ 2560 };
	static constexpr int yResolution{ 1440 };
	bool isRunning{};
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;

	void PrintVector(const qbVector<double>& inputVector) {
		int nRows{ inputVector.GetNumDims() };
		for (int row = 0; row < nRows; ++row) {
			std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << '\n';
		}
	}
};

#endif // !CAPP_H
