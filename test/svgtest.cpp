#include "SDL_svg.h"

#ifdef _WIN32
#include <SDL.h>
#endif

#ifdef __linux__ 
#include <SDL2/SDL.h>
#endif

#include <signal.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480

int main(int argc, char *argv[])
{
int dx=0, dy=0;
SDL_Surface *screen;
SDL_Window* gWin = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* image_one = NULL;
int done;
SDL_Event event;
SDL_Rect full;
SDL_Rect image_full;
double Scalex, Scaley;
int redraw=0;
int code;

	if(argc<2)
	{
		printf("Usage: %s <filename> [dx] [dy]\n",argv[0]);
		exit(0);
	}

	/* Initialize SDL */
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
		exit(1);
	}
    
    
	/* Set 640x480 32 bpp video mode */
    gWin = SDL_CreateWindow( "SDL_SVG Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if( gWin == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        exit(1);
    }
    
    gRenderer = SDL_CreateRenderer( gWin, -1, SDL_RENDERER_ACCELERATED);
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        exit(1);
    }
    
    full.x = 0;
    full.y = 0;
    full.w = WIDTH;
    full.h = HEIGHT;
    
	SDL_svg_context *TestImage = SVG_Load (argv[1]); //load image
	SVG_SetOffset (TestImage, SVG_Width(TestImage) / 2, SVG_Height(TestImage) / 2); //create svg offset
    screen = SDL_CreateRGBSurface(SDL_SWSURFACE,WIDTH, HEIGHT,32,0,0,0,0);
    SDL_FillRect(screen, &full, SDL_MapRGB(screen->format, 0x80, 0x80, 0x80));
    
	if(argc>2) sscanf(argv[2], "%d", &dx); //load values of dx, dy
	if(argc>3) sscanf(argv[3], "%d", &dy);

	Scalex = screen->w / SVG_Width(TestImage);
	Scaley = screen->h / SVG_Height(TestImage);
	SVG_SetScale (TestImage, Scalex, Scaley);
	SVG_RenderToSurface (TestImage, screen->w/2+dx, screen->h/2+dy, screen);
    
    if (screen == NULL) 
    {
        fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
        exit(1);
    }
    
    image_one = SDL_CreateTextureFromSurface(gRenderer, screen); 
    if (image_one == NULL) 
    {
        fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
        exit(1);
    }

	done = 0;
    SDL_Event e;
	while ( !done )
	{
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                done = 1;
            }
        }
        SDL_SetRenderDrawColor( gRenderer, 0x80, 0x80, 0x80, 0xFF );
        SDL_RenderClear( gRenderer );
        SDL_RenderCopy(gRenderer, image_one, &full, NULL);
        SDL_RenderPresent( gRenderer );
	}
	SVG_Free (TestImage);
	return 0;
}
