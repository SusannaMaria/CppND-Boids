#include "AltSpriteHolder.hpp"
#include "PolarVector.hpp"
#include <cmath>
#include <iostream>

AltSpriteHolder::AltSpriteHolder()
    : VertexHolder(), PositionHolder(), Quantity(0), ScaleHolder(), AngleHolder(), Tex(nullptr)
{
}

unsigned int AltSpriteHolder::addSprite()
{

    for (unsigned j = 0; j < 4; ++j)
    {
        VertexHolder.push_back(sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Color(255, 255, 255, 255)));
    }
 
    Quantity+=1;
    PositionHolder.push_back(sf::Vector2f(8, 8));
    ScaleHolder.push_back(sf::Vector2f(1.f, 1.f));
    AngleHolder.push_back(0.f);
    TexRectHolder.push_back(sf::IntRect(0, 0, 0, 0));
    setTextureRect(Quantity-1, sf::IntRect(0, 0, Tex->getSize().x, Tex->getSize().y));
    return Quantity-1;
}

AltSpriteHolder::AltSpriteHolder(sf::Texture &T, const unsigned amount)
    : VertexHolder(), PositionHolder(), Quantity(amount), ScaleHolder(), AngleHolder(), Tex(&T)
{
    VertexHolder.reserve(amount * 4);
    PositionHolder.reserve(amount);
    ScaleHolder.reserve(amount);
    AngleHolder.reserve(amount);

    for (unsigned i = 0; i < amount; ++i)
    {
        for (unsigned j = 0; j < 4; ++j)
        {
            VertexHolder.push_back(sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Color(255, 255, 255, 255)));
        }

        PositionHolder.push_back(sf::Vector2f(0, 0));
        ScaleHolder.push_back(sf::Vector2f(1.f, 1.f));
        AngleHolder.push_back(0.f);
        setTextureRect(i, sf::IntRect(0, 0, Tex->getSize().x, Tex->getSize().y));
    }
}

AltSpriteHolder::~AltSpriteHolder() {}

AltSpriteHolder::AltSpriteHolder(const AltSpriteHolder &other)
{
    Quantity = other.Quantity;
    Tex = other.Tex;
    VertexHolder = other.VertexHolder;
    AngleHolder = other.AngleHolder;
    PositionHolder = other.PositionHolder;
    ScaleHolder = other.ScaleHolder;
    TexRectHolder = other.TexRectHolder;
    hasTexture = other.hasTexture;
}

AltSpriteHolder &AltSpriteHolder::operator=(const AltSpriteHolder &rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    Quantity = rhs.Quantity;
    Tex = rhs.Tex;
    VertexHolder = rhs.VertexHolder;
    AngleHolder = rhs.AngleHolder;
    PositionHolder = rhs.PositionHolder;
    ScaleHolder = rhs.ScaleHolder;
    TexRectHolder = rhs.TexRectHolder;
    hasTexture = rhs.hasTexture;
    return *this;
}

void AltSpriteHolder::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.texture = Tex;
    target.draw(&VertexHolder[0], static_cast<unsigned>(VertexHolder.size()), sf::Quads, states);
}

void AltSpriteHolder::setTexture(sf::Texture &T)
{
    Tex = &T;
    setGlobalTextureRect(sf::IntRect(0, 0, Tex->getSize().x, Tex->getSize().y));
}

void AltSpriteHolder::setTextureRect(const unsigned index, const sf::IntRect &IR)
{
    TexRectHolder[index] = IR;
    updateTexCoords(index);
    updateVertexCoords(index, false);
}

void AltSpriteHolder::setGlobalTextureRect(const sf::IntRect &IR)
{
    for (unsigned i = 0; i < Quantity; ++i)
    {
        setTextureRect(i, IR);
    }
}

void AltSpriteHolder::updateTexCoords(const unsigned index)
{
    float left = static_cast<float>(TexRectHolder[index].left);
    float right = left + TexRectHolder[index].width;
    float top = static_cast<float>(TexRectHolder[index].top);
    float bottom = top + TexRectHolder[index].height;

    unsigned I = index * 4;

    VertexHolder[I++].texCoords = sf::Vector2f(left, top);
    VertexHolder[I++].texCoords = sf::Vector2f(left, bottom);
    VertexHolder[I++].texCoords = sf::Vector2f(right, bottom);
    VertexHolder[I].texCoords = sf::Vector2f(right, top);
}

void AltSpriteHolder::updateVertexCoords(const unsigned index, const bool Reset)
{
    sf::Vector2u S;
    S.x = TexRectHolder[index].width * ScaleHolder[index].x;
    S.y = TexRectHolder[index].height * ScaleHolder[index].y;

    unsigned I = index * 4;

    VertexHolder[I++].position = sf::Vector2f(0, 0);
    VertexHolder[I++].position = sf::Vector2f(0, S.y);
    VertexHolder[I++].position = sf::Vector2f(S.x, S.y);
    VertexHolder[I].position = sf::Vector2f(S.x, 0);

    if (Reset)
    {
        PositionHolder[index].x = 0.f;
        PositionHolder[index].y = 0.f;
    }
    else
    {
        move(index, PositionHolder[index]);
    }
}

void AltSpriteHolder::move(const unsigned index, const float x, const float y)
{
    unsigned limit = (index * 4) + 4;
    for (unsigned I = index * 4; I < limit; ++I)
    {
        VertexHolder[I].position.x += x;
        VertexHolder[I].position.y += y;
    }
    PositionHolder[index].x += x;
    PositionHolder[index].y += y;
}

void AltSpriteHolder::move(const unsigned index, const sf::Vector2f &V)
{
    move(index, V.x, V.y);
}

void AltSpriteHolder::globalMove(const sf::Vector2f &V)
{
    for (unsigned i = 0; i < Quantity; ++i)
    {
        move(i, V.x, V.y);
    }
}

void AltSpriteHolder::setPosition(const unsigned index, const float x, const float y)
{
    move(index, -(PositionHolder[index].x), -(PositionHolder[index].y));
    move(index, x, y);
}

void AltSpriteHolder::setPosition(const unsigned index, const sf::Vector2f &V)
{
    setPosition(index, V.x, V.y);
}

void AltSpriteHolder::setGlobalPosition(const sf::Vector2f &V)
{
    for (unsigned i = 0; i < Quantity; ++i)
    {
        setPosition(i, V);
    }
}

void AltSpriteHolder::setRotation(const unsigned index, const float ang)
{
    float ang_t = ang;
    AngleHolder[index] = fmod(ang, 360.f);
    PolarVector P = TurnToPolar(PositionHolder[index]);
    P.t = ang_t;
    setPosition(index, P.TurnToRectangular());
}

void AltSpriteHolder::setGlobalRotation(const float ang)
{
    for (unsigned i = 0; i < Quantity; ++i)
    {
        setRotation(i, ang);
    }
}

void AltSpriteHolder::rotate(const unsigned index, const float ang)
{
    setRotation(index, AngleHolder[index] + ang);
}

void AltSpriteHolder::globalRotate(const float ang)
{
    for (unsigned i = 0; i < Quantity; ++i)
    {
        rotate(i, ang);
    }
}

void AltSpriteHolder::rotateAroundSelf(const unsigned index, const float ang, const bool absolute = false)
{
    float ang_t = ang * toRadians;
    sf::Vector2f Tmp = PositionHolder[index];
    sf::Vector2f Off(-(TexRectHolder[index].width / 2.f), -(TexRectHolder[index].height / 2.f));

    setPosition(index, Off);
    unsigned limit = (index * 4) + 4;
    for (unsigned i = index * 4; i < limit; ++i)
    {
        PolarVector P(TurnToPolar(VertexHolder[i].position));
        P.t += ang_t;
        VertexHolder[i].position = P.TurnToRectangular();
    }
    move(index, Tmp - Off);
}

void AltSpriteHolder::globalRotateAroundSelf(const float ang)
{
    for (unsigned i = 0; i < Quantity; ++i)
    {
        rotateAroundSelf(i, ang);
    }
}

void AltSpriteHolder::resetSelfRotation(const unsigned index)
{
    updateVertexCoords(index, false);
}

void AltSpriteHolder::resetGlobalSelfRotation()
{
    for (unsigned i = 0; i < Quantity; ++i)
    {
        updateVertexCoords(i, false);
    }
}

void AltSpriteHolder::setScale(const unsigned index, const float x, const float y)
{
    ScaleHolder[index].x = x;
    ScaleHolder[index].y = y;
    for (unsigned i = index * 4; i < (index * 4) + 4; ++i)
    {
        VertexHolder[i].position.x *= x;
        VertexHolder[i].position.y *= y;
    }
}

void AltSpriteHolder::setScale(const unsigned index, const sf::Vector2f &V)
{
    setScale(index, V.x, V.y);
}

void AltSpriteHolder::setGlobalScale(const sf::Vector2f &V)
{
    for (unsigned i = 0; i < Quantity; ++i)
    {
        setScale(i, V);
    }
}

sf::Vector2f AltSpriteHolder::getPosition(const unsigned index) const
{
    return PositionHolder[index];
}

sf::Vector2f AltSpriteHolder::getScale(const unsigned index) const
{
    return ScaleHolder[index];
}

float AltSpriteHolder::getRotation(const unsigned index) const
{
    return AngleHolder[index];
}
