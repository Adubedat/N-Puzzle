#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <Grid.hpp>
# include <fstream>
# include <algorithm>
# include <random>
# include <chrono>
# include <string>

class	SyntaxException : public std::exception
{
	public:
		SyntaxException(std::string msg);
		virtual const char* what(void) const throw();
	private:
		std::string	_msg;
};

Grid* const             GenerateRandomGrid(int const &size);
Grid* const             GenerateGridFromFile(std::string const &src);
Grid*                   parseFile(std::ifstream &ifs);
void                    parseLine(std::string &line, std::vector<int> &v);
int                     parseWord(std::string::iterator &it);

#endif