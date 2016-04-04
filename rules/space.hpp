#pragma once

#include "../core/parser_core.hpp"

namespace TwistedSpirit
{
    // declaring them dirty and global reduces compile time stress

	/**
	 *	Matches \r, \n and \r\n.
	 *
	 *	\n: Linux
	 *	\r\n: Windows
	 *	\r: Mac up to version 9. OS X uses \n
	 */
    extern qi::rule <std::string::const_iterator> linebreak;

	/**
	 *	Matches (char)0x20 and tabs. Anything else isn't very useful in most cases.
	 *	Treating line breaks as space breaks a lot of grammars.
	 */
    extern qi::rule <std::string::const_iterator> space;

    /**
     *  Matches linebreak | space.
     */
    extern qi::rule <std::string::const_iterator> blank;
} // namespace TwistedSpirit
