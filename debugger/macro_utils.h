#ifndef MACRO_UTILS
#define MACRO_UTILS

/**
 * Used for displaying error codes, opcodes, and registers as strings.
 * 
 * To define a list of displayable codes:
 * 
 * #define LIST(X)		\
 * 		X(ENTRY1, 0)	\
 * 		X(ENTRY2, 1)
 * 
 * MACRO_TRACK(LIST) 			// for turning the LIST into a usable enum
 * MACRO_DISPLAY(LIST, to_str)	// for creating a function called to_str() to 
 * 								// convert the enum values to a string
 */

#define MACRO_TRACK(LIST) enum { LIST(MACRO_INST) };

#define MACRO_DISPLAY(LIST, FUNCNAME) 				\
	static inline char* FUNCNAME(int code) { 		\
		switch (code) { 							\
			LIST(STRING_CASE) 						\
			default: return "__";					\
		}											\
	}

#define MACRO_INST(NAME, VALUE) NAME = VALUE, 
#define STRING_CASE(NAME, VALUE) case VALUE: return #NAME;

#endif // MACRO_UTILS