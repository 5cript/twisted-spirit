#pragma once

#include "parser_core.hpp"
#include "parsing_results.hpp"

#include <stdexcept>
#include <type_traits>
#include <string>
#include <utility>

namespace TwistedSpirit
{
    template <typename GrammarT, typename CharType = char_type>
        std::pair <ParsingResult, typename GrammarT::grammar_result>
        parse(std::basic_string <CharType> const& text,
              bool doThrow = false,
              bool allowPartial = true)
    {
        using encoding::space;

        GrammarT grammar;
        typename GrammarT::grammar_result parsed;

        auto iter = std::cbegin(text);
        auto end = std::cend(text);

        //static_assert (std::is_same <decltype(iter), std::wstring::const_iterator>::value, "");

        bool result = qi::phrase_parse (iter, end, grammar, space, parsed);

        if (!result)
        {
            if (doThrow)
                throw std::runtime_error ("quick parsing failed");
            else
                return std::make_pair(ParsingResult::FAIL, typename GrammarT::grammar_result{});
        }
        else if (iter != end)
        {
            if (!allowPartial)
            {
                if (doThrow)
                    throw std::runtime_error ("quick parsing failed (no exact match)");
                else
                    return std::make_pair(ParsingResult::FAIL, typename GrammarT::grammar_result{});
            }
            return std::make_pair(static_cast <ParsingResult> (iter - std::cbegin(text)), typename GrammarT::grammar_result{});
        }
        return std::make_pair(ParsingResult::FULL_SUCCESS, parsed);
    }

} // namespace TwistedSpirit

#define TYPEDEF_GRAMMAR(NAME) \
using grammar = NAME < \
    qi_error::error_handler_cerr, \
    qi_error::warning_handler_cout, \
    std::string::const_iterator \
>
