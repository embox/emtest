/**
 * @file
 * @brief Common array utilities and spread arrays.
 * @details
 * TODO array_foreach general overview. -- Eldar
 *     <b>Spread array</b> is statically allocated array, which is initialized
 * (populated) in multiple compilation units. In other words you can define the
 * array itself in one unit and add elements to it in another unit. Except for
 * the way of definition and initialization, spread array is usual array, so
 * it can be declared and used at run time in regular manner.
 *
 *     Just alike for usual arrays there are two general approaches for
 * iterating over (or determining size of) spread array.
 *  - At compile time using the array name. See #ARRAY_SPREAD_SIZE().
 *  - At run time for those array which has a special element at the end of
 * array so-called terminator element (e.g. @c NULL). See
 * #ARRAY_SPREAD_DEF_TERMINATED().
 *
 *     Considering current use cases and some implementation issues, spread
 * arrays are always allocated in read-only data section as if you have defined
 * a regular array with @c const modifier (although you might not have to). To
 * prevent confusion and to take advantage of compiler type checking <b>always
 * include @c const modifier to element type</b> when defining spread array
 * with #ARRAY_SPREAD_DEF() and its derivatives or when declaring it using
 * @c extern.
 *
 * @date 13.06.10
 * @author Eldar Abusalimov
 */

#ifndef UTIL_ARRAY_H_
#define UTIL_ARRAY_H_

#include <stddef.h>

#include "util/macro.h"

/* The relative placement of sections within a particular array is controlled
 * by the value of order_tag argument. */
#define __ARRAY_SPREAD_SECTION(array_nm, order_tag) \
	".array_spread." #array_nm order_tag ".rodata,\"a\",%progbits;#"


/* Spread arrays implementation-private entries are named as follows
 * to prevent namespace pollution. */
#define __ARRAY_SPREAD_PRIVATE(array_nm, private_nm) \
	__array_spread__##array_nm##__##private_nm

#define __ARRAY_SPREAD_GUARD(array_nm) \
	MACRO_GUARD(__ARRAY_SPREAD_PRIVATE(array_nm, element))

/**
 * Defines a new spread array.
 *
 * @param element_type
 *   The type of array elements with optional modifiers.
 *   To control the scope of array definition the standard visibility modifiers
 *   may be used. Thus, without any modifier the array is defined in the global
 *   scope and could be referenced inside other compilation units.
 *   @c static modifier forces the array to be defined in the file scope
 *   and prevents any global symbol to be emitted to the resulting object.
 *   Static spread array cannot be referenced outside the definition file, but
 *   it remains accessible from other compilation units for elements addition
 *   using #ARRAY_SPREAD_ADD() macro and its @link #ARRAY_SPREAD_ADD_NAMED
 *   named derivative @endlink.
 *   Do not forget to specify @c const modifier explicitly (see general docs).
 * @param name
 *   The array name which is used to refer the array itself and to populate it
 *   using #ARRAY_SPREAD_ADD().
 *
 * @note
 *   This command should be used in the file scope, outside of any block.
 * @note
 *   The @a element_type must include @c const modifier (see general docs).
 */
#define ARRAY_SPREAD_DEF(element_type, name) \
		ARRAY_SPREAD_TERM_DEF(element_type, name, /* empty */)

#define ARRAY_SPREAD_TERM_DEF(element_type, name, _term) \
		element_type volatile const name[] __attribute__ ((used,        \
		/* Some versions of GCC do not take into an account section     \
		 * attribute if it appears after the definition. */             \
			section(__ARRAY_SPREAD_SECTION(name, "0_head")))) =         \
			{ /* Empty anchor to the array head. */ };                  \
		element_type volatile const __ARRAY_SPREAD_PRIVATE(name,term)[] \
		__attribute__ ((used,                                           \
		/* Some versions of GCC do not take into an account section     \
		 * attribute if it appears after the definition. */             \
			section(__ARRAY_SPREAD_SECTION(name, "8_term")))) =         \
			{ _term };                                                    \
		element_type volatile const __ARRAY_SPREAD_PRIVATE(name,tail)[] \
		__attribute__ ((used,                                           \
		/* Some versions of GCC do not take into an account section     \
		 * attribute if it appears after the definition. */             \
			section(__ARRAY_SPREAD_SECTION(name, "9_tail")))) =         \
			{ /* Empty anchor at the very end of the array. */ }

/**
 * Array spread declaration
 */
#define ARRAY_SPREAD_DECLARE(element_type, name)                 \
		extern element_type volatile const name[];               \
		extern element_type volatile const __ARRAY_SPREAD_PRIVATE(name, tail)[]

/**
 * Adds elements to the specified spread array.
 *
 * @param array_name
 *   The name of the spread array to which to add elements.
 * @param ...
 *   The elements to add.
 *
 * @note
 *   This command should be used in the file scope, outside of any block.
 */
#define ARRAY_SPREAD_ADD(name, item)                                       \
	static typeof(name[0]) __ARRAY_SPREAD_GUARD(name)[]  \
		__attribute__ ((used,                                               \
				section(__ARRAY_SPREAD_SECTION(name, "1_body")))) = { item }

/**
 * Gets the length of the specified spread array.
 *
 * @param array_name
 *   The array to check size for (must be a literal symbol).
 * @return
 *   Actual number of array elements including terminator element (if any).
 */
#define ARRAY_SPREAD_SIZE(array_name) \
	((size_t) (__ARRAY_SPREAD_PRIVATE(array_name, tail) - array_name))


/* Spread arrays and spread-specific iterators. */
#define array_spread_foreach(element, array) \
	for (typeof(element) volatile const *_ptr = (array),         \
				*_end = _ptr + (ARRAY_SPREAD_SIZE(array));       \
			(_ptr < _end) && (((element) = *_ptr) || 1); ++_ptr)

#define array_spread_nullterm_foreach(element, array) \
	__array_spread_nullterm_foreach_nm(element, array,  \
			MACRO_GUARD(__ptr))

#define __array_spread_nullterm_foreach_nm(element, array, _ptr) \
	for (typeof(element) volatile const *_ptr = (array);         \
			((element) = *_ptr); ++_ptr)

#endif /* UTIL_ARRAY_H_ */
