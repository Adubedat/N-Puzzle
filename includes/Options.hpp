#ifndef OPTIONS_HPP
# define OPTIONS_HPP

#include "Grid.hpp"
#include "Solver.hpp"

enum e_heuristic {
    mlc,
    man,
    ham
};

class	OptionException : public std::exception
{
	public:
		OptionException(std::string msg);
		virtual const char* what(void) const throw();
	private:
		std::string	_msg;
};

Grid*   getStartGrid(int const &argc, char** const &argv);
Solver* parseOptions(int const &argc, char** const &argv);

#endif
