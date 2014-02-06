#include <iostream>
#include <map>
#include <exception>
#include <string>
#include <vector>
#include <fstream>


#include "Factory.hpp"
#include "Clonable.hpp"
#include "Test.hpp"

#include <stdlib.h>  
#include <SDL/SDL.h> // Librairie SDL

std::ostream & operator << (std::ostream & o, const Test & c) { o << c.to_s(); return o;}
std::ostream & operator << (std::ostream & o, const Clonable & c) { o << c.to_s(); return o;}

int main()
{

	SDL_Surface *screen;     
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
      printf( "Impossible d'initialiser SDL:  %s\n", SDL_GetError( ) );
      exit( 1 );
  }
  atexit( SDL_Quit ); 

  screen = SDL_SetVideoMode( 640, 480, 16, SDL_HWSURFACE );
 
  if( screen == NULL )
  {
      printf( "Impossible d'initialiser le mode vidéo: %s\n", SDL_GetError( ) );
      exit( 1 );
  }   

  SDL_Delay( 3000 );

  return 0;
    
	std::vector<Clonable*> v;
	Factory<Clonable> myFactory;

	Test t;


	std::ifstream file("data.txt");
  std::string line;
  
  while(std::getline(file,line) )
  {
    try
    {
      v.push_back(myFactory.make(line));
    }
    catch( Factory<Clonable>::TypeNotFound & e )
    {
      std::cout << e.what() << "\n";
    }
  }
	return 0;
}


// g++ main.cpp --std=c++0x -o program && ./program 
