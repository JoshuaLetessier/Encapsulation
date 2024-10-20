#include "pch.h"

#include "GraphicGDI.h"

GraphicGDI::GraphicGDI(HDC memDC) {
	this->memDC = memDC;
}

GraphicGDI::~GraphicGDI() {
    // Libérer le Device Context quand la fen�tre se ferme
    if (hdc && hwnd) {
        ReleaseDC(hwnd, hdc);
    }
    if (memDC) {
        DeleteDC(memDC);
    }
}

void GraphicGDI::init(HWND hwnd) {
    this->hwnd = hwnd;
    hdc = GetDC(hwnd);
}

void GraphicGDI::draw(Ball* ball) {
    if (ball == nullptr) {
        return;
    }

    // Charger la texture de la balle
    std::wstring texturePath = ConvertToWideChar(ball->getTexture());
    if (!LoadBitmapCustom(texturePath)) {
        MessageBox(NULL, (L"Échec du chargement du bitmap pour : " + texturePath).c_str(), L"Erreur", MB_OK);
        return;
    }

    if (hBitmap == NULL) {
        MessageBox(NULL, L"Le bitmap est NULL après chargement", L"Erreur", MB_OK);
        return;
    }

    // Récupérer les dimensions du bitmap
    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);

    // Coordonnées et taille de la balle
    int x = static_cast<int>(ball->getX());
    int y = static_cast<int>(ball->getY());
    int size = static_cast<int>(ball->getSize());

    // Ajuster les coordonnées pour centrer l'image
    int centeredX = x - size / 2;
    int centeredY = y - size / 2;

    // Créer un DC temporaire et dessiner le bitmap centré avec AlphaBlend
    HDC tempDC = CreateCompatibleDC(memDC);
    HGDIOBJ oldBitmap = SelectObject(tempDC, hBitmap);

    BLENDFUNCTION blendFunc;
    blendFunc.BlendOp = AC_SRC_OVER;
    blendFunc.BlendFlags = 0;
    blendFunc.SourceConstantAlpha = 255;  // Alpha constant (255 = opaque)
    blendFunc.AlphaFormat = AC_SRC_ALPHA;  // Spécifier que le bitmap a un canal alpha

    AlphaBlend(memDC, centeredX, centeredY, size, size, tempDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, blendFunc);

    // Nettoyage
    SelectObject(tempDC, oldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(tempDC);

}

void GraphicGDI::removeTexture(Ball* ball)
{
}

void GraphicGDI::display() {}

void GraphicGDI::clear() {
    // Effacer la fen�tre en la remplissant avec une couleur blanche
    RECT rect;
    GetClientRect(hwnd, &rect);
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));  // Pinceau blanc
    FillRect(hdc, &rect, hBrush);  // Effacer la fen�tre

    DeleteObject(hBrush);  // Lib�rer les ressources
}

std::wstring GraphicGDI::ConvertToWideChar(const char* charArray) {
    std::string s = charArray;
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    std::wstring buf(len, L'\0');
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, &buf[0], len);
    return buf;
}

bool GraphicGDI::LoadBitmapCustom(const std::wstring& filename) {
    FILE* file;
    errno_t err = _wfopen_s(&file, filename.c_str(), L"rb");
    if (err != 0 || file == NULL) {
        MessageBox(NULL, L"Could not LOAD file", L"Error", MB_OK | MB_ICONERROR);
        return false;
    }

    BITMAPFILEHEADER bitmapFileH;
    fread(&bitmapFileH, sizeof(BITMAPFILEHEADER), 1, file);
    if (bitmapFileH.bfType != 0x4D42) {
        MessageBox(NULL, L"Not a valid BMP file", L"Error", MB_OK | MB_ICONERROR);
        fclose(file);
        return false;
    }

    BITMAPINFOHEADER bitmapInfoH;
    fread(&bitmapInfoH, sizeof(BITMAPINFOHEADER), 1, file);

    // Le BMP est en 24 bits, nous allons le convertir en 32 bits
    int width = bitmapInfoH.biWidth;
    int height = bitmapInfoH.biHeight;
    int paddedRowSize = ((width * 3 + 3) & (~3));  // 24 bits (3 octets par pixel) avec alignement
    int newRowSize = width * 4;  // 32 bits (4 octets par pixel)
    DWORD newSizeImage = newRowSize * height;

    // Allouer de la mémoire pour l'image 24 bits d'origine
    BYTE* originalData = new BYTE[paddedRowSize * height];
    if (!originalData) {
        MessageBox(NULL, L"Memory allocation failed", L"Error", MB_OK | MB_ICONERROR);
        fclose(file);
        return false;
    }

    // Lire les données du bitmap 24 bits
    fseek(file, bitmapFileH.bfOffBits, SEEK_SET);
    fread(originalData, 1, paddedRowSize * height, file);
    fclose(file);

    // Allouer de la mémoire pour la nouvelle image 32 bits
    BYTE* newBitmapData = new BYTE[newSizeImage];
    if (!newBitmapData) {
        MessageBox(NULL, L"Memory allocation for 32-bit image failed", L"Error", MB_OK | MB_ICONERROR);
        delete[] originalData;
        return false;
    }

    // Convertir chaque pixel 24 bits en 32 bits, en ajoutant la transparence pour le magenta
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int originalIndex = y * paddedRowSize + x * 3;
            int newIndex = y * newRowSize + x * 4;

            BYTE blue = originalData[originalIndex];
            BYTE green = originalData[originalIndex + 1];
            BYTE red = originalData[originalIndex + 2];

            // Si la couleur est magenta (FF00FF), rendre le pixel transparent
            if (red == 0xFF && green == 0x00 && blue == 0xFF) {
                newBitmapData[newIndex] = 255;
                newBitmapData[newIndex + 1] = 255;
                newBitmapData[newIndex + 2] = 255;
                newBitmapData[newIndex + 3] = 0x00;  // Alpha à 0 pour transparence
            }
            else {
                newBitmapData[newIndex] = blue;
                newBitmapData[newIndex + 1] = green;
                newBitmapData[newIndex + 2] = red;
                newBitmapData[newIndex + 3] = 0xFF;  // Alpha à 255 (opaque)
            }
        }
    }

    // Créer un nouveau bitmap 32 bits avec les données converties
    BITMAPINFO newBitmapInfo;
    memset(&newBitmapInfo, 0, sizeof(BITMAPINFO));
    newBitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    newBitmapInfo.bmiHeader.biWidth = width;
    newBitmapInfo.bmiHeader.biHeight = height;
    newBitmapInfo.bmiHeader.biPlanes = 1;
    newBitmapInfo.bmiHeader.biBitCount = 32;  // Format 32 bits
    newBitmapInfo.bmiHeader.biCompression = BI_RGB;
    newBitmapInfo.bmiHeader.biSizeImage = newSizeImage;

    HDC hdc = GetDC(NULL);
    hBitmap = CreateDIBitmap(hdc, &newBitmapInfo.bmiHeader, CBM_INIT, newBitmapData, &newBitmapInfo, DIB_RGB_COLORS);
    ReleaseDC(NULL, hdc);

    // Libérer la mémoire allouée
    delete[] originalData;
    delete[] newBitmapData;

    return hBitmap != NULL;
}

void GraphicGDI::setHDC(HDC hdc) {
    this->hdc = hdc;
}