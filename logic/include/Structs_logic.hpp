#ifndef STRUCT_LOGIC_HPP
#define STRUCT_LOGIC_HPP

#include <thread>
#include <map>
#include <string>
#include <iterator>
#include <iostream>
#include <list>
#include <cmath>

class Vector2 {
    private:
        float _x;
        float _y;

    public:
        Vector2();

        Vector2(float x, float y);

        float get_x() const;
        float get_y() const;

        Vector2 add(const Vector2& v) const;

        float length() const;

        Vector2 scale(float scale) const;

        Vector2 subtract(const Vector2& v) const;

        Vector2 normalize() const;

        static Vector2 zero();

        bool operator==(const Vector2& other) const;

        void set_x(float x);
        void set_y(float y);
};

class Retangulo {
    private:
        Vector2 _position;
        float _width;
        float _height;

    public:
        Retangulo();

        Retangulo(const Vector2& position, float width, float height);

        const Vector2& get_position() const;

        float get_width() const;

        float get_height() const;

        bool CheckCollisionRecs(const Retangulo& rec1, const Retangulo& rec2);

        bool operator==(const Retangulo& other) const;
};

/*class Texture2D {
    private:
        unsigned int _id;
        int _width;
        int _height;
        int _format;

    public:
        Texture2D(unsigned int id, int width, int height, int format);

        unsigned int get_id() const;

        int get_width() const;

        int get_height() const;

        int get_format() const;
};*/

#endif