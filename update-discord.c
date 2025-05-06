#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

// Function to increment the version number
void increment_version(char *version){
    int major, minor, patch;
    // Parse the version string
    sscanf(version, "%d.%d.%d", &major, &minor, &patch);

    // Increment the patch version
    patch++;

    // Format the new version string
    sprintf(version, "%d.%d.%d", major, minor, patch);
}

int main(){
    FILE *f = fopen("/opt/discord/resources/build_info.json", "r");
    if (!f){
        perror("Error opening file");
        return EXIT_FAILURE;  // Return failure if the file cannot be opened
    }

    // Read the entire file into a buffer
    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer){
        fclose(f);
        fprintf(stderr, "Memory allocation error\n");
        return EXIT_FAILURE;  // Return failure if memory allocation fails
    }

    fread(buffer, 1, fileSize, f);
    buffer[fileSize] = '\0';  // Null-terminate the string
    fclose(f);  // Close the file after reading

    // Parse the JSON
    cJSON *json = cJSON_Parse(buffer);
    if (!json){
        fprintf(stderr, "Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        free(buffer);
        return EXIT_FAILURE;  // Return failure if JSON parsing fails
    }

    // Extract the version
    cJSON *versionItem = cJSON_GetObjectItemCaseSensitive(json, "version");
    if (cJSON_IsString(versionItem) && (versionItem->valuestring != NULL)){
        // Increment the version
        char newVersion[20];  // Declare newVersion here
        strcpy(newVersion, versionItem->valuestring);
        increment_version(newVersion);

        // Update the version in the JSON object
        cJSON_SetValuestring(versionItem, newVersion);

        // Write the updated JSON back to the file
        char *updatedBuffer = cJSON_Print(json);
        if (!updatedBuffer){
            fprintf(stderr, "Error printing JSON.\n");
            cJSON_Delete(json);
            free(buffer);
            return EXIT_FAILURE;  // Return failure if printing fails
        }

        // Open the file for writing
        f = fopen("/opt/discord/resources/build_info.json", "w");
        if (!f){
            perror("Error opening file for writing");
            cJSON_Delete(json);
            free(updatedBuffer);
            free(buffer);
            return EXIT_FAILURE;  // Return failure if the file cannot be opened
        }

        // Write the updated JSON to the file
        fprintf(f, "%s", updatedBuffer);
        fclose(f);  // Close the file after writing

        // Print the updated version
        printf("Version updated successfully to: %s\n", newVersion);

        // Clean up
        free(updatedBuffer);
    } else {
        fprintf(stderr, "Version not found or is not a string.\n");
        cJSON_Delete(json);
        free(buffer);
        return EXIT_FAILURE;  // Return failure if version is not found
    }

    // Clean up
    cJSON_Delete(json);
    free(buffer);

    return EXIT_SUCCESS;  // Return success
}
