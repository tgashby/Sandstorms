/**
 * @file Layer.h
 *
 * @author Tag Ashby
 * @date 8/2012
 *
 */
#pragma once

#include <string>
#include <Texture.h>

class Layer
{
public:
   Layer(std::string texStr, double moveRate, bool tiled);
   ~Layer();
   
   void draw(double camX);
   
private:
   TGA::Texture texture;
   double moveRate;
   bool tiled;
   int numShifts;
   double offsetX;
};
