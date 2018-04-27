#include "Solver.hpp"


Solver::Solver(Grid* start, Grid* goal, IHeuristic* heuristic):
_finalGrid(goal), _heuristic(heuristic) {
    start->addHeuristic(heuristic);
    _opened.insert(start);
}

Solver::~Solver(){
    // TODO
}

void Solver::solve() {
    Grid* state;
    std::vector<Grid*> children;
    set_it twin_it;

    while (!_opened.empty()){
        //std::cout << "started looping" << std::endl;
        //pick element with the lowest cost (_opened is sorted)
        state = *(_opened.begin());
        //check if this element is the solution
        if (*state == *_finalGrid){
            std::cout << "Yeeeeeaaah!!!!!!" << std::endl;
            std::cout << state->get_g_cost() << " steps!" << std::endl;
            std::cout << "opened size : " << _opened.size() << std::endl;
            std::cout << "closed size : " << _closed.size() << std::endl;
            std::cout << state->toString();
            return;
        }
        else {
            // move state from opened to closed list
            _opened.erase(_opened.begin());
            _closed.insert(state);

            //std::string line;
            // std::getline(std::cin, line);
            // std::cout << "State :" << std::endl;
            // std::cout << state->toString() << std::endl;
            // std::cout << "g = " << state->get_g_cost() << " , h = " << state->get_h_cost() << ", f = " << state->get_f_cost() << std::endl;
            // std::cout << "hash =" << state->getHash() << std::endl;
            // std::cout << "---------------------" << std::endl;

            // explore all neighboring states (up to 4 children)
            children = state->expand();
            //std::cout << "Childrens :" << std::endl;
            for(Grid* &child : children){
                // std::cout << child->toString() << std::endl;
                // std::cout << "g = " << child->get_g_cost() << " , h = " << child->get_h_cost() << ", f = " << child->get_f_cost() << std::endl;
                // std::cout << "hash =" << child->getHash() << std::endl;
                // ignore those already visited
                if (_closed.find(child) != _closed.end()) {
                    //std::cout << "child in closed, deleted" << std::endl;
                    delete child;
                }
                // if child state is in the opened list, keep the lowest cost for that state
                else if ((twin_it = _opened.find(child)) != _opened.end()) {
                    //std::cout << "child found in opened" << std::endl;
                    if ((*twin_it)->get_f_cost() > child->get_f_cost()){
                        delete *twin_it;
                        _opened.erase(twin_it);
                        _opened.insert(child);
                    }
                }
                // if child state is not in the opened list, add it
                else {
                    //std::cout << "child not in opened, inserted" << std::endl;
                    _opened.insert(child);
                }
                //std::cout << "---------------------" << std::endl;
            }
            // std::cout << "opened size : " << _opened.size() << std::endl;
            // std::cout << "closed size : " << _closed.size() << std::endl;
        }
    }
}

// Grid*          Solver::getNextGridToExplore() const {
//     Grid*   min = *(_opened.begin());
//
//     for (auto elem : _opened) {
//         if (elem->get_f_cost() < min->get_f_cost())
//             min = elem;
//     }
//     std::cout << "min grid : " << std::endl << min->toString() << std::endl;
//     return (min);
// }

// void Solver::insertSorted(Grid* node, std::deque<Grid*> &set) {
//     for (set_it it = set.begin(); it < set.end(); it++){
//         if ((*it)->get_f_cost() >= node->get_f_cost()){
//             set.insert(it, node);
//             return ;
//         }
//     }
//     set.push_back(node);
// }
//
// set_it Solver::find(const Grid* node, std::deque<Grid*>& set) {
//     for (set_it it = set.begin(); it < set.end(); it++) {
//         if (**it == *node)
//             return it;
//     }
//     return set.end();
// }

bool    Solver::isFinal(Grid* grid) const {
    return grid == _finalGrid;
}

void    Solver::display() const {
    // Display solution
    // TODO
}
