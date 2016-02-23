#pragma once

#include "../core/parser_core.hpp"

namespace TwistedSpirit
{
    template GRAMMAR_TEMPLATE_SIGNATURE
    struct unescaped_string_grammar : qi::grammar<Iterator, std::string()>
    {
        unescaped_string_grammar() : unescaped_string_grammar::base_type(main)
        {
            using namespace common_usings;

            unesc_char.add("\\a", '\a')("\\b", '\b')("\\f", '\f')("\\n", '\n')
                          ("\\r", '\r')("\\t", '\t')("\\v", '\v')
                          ("\\\\", '\\')("\\\'", '\'')("\\\"", '\"')
            ;

            unesc_str =
                    qi::lit("\"")
                >  *((unesc_char | qi::char_) - qi::char_('"'))     [push_back(_val, qi::_1)]
                >   qi::lit("\"")
            ;

            main =
                    unesc_str       [_val = qi::_1]
            ;
        }

        qi::rule<Iterator, std::string()> unesc_str;
        qi::rule<Iterator, std::string()> main;
        qi::symbols<char const, char const> unesc_char;
    };
} // namespace TwistedSpirit
