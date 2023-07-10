#include "../logic/include/Structs_logic.hpp"

//
// VECTOR2
//

Vector2::Vector2() {
    
}

Vector2::Vector2(float x, float y){

    if (x < 0 || y < 0) {
        throw std::invalid_argument("A posicao nao pode ser negativa");
    }

    _x = x;
    _y = y;
}

float Vector2::get_x() const{
    return _x;
}

float Vector2::get_y() const{
    return _y;
}

void Vector2::set_x(int x){
    _x = x;
}

void Vector2::set_y(int y){
    _y = y;
}

Vector2 Vector2::add(const Vector2& v) const {
    return Vector2(_x + v.get_x(), _y + v.get_y());
}

float Vector2::length() const {
    return std::sqrt(_x * _x + _y * _y);
}

Vector2 Vector2::scale(float scale) const {
    return Vector2(_x * scale, _y * scale);
}

Vector2 Vector2::subtract(const Vector2& v) const {
    return Vector2(_x - v.get_x(), _y - v.get_y());
}

Vector2 Vector2::normalize() const {
    float length = this->length();
    if (length == 0) {
        return Vector2(0.0f, 0.0f);
    }
   
    return Vector2(_x / length, _y / length);
}

Vector2 Vector2::zero() {
    return Vector2(0.0f, 0.0f);
}


bool Vector2::operator==(const Vector2& other) const {
    return ((_x == other.get_x()) && (_y == other.get_y()));
}

//
// RETÂNGULO
//

Retangulo::Retangulo() {
    
}

Retangulo::Retangulo(const Vector2& position, float width, float height)
            : _position(position), _width(width), _height(height) {}

const Vector2& Retangulo::get_position() const {
    return _position;
}

float Retangulo::get_width() const {
    return _width;
}

float Retangulo::get_height() const {
    return _height;
}

bool Retangulo::CheckCollisionRecs(const Retangulo& rec1, const Retangulo& rec2) {
    const Vector2& pos1 = rec1.get_position();
    const Vector2& pos2 = rec2.get_position();
    float width1 = rec1.get_width();
    float height1 = rec1.get_height();
    float width2 = rec2.get_width();
    float height2 = rec2.get_height();

    bool collisionX = (pos1.get_x() + width1 >= pos2.get_x()) && (pos2.get_x() + width2 >= pos1.get_x());
    bool collisionY = (pos1.get_y() + height1 >= pos2.get_y()) && (pos2.get_y() + height2 >= pos1.get_y());

    return collisionX && collisionY;
}

bool Retangulo::operator==(const Retangulo& other) const {
    return (_position == other._position) && (_width == other._width) && (_height == other._height);
}

//
// TEXTURE
//

/*Texture2D::Texture2D(unsigned int id, int width, int height, int mipmaps, int format)
    : _id(id), _width(width), _height(height), _format(format) {}

unsigned int Texture2D::get_id() const {
    return _id;
}

int Texture2D::get_width() const {
    return _width;
}

int Texture2D::get_height() const {
    return _height;
}

int Texture2D::get_format() const {
    return _format;
}*/
