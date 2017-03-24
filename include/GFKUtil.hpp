#ifndef GFK_UTIL_INCLUDED
#define GFK_UTIL_INCLUDED

#include <iostream>
#include <cassert>
#include <memory>

// Comment this out if you do not want to see debug messages.
#define USING_DEBUGGING

// Comment this out if you do not want to use fatal error checking.
// *****************************************************************************
// * CAUTION! DISABLING FATAL ERROR CHECKING MAY RESULT IN UNDEFINED BEHAVIOR! *
// *                     * UNCOMMENT AT YOUR OWN RISK *                        *
// *****************************************************************************
#define USING_FATAL_ERROR_CHECKING

//****************************************************************************//
//****************************************************************************//
// Macro flags for debugging
#ifdef USING_DEBUGGING
	#define USING_DEBUG_MACROS
#endif

#ifdef USING_DEBUG_MACROS
	#define DEBUG(x) do { std::cerr << "[ Debug ]: In function " << __func__ << ", line " << __LINE__ <<": "<< x << std::endl; } while(0)
	#define DEBUG_WITH_TEST(test, message) \
		if(test) \
			DEBUG(message)

	#define WARNING(x) do { std::cerr << "[ Warning ]: In function " << __func__ << ", line " << __LINE__ <<": "<< x << std::endl; } while(0)
	#define WARNING_WITH_TEST(test, message) \
		if(test)\
			WARNING(message)
#else
	#define DEBUG(x) do {} while(0)
	#define DEBUG_WITH_TEST(a, b) do {} while(0)
	#define WARNING(x) do {} while(0)
	#define WARNING_WITH_TEST(a, b) do {} while(0)
#endif

// Error Handling Preprocessor Directives
#ifdef USING_FATAL_ERROR_CHECKING
	#define FATAL_ERROR_CHECK(assertion, message) \
		if(assertion) \
			std::cerr << "[ Fatal Error ]: " << message << std::endl; assert(!(assertion))
#else
	#define FATAL_ERROR_CHECK(assertion, message) WARNING_WITH_TEST(assertion, message << " *ALERT* This is an uncaught fatal error! Resulting application behavior may become undefined!")
#endif

//******************************************************************************
// Definitions (unless templated) of helpful utility functions go here!

// Python-like print function :)
void print();
template <typename first, typename... strings>
void print(first arg, const strings&... rest)
{
  std::cout << arg << " ";
  print(rest...);
}

//******************************************************************************
#endif
