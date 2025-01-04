#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <string>

using string = std::string;

class GameObject {
    private:
        SDL_Rect rect;

    public:
        SDL_Rect* getRect() { return &rect; }
        void setRect(const SDL_Rect& newRect) { rect = newRect; }
        void print();
};

class Level {
    private:
        std::string name;
        Uint16 numPlatforms = 0;

    public:
        Level() = default;
        ~Level() = default;

        std::vector<GameObject> platforms;
        GameObject ground;  

        string getName() const { return name; }
        void setName(const std::string& newName) { name = newName; }
        
        void print(){
            std::cout << "Name:" << this->name << std::endl;
            std::cout << "numPlatforms: " << this->numPlatforms << std::endl;
        }
        void addPlatform(GameObject newObject )
        {
            this->platforms.push_back(newObject);
            this->numPlatforms++;
        }

};

#endif
