#include "GenerateGrid.hpp"

Grid* const             GenerateRandomGrid(int const &size) {

    std::vector<int>  matrix(size * size);
    unsigned    seed = std::chrono::system_clock::now().time_since_epoch().count();

    for (int i = 0; i < size * size; i++) {
        matrix[i] = i;
    }

    std::shuffle(matrix.begin(), matrix.end(), std::default_random_engine(seed));
    return (new Grid(size, matrix, 0));
}

Grid* const             GenerateGridFromFile(std::string const &src) {
    std::ifstream   myFile(src);
    Grid*           grid;

    if (myFile.is_open())
        grid = parseFile(myFile);
    else {
        std::cout << "Error : This file can not be opened" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return (grid);
}

Grid*                   parseFile(std::ifstream &ifs) {

    std::string         line;
    std::vector<int>    v;
    int                 size;

    size = 0;
    while (std::getline(ifs, line)) {
        parseLine(line, v);
    }
    size = v[0];
    v.erase(v.begin());
    if (v.size() > size * size)
        std::cout << "Unvalid grid description, too much numbers" << std::endl;
    else if (v.size() < size * size)
        std::cout << "Unvalid grid description, not enough numbers" << std::endl;
    return (new Grid(size, v, 0));
}

void                    parseLine(std::string &line, std::vector<int> &v) {

    for (std::string::iterator it = line.begin(); it != line.end(); it++) {
        if (*it == '#')
            return ;
        else if (*it == ' ' || *it == '\t')
            ;
        else if (isdigit(*it))
            v.push_back(parseWord(it));
        else
            throw SyntaxException("Unexpected character founded");
    }
}

int                     parseWord(std::string::iterator &it) {

    std::string     str;
    int             nbr;

    while (isdigit(*it)) {
        str += *it;
        it++;
    }
    try {
        nbr = std::stoi(str);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return (std::stoi(str));
}

/*
**                  Exception class
*/

SyntaxException::SyntaxException(std::string msg) :
	_msg(msg)
{}

const char*		SyntaxException::what(void) const throw() {

	return (_msg.c_str());
}
