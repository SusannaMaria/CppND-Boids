

///.cpp

///Sprite Container class
///.hpp

#ifndef ALTSPRITEHOLDER_HPP
#define ALTSPRITEHOLDER_HPP

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Texture.hpp>

const float APi = 3.141592654;
const float toRadians = APi/180;
const float toDegrees = 180/APi;


class AltSpriteHolder : public sf::Drawable
{
    public:
        AltSpriteHolder(const unsigned amount);
        AltSpriteHolder(sf::Texture& T, const unsigned amount);
        ~AltSpriteHolder();

        AltSpriteHolder(const AltSpriteHolder& other);
        AltSpriteHolder& operator=(const AltSpriteHolder& other);

        void setTexture(sf::Texture& T);

        void setTextureRect(const unsigned index, const sf::IntRect& IR);
        void setGlobalTextureRect(const sf::IntRect& IR);
        void move(const unsigned index, const sf::Vector2f& V);
        void move(const unsigned index, const float x, const float y);
        void globalMove(const sf::Vector2f& V);

        void setPosition(const unsigned index, const sf::Vector2f& V);
        void setPosition(const unsigned index, const float x, const float y);
        void setGlobalPosition(const sf::Vector2f& V);

        void setRotation(const unsigned index, const float ang);
        void setGlobalRotation(const float ang);

        void rotate(const unsigned index, const float ang);
        void globalRotate(const float ang);

        void rotateAroundSelf(const unsigned index, const float ang, const bool absolute);
        void globalRotateAroundSelf(const float ang);

        void resetSelfRotation(const unsigned index);
        void resetGlobalSelfRotation();

        void scale(const unsigned index, const sf::Vector2f& V);
        void globalScale(const sf::Vector2f& V);

        void setScale(const unsigned index, const float x, const float y);
        void setScale(const unsigned index, const sf::Vector2f& V);
        void setGlobalScale(const sf::Vector2f& V);

        sf::Vector2f getPosition(const unsigned index) const;
        sf::Vector2f getScale(const unsigned index) const;
        float getRotation(const unsigned index) const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:

        unsigned Quantity;

        sf::Texture* Tex;

        std::vector<sf::Vertex> VertexHolder;

        std::vector<float> AngleHolder;
        std::vector<sf::Vector2f> PositionHolder;
        std::vector<sf::Vector2f> ScaleHolder;
        std::vector<sf::IntRect> TexRectHolder;

        bool hasTexture;

        void updateTexCoords(const unsigned index);
        void updateVertexCoords(const unsigned index, const bool Reset = true);

        void updateAngleRanges(const unsigned index);

};

#endif // ALTSPRITEHOLDER_HPP