#ifndef UNIT_TEST_THROW_EXCEPTION_WHEN_LOG_GUARD_H
#define UNIT_TEST_THROW_EXCEPTION_WHEN_LOG_GUARD_H


#include "core/utilities/test/unit_test_utlities/hook_guard.h"
#include <boost/preprocessor/cat.hpp>
#include <string>


namespace unit_test
{

    struct throw_exception_wheng_log_guard
    {
    public:

        throw_exception_wheng_log_guard( const std::string& exception_to_throw, unsigned long debug_level, const std::string& log_msg );
        ~throw_exception_wheng_log_guard();

    public:

        static void throw_exception_if_log( const std::string& log_msg );
        static void throw_exception_by_name( const std::string& exception_name );

        static std::string& m_exception_name();
        static std::string& m_log_message();

    private:

        int m_debug_level_backup;
        unit_test::hook_guard m_hook_guard;

    public:

        void TA_Base_Core_DebugUtil_log(const std::string& file, int line, unsigned long type, ...);
        void TA_Base_Core_DebugUtil_logGeneric(const std::string& file, int line, ...);

    };

} // namespace unit_test


#define unit_test_throw_exception_when_log_guard( exp_name, debug_level, log_msg ) unit_test::throw_exception_wheng_log_guard BOOST_PP_CAT(hook_guard_, __COUNTER__)( exp_name, debug_level, log_msg )


#endif
