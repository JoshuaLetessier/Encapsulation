#include "pch.h"
#ifdef _SFML
#include "GraphicSFML.h"

#include "Ball.h"


GraphicSFML::GraphicSFML()
{
	
}
GraphicSFML::~GraphicSFML()
{
	textures.clear();
    //if (window) {
    //    delete windo2w;
    //}

}

void GraphicSFML::init(HWND hwnd) {
    window = new sf::RenderWindow(hwnd);
}

void GraphicSFML::draw(Ball* ball) {
    // Vérifie si la texture est déjà chargée pour la balle
    if (!isTextureLoaded(ball)) {
        loadTexture(ball);  // Charge la texture si elle n'est pas déjà en cache
    }

    // Récupère la texture associée à la balle
    auto it = textures.find(ball);
    if (it != textures.end()) {
        sprite.setTexture(it->second);  // Associe la texture au sprite
    }
    else {
        MessageBox(NULL, L"Texture not found for ball", L"Error", MB_OK);
        return;
    }

    // Position et taille du sprite selon la balle
    sprite.setPosition(ball->getX(), ball->getY());
    sprite.setScale(ball->getSize() / sprite.getLocalBounds().width,
        ball->getSize() / sprite.getLocalBounds().height);

    // Vérifie que la fenêtre est ouverte avant de dessiner
    if (window && window->isOpen()) {
        window->draw(sprite);
    }
    else {
        MessageBox(NULL, L"Window not found or closed", L"Error", MB_OK);
    }
}

bool GraphicSFML::isTextureLoaded(Ball* ball) const {
    return textures.find(ball) != textures.end();
}


void GraphicSFML::loadTexture(Ball* ball) {
    std::string texturePath = ball->getTexture();

    // Vérifie si la texture est déjà dans le cache global
    if (textureCache.find(texturePath) != textureCache.end()) {
        textures[ball] = textureCache[texturePath];  // Associe la texture à la balle
        return;
    }

    // Charger l'image à partir du fichier
    sf::Image image;
    if (!image.loadFromFile(texturePath)) {
        MessageBox(NULL, L"Erreur: Impossible de charger l'image BMP", L"Erreur de Chargement", MB_OK | MB_ICONERROR);
        return;
    }

    // Remplacer le magenta (FF00FF) par de la transparence
    for (unsigned int x = 0; x < image.getSize().x; ++x) {
        for (unsigned int y = 0; y < image.getSize().y; ++y) {
            sf::Color pixel = image.getPixel(x, y);
            if (pixel == sf::Color(255, 0, 255)) {  // Magenta
                image.setPixel(x, y, sf::Color(0, 0, 0, 0));  // Transparence
            }
        }
    }

    // Charger la texture depuis l'image traitée
    sf::Texture texture;
    texture.loadFromImage(image);
    
    // Ajout dans le cache global et lier la texture à la balle
    textureCache[texturePath] = texture;
    textures[ball] = textureCache[texturePath];
}

void GraphicSFML::removeTexture(Ball* ball) {
    auto it = textures.find(ball);
    if (it != textures.end()) {
        textures.erase(it);
    }
}

void GraphicSFML::display() {
    window->display();
}

void GraphicSFML::clear() {
    window->clear(sf::Color::Black);
}

#endif // _SFML
