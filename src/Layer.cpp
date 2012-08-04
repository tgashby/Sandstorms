#include "..\include\Layer.h"

Layer::Layer( std::string texStr, double moveRate, bool tiled )
   : moveRate(moveRate)
   , tiled(tiled)
{
   texture.loadTexture(texStr);

   offsetX = 0;
   numShifts = 1;
}


Layer::~Layer()
{
}

void Layer::draw( double camX )
{
   if (tiled && camX >= texture.getWidth() / 2 * numShifts)
   {
      numShifts++;
      offsetX += texture.getWidth() / 2;
   }

   if (tiled && camX <= offsetX)
   {
      numShifts--;
      offsetX -= texture.getWidth() / 2;
   }

   texture.draw(static_cast<float>(camX * moveRate + offsetX), 0);
}
