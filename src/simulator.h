// Program Information ////////////////////////////////////////////////////////
/**
 * @file simulator.h
 *
 * @brief Definition file for simulator class
 * 
 * @author Brandon Thai Nguyen
 * 
 * @details Specifies all member methods of the simulator class
 *
 * @version 1.00
 *          Brandon Thai Nguyen (03 October 2016)
 *          Original Code
 *
 * @Note Requires vehicle.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_SIMULATOR_H
#define CLASS_SIMULATOR_H

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include "vehicle.h"

using namespace std;

// Class definition  //////////////////////////////////////////////////////////
class Simulator
{
public:
	// Constructors
	Simulator();
	~Simulator();

	// World Control
	void initCity(int xCoor, int yCoor);
	bool moveVehicle(int xCoorFrom, int yCoorFrom, int xCoorTo, int yCoorTo);
	void run(int ticks);
	void displayWorld();

private:
	int citySizeX;
	int citySizeY;
	Vehicle **city; // MAYBE ABSTRACT CITY IN IT'S OWN CLASS?
};
// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_SIMULATOR_H