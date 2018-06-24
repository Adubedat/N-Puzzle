#include "GenerateGrid.hpp"
#include "ManhattanLinearConflict.hpp"
#include "Solver.hpp"

Grid*   getStartGrid(int const &argc, char** const &argv) {

    try {
        if (argc < 2)
            throw SyntaxException("Parameters are missing\nExpected format : ./n-puzzle [-size n] [file]");
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-size") == 0 && (i + 1 < argc))
                return (GenerateRandomGrid(std::stoi(argv[++i])));
            else
                return (GenerateGridFromFile(argv[i]));
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return (NULL);
}

int     main(int argc, char** argv){

    Grid* start = getStartGrid(argc, argv);
    Grid* goal = generateSolution(start->getSize());

    IHeuristic* heuristic = new ManhattanLinearConflict(goal);

    Solver solver(start, goal, heuristic);

    if (! start->isSolvable(goal)){
         std::cout << "UUUUUNSOLVABLE BITCHES!!!" << std::endl;
    }
    else
        solver.solve();
    // start->swap({1,0});
    // start->swap({0,1});
    // std::cout << start->toString() << std::endl;
    // std::cout << std::endl;

    // std::vector<Grid*> children = start->expand();
    // for (std::vector<Grid*>::iterator i = children.begin(); i != children.end(); i++)
        // std::cout << (*i)->toString() << std::endl << std::endl;
}
