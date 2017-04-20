#include "TileMap.h"
#include "noiseutils.h"
#include <stdlib.h>     
#include <time.h>  
#include <iostream>
using namespace noise;

void Noisify(double * level, module::Perlin myModule, TileMap& map, int width, int height)
{
	srand(time(NULL));
	myModule.SetSeed(rand() * 100);
	for (unsigned int i = 0; i < width; ++i) {
		for (unsigned int j = 0; j < height; ++j)
		{
			level[i + j * width] = myModule.GetValue(double(i)/16, double(j)/16, (double)0.5);
		}
	}
	/*for (unsigned int i = 0; i < width; ++i) {
		for (unsigned int j = 0; j < height; ++j)
		{
			std::cout << level[i + j * width] << ", ";
		}
		std::cout << std::endl;
	}*/
	for (unsigned int i = 0; i < width; ++i) {
		for (unsigned int j = 0; j < height; ++j)
		{
			double t = level[i + j * width];
			if (t < -.5)
			{
				level[i + j * width] = 28;//Water
			}
			else if (t >= -.5 && t < -.3)
			{
				level[i + j * width] = 19;//Beach
			}
			else if (t >= -.3 && t < .2)
			{
				level[i + j * width] = 220;//Land
			}
			else if (t >= .2 && t < .6)
			{
				level[i + j * width] = 54;//Trees
			}
			else
			{
				level[i + j * width] = 62;//Mountain
			}

		}
	}
	map.load("set.gif", sf::Vector2u(16, 16), level, width, height);
}
int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(1024, 512), "Tilemap");
	module::Perlin myModule;
	myModule.SetSeed(0);
	/*utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(512, 256);
	heightMapBuilder.SetBounds(2.0, 6.0, 1.0, 5.0);
	heightMapBuilder.Build();
	utils::RendererImage renderer;
	utils::Image image;*/
	//renderer.SetSourceNoiseMap(heightMap);
	//renderer.SetDestImage(image);
	//renderer.ClearGradient();
	//renderer.AddGradientPoint(-1.0000, utils::Color(0, 0, 128, 255)); // deeps
	//renderer.AddGradientPoint(-0.2500, utils::Color(0, 0, 255, 255)); // shallow
	//renderer.AddGradientPoint(0.0000, utils::Color(0, 128, 255, 255)); // shore
	//renderer.AddGradientPoint(0.0625, utils::Color(240, 240, 64, 255)); // sand
	//renderer.AddGradientPoint(0.1250, utils::Color(32, 160, 0, 255)); // grass
	//renderer.AddGradientPoint(0.3750, utils::Color(224, 224, 0, 255)); // dirt
	//renderer.AddGradientPoint(0.7500, utils::Color(128, 128, 128, 255)); // rock
	//renderer.AddGradientPoint(1.0000, utils::Color(255, 255, 255, 255)); // snow
	//renderer.Render();
	
	/*utils::WriterBMP writer;
	writer.SetSourceImage(image);
	writer.SetDestFilename("tutorial.bmp");
	writer.WriteDestFile();*/
	// define the level with an array of tile indices
	/*double level[] =
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	};*/
	double level[32768];
	
	

	// create the tilemap from the level definition
	TileMap map;
	int width = 256;
	int height = 128;
	Noisify(level, myModule, map, width, height);
	

	// run the main loop
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// draw the map
		window.clear();
		window.draw(map);
		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Noisify(level, myModule, map, width, height);
		}
	}

	return 0;
}