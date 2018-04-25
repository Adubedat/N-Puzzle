#include "Solver.hpp"


Solver::Solver(Grid* start, IHeuristic* heuristic):
_heuristic(heuristic), _success(false) {
    _opened.push_back(start);
    _finalGrid = generateSolution(start->getSize());
}

Solver::~Solver(){
    // TODO
}

void Solver::explore() {
    Grid* target;

    // selectionner la grille de plus faible cout parmi opened
    // target = min...
    // la mettre dans _closed

    // Obtenir les 4 grilles voisines
    std::vector<Grid *> neighbors = target->expand();

    // Evaluer les 4 grilles voisines
        // Calculer leur cout
        // Comparer
        //
    // TODO
}

void Solver::solve() {
    Grid* state;
    std::vector<Grid*> children;
    deque_it twin_it;

    while (!_opened.empty()){
        std::cout << "started looping" << std::endl;
        //pick element with the lowest cost (_opened is sorted)
        state = _opened.front();
        //check if this element is the solution
        if (*state == *_finalGrid){
            std::cout << "Yeeeeeaaah!!!!!!" << std::endl;
            std::cout << state->get_g_cost() << " steps!" << std::endl;
            std::cout << state->toString();
            return;
        }
        else {
            // move state from opened to closed list
            _opened.pop_front();
            _closed.push_back(state);

            std::cout << state->toString() << std::endl << std::endl;
            std::cout << "g = " << state->get_g_cost() << " , h = " << state->get_h_cost() << std::endl;

            // explore all neighboring states (up to 4 children)
            children = state->expand();
            for(Grid* &child : children){
                // ignore those already visited
                if (find(child, _closed) != _closed.end())
                    delete child;
                // if child state is in the opened list, keep the lowest cost for that state
                else if ((twin_it = find(child, _opened)) != _opened.end()) {
                    if ((*twin_it)->get_f_cost() > child->get_f_cost()){
                        delete *twin_it;
                        _opened.erase(twin_it);
                        insertSorted(child, _opened);
                    }
                }
                // if child state is not in the opened list, add it
                else
                    insertSorted(child, _opened);
            }
        }
    }
}

void Solver::insertSorted(Grid* node, std::deque<Grid*> &set) {
    for (deque_it it = set.begin(); it < set.end(); it++){
        if ((*it)->get_f_cost() > node->get_f_cost()){
            set.insert(it, node);
            return ;
        }
    }
    set.push_back(node);
}

deque_it Solver::find(const Grid* node, std::deque<Grid*>& set) {
    for (deque_it it = set.begin(); it < set.end(); it++) {
        if (**it == *node)
            return it;
    }
    return set.end();
}

bool    Solver::isFinal(Grid* grid) const {
    return grid == _finalGrid;
}

void    Solver::display() const {
    // Display solution
    // TODO
}
