#ifndef EXTERNAL_RESOURCE_PATH_H
#define EXTERNAL_RESOURCE_PATH_H

#include <stddef.h>
#include <stdbool.h>

// Initialize the resource system
// This should be called at the start of your program
void InitResourcePaths(void);

// Free any allocated memory by the resource system
void CloseResourcePaths(void);

// Get the full path to a resource file
// Returns the first matching file found in the search paths
// Search order: 
// 1. Current project resources directory
// 2. Engine resources directory
const char* GetResourcePath(const char* fileName);

// Check if a resource exists in any of the resource directories
bool ResourceExists(const char* fileName);

// Add a custom resource directory to search
// Returns true if directory was successfully added
bool AddResourceDirectory(const char* directory);

#endif // EXTERNAL_RESOURCE_PATH_H 
