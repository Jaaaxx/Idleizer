#include "external/resource_path.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RESOURCE_DIRS 10
#define MAX_PATH_LENGTH 512

static char* resourceDirs[MAX_RESOURCE_DIRS] = {0};
static int numResourceDirs = 0;
static char fullPath[MAX_PATH_LENGTH] = {0};

// Add the base engine resources directory and the current working directory resources
void InitResourcePaths(void) {
    // Clear any existing paths
    CloseResourcePaths();
    
    // Get the current working directory and add its resources folder
    const char* currentDir = GetWorkingDirectory();
    
    if (currentDir != NULL) {
        // First try the current directory resources
        char projectResourceDir[MAX_PATH_LENGTH];
        snprintf(projectResourceDir, MAX_PATH_LENGTH, "%s/resources", currentDir);
        AddResourceDirectory(projectResourceDir);
        
        // Check if we're in an example directory
        if (strstr(currentDir, "examples/") != NULL) {
            // We're in an example subdirectory, try to find the engine resources
            // by navigating up to the engine root
            
            // First check two levels up (for examples/ExampleName/)
            char engineResourceDir[MAX_PATH_LENGTH];
            snprintf(engineResourceDir, MAX_PATH_LENGTH, "%s/../../resources", currentDir);
            AddResourceDirectory(engineResourceDir);
            
            // Also check three levels up (for safety)
            snprintf(engineResourceDir, MAX_PATH_LENGTH, "%s/../../../resources", currentDir);
            AddResourceDirectory(engineResourceDir);
            
            // Also check one level up (for direct examples folder)
            snprintf(engineResourceDir, MAX_PATH_LENGTH, "%s/../resources", currentDir);
            AddResourceDirectory(engineResourceDir);
        } else {
            // We're in the engine root, just add the resources dir
            AddResourceDirectory("resources");
        }
    }
}

void CloseResourcePaths(void) {
    for (int i = 0; i < numResourceDirs; i++) {
        if (resourceDirs[i]) {
            free(resourceDirs[i]);
            resourceDirs[i] = NULL;
        }
    }
    numResourceDirs = 0;
}

bool AddResourceDirectory(const char* directory) {
    if (numResourceDirs >= MAX_RESOURCE_DIRS) {
        TraceLog(LOG_WARNING, "Cannot add resource directory, reached maximum number of directories");
        return false;
    }
    
    // Check if directory exists
    if (!DirectoryExists(directory)) {
        TraceLog(LOG_DEBUG, "Directory does not exist: %s", directory);
        return false;
    }
    
    // Check if this directory is already in our list
    for (int i = 0; i < numResourceDirs; i++) {
        if (strcmp(resourceDirs[i], directory) == 0) {
            // Directory already added
            return true;
        }
    }
    
    // Add the directory to our list
    resourceDirs[numResourceDirs] = strdup(directory);
    numResourceDirs++;
    return true;
}

const char* GetResourcePath(const char* fileName) {
    // For empty filename, return NULL
    if (!fileName || fileName[0] == '\0') {
        return NULL;
    }
    
    // If the file path is already absolute and exists, return it directly
    if ((fileName[0] == '/' || fileName[0] == '\\' || (strlen(fileName) > 1 && fileName[1] == ':')) && 
        FileExists(fileName)) {
        return fileName;
    }
    
    // Check in all resource directories
    for (int i = 0; i < numResourceDirs; i++) {
        snprintf(fullPath, MAX_PATH_LENGTH, "%s/%s", resourceDirs[i], fileName);
        if (FileExists(fullPath)) {
            return fullPath;
        }
    }
    
    // If not found, log the issue
    TraceLog(LOG_WARNING, "Resource not found in any directory: %s", fileName);
    
    // Return the original filename as fallback (this allows direct paths to work)
    return fileName;
}

bool ResourceExists(const char* fileName) {
    // For empty filename, return false
    if (!fileName || fileName[0] == '\0') {
        return false;
    }
    
    // If the file path is already absolute, check directly
    if (fileName[0] == '/' || fileName[0] == '\\' || (strlen(fileName) > 1 && fileName[1] == ':')) {
        return FileExists(fileName);
    }
    
    // Check in all resource directories
    for (int i = 0; i < numResourceDirs; i++) {
        snprintf(fullPath, MAX_PATH_LENGTH, "%s/%s", resourceDirs[i], fileName);
        if (FileExists(fullPath)) {
            return true;
        }
    }
    
    // Not found in any resource directory
    return false;
} 
