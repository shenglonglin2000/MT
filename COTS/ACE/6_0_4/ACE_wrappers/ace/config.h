      #ifndef ACE_CONFIG_H
	#ifdef WIN32
		#include "ace/config-win32.h"
	#else
		#include "ace/config-sunos5.7.h"
	#endif
      #undef ACE_HAS_REGEX
	  #ifndef ACE_HAS_WCHAR
		 #define ACE_HAS_WCHAR
	  #endif
#ifdef _UNICODE		
	  #ifndef ACE_USES_WCHAR
		#define ACE_USES_WCHAR
	  #endif
#endif
      #endif /* ACE_CONFIG_H */
