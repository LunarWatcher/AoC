#pragma once

#ifdef __SIZEOF_INT128__
// Hi future me:
// You could do this, but don't use it in a hashmap/-set. It appears to be absurdly slow for some reason.
// An int64_t saved three orders of magnitude worth of time on 2025d10p2 for whatever reason. Either that or 
// I missed another change. I've discarded enough code there and I don't feel like reverting to check.
#define HAS_128_BIT_INT
#endif
