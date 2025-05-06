#!/bin/bash

# Script to install the discord-update tool

# Define variables
FILE_NAME="update-discord"
DESTINATION="/usr/bin/$FILE_NAME"

# Check if the script is run as root
if [ "$EUID" -ne 0 ]; then
  echo "Please run as root or with sudo."
  exit 1
fi

# Check if the file exists in current directory
if [ ! -f "$FILE_NAME" ]; then
  echo "Error: $FILE_NAME not found in the current directory."
  echo "Please download the release file and place it in this directory."
  exit 1
fi

# Move the file to /usr/bin
echo "Moving $FILE_NAME to /usr/bin..."
mv "$FILE_NAME" "$DESTINATION"

# Make it executable
chmod +x "$DESTINATION"

# Verify installation
echo "Installation complete. You can run the updater with:"
echo "  sudo $FILE_NAME"

# Optional: run the updater to show version
# sudo "$DESTINATION"

exit 0
