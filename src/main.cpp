#include "GenerateGrid.hpp"

int main(int argc, char** argv){

    Grid* start = GenerateGridFromFile(argv[1]);
    start->swap({1,0});
    start->swap({0,1});
    std::cout << start->toString() << std::endl;
    std::cout << std::endl;

    std::vector<Grid*> children = start->expand();
    for (std::vector<Grid*>::iterator i = children.begin(); i != children.end(); i++)
        std::cout << (*i)->toString() << std::endl << std::endl;
}
