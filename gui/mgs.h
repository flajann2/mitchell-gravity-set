#pragma once

#include <string>
#include <iostream>
#include <cassert>
#include <QtCore/qmath.h>

using namespace std;

namespace mgs
{
  static const std::string asset_dir = "assets/";

  static const float yRange = 20.0f;
  static const float xRange = yRange;
  static const float zRange = yRange;
  static const float ellipse_a = xRange / 4.0f;
  static const float ellipse_b = yRange;
  static const float doublePi = float(M_PI) * 2.0f;
  static const float radiansToDegrees = 360.0f / doublePi;
  static const float animationFrames = 100.0f;

  // the count of one side of the
  // freePointMassCube. This value will be cubed, so
  // keep this number low.
  static const int freePointMassCube = 10; 
}
