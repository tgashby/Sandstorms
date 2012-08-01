/**
 * @file Level.h
 *
 * @author Tag Ashby
 * @date 7/2012
 * 
 */
#pragma once

#include <Engine.h>
#include <Singleton.h>
#include <Texture.h>
#include <string>
#include <vector>
#include "Platform.h"
#include "Artifact.h"

/**
 * @class Level
 *
 * @brief Represents a single level, complete with platforms.
 *
 */
class Level 
{
public:
  /**
  * Level
  *
  * Creates a new Level with the specified background texture.
  * @param std::string backgroundTex - path to the texture file
  * @param moveRate - the rate at which the background moves with the camera
  * @param bool tiled - whether or not the background should be tiled as we progress
  * @param artifacts - the artifacts in the level
  * @param std::vector<Platform * > platforms - a collection of platforms in the level
  */
  Level (std::string backgroundTex, double moveRate = 1, bool tiled = false, 
     std::vector<Artifact*> artifacts = std::vector<Artifact*>(), 
     std::vector<Platform*> platforms = std::vector<Platform*>());

  /**
  * addPlatform
  *
  * Add a platform to the level.
  * @param Platform * newPlatform - the platform to add to the level
  */
  void addPlatform (Platform* newPlatform);

  /**
  * addPlatform
  *
  * Add a platform to the level.
  * @param std::string textureStr - path to the platform's texture
  * @param int x - the x position of the platform
  * @param int y - the y position of the platform
  * @param int width - the width of the platform
  * @param int height - the height of the platform
  */
  void addPlatform (std::string textureStr, int x, int y, int width, int height);

  /**
  * addArtifact
  *
  * Add an artifact to the level.
  * @param newArtifact - the new artifact
  */
  void addArtifact (Artifact* newArtifact);

  /**
  * addArtifact
  *
  * Add an artifact to the level
  * @param artifactStr - path to artifact's image
  * @param x - the x position of the artifact
  * @param y - the y position of the artifact
  * @param width - the width of the artifact
  * @param height - the height of the artifact
  */
  void addArtifact (std::string artifactStr, int x, int y, int width, int height);

  /**
   * draw
   *
   * Draw the background and all platforms.
   */
  void draw();

  std::vector<Platform*> getPlatforms();

private:
   TGA::Texture background;
   bool tiled;
   double moveRate;
   std::vector<Platform*> platforms;
   std::vector<Artifact*> artifacts;
};

