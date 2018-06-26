#include "Solver.hpp"
#include "Options.hpp"
#include <fstream>

int     main(int argc, char** argv){
    Solver *solver;

    solver = parseOptions(argc, argv);
    solver->solve();
    solver->display();
    delete solver;
}
