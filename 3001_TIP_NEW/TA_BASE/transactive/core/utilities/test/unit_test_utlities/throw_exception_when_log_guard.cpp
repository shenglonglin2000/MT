#include "core/utilities/test/unit_test_utlities/throw_exception_when_log_guard.h"
#include "core/utilities/src/RunParams.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/Logger.h"
#include "core/corba/src/CorbaUtil.h"
#include "core/corba/IDL/src/IChannelLocatorCorbaDef.h"
#include "core/synchronisation/src/ThreadGuard.h"
#include "core/exceptions/idl/src/CommonExceptionsCorbaDef.h"
#include "core/exceptions/src/DatabaseException.h"
#include "core/exceptions/src/DataException.h"
#include "core/exceptions/src/TcpSocketException.h"
#include "core/exceptions/src/UtilitiesException.h"
#include "core/ftp/src/FTPException.h"
#include "core/exceptions/src/ManagedProcessException.h"
#include "core/process_management/IDL/src/IProcessManagerCorbaDef.h"
#include <omniORB4/CORBA.h>


namespace unit_test
{

    namespace
    {
        class TA_Base_Core_DebugUtil
        {
        public:
            static void hook_to_debug_util_member_functions()
            {
                assert( sizeof(TA_Base_Core::DebugUtil) == sizeof(TA_Base_Core_DebugUtil) );

                static bool once_called = false;
                if ( false == once_called  )
                {
                    once_called = true;
                    hook_member_function_no_swap( TA_Base_Core_DebugUtil::preLogChecks, TA_Base_Core::DebugUtil::preLogChecks );
                    hook_member_function_no_swap( TA_Base_Core_DebugUtil::logMessage, TA_Base_Core::DebugUtil::logMessage );
                    hook_member_function_no_swap( TA_Base_Core_DebugUtil::getStringDebugLevel, TA_Base_Core::DebugUtil::getStringDebugLevel );
                    hook_member_function_no_swap( TA_Base_Core_DebugUtil::getLock, TA_Base_Core::DebugUtil::getLock );
                }
            }
            virtual ~TA_Base_Core_DebugUtil() {};
        public:
            bool preLogChecks(TA_Base_Core::DebugUtil::EDebugLevel) { return false; }
            void logMessage(const std::string, int, TA_Base_Core::DebugUtil::EDebugType, va_list, bool, bool) {}
            static const char* getStringDebugLevel(TA_Base_Core::DebugUtil::EDebugLevel) { return NULL; }
            static TA_Base_Core::ReEntrantThreadLockable& getLock() { static TA_Base_Core::ReEntrantThreadLockable lock; return lock; };
        public:
            TA_Base_Core::DebugUtil::EDebugLevel m_currDebugLevel;
            TA_Base_Core::DebugUtil::EDebugLevel m_lastMsgLevel;
            std::string m_filename;
            std::string m_defaultFilename;
            std::fstream m_outFile;
            unsigned int m_maxSizeInBytes;
            unsigned int m_sizeInBytes;
            int m_maxFiles;
            int m_fileCount;
            bool m_firstSetFile;
            bool m_encodePidInFilenames;
            TA_Base_Core::Logger* m_logger;
            std::vector<bool> m_disabledLevels;
            std::vector<bool> m_fileLevels;
            std::vector<std::string> m_levelFilenames;
            std::vector<int> m_filenameNumber;
        };
    }


    throw_exception_wheng_log_guard::throw_exception_wheng_log_guard( const std::string& exception_name, unsigned long debug_level, const std::string& log_string )
        : m_debug_level_backup( -1 )
    {
        // hook log functions
        get_member_function_address_vc8( src_1, TA_Base_Core::DebugUtil::log );
        get_member_function_address_vc8( dst_1, throw_exception_wheng_log_guard::TA_Base_Core_DebugUtil_log );
        m_hook_guard.add_local_hook( src_1, dst_1 );

        get_member_function_address_vc8( src_2, TA_Base_Core::DebugUtil::logGeneric );
        get_member_function_address_vc8( dst_2, throw_exception_wheng_log_guard::TA_Base_Core_DebugUtil_logGeneric );
        m_hook_guard.add_local_hook( src_2, dst_2 );

        // save exception
        m_exception_name() = exception_name;
        m_log_message() = log_string;

        // backup current debug level
        TA_Base_Core::DebugUtil::EDebugLevel current_debug_level = TA_Base_Core::DebugUtil::getInstance().getLevel();

        if ( static_cast<unsigned long>( current_debug_level ) < debug_level )
        {
            m_debug_level_backup = static_cast<long>( current_debug_level );
            TA_Base_Core::DebugUtil::getInstance().setLevel( static_cast<TA_Base_Core::DebugUtil::EDebugLevel>( debug_level ) );
        }
    }


    throw_exception_wheng_log_guard::~throw_exception_wheng_log_guard()
    {
        if ( m_debug_level_backup != -1 )
        {
            TA_Base_Core::DebugUtil::getInstance().setLevel( static_cast<TA_Base_Core::DebugUtil::EDebugLevel>( m_debug_level_backup ) );
        }

        m_exception_name() = "";
        m_log_message() = "";
    }


    void throw_exception_wheng_log_guard::throw_exception_if_log( const std::string& log_msg )
    {
        if ( log_msg.find( m_log_message() ) != std::string::npos )
        {
            throw_exception_by_name( m_exception_name() );
        }
    }


    void throw_exception_wheng_log_guard::throw_exception_by_name( const std::string& exception_name )
    {
        #define throw_exception_impl( exp_name, exp_type ) if ( exp_name == exception_name ) { throw exp_type; }
        throw_exception_impl( "..." , "..." );
        throw_exception_impl( "CORBA::Exception", CORBA::UNKNOWN() );
        throw_exception_impl( "PortableServer::POA::ObjectNotActive", PortableServer::POA::ObjectNotActive() );
        throw_exception_impl( "TA_Base_Core::OperationModeException", TA_Base_Core::OperationModeException() );
        throw_exception_impl( "std::exception", std::bad_exception() );
        throw_exception_impl( "CosNotifyFilter::InvalidGrammar", CosNotifyFilter::InvalidGrammar() );
        throw_exception_impl( "CosNotifyFilter::InvalidConstraint", CosNotifyFilter::InvalidConstraint() );
        throw_exception_impl( "CosNotifyChannelAdmin::AdminLimitExceeded", CosNotifyChannelAdmin::AdminLimitExceeded() );
        throw_exception_impl( "CosEventChannelAdmin::AlreadyConnected", CosEventChannelAdmin::AlreadyConnected() );
        throw_exception_impl( "TA_Base_Core::FederationFailed", TA_Base_Core::FederationFailed() );
        throw_exception_impl( "TA_Base_Core::DataException", TA_Base_Core::DataException( "", TA_Base_Core::DataException::WRONG_TYPE, "" ) );
        throw_exception_impl( "TA_Base_Core::DatabaseException", TA_Base_Core::DatabaseException( "" ) );
        throw_exception_impl( "TA_Base_Core::TcpSocketException", TA_Base_Core::TcpSocketException() );
        throw_exception_impl( "TA_Base_Core::TransactiveException", TA_Base_Core::TransactiveException() );
        throw_exception_impl( "TA_Base_Core::FTPException", TA_Base_Core::FTPException() );
        throw_exception_impl( "TA_Base_Core::UtilitiesException", TA_Base_Core::UtilitiesException() );
        throw_exception_impl( "TA_Base_Core::ManagedProcessException", TA_Base_Core::ManagedProcessException() );
        throw_exception_impl( "TA_Base_Core::ProcessRunningException", TA_Base_Core::ProcessRunningException() );
        throw_exception_impl( "unsigned int", static_cast<unsigned int>(0) );
        #undef throw_exception_impl
    }


    std::string& throw_exception_wheng_log_guard::m_exception_name()
    {
        static std::string exception_name;
        return exception_name;
    }


    std::string& throw_exception_wheng_log_guard::m_log_message()
    {
        static std::string log_message;
        return log_message;
    }


    void throw_exception_wheng_log_guard::TA_Base_Core_DebugUtil_log(const std::string& file, int line, unsigned long type, ...)
    {
        {
            va_list arg_list;
            va_start( arg_list, type );

            if ( TA_Base_Core::DebugUtil::GenericLog == static_cast<TA_Base_Core::DebugUtil::EDebugType>( type ) )
            {
                int level = va_arg ( arg_list, int ); // ignore
            }

            char* format_string = va_arg( arg_list, char* );
            unit_test::throw_exception_wheng_log_guard::throw_exception_if_log( format_string );

            va_end( arg_list );
        }

        assert( sizeof(TA_Base_Core::DebugUtil) == sizeof(TA_Base_Core_DebugUtil) );

        TA_Base_Core_DebugUtil* m_this = reinterpret_cast<TA_Base_Core_DebugUtil*>( this );
        TA_Base_Core_DebugUtil::hook_to_debug_util_member_functions();

        TA_Base_Core::ThreadGuard guard ( m_this->getLock() );

        va_list args;
        va_start ( args, type );

        try
        {
            int level;
            if ( type == TA_Base_Core::DebugUtil::GenericLog )
            {
                level = va_arg ( args, int );
                std::string levelCheck = m_this->getStringDebugLevel ( ( TA_Base_Core::DebugUtil::EDebugLevel ) level );
                va_start ( args, type );
            }
            else
            {
                char* firstArg = va_arg ( args, char* );
                std::string temp(firstArg);
                va_start ( args, type );
                level = m_this->m_logger->getLevel ( static_cast<TA_Base_Core::DebugUtil::EDebugType>( type ) );
            }

            m_this->m_lastMsgLevel = ( TA_Base_Core::DebugUtil::EDebugLevel ) level;

            if ( m_this->preLogChecks(static_cast<TA_Base_Core::DebugUtil::EDebugLevel>(level) ) )
            {
                // Reset the arg pointer
                va_end ( args );
                return;
            }

            bool simpleLog = false;
            bool printCache = false;

            if ( level <= m_this->m_currDebugLevel )
            {
                m_this->logMessage( file, line, static_cast<TA_Base_Core::DebugUtil::EDebugType>( type ), args, simpleLog, printCache );
            }

            va_end ( args );
        }
        catch ( ... )
        {
            std::cerr << "DebugUtil::log(): Caught an unknown exception. Message will not be logged." << std::endl;
            va_end ( args );
            throw;
        }
    }


    void throw_exception_wheng_log_guard::TA_Base_Core_DebugUtil_logGeneric( const std::string& file, int line, ... )
    {
        {
            va_list arg_list;
            va_start( arg_list, line );
            int level = va_arg ( arg_list, int ); // ignore

            char* format_string = va_arg( arg_list, char* );
            unit_test::throw_exception_wheng_log_guard::throw_exception_if_log( format_string );

            va_end( arg_list );
        }

        assert( sizeof(TA_Base_Core::DebugUtil) == sizeof(TA_Base_Core_DebugUtil) );

        TA_Base_Core_DebugUtil* m_this = reinterpret_cast<TA_Base_Core_DebugUtil*>( this );
        TA_Base_Core_DebugUtil::hook_to_debug_util_member_functions();

        TA_Base_Core::ThreadGuard guard (m_this->getLock());

        va_list args;
        va_start ( args, line );

        try
        {
            int level;
            level = va_arg ( args, int );

            std::string levelCheck = m_this->getStringDebugLevel ( ( TA_Base_Core::DebugUtil::EDebugLevel ) level );

            va_start ( args, line );

            m_this->m_lastMsgLevel = ( TA_Base_Core::DebugUtil::EDebugLevel ) level;

            if ( m_this->preLogChecks(static_cast<TA_Base_Core::DebugUtil::EDebugLevel>(level)) )
            {
                va_end ( args );
                return;
            }

            bool printCache;
            bool simpleLog = false;
            if ( m_this->m_currDebugLevel == TA_Base_Core::DebugUtil::DebugFatal || m_this->m_currDebugLevel == TA_Base_Core::DebugUtil::DebugError )
            {
                if ( level <= m_this->m_currDebugLevel )
                {
                    printCache = true;
                    m_this->logMessage( file, line, TA_Base_Core::DebugUtil::GenericLog, args, simpleLog, printCache );
                }
                else
                {
                    m_this->m_logger->addToCache ( TA_Base_Core::DebugUtil::GenericLog, file, line, args, simpleLog );
                }
            }
            else
            {
                if ( level > m_this->m_currDebugLevel )
                {
                }
                else
                {
                    printCache = false;
                    m_this->logMessage( file, line, TA_Base_Core::DebugUtil::GenericLog, args, simpleLog, printCache );
                }
            }

            va_end ( args );
        }
        catch ( ... )
        {
            std::cerr << "DebugUtil::logGeneric(): Caught an unknown exception. Message will not be logged" << std::endl;
            va_end ( args );
            throw;
        }
    }


}
