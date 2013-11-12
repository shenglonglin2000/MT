Brad Cleaver
05/02/2004

Purpose:
This directory contains the unit tests the TA_FTP library.

Compiling:
These unit tests depend on a number of projects.  For the test to run successfully each must be compiled with:
  TA_ASSERT_FAIL=EXCEPTION
  TA_ASSERT_LOG (can be 0 or 1)

Instructions:
Usage: Ftp Test.exe
                        --FTPServer=<Server address>
                        --FTPPort=<Server port, default=21>
                        --FTPUser=<user name>
                        --FTPPassword=<user password>
                        --FTPFileName=<file to retrieve from ROOT directory>
                        --FTPDirectory=<directory to change into>
                        --FTPFullPath=<file to retreive with full path>

All of the above command line arguments must be specified apart from --FTPPort.  Before running the tests the details
should be checked to ensure they are valid!

Important Notes:
1. --FTPFileName *must* contain no path information and be in the root directory of the FTP server
2. --FTPFullPath *must* point to a file in a directory besides root.