
#include <SDL.h>
#include <glew.h>

#include <stdio.h>
#include <string>
#include <cmath>
#include <vector>

#include <iostream>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1

SDL_Window * sdlWindow;
SDL_GLContext sdlContext;
SDL_Event event;


bool Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to init SDL\n";
		return false;
	}

	sdlWindow = SDL_CreateWindow("OpenGL - SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_OPENGL);

	if (!sdlWindow)
	{
		std::cout << "Unable to create window\n";
		return false;
	}

	sdlContext = SDL_GL_CreateContext(sdlWindow);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetSwapInterval(1);

	return true;
}

void loop()
{
	glColor3f(0.0,255.0,255.0);

	glBegin(GL_LINE_STRIP);
	glVertex2f(1.0,1.0);
	glVertex2f(1.0, 90.0);
	glVertex2f(30.0, 90.0);
	glVertex2f(30.0, 1.0);
	glVertex2f(1.0, 1.0);
	glEnd();

	SDL_GL_SwapWindow(sdlWindow);
}

void destroy()
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(sdlContext);

	// Destroy our window
	SDL_DestroyWindow(sdlWindow);

	// Shutdown SDL 2
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	if (!Init())
		return -1;

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(sdlWindow);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 800.0f, 600.0f, 0.0f, 0.0f, 1.0f);


	bool quit = true;

	while (quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = false;

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = false;
					break;
				case SDLK_r:
					// Cover with red and update
					glClearColor(1.0, 0.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(sdlWindow);
					break;
				case SDLK_g:
					// Cover with green and update
					glClearColor(0.0, 1.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(sdlWindow);
					break;
				case SDLK_b:
					// Cover with blue and update
					glClearColor(0.0, 0.0, 1.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(sdlWindow);
					break;
				default:
					break;
				}
			}
		}

		loop();
	}

	destroy();

	return 0;
}
