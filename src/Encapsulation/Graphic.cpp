#include "pch.h"
#include "Graphic.h"

Graphic::Graphic()
{
}

Graphic::~Graphic()
{
}

void Graphic::init(HWND hwnd)
{
}

void Graphic::draw(Ball* ball)
{
}

void Graphic::loadTexture(Ball* ball)
{
}

void Graphic::display()
{
}

void Graphic::clear()
{
}

bool Graphic::isBMP24Bits(std::string texturePath)
{
    std::ifstream file(texturePath, std::ios::binary);
    if (!file) {
        MessageBox(NULL, L"Erreur: Impossible d'ouvrir le fichier", L"Erreur", MB_OK | MB_ICONERROR);
        return false;
    }

    // Vérification de l'en-tête BMP
    unsigned char header[54]; // L'en-tête d'un BMP fait 54 octets
    file.read(reinterpret_cast<char*>(header), 54);

    // Vérifier les 2 premiers octets pour "BM" (signature BMP)
    if (header[0] != 'B' || header[1] != 'M') {
        MessageBox(NULL, L"Erreur: Ce fichier n'est pas un BMP", L"Erreur", MB_OK | MB_ICONERROR);
        file.close();
        return false;
    }

    // Vérifier la profondeur de couleur (nombre de bits par pixel)
    int bitDepth = header[28];  // L'indice 28 contient la profondeur de couleur

    if (bitDepth != 24) {
        MessageBox(NULL, L"Erreur: Le fichier BMP n'est pas en 24 bits", L"Erreur", MB_OK | MB_ICONERROR);
        file.close();
        return false;
    }

    file.close();
    return true;
}
