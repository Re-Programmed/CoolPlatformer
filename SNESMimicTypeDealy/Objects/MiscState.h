#pragma once

#include <string>

//Use SERIALIZED for parameters that will be saved when the object is encoded.
#define SERIALIZED

/*
	MiscState objects should return SaveParams that contain data with no '\' characters, since they will be used by the MiscStateGroup to store each individual object.
	MiscState objects are responsible for how they encode and decode the given string.
	A MiscState contains two functions, a Decode and Encode function that both return and take a string that serialize the given object into data that can be saved to a file.

	MiscState objects need an empty constructor.
*/

namespace GAME_NAME
{
	class MiscState abstract
	{
	public:

		typedef std::string SaveParam;

		virtual void Decode(SaveParam params) = 0;
		virtual SaveParam Encode() = 0;
	};
}