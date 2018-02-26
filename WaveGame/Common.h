#pragma once

///Used to shorten the namespace that's being used.
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <string>
#include <exception>
#include <SFML\Graphics.hpp>
#include <math.h>

#define PI 3.141592653
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
namespace FS = std::experimental::filesystem;

///<summary>
/// A macro to ruduce the amount of clutter from error checking.
/// Checks if an expression is true, if it is an exception is thrown.
///</summary>
///<param name = "Expression">The expression to be tested.</param>
///<param name = "Message">The message which is to be used in the exception. Must be string or char*.</param>
#define ERROR_IF_TRUE(Expression, Message) \
	if(Expression) \
		throw std::runtime_error(Message);

///<summary>
/// A macro to ruduce the amount of clutter from error checking.
/// Checks if an expression is false, if it is an exception is thrown.
///</summary>
///<param name = "Expression">The expression to be tested.</param>
///<param name = "Message">The message which is to be used in the exception. Must be string or char*.</param>
#define ERROR_IF_FALSE(Expression, Message) \
	if (!Expression) \
		throw std::runtime_error(Message);

namespace Engine::Misc
{	
	extern void WaitForAnyKeyAndExit(int ReturnCode = EXIT_FAILURE);
	extern bool StringToBool(std::string Str);
	extern std::string ToUpper(std::string Str);
	extern std::string ToLower(std::string Str);
	extern double ToRadians(double Degrees);
	extern double ToDegrees(double Radians);
	extern double Difference(double a, double b);
	extern float EuclideanDistance(sf::Vector2f P, sf::Vector2f Q);
	extern bool VectorLessThan(sf::Vector2i Element1, sf::Vector2i Element2);
	extern bool VectorLessThan(sf::Vector2f Element1, sf::Vector2f Element2);
	extern bool VectorGreaterThan(sf::Vector2f Element1, sf::Vector2f Element2);
	extern float NormaliseToRange(float Min, float Max, float Data);
	extern sf::Vector2f AlignPlayer(void* P);
}