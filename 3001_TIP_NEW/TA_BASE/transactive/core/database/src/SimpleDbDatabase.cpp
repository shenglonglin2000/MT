/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/data_access_interface/src/SimpleDbDatabase.cpp $
  * @author Nick Jardine
  * @version $Revision: #11 $
  * Last modification: $DateTime: 2013/09/19 15:28:59 $
  * Last modified by: Nick Jardine
  * 
  * SimpleDbDatabase is an implementation of IDatabase, and is responsible for executing queries
  * on the database. It does not analyse the returned data - that is the responsiblility of 
  * SimpleDbData. 
  * SimpleDbDatabase is specific to SimpleDb and will not work for any other database library.
  * 
  */


///////////////////////////////////////////////////////////
//
//  SimpleDbDatabase.cpp
//  Implementation of the Class SimpleDbDatabase
//  Generated by Enterprise Architect
//  Created on:      11-Mar-2003 15:25:06
//  Original author: Karen Graham
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////

#ifdef __WIN32__
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#endif

#include <sstream>
#include "core/database/src/SimpleDbDatabase.h"
#include "core/database/src/SimpleDbData.h"
#include "core/database/src/DbStatus.h"
#include "core/database/src/SimpleDb.h"
#include "core/database/src/DBException.h"
#include "core/exceptions/src/DatabaseException.h"
#include "core/exceptions/src/DbConnectionFailed.h"
#include "core/exceptions/src/DbUniqueConstraintViolated.h"
#include "core/exceptions/src/SQLException.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/TAAssert.h"
#include "core/utilities/src/RunParams.h"

using TA_Base_Core::DebugUtil;

using TA_Base_Core::DatabaseException;

namespace TA_Base_Core
{
 
    void SimpleDbDatabase::connect(const std::string& connectionString)
	{
		FUNCTION_ENTRY("connect");

		if (NULL != m_db && m_db->IsNeedChange(connectionString))
		{
			// release the m_db object and change to the new connection string
			disconnect();
		}

        if (m_db == NULL) // The pointer has not been initialised. We need to set it up.
		{
			// Get the database connection information (i.e. servicename:username:password).
			//
			
            LOG_GENERIC( SourceInfo, DebugUtil::DebugDebug, 
				"SimpleDbDatabase::connect(): Database connection string is: %s", connectionString.c_str());

			// Parse the Connection String to seperate the database connection information.
			//
			std::vector<std::string> dbConnData;
			SimpleDb::ParseConnectStr(connectionString, dbConnData); 

			// 3 is used because dbConnData should consist of servicename:username:password
			// The comparrison operator is "<" to support legacy connection strings that include
			// the hostname on the end. Oracle will ignore all but the first three items anyway, so
			// as long as we have at least three, then there is not a problem.
			if (dbConnData.size() < 5) //The connection string is not valid
			{
                FUNCTION_EXIT;
				TA_THROW( DbConnectionFailed("The database connection string is not valid.") );
			}

			// SimpleDb creates the database connection in the constructor, hence we must 
			// pass the connection string with a call to "new"
			try
			{
				m_db = new SimpleDb(dbConnData[0].c_str(), dbConnData[1].c_str(), dbConnData[2].c_str(), dbConnData[3].c_str(), dbConnData[4].c_str());
			}
			catch( const DBException& e )
			{
                try
                {
                    // mark this db bad if we can
                    std::string db (RPARAM_DBPREFIX /*+ dbConnData[1]*/ );
					if (!dbConnData[4].empty())					
						db += (dbConnData[1] + "@" + dbConnData[4]);
					else
						db += dbConnData[1];

                    DbStatus::getInstance().onRunParamChange(db, std::string(RPARAM_DBOFFLINE));
                }
                catch(...)
                {
                }

				LOG_GENERIC( SourceInfo, DebugUtil::DebugError,"TA_Base_Core::DBException: %s", e.getSummary().c_str() );
								
                FUNCTION_EXIT;
				TA_THROW( DatabaseException(e.getReason()) );
			}
		}

        try
        {
            _TryToOpenDb();
        }
        catch( const DBException& e )
        {
            // this db has gone bad, caller should try another one
            disconnect();
            try
            {
			    // Parse the Connection String to seperate the database connection information.
			    //
			    std::vector<std::string> dbConnData;
			    SimpleDb::ParseConnectStr(connectionString, dbConnData); 
                // mark this db bad if we can
                std::string db (RPARAM_DBPREFIX /*+ dbConnData[1]*/ );
				if (!dbConnData[4].empty())					
					db += (dbConnData[1] + "@" + dbConnData[4]);
				else
					db += dbConnData[1];
                DbStatus::getInstance().onRunParamChange(db, std::string(RPARAM_DBOFFLINE));
            }
            catch(...) // don't care about errors - nothing we can do about them anyway
            {
            }
			LOG_GENERIC( SourceInfo, DebugUtil::DebugError,"TA_Base_Core::DBException: %s", e.getSummary().c_str() );

            FUNCTION_EXIT;
            TA_THROW( DatabaseException(e.getReason()) );
        }
		FUNCTION_EXIT;
	}


	void SimpleDbDatabase::disconnect()
	{
		FUNCTION_ENTRY("disconnect");
		if (NULL != m_db)
		{
			try
			{
				m_db->Close();
			}
			catch( const DBException& e )
			{
				LOG_GENERIC( SourceInfo, DebugUtil::DebugError,"TA_Base_Core::DBException: %s", e.getSummary().c_str() );

			}

			delete m_db;
			m_db = NULL;
		}
		FUNCTION_EXIT;
	}

	SimpleDbDatabase::~SimpleDbDatabase()
	{
		FUNCTION_ENTRY("~SimpleDbDatabase");
		disconnect();
		FUNCTION_EXIT;
	}

	void SimpleDbDatabase::cleanQuery()
	{
		FUNCTION_ENTRY("cleanQuery");
		if(m_db != NULL)
		{
			try
			{
				m_db->cleanQuery();
			}
			catch ( ... )
			{
				LOG_GENERIC( SourceInfo, DebugUtil::DebugError,"TA_Base_Core::DBException: %s", "database cleanQuery failure");
			}
		}
		else
		{
			LOG_GENERIC( SourceInfo, DebugUtil::DebugError,"TA_Base_Core::DBException: %s", "database is NULL");
		}
		FUNCTION_EXIT;
	}

	IData* SimpleDbDatabase::executeQuery(const SQLStatement& rSqlObj,const std::vector<std::string>& columnNames)
	{
		return( executeQuery( rSqlObj, columnNames, SimpleDb::MAX_ROWS ) );
	}	

	IData* SimpleDbDatabase::executeQuery(const SQLStatement& rSqlObj,const std::vector<std::string>& columnNames,
		const unsigned long numRows )
	{
		FUNCTION_ENTRY("executeQuery");

		// Assert the pre-conditions on this function
		//TA_ASSERT(0 < sql.size(),"SQL statement passed in is zero size");
		TA_ASSERT(0 < numRows, "numRows is 0 - this is not a sensible number");
		TA_ASSERT(static_cast<unsigned int>(SimpleDb::MAX_ROWS) >= numRows, "numRows is greater than SimpleDb::MAX_ROWS - this is not permissable by SimpleDb");
		TA_ASSERT(columnNames.size() <= static_cast<unsigned int>(m_db->getMaxColumns()), "number of columns is greater than OCIAccess::MAX_COLS - not permissable by SimpleDb");
		TA_ASSERT(0 < columnNames.size(), "columnNames is zero size");
		TA_ASSERT(NULL != m_db, "Database pointer is null."); // connect has not been called		

		// Create a buffer in which to store the retrieved data
		Buffer data;
		try
		{
			_TryToOpenDb();

			m_db->Exec( rSqlObj, columnNames.size(), data, numRows );
		}
		catch( const DBException& e )
		{
			disconnect();
			try
			{
				DatabaseFactory::getInstance().getDatabase(m_dataType, m_dataAction, this);
				m_db->Exec( rSqlObj, columnNames.size(), data, numRows );
			}
			catch(const DBException& e)
			{
				disconnect();
				try
				{
					DatabaseFactory::getInstance().getDatabase(m_dataType, m_dataAction, this);
					m_db->Exec( rSqlObj, columnNames.size(), data, numRows );
				}
				catch(...)
				{
					// if we catch anything it means there are no dbs available
					// so just throw original error
					LOG_GENERIC( SourceInfo, DebugUtil::DebugError, "TA_Base_Core::DBException : %s", e.getSummary().c_str());

					m_db->Close();
					TA_THROW( DbConnectionFailed(e.getReason()) );
				}
			}			
		}
		catch(const DatabaseException& e)
		{
			// if we catch anything in here, it means the db in used no long available
			// so just record the log, next time the application getDatabase will try another db
			
			LOG_GENERIC( SourceInfo, DebugUtil::DebugError, "TA_Base_Core::DatabaseException : %s", e.what());

		}

		// Set the member variables to match the passed-in variables
		m_columnNames = columnNames;


		// Place the data we just loaded into an instance of TA_Base_Core::SimpleDbData (which IS A IData)
		TA_Base_Core::SimpleDbData* idata = new TA_Base_Core::SimpleDbData(columnNames,data);
		m_numRows = idata->getNumRows();

		FUNCTION_EXIT;
		return idata; // Return a pointer to the new IData object
	}


	void SimpleDbDatabase::executeModification(const SQLStatement& rSqlObj)
	{
		FUNCTION_ENTRY("executeModification");

		/*LOG ( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug,
			"The SQL modification to execute is: %s", sql.c_str());*/

		// Assert the pre-conditions on this function
		//TA_ASSERT(0 < sql.size(),"SQL statement passed in is zero size");
		TA_ASSERT(NULL != m_db, "Database pointer is null."); // connect has not been called		

		try
		{
			_TryToOpenDb();

			m_db->Exec( rSqlObj );
		}
		catch( const DBException& e )
		{
			LOG_GENERIC( SourceInfo, DebugUtil::DebugError, "TA_Base_Core::DBException : %s", e.getSummary().c_str());

			// this db has gone bad, try another one
			disconnect();
			try
			{
				DatabaseFactory::getInstance().getDatabase(m_dataType, m_dataAction, this);
				m_db->Exec( rSqlObj );
			}
			catch( const DBException& e )
			{
				disconnect();
				try
				{
					DatabaseFactory::getInstance().getDatabase(m_dataType, m_dataAction, this);
					m_db->Exec( rSqlObj );
				}
				catch(...)
				{
					// if we catch anything it means there are no dbs available
					// so just throw original error
					LOG_GENERIC( SourceInfo, DebugUtil::DebugError, "TA_Base_Core::DBException : %s", e.getSummary().c_str());

					m_db->Close();
					TA_THROW( DbConnectionFailed(e.getReason()) );
				}
			}				

		}
		catch(const DatabaseException& e)
		{
			// if we catch anything in here, it means the db in used no long available
			// so just record the log, next time the application getDatabase will try another db
			LOG_GENERIC( SourceInfo, DebugUtil::DebugError, "TA_Base_Core::DatabaseException : %s", e.what());
			throw e;
					
		}
		FUNCTION_EXIT;
	}

	IData* SimpleDbDatabase::executeProcedure(const SQLStatement& rSqlObj,const std::vector<std::string>& columnNames,
		const unsigned long numRows /*=1000*/)
	{
		// Due to restrictions in SimpleDb, we are not able to return data from a procedure.
		// As such, the use of this method is a programming error.
		TA_ASSERT(false,"This method is not valid for SimpleDbDatabase");

		// We have to return here to allow the program to compile
		return NULL;
	}

	void SimpleDbDatabase::executeProcedure(const SQLStatement& rSqlObj)
	{
		// Oracle procedures are executed in the same manner as standard queries - therefore we use
		// the same code
		executeModification(rSqlObj);
	}


	bool SimpleDbDatabase::moreData(IData*& returnData)
	{
		FUNCTION_ENTRY("moreData");

		// The IData pointer MUST be null when passed to this method. If it is not, a memory leak 
		// will result. This is tested by the assert.
		TA_ASSERT(NULL != m_db, "Database pointer is null");
		//TA_ASSERT( false != m_db->IsOpen(), "Database must be open to request more data" );
		if (! m_db->IsOpen())
		{
			try
			{
				_TryToOpenDb();
				LOG_GENERIC( SourceInfo, DebugUtil::DebugWarn, "Database should be opened while requesting more data,something wrong may occurred");
			}			
			catch (DatabaseException& )
			{
				LOG_GENERIC( SourceInfo, DebugUtil::DebugError, "moreData: Database exception or crash down");
				return false;
			}
			catch(...)
			{
				LOG_GENERIC( SourceInfo, DebugUtil::DebugError, "moreData: Unknown Database exception");
				return false;
			}
			
		}

		if (true == m_db->HasMore()) // There is data to read
		{
			Buffer data;

			try
			{
				LOG_GENERIC( SourceInfo, DebugUtil::DebugDatabase, "SimpleDbDatabase::moreData calling FetchMore...");
				m_db->FetchMore( m_columnNames.size(),data, SimpleDb::MAX_ROWS );
			}
			catch( const DBException& e )
			{
				LOG_GENERIC( SourceInfo, DebugUtil::DebugError, "TA_Base_Core::DBException : %s", e.getSummary().c_str() );
				TA_THROW(DatabaseException(e.getReason()) );
			}

	        // Check if there was actually more data to retrieve
            if(data.size() == 0)
            {
				FUNCTION_EXIT;
                return false;
            }

			returnData = new TA_Base_Core::SimpleDbData(m_columnNames, data);
			FUNCTION_EXIT;
			return true;
		}
 		else
 		{
			m_db->cleanQuery();
 		}

		FUNCTION_EXIT;
		return false; // There was no more data to read
	}


	void SimpleDbDatabase::readBLOB( const std::string& fieldName, const std::string& tableName, 
									 const std::string& whereClause, std::vector<unsigned char>& data )
	{
		TA_ASSERT( m_db != NULL, "Database pointer has not been initialised" );
		TA_ASSERT( fieldName.length() > 0, "The BLOB field name has not been specified" );
		TA_ASSERT( tableName.length() > 0, "The BLOB table name has not been specified" );
		
		_TryToOpenDb();
		
		try
		{
			m_db->readBLOB( fieldName, tableName, whereClause, data );
		}
		catch( const DBException& e )
		{
            // this db has gone bad, try another one
            disconnect();
            try
            {
                DatabaseFactory::getInstance().getDatabase(m_dataType, m_dataAction, this);
                m_db->readBLOB( fieldName, tableName, whereClause, data );
            }
            catch(...)
            {
                // if we catch anything it means there are no dbs available
                // so just throw original error
				LOG_GENERIC( SourceInfo, DebugUtil::DebugError, "TA_Base_Core::DBException : %s", e.getSummary().c_str() );

                LOG_GENERIC( SourceInfo, DebugUtil::DebugError,  "Failed to read BLOB filed %s from table %s with clause %s", 
					fieldName.c_str(), tableName.c_str(), whereClause.c_str() );

                TA_THROW( DatabaseException(e.getReason()) );
            }
		}
	}	


	void SimpleDbDatabase::writeBLOB( const std::string& fieldName, const std::string& tableName, 
									  const std::string& whereClause, std::vector<unsigned char>& data )
	{
		TA_ASSERT( m_db != NULL, "Database pointer has not been initialised" );
		TA_ASSERT( fieldName.length() > 0, "The BLOB field name has not been specified" );
		TA_ASSERT( tableName.length() > 0, "The BLOB table name has not been specified" );
		
		_TryToOpenDb();


		try
		{
			m_db->writeBLOB( fieldName, tableName, whereClause, data );
		}
		catch( const DBException& e )
		{
            // this db has gone bad, try another one
            disconnect();
            try
            {
                DatabaseFactory::getInstance().getDatabase(m_dataType, m_dataAction, this);
                m_db->writeBLOB( fieldName, tableName, whereClause, data );
            }
            catch(...)
            {
                // if we catch anything it means there are no dbs available
                // so just throw original error
				LOG_GENERIC( SourceInfo, DebugUtil::DebugError, "TA_Base_Core::DBException : %s", e.getSummary().c_str() );

                LOG_GENERIC( SourceInfo, DebugUtil::DebugError, "Failed to write BLOB filed %s to table %s with clause %s", 
					fieldName.c_str(), tableName.c_str(), whereClause.c_str() );

                TA_THROW( DatabaseException(e.getReason()) );
            }
		}
	}	


    //Mintao++: use for Distributed DB
    std::string SimpleDbDatabase::escapeAQSQLString(const std::string& theString)
    {
        return (escapeInsertString(escapeInsertString(theString)));         
    }
    //Mintao++: use for Distributed DB

	int SimpleDbDatabase::getDbServerType()
	{
		return _GetDbServerType();
	}	

	void SimpleDbDatabase::setDataTypeAction(EDataTypes dataType, EDataActions dataAction)
	{
		m_dataType   = dataType;
		m_dataAction = dataAction;
	}

	int SimpleDbDatabase::_GetDbServerType()
	{
		return m_db->GetDbServerType();
	}

	void SimpleDbDatabase::prepareSQLStatement(SQLStatement& rSqlStatement, const SQLTypeAdapter& arg0)
	{
		return prepareSQLStatement(rSqlStatement, SQLVarParms() << arg0);
	}

	void SimpleDbDatabase::prepareSQLStatement(SQLStatement& rSqlStatement, SQLVarParms& varParms)
	{
		FUNCTION_ENTRY("prepareSQLStatement");
		try
		{
			LOG_GENERIC( SourceInfo, DebugUtil::DebugSQL, "Begin prepare SQL statement...");

			rSqlStatement.strCommon.clear();
			rSqlStatement.strMySQL.clear();
			rSqlStatement.strSqlite.clear();
			rSqlStatement.strSqlite.clear();

			SQLCode::getInstance().buildSQLStatement(varParms, rSqlStatement);

			LOG_GENERIC( SourceInfo, DebugUtil::DebugSQL, "End prepare SQL statement.");
		}
		catch (BadParamCount* e)
		{
			SQLCodeException SQLException(e->what());
			throw SQLException;
		}
		catch (BadIndex* e)
		{
			SQLCodeException SQLException(e->what());
			throw SQLException;
		}
		catch (...)
		{
			SQLCodeException SQLException("Unknown SQLCode exception");
			throw SQLException;
		}
		FUNCTION_EXIT;
	}	

    std::string SimpleDbDatabase::escapeInsertString(const std::string& theString)
    {
        // create a new string to hold the parsed string
        std::string escapedString = theString;
        int pos = escapedString.find_first_of("'");
        while (-1 != pos)
        {
            char charToInsert = escapedString.at(pos);
            escapedString.insert(pos,&charToInsert, 1);
			pos = escapedString.find_first_of("'", pos + 2);
        }
        return escapedString;
    }

    std::string SimpleDbDatabase::escapeQueryString(const std::string& theString)
    {
        return escapeInsertString(theString);
    }

   
    void SimpleDbDatabase::beginTransaction()
    {
        TA_ASSERT(false,"beginTransaction() is not supported by SimpleDb");
    }

   
    void SimpleDbDatabase::commitTransaction()
    {
        TA_ASSERT(false,"commitTransaction() is not supported by SimpleDb");
    }

    void SimpleDbDatabase::rollbackTransaction()
    {
        TA_ASSERT(false,"rollbackTransaction() is not supported by SimpleDb");
    }

	void SimpleDbDatabase::_TryToOpenDb()
	{
		if( false == m_db->IsOpen() )
		{
			try
			{
				m_db->Open();
			}
			catch( const DBException& e )
			{
				LOG_GENERIC( SourceInfo, DebugUtil::DebugError, "TA_Base_Core::DBException : %s", e.getSummary().c_str() );

				TA_THROW(e);				
			}
		}
	}




} // closes TA_Base_Core
