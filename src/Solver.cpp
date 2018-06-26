#include "Solver.hpp"

Solver::Solver( Grid* start, Grid* goal, IHeuristic* heuristic):
                _finalGrid(goal), _result(NULL), _heuristic(heuristic),
                _total_selected(0), _total_represented(1) {
    start->addHeuristic(heuristic);
    _opened.insert(start);
}

Solver::~Solver(){
    delete _heuristic;

    typedef std::multiset<Grid*, compareCost>::iterator multiset_it;
    for(multiset_it it = _opened.begin(); it != _opened.end(); it++)
        delete *it;
    _opened.clear();

    typedef std::set<Grid*, compareHash>::iterator set_it;
    for(set_it it = _closed.begin(); it != _closed.end(); it++)
        delete *it;
    _closed.clear();
}

void Solver::solve() {
    Grid*               state;
    std::vector<Grid*>  children;
    set_it              twin_it;
    int                 depth = 0;

    while (!_opened.empty()){
        //pick element with the lowest cost (_opened is sorted)
        state = *_opened.begin();
        if (_closed.find(state) != _closed.end()) {
            _opened.erase(_opened.begin());
            continue ;
        }
        this->_total_selected += 1;

        // Output
        if (state->get_g_cost() > depth){
            depth = state->get_g_cost();
            std::cout << "Depth: " << depth << std::endl;
        }

        //check if this element is the solution
        if (*state == *_finalGrid) {
            this->_result = state;
            return;
        }
        else {
            _closed.insert(state);
            // move state from opened to closed list

            // explore all neighboring states (up to 4 children)
            children = state->expand();
            for(Grid* &child : children){
                _opened.insert(child);
                this->_total_represented += 1;
            }
        }
    }
}

bool    Solver::isFinal(Grid* grid) const {
    return grid == _finalGrid;
}

void    Solver::display() const {
    std::cout << "============ SOLVING COMPLETE ===========" << std::endl << std::endl;
    std::cout << "Total number of states ever selected (time complexity): ";
    std::cout << this->_total_selected << std::endl;
    std::cout << "Total number of states ever reprensented (size complexity): ";
    std::cout << this->_total_represented << std::endl;
    std::cout << "Number of moves: " << this->_result->get_g_cost() << std::endl;

    std::cout << std::endl << "Here are all the moves: (Press enter to view the next) " << std::endl;
    std::vector<const Grid*> genealogy = this->_result->getGenealogy();
    for(std::vector<const Grid*>::iterator it = genealogy.begin(); it != genealogy.end(); it++){
        std::cin.get();
        std::cout << (*it)->toString() << std::endl;
    }
    std::cout << std::endl << "FINISHED!" << std::endl;
}
