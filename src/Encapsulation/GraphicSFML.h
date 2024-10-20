#pragma once

#ifdef _SFML
#include "Graphic.h"

class GraphicSFML : public Graphic
{
public:
    sf::RenderWindow* window;
    std::unordered_map<std::string, sf::Texture> textureCache;
    std::unordered_map<Ball*, sf::Texture> textures;
    sf::Sprite sprite;

	GraphicSFML();
	virtual ~GraphicSFML();

	void init(HWND hwnd) override;
	void draw(Ball* ball) override;
	bool isTextureLoaded(Ball* ball) const;
	void loadTexture(Ball* ball) override;
	void removeTexture(Ball* ball) override;
	void display() override;
	void clear() override;

};

#endif // _SFML