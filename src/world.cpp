// Program Information ////////////////////////////////////////////////////////
/**
 * @file world.cpp
 * 
 * @author Brandon Thai Nguyen
 *
 * @brief Implementation file for world class
 * 
 * @details Implements all member methods of the world class
 *
 * @version 1.00
 *          Brandon Thai Nguyen (03 October 2016)
 *          Original Code
 *
 * @Note Requires world.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_WORLD_CPP
#define CLASS_WORLD_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "world.h"

// Class implementation ///////////////////////////////////////////////////////

 /**
 * @brief Default/Initialization constructor
 *
 * @details Constructs World 
 *          
 * @pre None
 *
 * @post Initializes all data quantities
 *
 * @par Algorithm 
 *      Standard initialization constructor operation
 * 
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
World<DataType>::World()
{
    worldSizeX = 0;
    worldSizeY = 0;
}

 /**
 * @brief World Destructor
 *
 * @details Deletes the world and all its objects
 *          
 * @pre Assumes at least one node constructed
 *
 * @post All linked list nodes are removed
 *
 * @par Algorithm 
 *      Dynamically allocate an array of pointers (x-axis) then dynamically  
 *      
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
World<DataType>::~World()
{
    // Varible Declaration
    DataType **tempWorldYPtr;
    DataType *tempObjectPtr;

    // Delete world
    for(int x = 0; x < worldSizeX; x++)
    {
        // Delete objects
        for(int y = 0; y < worldSizeY; y++)
        {
            if(world[x][y] != NULL)
            {
                tempObjectPtr = world[x][y];
                delete tempObjectPtr;                
            }
        }

        // Delete world Y
        tempWorldYPtr = world[x];    
        delete tempWorldYPtr;
    }
    delete world;

    worldSizeX = 0;
    worldSizeY = 0;
}

 /**
 * @brief Initialize world
 *
 * @details Dynamically constructs the world with given parameters
 *          
 * @pre None
 *
 * @post World initialized
 *
 * @par Algorithm 
 *      Dynamically allocates the xCoor pointer and the yCoor pointers based on
 *      the parameters and sets all object pointers to NULL
 *      
 * @exception None
 *
 * @param [in] sizeX
 *             Max x-axis world size to be set
 *
 *        [in] sizeY
 *             Max y-axos world size to be set
 *
 * @return None
 *
 * @note 
 */
template <class DataType>
void World<DataType>::initWorld(int sizeX, int sizeY)
{
    // Set city size limits
    worldSizeX = sizeX;
    worldSizeY = sizeY;

    // Dynamically size city
    world = new DataType **[worldSizeX];
    for(int x = 0; x < worldSizeX; x++)
    {
        world[x] = new DataType *[worldSizeY];

        // Point object pointers to NULL
        for(int y = 0; y < worldSizeY; y++)
        {
            world[x][y] = NULL;
        }
    }

}
/**
 * @brief Populate World
 *
 * @details Fills the world with objects
 *          
 * @pre Assumes initialized world object and world data member
 *
 * @post World filled with objects
 *
 * @par Algorithm 
 *      Create n amound of new objects at random coordinates without overlapping
 *      previously created objects
 *      
 * @exception Cannot populate before world initialization
 *
 * @param [in] numObjects
*              Number of objects to fill the world with
 *
 * @return Boolean signifying populating success
 *
 * @note Number of objects can not exceed world capacity
 */

template <class DataType>
bool World<DataType>::populateWorld(int numObjects)
{
    // Varible Declaration
    bool objectPresent;
    int xCoor, yCoor;
    DataType *newObject;

    // Seed number generator
    srand(time(NULL));

    // Check if number of objects exceed capacity
    if(numObjects >= (worldSizeX * worldSizeY))
    {
        return false;
    }
    // Populate world
    for(int i = 0; i < numObjects; i++)
    {
        do
        {
            // Get random coordinates
            xCoor = rand() % worldSizeX - 1;
            yCoor = rand() % worldSizeY - 1;

            // Check if object is present at that coordinate
            objectPresent = isObjectPresent(xCoor,yCoor);

            // If no object present, create new object
            if(!objectPresent)
            {
                world[xCoor][yCoor] = new DataType;               
            }

        }
        while(objectPresent);
    }
    return true;
}

 /**
 * @brief 
 *
 * @details 
 *          
 * @pre 
 *
 * @post 
 *
 * @par Algorithm 
 *      
 *      
 * @exception 
 *
 * @param 
 *
 * @return 
 *
 * @note 
 */
template <class DataType>
void World<DataType>::displayWorld()
{

}

 /**
 * @brief 
 *
 * @details 
 *          
 * @pre 
 *
 * @post 
 *
 * @par Algorithm 
 *      
 *      
 * @exception 
 *
 * @param 
 *
 * @return 
 *
 * @note 
 */
template <class DataType>
bool World<DataType>::isObjectPresent(int xCoor, int yCoor)
{

}

 /**
 * @brief 
 *
 * @details 
 *          
 * @pre 
 *
 * @post 
 *
 * @par Algorithm 
 *      
 *      
 * @exception 
 *
 * @param 
 *
 * @return 
 *
 * @note 
 */
template <class DataType>
bool World<DataType>::insertObject(int xCoor, int yCoor, DataType *object)
{

}

/**
 * @brief 
 *
 * @details 
 *          
 * @pre 
 *
 * @post 
 *
 * @par Algorithm 
 *      
 *      
 * @exception 
 *
 * @param 
 *
 * @return 
 *
 * @note 
 */
template <class DataType>
bool World<DataType>::removeObject(int xCoor, int yCoor, DataType *object)
{
    // Check range
    if(xCoor > worldSizeX || yCoor > worldSizeY)
    {   
        return false;
    }
    // Return and remove object if present
    if(world[xCoor][yCoor] != NULL)
    {
        object = world[xCoor][yCoor];
        world[xCoor][yCoor] = NULL;
        return true;
    }

    // Returns false if object not present
    return false;
}

 /**
 * @brief Get object
 *
 * @details Returns the object from the world at the specified coordinates
 *          
 * @pre Assume initialized world object
 *
 * @post Object from world returned
 *
 * @par Algorithm 
 *      
 *      
 * @exception None
 *
 * @param [in] xCoor
 *             X-axis coordinate
 *
 *        [in] yCoor
 *             Y-axis coordinate
 *
 *        [out] object
 *              Object returned from the world
 *
 * @return boolean specifying if object returned sucessfully
 *
 * @note Returns false if the coordinates given are out of range and if there is
 *       no object at specified coordinates 
 */
template <class DataType>
bool World<DataType>::getObject(int xCoor, int yCoor, DataType *object)
{
    // Check range
    if(xCoor > worldSizeX || yCoor > worldSizeY)
    {   
        return false;
    }
    // Return object if present
    if(world[xCoor][yCoor] != NULL)
    {
        object = world[xCoor][yCoor];
        return true;
    }

    // Returns false if object not present
    return false;

}
// Terminating precompiler directives  ////////////////////////////////////////

#endif      // #ifndef CLASS_WORLD_CPP