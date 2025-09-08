#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

std::streamoff countBytesOfFile(std::fstream &file) {
    std::streampos begin, end;

    // Set pointer to beginning
    file.seekg(0, std::ios::beg);
    begin = file.tellg();

    // Seek to end to get file size
    file.seekg(0, std::ios::end);
    end = file.tellg();

    // Reset pointer back to beginning
    file.clear();
    file.seekg(0, std::ios::beg);

    // Return difference (bytes), handle error
    return (begin != -1 && end != -1) ? (end - begin) : 0;
}

std::size_t countCharsOfFile(std::fstream &file) {
    std::size_t counter = 0;
    char ch;

    // Set pointer to beginning
    file.seekg(0, std::ios::beg);

    // Read characters one by one
    while (file.get(ch))
        counter++;

    // Reset pointer back to beginning
    file.clear();
    file.seekg(0, std::ios::beg);

    return counter;
}

std::size_t countLinesOfFile(std::fstream &file) {
    std::size_t counter = 0;
    std::string line;

    // Set pointer to beginning
    file.seekg(0, std::ios::beg);

    while (getline(file, line))
        counter++;

    // Reset pointer back to beginning
    file.clear();
    file.seekg(0, std::ios::beg);

    return counter;
}

std::size_t countWordsOfFile(std::fstream &file) {
    std::size_t counter = 0;
    std::string word;

    // Set pointer to beginning
    file.seekg(0, std::ios::beg);

    while (file >> word)
        counter++;

    // Reset pointer back to beginning
    file.clear();
    file.seekg(0, std::ios::beg);

    return counter;
}

// Validate command-line option (-l, -w, -c, -m)
bool isOptionValid(const std::string &option) {
    return option.length() == 2 && option[0] == '-';
}

int main(int argc, char *argv[]) {
    // Handle insufficient arguments
    if (argc < 2) {
        std::cerr << "Usage: ./ccwc <-l | -w | -c | -m> <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string option;
    std::string fileName;

    // Case: only one argument (filename only)
    if (argc == 2) {
        fileName = argv[1];

        // Open file for default output (lines words bytes)
        std::fstream file(fileName, std::ios::in);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << fileName << std::endl;
            return EXIT_FAILURE;
        }

        // Default output: lines words bytes
        std::cout << countLinesOfFile(file) << " ";
        std::cout << countWordsOfFile(file) << " ";
        std::cout << countBytesOfFile(file) << " " << fileName << std::endl;

        file.close();
        return EXIT_SUCCESS;
    }

    // Case: two arguments (option + filename)
    option = argv[1];
    fileName = argv[2];

    if (!isOptionValid(option)) {
        std::cerr << "Invalid option! Use -l, -w, -c, or -m." << std::endl;
        return EXIT_FAILURE;
    }

    std::fstream file(fileName, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        return EXIT_FAILURE;
    }

    char opt = option[1];
    switch (opt) {
        case 'l':
            std::cout << countLinesOfFile(file) << " " << fileName << std::endl;
            break;
        case 'w':
            std::cout << countWordsOfFile(file) << " " << fileName << std::endl;
            break;
        case 'c':
            std::cout << countBytesOfFile(file) << " " << fileName << std::endl;
            break;
        case 'm':
            std::cout << countCharsOfFile(file) << " " << fileName << std::endl;
            break;
        default:
            std::cerr << "Invalid option! Use -l, -w, -c, or -m." << std::endl;
            file.close();
            return EXIT_FAILURE;
    }

    file.close();
    return EXIT_SUCCESS;
}