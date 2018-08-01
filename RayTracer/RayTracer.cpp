// RayTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Render.h"
#include <fstream>
#include <iostream>


int main()
{
	Render r;
	r.traze();
	std::ofstream out("out.raw", std::ios::out, std::ios::binary);
	for (int a = 0; a < r.screen_matrix.size(); a++) {
		if (a % 250 == 0)
		{
			//out << '\n';
		}
		out << (uint8_t)r.screen_matrix[a];
	}
	out.close();
	//std::cin.get();
    return 0;
}

