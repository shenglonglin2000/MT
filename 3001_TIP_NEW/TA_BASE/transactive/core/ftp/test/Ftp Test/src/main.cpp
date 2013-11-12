/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/ftp/test/Ftp Test/src/main.cpp $
  * @author:  Bradley Cleaver
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * The main source file for the FTP unit test.
  *
  */

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif // defined (_MSC_VER)


// Standard includes.
#include <iostream>

// Core includes.
#include "core/utilities/src/RunParams.h"
#include "core/utilities/src/DebugUtil.h"

// Cots includes.
#include "cots/CppUnit/src/TestFramework.h"

// Test harness includes.
#include "FTPClientTest.h"
#include "FTPManagerTest.h"
#include "FTPReplyTest.h"

using namespace TA_Base_Core;

/**
  * The main method for the FTP unit test. Mostly borrowed from the original
  * test program for TA_FTP.
  */
int main( int argc, char** argv )
{
	try
	{
		std::string USAGE( argv[0] );
		USAGE.append( "\n\
\t\t\t--FTPServer=<Server address>\n\
\t\t\t--FTPPort=<Server port, default=21>\n\
\t\t\t--FTPUser=<user name>\n\
\t\t\t--FTPPassword=<user password>\n\
\t\t\t--FTPFileName=<file to retrieve from ROOT directory>\n\
\t\t\t--FTPDirectory=<directory to change into>\n\
\t\t\t--FTPFullPath=<file to retreive with full path>" );

	    //
    	// Initialise RunParams
    	//
		RunParams::getInstance().parseCmdLine(argc, argv);
		
		std::vector<unsigned char> buffer;

		//
		// Check for mandatory parameters
		//
		if ( ( ! RunParams::getInstance().isSet( "FTPServer"    ) ) ||
			 ( ! RunParams::getInstance().isSet( "FTPUser"      ) ) ||
             ( ! RunParams::getInstance().isSet( "FTPFileName"  ) ) ||
             ( ! RunParams::getInstance().isSet( "FTPDirectory" ) ) ||
             ( ! RunParams::getInstance().isSet( "FTPFullPath"  ) ) ) 
		{
			std::cout << std::endl << "Usage: " << USAGE << std::endl << std::endl;
            std::cout << std::endl << "Please ensure these settings are valid before running this test!" << std::endl;
			return 0;
		}

		std::string serverAddress = RunParams::getInstance().get( "FTPServer" );
		unsigned int serverPort = RunParams::getInstance().isSet( "FTPPort" ) ? atoi( RunParams::getInstance().get( "FTPPort" ).c_str() ) : 21;
		std::string userName = RunParams::getInstance().get( "FTPUser" );
		std::string userPassword = RunParams::getInstance().get( "FTPPassword" );
		std::string fileName = RunParams::getInstance().get( "FTPFileName" );
        std::string directory = RunParams::getInstance().get( "FTPDirectory" );
        std::string fullPath = RunParams::getInstance().get( "FTPFullPath" );


        // Generate and run the tests.

        TestRunner runner;

        FTPClientTest testcase1( serverAddress, serverPort, userName, userPassword, fileName, directory );
        runner.addSuite( testcase1.suite() );

        FTPManagerTest testcase2( serverAddress, serverPort, userName, userPassword, fullPath );
        runner.addSuite( testcase2.suite() );

        FTPReplyTest testcase3;
        runner.addSuite( testcase3.suite() );

        // Run config file. Make sure it is in the cfg directory.
        runner.begin( "./cfg/config.ini" );
	}
	catch( TransactiveException& tex )
	{
		std::cout << "Caught Transactive exception : " << tex.what() << std::endl;
	}
	catch( ... )
	{
		std::cout << "Caught unknown exception" << std::endl;
	}    

    return 0;
}
