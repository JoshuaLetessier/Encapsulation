#pragma once
#include "Graphic.h"
#include "Ball.h"

class GraphicGDI : public Graphic {
public:
    HDC hdc;

    GraphicGDI(HDC memDC);
    virtual ~GraphicGDI();

    void init(HWND hwnd) override;
    void draw(Ball* ball) override;
    void removeTexture(Ball* ball) override;
    void display() override;
    void clear() override;
    std::wstring ConvertToWideChar(const char* charArray);
    bool LoadBitmapCustom(const std::wstring& filename);
    void setHDC(HDC hdc);

private:
    HWND hwnd;
    HBITMAP hBitmap;
    HDC memDC;
};