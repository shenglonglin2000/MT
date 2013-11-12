/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/UselessLogger/src/UselessClass.h $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * A simple class that will only contain one method that will do
  * absolutely nothing.  It MUST have a constructor and destructor with the
  * FUNCTION_ENTRY and FUNCTION_EXIT macros.  The one method will be called
  * so that a smartarse compiler doesn't optimise it by removing the class
  * altogether (although in Debug mode there should be no optimisation, but
  * better to be safe than sorry.
  *
  * Note: The reason why the class is defined in the declaration is that it is
  * such a stupid little class that doesn't actually do anything productive.
  *
  */

#include "core/utilities/src/DebugUtil.h"

class UselessClass
{
public:
    /**
     * A UselessClass instance.
     */
    static UselessClass uselessInstance;

    /**
     * Constructs a UselessClass instance.
     */
    UselessClass()
    {
        FUNCTION_ENTRY( "Constructor" );
        for( int i = 0; i < 1000; i++ ) /* No-op */;
        FUNCTION_EXIT( "Constructor" );
    };
    /**
     * A useless method.
     */
    void uselessMethod()
    {
        FUNCTION_ENTRY( "UselessMethod" );
        for( int i = 0; i < 1000; i++ ) /* No-op */;
        FUNCTION_EXIT( "UselessMethod" );
    }
    /**
     * Destructs a UselessClass instance.
     */
    virtual ~UselessClass()
    {
        FUNCTION_ENTRY( "Destructor" );
        for( int i = 0; i < 1000; i++ ) /* No-op */;
        FUNCTION_EXIT( "Destructor" );
    };
};