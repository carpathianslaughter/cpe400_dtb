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
 * @version
 *          1.1
 *          Tyler Goffinet
 *          Updated for use with vehicle classes
 *
 *          1.0
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
 * @details Constructs World Class
 *          
 * @pre None
 *
 * @post Initializes all data quantities
 *
 * @par Algorithm 
 *      Standard initialization operation
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
 : worldSizeX(0), worldSizeY(0), numObjects(0)
{
    // Init list used
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
 * @note Can be ran multiple times
 *
 * @note World is empty after initialization
 */
template <class DataType>
bool World<DataType>::initWorld(int sizeX, int sizeY)
{
    // Check sizes
    if(sizeX <= 0 || sizeY <= 0)
    {
        return false;
    }

    // Clear world
    if(numObjects > 0)
    {
        clearWorld();        
    }

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
    // DIS IS TYLER'S JOB!
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
 *
 * @note INCOMPLETE FUNCTION: Need something to assign the coordinates to the vehicle
 */
template <class DataType>
bool World<DataType>::populateWorld(int numObjectsToInsert)
{
    // Varible Declaration
    bool objectPresent;
    int xCoor, yCoor;
    DataType *newObject;

    // Seed number generator
    srand(time(NULL));
  
    // Check number if objects being added to avoid overflow
    if((numObjects + numObjectsToInsert) >= (worldSizeX * worldSizeY / 2))
    {
        return false;
    }

    // Check if number of objects exceed capacity
    if(numObjectsToInsert >= (worldSizeX * worldSizeY / 2)
                                                     && numObjectsToInsert > 0)
    {
        return false;
    }
  
    // Populate world
    for(int i = 0; i < numObjectsToInsert; i++)
    {
        // Loop until empty coordinates found
        do
        {
            // Get random coordinates
            xCoor = rand() % (worldSizeX - 1);
            yCoor = rand() % (worldSizeY - 1);

            // Check if object is present at that coordinate
            objectPresent = isObjectPresent(xCoor,yCoor);

            // If no object present, create new object
            if(!objectPresent)
            {
                // Create new object
                world[xCoor][yCoor] = new DataType;

                // TODO: PROBABLY NEED SOMETHING HERE TO LET VEHICLE KNOW ITS COORDINATES!

                // Push new object onto list
                objectList.push_back(world[xCoor][yCoor]);

                // Increment object counter
                numObjects++;
            }
        }
        while(objectPresent);
    }
    // Return true indicating population success
    return true;
}

 /**
 * @brief Clear World
 *
 * @details Deletes all objects present in the world
 *          
 * @pre Assume initialized class object
 *
 * @post All elements in world deleted
 *
 * @par Algorithm 
 *      Go through each world array element and delete object. Set the object
 *      pointer to NULL
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
void World<DataType>::clearWorld()
{
    // Varible Declaration
    DataType *tempObjectPtr;

    // Go through the world and delete any elements present
    for(int x = 0; x < worldSizeX; x++)
    {
        for(int y = 0; y < worldSizeY; y++)
        {
            // Delete object if found
            if(world[x][y] != NULL)
            {
                tempObjectPtr = world[x][y];
                delete tempObjectPtr;
                world[x][y] = NULL;
            }
        }
    }

    // Clear list
    objectList.clear();
    numObjects = 0;
}

 /**
 * @brief Run World
 *
 * @details Runs the world an arbituary amount of ticks
 *          
 * @pre Assume initialized class object
 *
 * @post World ran
 *
 * @par Algorithm 
 *      Go through each array element checking each 
 *      
 * @exception None
 *
 * @param [in] ticks
 *             Number of times to run each element's function
 *
 * @return None
 *
 * @note None
 */
template <class DataType>
void World<DataType>::runWorld(int ticks)
{
    // Varible Declaration

    // Run world for n amount of ticks
    for(int i = 0; i < ticks; i++)
    {
        // Go through elements in world X axis 
        for(int x = 0; x < worldSizeX; x++)
        {
            // Go through elements in world Y axis
            for (int y = 0; y < worldSizeY; y++)
            {
                // Go through each object and run their commands
                if(world[x][y] != NULL)
                {
                    // NEED VEHICLE IMPLEMENTATION!!!!!!
                    /* Probably go through each present element and check to see
                       if they need to be moved, if they need to transmit the 
                       data to the next vehicle, .etc */
                }

            }
        }
    }
}

 /**
 * @brief Is object present
 *
 * @details Checks if an object is present at given location
 *          
 * @pre Assumes initialized class object
 *
 * @post Returns if the object is present or not
 *
 * @par Algorithm 
 *      Check if the coordinates are in range, then check if a NULL ptr is not
 *      present at given coordinates
 *      
 * @exception None
 *
 * @param [in] xCoor
 *             X-axis coordinate
 *
 *        [in] yCoor
 *             Y-axis coordinate
 *
 * @return Boolean signifying if an object is present
 *
 * @note None
 */
template <class DataType>
bool World<DataType>::isObjectPresent(int xCoor, int yCoor)
{
    // Check range
    if(xCoor >= worldSizeX || yCoor >= worldSizeY)
        return false;
    // Check if object is present
    if(world[xCoor][yCoor] != NULL)
        return true;
    return false;
}

 /**
 * @brief Get Number of Objects
 *
 * @details Returns the number of objects present in the world
 *          
 * @pre Assumes initialized class object
 *
 * @post Number of objects returned
 *
 * @par Algorithm 
 *      Return numObject varible
 *      
 * @exception None
 *
 * @param None
 *
 * @return Integer specifying of objects present in the world
 *
 * @note None
 */
template <class DataType>
int World<DataType>::getNumObjects()
{
    return numObjects;
}

 /**
 * @brief Get Object List
 *
 * @details Returns the list of objects in the world
 *          
 * @pre Assume initialized object class
 *
 * @post List of objects returned
 *
 * @par Algorithm 
 *      Return the list of objects's address
 *      
 * @exception None
 *
 * @param None
 *
 * @return Address of list of object pointers
 *
 * @note None
 */
template <class DataType>
std::vector<DataType*> &World<DataType>::getObjectList()
{
    return objectList;
}

 /**
 * @brief Insert Object
 *
 * @details Inserts object at specified coordinates
 *          
 * @pre Assume initialized class object
 *
 * @post Object inserted into world
 *
 * @par Algorithm 
 *      Check if there is not already an object present at given coordinates and
 *      insert the object into the world and push that object into the list
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
 *              Object to insert into the world
 *
 * @return Bool stating insertion success
 *
 * @note None
 */
template <class DataType>
bool World<DataType>::insertObject(int xCoor, int yCoor, DataType *object)
{
    // Check range
    if(xCoor > worldSizeX || yCoor > worldSizeY)
    {
        return false;
    }

    // Insert object if nothing is present
    if(!isObjectPresent(xCoor,yCoor))
    {
        // Create new object
        world[xCoor][yCoor] = object;

        // Insert at end of object list
        objectList.push_back(world[xCoor][yCoor]);

        // Return
        return true;
    }

    // Returns false if object is already present    
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
 *      Check to see if the coordinates given are in range and see if there is
 *      an object present then return the address of the object
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
    if(isObjectPresent(xCoor,yCoor))
    {
        // Return object
        object = world[xCoor][yCoor];

        // Return
        return true;
    }
    // Returns false if object not present
    return false;

}

/**
 * @brief Remove Object
 *
 * @details Returns object and removes it from the world
 *          
 * @pre Assume initialized class object
 *
 * @post Object returned and removed from world and list of objects present
 *
 * @par Algorithm 
 *      Check to see if the coordinates given are in range and see if there is
 *      an object present then return the address of the object and remove it
 *      from the world and list of objects present
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
 * @return Bool indicating success
 *
 * @note Returns false if the coordinates given are out of range and if there is
 *       no object at specified coordinates 
 *
 * @note Function does not delete the object, only removes and returns it
 */
template <class DataType>
bool World<DataType>::removeObject(int xCoor, int yCoor, DataType *object)
{
    // Varible Declaration
    int index;
    bool removalSuccess;

    // Check range
    if(xCoor > worldSizeX || yCoor > worldSizeY)
    {   
        return false;
    }
    // Return object if present
    if(isObjectPresent(xCoor,yCoor))
    {
        // Return object
        object = world[xCoor][yCoor];

        // Remove object from list
        index = findFromList(object); /* Index returns -1 if not found */

        if(index <= -1) /* This should theoretically never happen but . . . */
        {
            std::cout << "FATAL ERROR: OBJECT REMOVED FROM WORLD BUT ";
            std::cout << "UNSUCCESSFULLY REMOVED FROM LIST . . ." << std::endl;
            return false;
        }
        removeFromList(index);

        // Return
        return true;
    }

    // Returns false if object not present
    return false;
}

/**
 * @brief Find From List
 *
 * @details Finds the matching object in the object address list
 *          
 * @pre None
 *
 * @post Vector index at marching object returned
 *
 * @par Algorithm 
 *      Go through the vector searching for a matching object address
 *      
 * @exception None
 *
 * @param [in] object
 *             Object address to search for
 *
 * @return Vector index at marching object
 *
 * @note Returns -1 if no object found
 */
template <class DataType>
int World<DataType>::findFromList(DataType *object)
{
    // Go through the list until matching object address found
    for(int index = 0; index < objectList.size(); index++)
    {
        // Compare addresses
        if(objectList[index] == object)
        {
            // Return the vector index at the matching object address
            return index;
        }
    }
    return -1; // -1 stating that search failed
}

/**
 * @brief Remove from list
 *
 * @details Removes item from the vector
 *          
 * @pre None
 *
 * @post Item removed from list
 *
 * @par Algorithm 
 *      Shift vector elements forward overwriting the element at index specified
 *      
 * @exception None
 *
 * @param [in] index
 *             Vector index to delete
 *
 * @return Boolean stated if deletion is sucessful
 *
 * @note None
 */
template <class DataType>
bool World<DataType>::removeFromList(int index)
{
    // Check if index is in range
    if(index >= objectList.size())
    {
        return false;
    }

    // Shift elements back
    for(int i = index; index < objectList.size() - 1; index++)
    {
        objectList[i] = objectList[i + 1];
    }

    // Delete last element
    objectList.pop_back();

    // Return
    return true;
}
// Terminating precompiler directives  ////////////////////////////////////////

#endif      // #ifndef CLASS_WORLD_CPP
