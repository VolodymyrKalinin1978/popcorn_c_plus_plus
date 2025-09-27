#include "Platform.h"

// AsPlatform
//-------------------------------------------------------------------------------------------------------------------------
AsPlatform::AsPlatform():
   Inner_Width(21),
   X_Pos(AsConfig::Border_X_Offset),
   X_Step(AsConfig::Global_Scale * 2),
   Width(28),
   Platform_Circle_Pen(0),
   Platform_Inner_Pen(0),
   High_Light_Pen(0),
   Platform_Circle_Brush(0),
   Platform_Inner_Brush(0),
   Platform_Rect{},
   Prev_Platform_Rect{}
{}

//-------------------------------------------------------------------------------------------------------------------------
void AsPlatform::Init()
{
   High_Light_Pen = CreatePen(PS_SOLID, 0, RGB(255, 255, 255));

   AsConfig::Create_Pen_Brush(151, 0, 0, Platform_Circle_Pen, Platform_Circle_Brush);
   AsConfig::Create_Pen_Brush(0, 128, 192, Platform_Inner_Pen, Platform_Inner_Brush);
};

//-------------------------------------------------------------------------------------------------------------------------
void AsPlatform::Redraw_Platform(HWND hwnd)
{
   Prev_Platform_Rect = Platform_Rect;

   Platform_Rect.left = X_Pos * AsConfig::Global_Scale;
   Platform_Rect.top = AsConfig::Y_Pos * AsConfig::Global_Scale;
   Platform_Rect.right = Platform_Rect.left + Width * AsConfig::Global_Scale;
   Platform_Rect.bottom = Platform_Rect.top + Height * AsConfig::Global_Scale;

   InvalidateRect(hwnd,  &Prev_Platform_Rect, FALSE);
   InvalidateRect(hwnd,  &Platform_Rect, FALSE);
}

//-------------------------------------------------------------------------------------------------------------------------
// Відмалювання платформи у грі
void AsPlatform::Draw(HDC hdc, RECT &paint_area, HPEN bg_pen, HBRUSH bg_brush)
{
   int x = X_Pos;
   int y = AsConfig::Y_Pos;
   RECT intersection_rect;

   if (!IntersectRect(&intersection_rect, &paint_area, &Platform_Rect))
      return;
   // Очистка пдатформи

   SelectObject(hdc, bg_pen);
   SelectObject(hdc, bg_brush);
   Rectangle(hdc, Prev_Platform_Rect.left, Prev_Platform_Rect.top, Prev_Platform_Rect.right, Prev_Platform_Rect.bottom);

   // 1. Малюємо бокові кульки
   SelectObject(hdc, Platform_Circle_Pen);
   SelectObject(hdc, Platform_Circle_Brush);

   Ellipse(hdc, x * AsConfig::Global_Scale, y * AsConfig::Global_Scale, (x + Circle_Size) * AsConfig::Global_Scale, (y + Circle_Size) * AsConfig::Global_Scale);
   Ellipse(hdc, (x + Inner_Width)* AsConfig::Global_Scale, y * AsConfig::Global_Scale, (x + Inner_Width + Circle_Size) * AsConfig::Global_Scale, (y + Circle_Size) * AsConfig::Global_Scale);

   // 2. Мальюємо блік на лівій кульці
   SelectObject(hdc, High_Light_Pen);
   Arc(hdc, (x + 1) * AsConfig::Global_Scale, (y + 1) * AsConfig::Global_Scale, (x + Circle_Size - 1) * AsConfig::Global_Scale, (y + Circle_Size - 1) * AsConfig::Global_Scale,
      (x + 1 + 1) * AsConfig::Global_Scale, (y + 1) * AsConfig::Global_Scale, (x + 1) * AsConfig::Global_Scale, (y + 1 + 2) * AsConfig::Global_Scale);

   //Arc(hdc, (x + Inner_Width + 1) * Global_Scale, (y + 1) * Global_Scale, (x + Inner_Width + Circle_Size - 1) * Global_Scale, (y + Circle_Size - 1) * Global_Scale,
   //  (x + Inner_Width + Circle_Size + 1) * Global_Scale, y  * Global_Scale, (x + 1) * Global_Scale, (y + 1 + 2) * Global_Scale);

   // 3. Мальюємо середнью частину платформи
   SelectObject(hdc, Platform_Inner_Pen);
   SelectObject(hdc, Platform_Inner_Brush);

   RoundRect(hdc, (x + 4) * AsConfig::Global_Scale, (y + 1) * AsConfig::Global_Scale, (x + 4 + Inner_Width - 1) * AsConfig::Global_Scale, (y + 1 + 5) * AsConfig::Global_Scale, 3 * AsConfig::Global_Scale, 3 * AsConfig::Global_Scale);

}

//-------------------------------------------------------------------------------------------------------------------------
