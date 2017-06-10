#ifndef UtilsH
#define UtilsH

#include <regex>
#include <map>
#include <algorithm>

#include "NetworkingToolboxException.h"

// trim from start (in place)
void ltrim(std::string &);

// trim from end (in place)
void rtrim(std::string &);

// trim from both ends (in place)
void trim(std::string &);

// trim from start (copying)
std::string ltrimmed(std::string);

// trim from end (copying)
std::string rtrimmed(std::string);

// trim from both ends (copying)
std::string trimmed(std::string);

// split a string based on a regex
std::vector<std::string> split(const std::string &, const std::string &);

#endif // UtilsH

