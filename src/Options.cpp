#include "Options.hpp"
#include "GenerateGrid.hpp"
#include "Hamming.hpp"
#include "ManhattanLinearConflict.hpp"

static void         usageMessage( void ) {
    std::cout << "Usage:\n./n-puzzle [-size n] [file] [-heuristic mlc|man|ham] [-greedy] [-ucost] [-regular]\n\
\tmlc : Manhattan distance with linear conflict gestion\n\
\tman : Manhattan distance\n\
\tham : Hamming\n\
\t-greedy : Only use heuristic function to find the fastest path\n\
\t-ucost : Ignore heuristic and explore all the possible paths\n\
\t-regular: Solve puzzle by rows" << std::endl;
}

static e_heuristic  checkHeuristic(char* const &str) {
    if (strcmp(str, "mlc") == 0)
        return mlc;
    else if (strcmp(str, "man") == 0)
        return man;
    else if (strcmp(str, "ham") == 0)
        return ham;
    else
        throw OptionException("Error: Unadmissible heuristic");
}

Solver*             parseOptions(int const &argc, char** const &argv) {
    Grid*       start = NULL;
    e_heuristic heuristic = mlc;
    e_strategy  strategy = NONE;
    IHeuristic* iheuristic = NULL;
    Grid*       goal = NULL;
    bool        regular = false;

    try {
        if (argc < 2)
            throw OptionException("Error: Parameters are missing");
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-heuristic") == 0 && (i + 1 < argc))
                heuristic = checkHeuristic(argv[++i]);
            else if (strcmp(argv[i], "-size") == 0 && (i + 1 < argc))
                start = GenerateRandomGrid(std::stoi(argv[++i]));
            else if (strcmp(argv[i], "-greedy") == 0)
                strategy = GREEDY;
            else if (strcmp(argv[i], "-ucost") == 0)
                strategy = UC;
            else if (strcmp(argv[i], "-regular") == 0)
                regular = true;
            else
                start = GenerateGridFromFile(argv[i]);
        }
        if (start == NULL)
            throw OptionException("Error: Start grid is missing");
        std::cout << "Input grid:" << std::endl << start->toString() << std::endl << std::endl;
        if (regular)
            goal = generateRegularSolution(start->getSize());
        else
            goal = generateSolution(start->getSize());
        if (! start->isSolvable(goal))
            throw SyntaxException("Error: This puzzle is unsolvable.");
        if (heuristic == mlc)
            iheuristic = new ManhattanLinearConflict(goal, strategy);
        else if (heuristic == man)
            iheuristic = new Manhattan(goal, strategy);
        else
            iheuristic = new Hamming(goal, strategy);
        return (new Solver(start, goal, iheuristic));

    } catch (OptionException &e) {
        std::cout << e.what() << std::endl << std::endl;
        usageMessage();
        std::exit(EXIT_FAILURE);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

/*
**                  Exception class
*/

OptionException::OptionException(std::string msg) :
	_msg(msg)
{}

const char*		OptionException::what(void) const throw() {
	return (_msg.c_str());
}
