#pragma once

#include "qi_includes.hpp"
#include "phoenix_includes.hpp"
#include "fusion_includes.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <cstdint>
#include <string>

namespace TwistedSpirit
{
    namespace qi = boost::spirit::qi;
    namespace encoding = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;
    namespace spirit = boost::spirit;
    namespace fusion = boost::fusion;

    using char_type = char;
    using const_iterator_type = std::basic_string <char_type>::const_iterator;

	struct empty {};

    namespace common_usings
    {
        // qi
        using qi::lit;
        using qi::lexeme;
        using qi::eps;
        using qi::on_error;
        using qi::accept;
        using qi::fail;
        using qi::repeat;
        using qi::int_;
        using qi::double_;
        using qi::digit;
		using qi::xdigit;
        using qi::long_double;
        using qi::long_long;
        using qi::ulong_long;
        using namespace qi::labels;

        // phoenix
        using phoenix::while_;
        using phoenix::if_;
        using phoenix::at_c;
        using phoenix::push_back;
		using phoenix::ref;
		using phoenix::cref;


        // encoding dependent
        namespace ascii
        {
            namespace b_ascii = boost::spirit::standard;
            using b_ascii::char_;
            using b_ascii::string;
        }
        namespace wide
        {
            namespace b_wide = boost::spirit::standard_wide;
            using b_wide::char_;
            using b_wide::string;
        }
    }

    namespace qi_error
    {
        struct handler_base {
            template <typename, typename, typename, typename, typename>
                struct result { typedef void type; };

            virtual ~handler_base() {}
        };

        struct error_handler_base : public handler_base {};

        struct warning_handler_base : public handler_base {};

        struct error_handler_cerr : public error_handler_base {
            template <typename Iterator, typename WhatType>
            void operator()(Iterator begin, Iterator end, Iterator where, WhatType what, ...) const
            {
                std::cerr   << "Error in for loop parser - expecting: "
                            << what
                            << " at: "
                            << where - begin
                            << " in expression: \""
                            << std::string (begin, where)
                            << "\""
                            << " from end: "
                            << end - where
                            << "\n"
                ;
            }
        };

        struct error_handler_silent : public error_handler_base {
            template <typename Iterator, typename WhatType>
            void operator()(Iterator, Iterator, Iterator, WhatType, ...) const
            {
                // ... ignore
            }
        };

        struct warning_handler_cout : public warning_handler_base {
            template <typename Iterator, typename WhatType>
            void operator()(Iterator begin, Iterator end, Iterator where, WhatType what, ...) const
            {
                std::cout   << "warning: "
                            << what
                            << " at: "
                            << where - begin
                            << " in expression: \""
                            << std::string (begin, where)
                            << "\""
                            << " from end: "
                            << end - where
                            << "\n"
                ;
            }
        };

        struct warning_handler_silent : public warning_handler_base {
            template <typename, typename>
            void operator()(...) const
            {
                // ... ignore
            }
        };

        struct debug_streamer {
            template <typename>
            struct result { typedef void type; };

            template <typename T>
            void operator()(T const& str) const {
                std::cout << str << "\n";
            }
        };
    }

} // namespace TwistedSpirit

#define GRAMMAR_TEMPLATE_SIGNATURE <typename ErrorHandler, typename WarningHandler, typename Iterator>
#define GRAMMAR_TEMPLATE_SIGNATURE_FORWARD <ErrorHandler, WarningHandler, Iterator>


#define HANDLE_QI_ERROR(rule, id)							\
on_error<fail>												\
(															\
    rule,													\
    error_handler(qi::_1, qi::_2, qi::_3, qi::_4, id)		\
)
// MAKRO END

#define HANDLE_QI_WARNING(rule, id)							\
on_error<accept>											\
(															\
	rule,													\
	warning_handler(qi::_1, qi::_2, qi::_3, qi::_4, id)		\
)
// MAKRO END

#define INSTALL_ERROR_HANDLER								\
const phoenix::function <ErrorHandler> error_handler
// MAKRO END

#define INSTALL_WARNING_HANDLER								\
const phoenix::function <WarningHandler> warning_handler
// MAKRO END

#define INSTALL_DEBUG_HANDLER								\
const phoenix::function <qi_error::debug_streamer> dout
// MAKRO END
