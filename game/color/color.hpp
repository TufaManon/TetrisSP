#pragma once
#include <string>
#include <initializer_list>
using ui8 = uint8_t;
using ui16 = uint16_t;

using std::string;

template <typename T>
T Max(std::initializer_list<T> list)
{
    if (list.size() == 0)
        return 0;
    auto it = list.begin();
    auto max = *it;
    it++;
    for (; it != list.end(); it++)
    {
        if (*it > max)
            max = *it;
    }
    return max;
}
/// <summary>
/// get the minimum one in the given list by use greater-than sign
/// </summary>
/// <typeparam name="T">the type of given list</typeparam>
/// <param name="list">initializer list of elements you want to compare</param>
/// <returns>the minimum element</returns>
template <typename T>
T Min(const std::initializer_list<T> list)
{
    auto it = list.begin();
    auto min = *it;
    it++;
    for (; it != list.end(); it++)
    {
        if (*it < min)
            min = *it;
    }
    return min;
}

struct RGBA
{
private:
    bool Check(std::string hex)
    {
        if (hex.size() == 0)
            return false;
        bool right_head = hex[0] == '#';
        bool right_range = true;
        bool right_size = hex.size() == 7 || hex.size() == 4;
        for (auto c : hex.substr(1))
        {
            right_range &= c >= 0x41 && c < 0x46 || c >= 0x61 && c <= 0x66 || c >= 0x30 && c <= 0x39;
        }
        return right_head && right_range && right_size;
    }

    int HexStringToInt(char c)
    {
        if (c <= 0x39)
            return c - 0x30;
        if (c <= 0x46)
            return c - (0x41 - 10);
        if (c <= 0x66)
            return c - (0x61 - 10);
        return 0;
    }

public:
    ui8 red, green, blue;
    float alpha;

    RGBA(const RGBA &right)
    {
        *this = right;
    }

    RGBA(int hex, float alpha = 1.0)
    {
        red = hex >> 16;
        green = (hex >> 8) - (red << 8);
        blue = hex - (hex << 8);
        this->alpha = alpha;
    }

    RGBA(std::string hex, float alpha = 1.0)
    {
        if (!Check(hex))
            return;
        if (hex.size() == 4)
        {
            SetRGBA((HexStringToInt(hex[1]) << 4) + HexStringToInt(hex[1]),
                    (HexStringToInt(hex[2]) << 4) + HexStringToInt(hex[2]),
                    (HexStringToInt(hex[3]) << 4) + HexStringToInt(hex[3]), alpha);
        }
        else
        {
            SetRGBA((HexStringToInt(hex[1]) << 4) + HexStringToInt(hex[2]),
                    (HexStringToInt(hex[3]) << 4) + HexStringToInt(hex[4]),
                    (HexStringToInt(hex[5]) << 4) + HexStringToInt(hex[6]), alpha);
        }
    }

    void SetRGBA(ui8 r, ui8 g, ui8 b, float a)
    {
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }

    RGBA(ui8 r = 255,
         ui8 g = 255,
         ui8 b = 255,
         float a = 1.0)
    {
        if (r > 255 || g > 255 || b > 255 || a > 1.0)
        {
            red = 255;
            blue = 255;
            green = 255;
            alpha = 1.0;
            return;
        }
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }

    constexpr double Nor(ui8 color) const
    {
        return ((double)color / 255);
    }

    unsigned int GetHue(double max, double min) const
    {
        if (max == min)
            return 0;

        int h = 0;

        auto _red = Nor(red);
        auto _green = Nor(green);
        auto _blue = Nor(blue);

        double diff = max - min;

        if (max == _red)
        {
            h = 60 * (_green - _blue) / diff;
            if (h >= 0)
                return h;
            else
                return 360 + h;
        }
        else if (max == _green)
            h = 60 * ((_blue - _red) / diff) + 120;
        else if (max == _blue)
            h = 60 * ((_red - _green) / diff) + 240;
        return h;
    }

    unsigned int GetHue() const
    {
        auto _red = Nor(red);
        auto _green = Nor(green);
        auto _blue = Nor(blue);
        return GetHue(Max({_red, _green, _blue}), Min({_red, _green, _blue}));
    }

    double GetSaturation() const
    {
        auto _red = Nor(red);
        auto _green = Nor(green);
        auto _blue = Nor(blue);
        return GetSaturation(Max({_red, _green, _blue}), Min({_red, _green, _blue}));
    }

    double GetSaturation(double max, double min) const
    {
        auto lightness = GetLightness(max, min);
        if (lightness == 0 || max == min)
            return 0;
        if (lightness <= 0.5)
            return (max - min) / (max + min);
        if (lightness > 0.5)
            return (max - min) / (2 - (max + min));
        return 0;
    }

    double GetLightness() const
    {
        auto _red = Nor(red);
        auto _green = Nor(green);
        auto _blue = Nor(blue);
        return GetLightness(Max({_red, _green, _blue}), Min({_red, _green, _blue}));
    }

    double GetLightness(double max, double min) const
    {
        return (max + min) / 2;
    }

    operator SDL_Color()
    {
        return { red, green, blue, (Uint8)(alpha * 255) };
    }
};

struct HSLA
{
    const double MAX_SATURATION = 1;
    const double MIN_SATURATOIN = 0;

    const double MAX_LIGHTNESS = 1;
    const double MIN_LIGHTNESS = 0;

    unsigned int hue = 0;
    double saturation = 0;
    double lightness = 0;

    float alpha;

    HSLA(double h, double s, double l, float a)
    {
        hue = h;
        saturation = s;
        lightness = l;
        alpha = a;
    }

    HSLA(const RGBA &color) : HSLA(color.GetHue(), color.GetSaturation(), color.GetLightness(), color.alpha)
    {
    }

    HSLA(const HSLA &hsla)
    {
        hue = hsla.hue;
        saturation = hsla.saturation;
        lightness = hsla.lightness;
        alpha = hsla.alpha;
    }

    HSLA &operator=(const HSLA &hsla)
    {
        hue = hsla.hue;
        saturation = hsla.saturation;
        lightness = hsla.lightness;
        alpha = hsla.alpha;
    }

    RGBA ToRGBA() const
    {
        return HSLA2RGBA(hue, saturation, lightness, alpha);
    }

private:
    double Hue2RGB(double v1, double v2, double vH) const
    {
        if (vH < 0)
            vH += 1.0;
        if (vH > 1)
            vH -= 1.0;
        if (6.0 * vH < 1)
            return v1 + (v2 - v1) * 6.0 * vH;
        if (2.0 * vH < 1)
            return v2;
        if (3.0 * vH < 2)
            return v1 + (v2 - v1) * ((2.0 / 3.0) - vH) * 6.0;
        return v1;
    }

    RGBA HSLA2RGBA(double h, double s, double l, double a) const
    {
        if (s == 0)
            return RGBA(255 * l, 255 * l, 255 * l, a);
        double q, p, hk = h / 360;
        if (l >= 0.5)
            q = (l + s) - (l * s);
        else
            q = l * (1 + s);
        p = 2 * l - q;

        return RGBA(255 * Hue2RGB(p, q, hk + (1.0 / 3.0)), 255 * Hue2RGB(p, q, hk), 255 * Hue2RGB(p, q, hk - (1.0 / 3.0)), a);
    }
};


