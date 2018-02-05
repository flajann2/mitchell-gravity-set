#pragma once

#include <string>
#include <iostream>
#include <cassert>
#include <QtCore/qmath.h>

using namespace std;

namespace mgs
{
  static const std::string asset_dir = "assets/";

  static const double xRange = 20.0f;
  static const double yRange = xRange;
  static const double zRange = xRange;

  static const double defaultStarMass = 1000.0;
  
  static const double doublePi = double(M_PI) * 2.0f;
  static const double radiansToDegrees = 360.0f / doublePi;
  static const double animationFrames = 100.0f;

  static const double defaultStarArrangementFactor = 0.50;
  
  // the count of one side of the
  // freePointMassCube. This value will be cubed, so
  // keep this number low.
  static const int freePointMassCube = 10;
}
