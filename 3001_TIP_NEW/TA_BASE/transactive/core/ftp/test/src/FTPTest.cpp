/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/ftp/test/src/FTPTest.cpp $
 * @author:  Jade Welton
 * @version: $Revision: #2 $
 *
 * Last modification: $DateTime: 2012/02/06 16:15:14 $
 * Last modified by:  $Author: haijun.li $
 * 
 * Simple test program for the FTP interface
 *
 */

#include <iostream>
#include <fstream>

#include "core/ftp/src/FTPManager.h"
#include "core/utilities/src/RunParams.h"
#include "core/utilities/src/DebugUtil.h"
// #include "core/process_management/src/UtilityInitialiser.h"
#include "core/exceptions/src/TransactiveException.h"

using TA_Base_Core::RunParams;
using TA_Base_Core::DebugUtil;
using TA_Base_Core::FTPManager;
using TA_Base_Core::TransactiveException;

// Stolen from ProcessManagement::UtilityInitialiser
void initialiseDebugUtil()
{
	// Set the debug file name
    std::string param = RunParams::getInstance().get(RPARAM_DEBUGFILE);
    if (!param.empty())
    {
        DebugUtil::getInstance().setFile(param.c_str());
    }

    // Set the debug level
    param = RunParams::getInstance().get(RPARAM_DEBUGLEVEL);
    if (!param.empty())
    {
        DebugUtil::getInstance().setLevel(DebugUtil::getDebugLevelFromString(param.c_str()));
    }

    // Set the maximum size of a debug file in bytes
    param = RunParams::getInstance().get(RPARAM_DEBUGFILEMAXSIZE);
    if (!param.empty())
    {
        DebugUtil::getInstance().setMaxSize(atoi(param.c_str()));
    }

    // Set the maximum number of log files
    param = RunParams::getInstance().get(RPARAM_DEBUGMAXFILES);
    if (!param.empty())
    {
        DebugUtil::getInstance().setMaxFiles(atoi(param.c_str()));
    }
}

int main( int argc, char* argv[] )
{
	try
	{

		std::string USAGE( argv[0] );
		USAGE.append( "\t--NumberOfLoops=<number of times to retrieve file>\n\t\t\t--FTPServer=<Server address>\n\t\t\t--FTPPort=<Server port, default=21>\n\t\t\t--FTPUser=<user name>\n\t\t\t--FTPPassword=<user password>\n\t\t\t--FTPFileName=<file to retrieve>" );

	    //
    	// Initialise RunParams, DebugUtil
    	//
//    	TA_Base_Core::TA_ProcessManagement::UtilityInitialiser::initialiseUtilities( argc, argv );
		RunParams::getInstance().parseCmdLine(argc, argv);
		initialiseDebugUtil();
		
		std::vector<unsigned char> buffer;
 
		//
		// Check for mandatory parameters
		//
		if ( ( ! RunParams::getInstance().isSet( "NumberOfLoops" ) ) ||
			 ( ! RunParams::getInstance().isSet( "FTPServer" ) )  ||
			 ( ! RunParams::getInstance().isSet( "FTPUser" ) ) ||
			 ( ! RunParams::getInstance().isSet( "FTPFileName" ) )  ) 
		{
			std::cout << std::endl << "Usage: " << USAGE << std::endl << std::endl;
			return 0;
		}

		int numberOfLoops = atoi( RunParams::getInstance().get( "NumberOfLoops" ).c_str() );

		std::string serverAddress = RunParams::getInstance().get( "FTPServer" );
		unsigned int serverPort = RunParams::getInstance().isSet( "FTPPort" ) ? atoi( RunParams::getInstance().get( "FTPPort" ).c_str() ) : 21;
		std::string userName = RunParams::getInstance().get( "FTPUser" );
		std::string userPassword = RunParams::getInstance().get( "FTPPassword" );
		std::string fileName = RunParams::getInstance().get( "FTPFileName" );

		std::string actualFileName;
		unsigned int slashPos = fileName.find_last_of( "/" );
		if ( slashPos != std::string::npos )
		{
    		actualFileName.assign( fileName.substr( slashPos + 1, std::string::npos ) );
		}
		else
		{
    		actualFileName.assign( fileName );
		}

		char fileOutName[256];

		for( int i = 0; i < numberOfLoops; ++i )
		{

			//
			//	Retrieve file via FTPManager
			//
			FTPManager::getInstance().retrieveFile( serverAddress, userName, userPassword, fileName, buffer, serverPort );

			//
			// Write buffer to file
			//
			sprintf( fileOutName, "%02d_%s", i+1, actualFileName.c_str() ); 
			std::ofstream fileOut( fileOutName );
			fileOut.write( reinterpret_cast<const char*>( &(buffer[0]) ), buffer.size() );
			fileOut.close();
			buffer.clear();
		}
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

		
		
