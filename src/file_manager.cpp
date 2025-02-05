#include "file_manager.h"
#include <string>
#include <iostream>
#include <fstream>

std::string BirdCPPFileManager::read_file(std::string file_path) {
    // Create a text string, which is used to output the text file
    std::string myText;
    std::string result;

    // Read from the text file
    std::ifstream MyReadFile(file_path);

    // Use a while loop together with the getline() function to read the file line by line
    while (std::getline(MyReadFile, myText)) {
      // Output the text from the file
      result.append(myText+"\n");
    }

    // Close the file
    MyReadFile.close();

    return result;
}
