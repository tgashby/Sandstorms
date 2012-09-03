/**
 * @file SoundManager.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */
#include <SDL.h>
#include <map>
#include <string>
#include "Sound.h"
#include "Music.h"

namespace TGA
{
   /**
    * @class SoundManager
    *
    * @brief Manages all sounds and music files
    *
    * Differentiates between Sounds and Music. At the end of the day, there's
    * really almost no difference.
    */
   class SoundManager 
   {
   public:
      SoundManager();

      /**
      * addSound
      *
      * Add a sound to the manager.
      * @param sound - pointer to the Sound
      * @param soundName - the name to give the sound
      */
      void addSound (Sound* sound, std::string soundName);

      /**
      * removeSound
      *
      * Removes a sound from the collection.
      * @param soundName - the name given to the sound
      */
      void removeSound (std::string soundName);

      /**
      * playSound
      *
      * Plays the given sound a set number of times.
      * @param soundName - the name given to the sound
      * @param loops - the number of times to play the sound, -1 for indefinitely
      */
      void playSound (std::string soundName, int loops);

      /**
      * pauseSound
      *
      * Pauses the given sound.
      * @param soundName - the name given to the sound
      */
      void pauseSound (std::string soundName);

      /**
      * removeAllSounds
      *
      * Remove every sound in the collection.
      */
      void removeAllSounds ();

      /**
      * addMusic
      *
      * Add a music track to the collection.
      * @param music - the pointer to the Music
      * @param musicName - the name to give to the music track
      */
      void addMusic (Music* musicTrack, std::string musicName);

      /**
      * removeMusic
      *
      * Remove the given music track.
      * @param musicName - the name given to the music track
      */
      void removeMusic (std::string musicName);

      /**
      * playMusic
      *
      * Plays the given music track a number of times.
      * @param musicName - the name given to the music track
      * @param loops - the number of times to play the track,
      * -1 for indefinitely
      */
      void playMusic (std::string musicName, int loops);

      /**
      * pauseMusic
      *
      * Pauses the given music.
      * @param soundName - the name given to the sound
      */
      void pauseMusic (std::string musicName);

      /**
      * removeAllMusic
      *
      * Removes all music tracks from the collection.
      */
      void removeAllMusic ();

      /**
      * pauseAllSounds
      *
      * Pauses all sounds.
      */
      void pauseAllSounds();

   private:
      std::map<std::string, Sound*> sounds;
      std::map<std::string, Music*> music;
   };
}
