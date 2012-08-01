/**
 * @file Music.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */


namespace TGA
{
   /**
    * @class Music
    *
    * @brief Represents a music track (as opposed to a sound effect)
    *
    */
   class Music 
   {
   public:
      /**
      * Music
      *
      * Loads a music track from the given filename.
      * @param fileName - path to the sound file
      */
      Music (std::string fileName);

      /**
      * play
      *
      * Plays the sound a number of times, -1 for indefinitely.
      * @param loops - the number of times to play the sound.
      */
      void play (int loops);

      /**
      * pause
      *
      * Pauses the sound.
      */
      void pause ();
   private:
      Mix_Music* sound;
   };
}
