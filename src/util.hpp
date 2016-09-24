#pragma once

#include <cstdlib>

// clang-format off
#ifndef DEBUG
	#ifdef _MSC_VER
		#define ALWAYS_INLINE __forceinline
	#elif defined __GNUC__
		#define ALWAYS_INLINE __attribute__((always_inline)) inline
	#else
		#define ALWAYS_INLINE inline
	#endif
#else
	#define ALWAYS_INLINE inline
#endif
// clang-format on

namespace CAS {
	namespace _util {
		// A utility function to check if a char is in a list of
		// other characters
		template <size_t loc>
		ALWAYS_INLINE size_t impl_char_is_in(char cmp) {
			(void) cmp;
			return 0;
		}

		template <size_t loc, class... Args>
		ALWAYS_INLINE size_t impl_char_is_in(char cmp, char c1, Args... a) {
			if (cmp == c1) {
				return loc;
			}
			else {
				return impl_char_is_in<loc + 1>(cmp, a...);
			}
		}

		template <class... Args>
		inline size_t char_is_in(char cmp, Args... a) {
			return impl_char_is_in<1>(cmp, a...);
		}

		// Related utilites for specialties.
		inline bool is_whitespace(char cmp) {
			return char_is_in(cmp, ' ', '\t');
		}
	}
}
