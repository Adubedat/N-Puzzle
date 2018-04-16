#include "Parser.hpp"

/*
**                  Constructors and destructor
*/

GenerateGrid::GenerateGrid() {}

GenerateGrid::~GenerateGrid() {}

/*
**                  Getters
*/

Grid* const     GenerateGrid::from(int const &size) {
    return (grid);
}

Grid* const     GenerateGrid::from(std::string const &src) {
    std::ifstream   myFile(src);

    if (myFile.isOpen())
        parseFile(myFile);
    else
        std::cout << "Error : This file can not be opened" << std::endl;
    return (grid);
}
