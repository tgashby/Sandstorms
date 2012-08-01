/**
 * @file Sound.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */


namespace TGA
{
   /**
    * @class Sound
    *
    * @brief Represents a sound effect (as opposed to a music track)
    *
    */
   class Sound 
   {
   public:
      /**
      * Sound
      *
      * Loads a song from the given filename.
      * @param fileName - path to the sound file
      */
      Sound (std::string fileName);

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
      Mix_Chunk* sound;
   };
}
