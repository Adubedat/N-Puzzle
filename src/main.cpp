#include "GenerateGrid.hpp"

int main(int argc, char** argv){

    Grid* start = GenerateGridFromFile(argv[1]);
    std::cout << start->toString() << std::endl;

}
