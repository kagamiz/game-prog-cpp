# Game Programming in C++ Code
This repository contains the source code for *Game Programming in C++* by Sanjay Madhav.

The source code for the chapters is released under the BSD 3-clause
license. See LICENSE for more details. Note that this license does not apply to
the code in the External directory. Each External project is licensed separately.

# Building the Code

## linux prerequisites

* cmake (>= 3.26.1)
* repo (>= v2.32)

Code for Chapter 7 and beyond uses the FMOD API for audio. This requires
a separate installation from (https://www.fmod.com/download). Download
and install version 1.09.x of the FMOD Studio API (newer versions are untested).
On Windows, install FMOD to the default directory. On Mac, copy the contents
of the FMOD package into External/FMOD.
