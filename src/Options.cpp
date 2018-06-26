#include "Options.hpp"
#include "GenerateGrid.hpp"
#include "Hamming.hpp"
#include "ManhattanLinearConflict.hpp"

static e_heuristic  checkHeuristic(char* const &str) {
    if (strcmp(str, "mlc") == 0)
        return mlc;
    else if (strcmp(str, "man") == 0)
        return man;
    else if (strcmp(str, "ham") == 0)
        return ham;
    else
        throw SyntaxException("Error: Admissible heuristics are mlc(ManhattanLinearConflict), man(Manhattan distance) and ham(Hamming distance)");
}

Solver*             parseOptions(int const &argc, char** const &argv) {
    Grid*       start = NULL;
    e_heuristic heuristic = mlc;
    IHeuristic* iheuristic = NULL;
    Grid*       goal = NULL;

    try {
        if (argc < 2)
            throw SyntaxException("Parameters are missing\nExpected format : ./n-puzzle [-size n] [file] [-heuristic mlc|man|ham]");
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-heuristic") == 0 && (i + 1 < argc))
                heuristic = checkHeuristic(argv[++i]);
            else if (strcmp(argv[i], "-size") == 0 && (i + 1 < argc))
                start = GenerateRandomGrid(std::stoi(argv[++i]));
            else
                start = GenerateGridFromFile(argv[i]);
        }
        if (start == NULL)
            throw SyntaxException("Start grid is missing\nExpected format : ./n-puzzle [-size n] [file] [-heuristic mlc|man|ham]");
        goal = generateSolution(start->getSize());
        if (! start->isSolvable(goal))
            throw SyntaxException("This puzzle is unsolvable.");
        if (heuristic == mlc)
            iheuristic = new ManhattanLinearConflict(goal);
        else if (heuristic == man)
            iheuristic = new Manhattan(goal);
        else
            iheuristic = new Hamming(goal);
        return (new Solver(start, goal, iheuristic));

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
