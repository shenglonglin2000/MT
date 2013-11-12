#ifndef UNIT_TEST_GENERIC_STUB_H
#define UNIT_TEST_GENERIC_STUB_H


#include "core/utilities/test/unit_test_utlities/throw_exception_when_log_guard.h"
#include <boost/type_traits.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <map>
#include <iostream>


#define CAT                 BOOST_PP_CAT
#define REPEAT              BOOST_PP_REPEAT
#define ENUM_PARAMS         BOOST_PP_ENUM_PARAMS
#define ENUM_BINARY_PARAMS  BOOST_PP_ENUM_BINARY_PARAMS
#define INC                 BOOST_PP_INC


namespace unit_test
{

    template<typename T, bool if_is_pointer, bool if_is_const, bool if_is_reference>
    struct generic_assign
    {
        generic_assign( typename boost::add_reference<T>::type lhs, typename boost::add_reference<T>::type rhs ) { throw "!!!SHOULD NOT BE CALLED!!!"; }
    };

    template<typename T, bool if_is_pointer>
    struct generic_assign<T, if_is_pointer, false, true>
    {
        generic_assign( typename boost::add_reference<T>::type lhs, typename boost::add_reference<T>::type rhs )
        {
            lhs = rhs;
            /*DEBUG LOG*/ std::cout << "[generic_stub] " << "generic_assign<T=" << typeid(T).name() << ", if_is_pointer=" << if_is_pointer << ", if_is_const=false, if_is_reference=true>()" << std::endl;
        }
    };

    template<typename T>
    struct generic_assign<T, true, false, false>
    {
        generic_assign( typename boost::add_reference<T>::type lhs, typename boost::add_reference<T>::type rhs )
        {
            // *lhs = *rhs;
            lhs = rhs;
            /*DEBUG LOG*/ std::cout << "[generic_stub] " << "generic_assign<T=" << typeid(T).name() << ", if_is_pointer=true, if_is_const=false, if_is_reference=true>()" << std::endl;
        }
    };

    template<>
    struct generic_assign<char*, true, false, false>
    {
        generic_assign( char* lhs, char* rhs )
        {
            strcpy( lhs, rhs );
            /*DEBUG LOG*/ std::cout << "[generic_stub] " << "generic_assign<T=char*, if_is_pointer=true, if_is_const=false, if_is_reference=true>()" << std::endl;
        }
    };

    template<typename U/*unique*/>
    struct generic_stub
    {
        static void set_exception_name( const std::string& exception_name ) { m_exception_name() = exception_name; }

        static void clean_up()
        {
            m_call_time() = 0;
            m_exception_name() = "";
            m_exception_names().clear();
            /*DEBUG LOG*/ std::cout << "[generic_stub] " << "generic_stub<" << typeid(U).name() << ">::clean_up()" << std::endl;
        }

        static void throw_exception_impl()
        {
            if ( 0 < m_exception_names().size() && m_exception_names().find( m_call_time() ) != m_exception_names().end() )
            {
                unit_test::throw_exception_wheng_log_guard::throw_exception_by_name( m_exception_names()[m_call_time()] );
            }
            else
            {
                unit_test::throw_exception_wheng_log_guard::throw_exception_by_name( m_exception_name() );
            }
        }

        template<typename R>
        static typename boost::add_reference<R>::type generic_impl()
        {
            if ( 0 < m_returns<R>().size() && m_call_time() < m_returns<R>().size() )
            {
                // return m_returns<R>()[m_call_time()];
                return m_returns<typename boost::remove_reference<R>::type>()[m_call_time()];
            }
            else
            {
                // return m_return<R>();
                return m_return<typename boost::remove_reference<R>::type>();
            }
        }

        static void generic_void_impl()
        {
            throw_exception_impl();
            m_call_time()++;
        }

        #define function_template_assign_value_to_out_parameter_n_body(z, n, zz) \
            std::map<size_t, typename boost::remove_reference<CAT(T, n)>::type>& CAT(outs_, n) = CAT(m_outs_, n)<typename boost::remove_reference<CAT(T, n)>::type>(); \
            typename boost::add_reference<CAT(T, n)>::type CAT(out_, n) = CAT(m_out_, n)<typename boost::remove_reference<CAT(T, n)>::type>(); \
            if ( CAT(m_is_need_assign_value_to_out_parameter_, n)() ) \
            { \
                if ( 0 < CAT(outs_, n).size() && CAT(outs_, n).find( m_call_time() ) != CAT(outs_, n).end() ) \
                { \
                    /*DEBUG LOG */ std::cout << "assign_value_to_out_parameter_" << n << "() - assign to m_outs_" << n << std::endl;\
                    generic_assign< CAT(T, n), \
                                  boost::is_pointer<CAT(T, n)>::value, \
                                  boost::is_const<typename boost::remove_reference<typename boost::remove_pointer<CAT(T, n)>::type>::type>::value, \
                                  boost::is_reference<CAT(T, n) >::value>( CAT(p, n), CAT(outs_, n)[m_call_time()] ); \
                } \
                else \
                { \
                    /*DEBUG LOG*/ std::cout << "assign_value_to_out_parameter_" << n << "() - assign to m_out_" << n << std::endl; \
                    generic_assign< CAT(T, n), \
                                  boost::is_pointer<CAT(T, n)>::value, \
                                  boost::is_const<typename boost::remove_reference<typename boost::remove_pointer<CAT(T, n)>::type>::type>::value, \
                                  boost::is_reference<CAT(T, n)>::value >( CAT(p, n), CAT(out_, n) ); \
                } \
            }
        #define function_template_assign_value_to_out_parameter_n(z, n, function_name) \
            template<ENUM_PARAMS(INC(n), typename T)> \
            static void CAT(function_name, n)( ENUM_BINARY_PARAMS(INC(n), T, p) ) \
            { \
                REPEAT(INC(n), function_template_assign_value_to_out_parameter_n_body, z) \
                /*DEBUG LOG*/ std::cout << "[generic_stub] " << #function_name << n << "<" << typeid(typename boost::remove_reference<T0>::type).name() << ">()" << std::endl; \
            }
        REPEAT( 10, function_template_assign_value_to_out_parameter_n, assign_value_to_out_parameter_);
        #undef function_template_assign_value_to_out_parameter_n
        #undef function_template_assign_value_to_out_parameter_n_body

        template<typename T>
        static void set_return( T p)
        {
            m_return<typename boost::remove_reference<T>::type>() = p;
            /*DEBUG LOG*/ std::cout << "[generic_stub] " << "set_return<" << typeid(T).name() << ">()" << std::endl;
        }

        #define function_template_set_returns_body(z, n, zz) m_returns<typename boost::remove_reference<CAT(T, n)>::type>()[n] = CAT(p, n);
        #define function_template_set_returns(z, n, zz) \
            template<ENUM_PARAMS(INC(n), typename T)> \
            static void set_returns( ENUM_BINARY_PARAMS(INC(n), T, p) ) \
            { \
                REPEAT(INC(n), function_template_set_returns_body, z); \
                /*DEBUG LOG*/ std::cout << "[generic_stub] " << "set_returns<" << typeid(T0).name() << ">()" << std::endl; \
            }
        REPEAT( 10, function_template_set_returns, z);
        #undef function_template_set_returns
        #undef function_template_set_returns_body

        #define function_template_set_out_n(z, n, zz) \
            template<typename T> \
            static void CAT(set_out_, n)( T p ) \
            { \
                CAT(m_is_need_assign_value_to_out_parameter_, n)() = true; \
                CAT(m_out_, n)<typename boost::remove_reference<T>::type>() = p; \
                /*DEBUG LOG*/ std::cout << "[generic_stub] " << "set_out_" << n << "<" << typeid(T).name() << ">()" << std::endl; \
            };
        REPEAT(10, function_template_set_out_n, z);
        #undef function_template_set_out_n

        #define function_template_set_outs_n(z, n, zz) REPEAT( 10, function_template_set_outs_x, n);
        #define function_template_set_outs_x_body(z, n, outs)  outs[n] = CAT(p, n); /*DEBUG: std::cout << #outs << "[" << n << "]=" << CAT(p, n) << std::endl;*/
        #define function_template_set_outs_x(z, n, param_num) \
            template<ENUM_PARAMS(INC(n), typename T)> \
            static void CAT(set_outs_, param_num)( ENUM_BINARY_PARAMS(INC(n), T, p) ) \
            { \
                CAT(m_is_need_assign_value_to_out_parameter_, param_num)() = true; \
                REPEAT(INC(n), function_template_set_outs_x_body, CAT(m_outs_, param_num)<typename boost::remove_reference<CAT(T, n)>::type>() ); \
                /*DEBUG LOG*/ std::cout << "[generic_stub] " << "set_outs_" << n << "<" << typeid(T0).name() << ">()" << std::endl; \
            }
        REPEAT( 10, function_template_set_outs_n, z);
        #undef function_template_set_outs_x
        #undef function_template_set_outs_x_body
        #undef function_template_set_outs_n

    public:

        static size_t& m_call_time() { static size_t call_time; return call_time; }
        static std::string& m_exception_name() { static std::string exception_name; return exception_name; }
        static std::map<size_t, std::string>& m_exception_names() { static std::map<size_t, std::string> exception_names; return exception_names; }

        #define m_is_need_assign_value_to_out_parameter_n(z, n, function_name) \
            static bool& CAT(function_name, n)() \
            { \
                static bool is_need; \
                /*DEBUG LOG*/ std::cout << "[generic_stub] " << #function_name << n << "=" << is_need << std::endl; \
                return is_need; \
            }
        REPEAT(10, m_is_need_assign_value_to_out_parameter_n, m_is_need_assign_value_to_out_parameter_);
        #undef m_is_need_assign_value_to_out_parameter_n

        template<typename R>
        static typename boost::add_reference<R>::type m_return()
        {
            static typename boost::remove_reference<R>::type object;
            /*DEBUG LOG*/ std::cout << "m_return<" << typeid(typename boost::remove_reference<R>::type).name() << ">()" << std::endl;
            return object;
        }

        template<typename R>
        static std::map<size_t, typename boost::remove_reference<R>::type>& m_returns()
        {
            //IMPORTANT NOTE: CAN NOT use std::vector, because std::vector<bool> is special!!!
            static std::map<size_t, typename boost::remove_reference<R>::type> objects;
            /*DEBUG LOG*/ std::cout << "[generic_stub] " << "m_returns<" << typeid(typename boost::remove_reference<R>::type).name() << ">()" << std::endl;
            return objects;
        }

        #define function_template_m_outs_n(z, n, zz) \
            template<typename T> \
            static typename boost::add_reference<T>::type CAT(m_out_, n)() \
            { \
                static typename boost::remove_reference<T>::type m_out; \
                /*DEBUG LOG*/ std::cout << "[generic_stub] " << "m_out_" << n << "<" << typeid(typename boost::remove_reference<T>::type).name() << ">()" << std::endl; \
                return m_out; \
            } \
            template<typename T> \
            static std::map<size_t, typename boost::remove_reference<T>::type>& CAT(m_outs_, n)() \
            { \
                static std::map<size_t, typename boost::remove_reference<T>::type> m_outs; \
                /*DEBUG LOG*/ std::cout << "[generic_stub] " << "m_outs_" << n << "<" << typeid(typename boost::remove_reference<T>::type).name() << ">()" << std::endl; \
                return m_outs; \
            }
        REPEAT( 10, function_template_m_outs_n, z);
        #undef function_template_m_outs_n

    };

    template<typename U, typename R>
    struct generic_stub_0 : generic_stub<U>
    {
        ~generic_stub_0()
        {
            clean_up();
        }

        R impl()
        {
            return internal_impl();
        }

        static R static_impl()
        {
            return internal_impl();
        }

        static void clean_up()
        {
            generic_stub::clean_up();
            m_returns<R>().clear();
            /*DEBUG LOG*/ std::cout << "[generic_stub] " << "generic_stub_0<" << typeid(U).name() << ", " << typeid(R).name() << ">::clean_up()" << std::endl;
        }

    private:

        static R internal_impl()
        {
            generic_stub::throw_exception_impl();
            typename boost::add_reference<R>::type r = generic_stub::generic_impl<R>();
            m_call_time()++;
            return r;
        }
    };

    template<typename U>
    struct generic_stub_0<U, void> : generic_stub<U>
    {
        ~generic_stub_0()
        {
            clean_up();
        }

        void impl()
        {
            internal_impl();
        }

        static void static_impl()
        {
            internal_impl();
        }

        static void clean_up()
        {
            generic_stub::clean_up();
        }

    private:

        static void internal_impl()
        {
            generic_stub::generic_void_impl();
        }
    };

    #define clean_up_m_outs_n_body(z, n, t) \
        CAT(m_outs_, n)<typename boost::remove_reference<t>::type>().clear(); \
        CAT(m_is_need_assign_value_to_out_parameter_, n)() = false;
    #define class_template_generic_stub_n(z, n, zz) \
        template<typename U, typename R, ENUM_PARAMS(INC(n), typename T)> \
        struct CAT(generic_stub_, INC(n)) : generic_stub<U> \
        { \
            ~CAT(generic_stub_, INC(n))() { clean_up(); } \
            R impl( ENUM_BINARY_PARAMS(INC(n), T, p) ) \
            { \
                return internal_impl( ENUM_PARAMS(INC(n), p) ); \
            } \
            static R static_impl( ENUM_BINARY_PARAMS(INC(n), T, p) ) \
            { \
                return internal_impl( ENUM_PARAMS(INC(n), p) ); \
            } \
            static void clean_up() \
            { \
                generic_stub::clean_up(); \
                m_returns<R>().clear(); \
                REPEAT( INC(n), clean_up_m_outs_n_body, CAT(T, n) ); \
                /*DEBUG LOG*/ std::cout << "[generic_stub] " << "generic_stub_" << n << "<" << typeid(U).name() << ", " << typeid(R).name() << ", ...>::clean_up()" << std::endl; \
            } \
        private: \
            static R internal_impl( ENUM_BINARY_PARAMS(INC(n), T, p) ) \
            { \
                generic_stub::throw_exception_impl(); \
                generic_stub::CAT(assign_value_to_out_parameter_, n)<ENUM_PARAMS(INC(n), T)>( ENUM_PARAMS(INC(n), p) ); \
                typename boost::add_reference<R>::type r = generic_stub::generic_impl<R>(); \
                m_call_time()++; \
                return r; \
            } \
        }; \
        template<typename U, ENUM_PARAMS(INC(n), typename T)> \
        struct CAT(generic_stub_, INC(n))<U, void, ENUM_PARAMS(INC(n), T)> : generic_stub<U> \
        { \
            ~CAT(generic_stub_, INC(n))() { clean_up(); } \
            void impl( ENUM_BINARY_PARAMS(INC(n), T, p) ) \
            { \
                internal_impl( ENUM_PARAMS(INC(n), p) ); \
            } \
            static void static_impl( ENUM_BINARY_PARAMS(INC(n), T, p) ) \
            { \
                internal_impl( ENUM_PARAMS(INC(n), p) ); \
            } \
            static void clean_up() \
            { \
                generic_stub::clean_up(); \
                REPEAT( INC(n), clean_up_m_outs_n_body, CAT(T, n) ); \
                /*DEBUG LOG*/ std::cout << "[generic_stub] " << "generic_stub_" << n << "<" << typeid(U).name() << ", void, ...>::clean_up()" << std::endl; \
            } \
        private: \
            static void internal_impl( ENUM_BINARY_PARAMS(INC(n), T, p) ) \
            { \
                generic_stub::CAT(assign_value_to_out_parameter_, n)<ENUM_PARAMS(INC(n), T)>( ENUM_PARAMS(INC(n), p) ); \
                generic_stub::generic_void_impl(); \
            } \
        };
    REPEAT( 10, class_template_generic_stub_n, z);
    #undef class_template_generic_stub_n
    #undef clean_up_m_outs_n_body

} // namespace unit_test


#undef CAT
#undef REPEAT
#undef ENUM_PARAMS
#undef ENUM_BINARY_PARAMS
#undef INC


#define unit_test_declare_stub_class_0( stub, T0 ) struct stub : public unit_test::generic_stub_0<stub, T0> {}
#define unit_test_declare_stub_class_1( stub, T0, T1 ) struct stub : public unit_test::generic_stub_1<stub, T0, T1> {}
#define unit_test_declare_stub_class_2( stub, T0, T1, T2 ) struct stub : public unit_test::generic_stub_2<stub, T0, T1, T2> {}
#define unit_test_declare_stub_class_3( stub, T0, T1, T2, T3 ) struct stub : public unit_test::generic_stub_3<stub, T0, T1, T2, T3> {}
#define unit_test_declare_stub_class_4( stub, T0, T1, T2, T3, T4 ) struct stub : public unit_test::generic_stub_4<stub, T0, T1, T2, T3, T4> {}
#define unit_test_declare_stub_class_5( stub, T0, T1, T2, T3, T4, T5 ) struct stub : public unit_test::generic_stub_5<stub, T0, T1, T2, T3, T4, T5> {}
#define unit_test_declare_stub_class_6( stub, T0, T1, T2, T3, T4, T5, T6 ) struct stub : public unit_test::generic_stub_6<stub, T0, T1, T2, T3, T4, T5, T6> {}
#define unit_test_declare_stub_class_7( stub, T0, T1, T2, T3, T4, T5, T6, T7 ) struct stub : public unit_test::generic_stub_7<stub, T0, T1, T2, T3, T4, T5, T6, T7> {}
#define unit_test_declare_stub_class_8( stub, T0, T1, T2, T3, T4, T5, T6, T7, T8 ) struct stub : public unit_test::generic_stub_8<stub, T0, T1, T2, T3, T4, T5, T6, T7, T8> {}
#define unit_test_declare_stub_class_9( stub, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9 ) struct stub : public unit_test::generic_stub_9<stub, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> {}


#endif // UNIT_TEST_HOOK_GUARD_H
