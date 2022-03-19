#pragma once

#include <include/glm.h>

namespace Transform2D
{
	// Translate matrix
	inline glm::mat3 Translate(float tx, float ty)
	{
		// TODO implement translate matrix
		return glm::mat3(
			1, 0, 0,     // coloana 1 in memorie 
			0, 1, 0,     // coloana 2 in memorie 
			tx, ty, 1);
	}

	// Scale matrix
	inline glm::mat3 Scale(float sx, float sy)
	{
		// TODO implement scale matrix
		return glm::transpose(
			glm::mat3(sx, 0, 0,
				0, sy, 0,
				0, 0, 1));
	}

	// Rotate matrix
	inline glm::mat3 Rotate(float radians)
	{
		// TODO implement rotate matrix
		return glm::mat3(
			cos(radians), sin(radians), 0,     // coloana 1 in memorie 
			-sin(radians), cos(radians), 0,     // coloana 2 in memorie 
			0, 0, 1);
	}
}
