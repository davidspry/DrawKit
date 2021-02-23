/*
▀██▀▀█▄                               ▀██▀  █▀   ██    ▄
 ██   ██  ▄▄▄ ▄▄   ▄▄▄▄   ▄▄▄ ▄▄▄ ▄▄▄  ██ ▄▀    ▄▄▄  ▄██▄
 ██    ██  ██▀ ▀▀ ▀▀ ▄██   ██  ██  █   ██▀█▄     ██   ██
 ██    ██  ██     ▄█▀ ██    ███ ███    ██  ██    ██   ██
▄██▄▄▄█▀  ▄██▄    ▀█▄▄▀█▀    █   █    ▄██▄  ██▄ ▄██▄  ▀█▄▀


AUTHOR    David Spry
VERSION   0.0.0 - 0.1 - A
MODIFIED  23 February 2021
*/

#ifndef DK_INCLUDED_H
#define DK_INCLUDED_H

#include "dk.pch"

#include "UITypes.h"
#include "UIPrimitives.h"
#include "GlobalInterface.hpp"

#endif

// TASKS & IDEAS
// =============
//   1. Store normalised triangle vertices in Triangle. Compute 'pixel-space' values when drawn.
//   2. Move to floating point positions for components.
//   3. Add 'easing' (i.e., ease-in, ease-out) for animation purposes
//   4. Add utilities (colour schemes, value transition, window options, etc.)
//   5. Add libsoundio convenience classes for real-time sound
//   6. Add camera classes
//   7. Add batch class system for batch rendering arbitrary shapes/geometry
//   8. Consider creating wavetables for fast sinusoidal functions
//   9. Add sound classes -- oscillators, envelopes, etc.

// ISOMETRIC CAMERA ROTATIONS
// ==========================
//    ortho = glm::rotate(ortho, glm::radians(35.264f), glm::vec3(1.0f, 0.0f, 0.0f));
//    ortho = glm::rotate(ortho, glm::radians(45.000f), glm::vec3(0.0f, 0.0f, 1.0f));
