#include "space.hpp"

namespace TwistedSpirit
{
    qi::rule <std::string::const_iterator> linebreak = qi::lit("\r\n") || qi::char_('\n') || qi::char_('\r');
    qi::rule <std::string::const_iterator> space = qi::char_(' ') || qi::char_('\t');
    qi::rule <std::string::const_iterator> blank = linebreak | space;

} // namespace TwistedSpirit

