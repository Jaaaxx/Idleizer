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
    
    // Add the engine's resources directory (assuming it's relative to the executable directory)
    AddResourceDirectory("resources");
    
    // Get the current working directory and add its resources folder
    const char* currentDir = GetWorkingDirectory();
    if (currentDir != NULL) {
        char projectResourceDir[MAX_PATH_LENGTH];
        snprintf(projectResourceDir, MAX_PATH_LENGTH, "%s/resources", currentDir);
        AddResourceDirectory(projectResourceDir);
        
        // For examples, also try adding a resources directory one level up 
        // (useful for projects in examples/ subdirectories)
        char parentDir[MAX_PATH_LENGTH];
        snprintf(parentDir, MAX_PATH_LENGTH, "%s/..", currentDir);
        
        // Store the original directory so we can return to it
        const char* originalDir = currentDir;
        
        if (ChangeDirectory(parentDir)) {
            const char* newDir = GetWorkingDirectory();
            if (newDir != NULL) {
                char parentResourceDir[MAX_PATH_LENGTH];
                snprintf(parentResourceDir, MAX_PATH_LENGTH, "%s/resources", newDir);
                AddResourceDirectory(parentResourceDir);
            }
            
            // Return to original directory
            ChangeDirectory(originalDir);
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
        return false;
    }
    
    // Add the directory to our list
    resourceDirs[numResourceDirs] = strdup(directory);
    numResourceDirs++;
    
    TraceLog(LOG_INFO, "Added resource directory: %s", directory);
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
    
    // If not found in resource directories, return the original filename
    // (This allows using paths relative to the current directory as a fallback)
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
