#ifndef UNIT_TEST_HOOK_GUARD_H
#define UNIT_TEST_HOOK_GUARD_H


#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/preprocessor/cat.hpp>


namespace unit_test
{

    class hook_guard
    {
    public:

        hook_guard();
        hook_guard( void* src, void* dst, bool is_swap = true );
        hook_guard( const char* dll_name, const char* dll_function_name, void* dst );
        ~hook_guard();

        void add_local_hook( void* src, void* dst, bool is_swap = true );
        void remove_local_hook( void* src, void* dst );

        void add_local_dll_hook( const char* dll_name, const char* dll_function_name, void* dst );
        void remove_local_dll_hook( const char* dll_name, const char* dll_function_name, void* dst );

        static void add_global_hook( void* src, void* dst, bool is_swap = true );
        static void remove_global_hook( void* src, void* dst );

        static void add_global_dll_hook( const char* dll_name, const char* dll_function_name, void* dst );
        static void remove_global_dll_hook( const char* dll_name, const char* dll_function_name, void* dst );

    public:

        template<typename member_function_ptr_type> static void* get_overload_member_function_address( member_function_ptr_type member_function )
        {
            // TODO: sometimes this function will fail!!! (Note: thunk)
            member_function_ptr_type member_function_ptr = member_function;
            return (void*)( *( ( long *)&member_function_ptr ) );
        }

    private:

        static void add_hook_impl( std::map<long*, long>& src_backup, std::map<long*, long>& dst_backup, void* src, void* dst, bool is_swap = true );
        static void remove_hook_impl( std::map<long*, long>& src_backup, std::map<long*, long>& dst_backup, void* src, void* dst );
        static void add_dll_hook_impl( std::map<long*, long>& src_backup, std::map<long*, long>& dst_backup, const char* dll_name, const char* dll_function_name, void* dst );
        static void remove_dll_hook_impl( std::map<long*, long>& src_backup, std::map<long*, long>& dst_backup, const char* dll_name, const char* dll_function_name, void* dst );

        static long* get_address_of_operand_of_jmp_instruction( void* instruction_address );
        static long* get_address_of_dll_function( const char* dll_name, const char* dll_function_name );

        static void remove_item_from_map( std::map<long*, long>& the_map, long* the_item );
        static void remove_all_items_from_map( std::map<long*, long>& the_map );

        static void modify_memory( long* address, long value );

    private:

        static std::map<long*, long>& m_global_src_backup();
        static std::map<long*, long>& m_global_dst_backup();

    private:

        std::map<long*, long> m_local_src_backup;
        std::map<long*, long> m_local_dst_backup;
    };

    typedef boost::shared_ptr<hook_guard> hook_guard_ptr;

}


#define get_member_function_address_vc8(member_function_address, member_function_type)              \
void* member_function_address;                                                                      \
{                                                                                                   \
    __asm                                                                                           \
    {                                                                                               \
        mov eax,offset member_function_type                                                         \
    };                                                                                              \
    __asm                                                                                           \
    {                                                                                               \
        mov member_function_address, eax                                                            \
    };                                                                                              \
}

#define hook_member_function_guard_impl(guard, src_addr, dst_addr, src_mem_fun, dst_mem_fun)        \
    get_member_function_address_vc8( src_addr, src_mem_fun );                                       \
    get_member_function_address_vc8( dst_addr, dst_mem_fun );                                       \
    unit_test::hook_guard guard(src_addr, dst_addr )

#define hook_member_function_guard( src_mem_fun, dst_mem_fun )                                      \
    hook_member_function_guard_impl( BOOST_PP_CAT(___hook_member_function_guard___, __LINE__),      \
                                     BOOST_PP_CAT(___hook_member_function_src_addr___, __LINE__),   \
                                     BOOST_PP_CAT(___hook_member_function_dst_addr___, __LINE__),   \
                                     src_mem_fun,                                                   \
                                     dst_mem_fun )

#define hook_member_function( src_mem_fun, dst_mem_fun )                                            \
{                                                                                                   \
    get_member_function_address_vc8( src_addr, src_mem_fun );                                       \
    get_member_function_address_vc8( dst_addr, dst_mem_fun );                                       \
    unit_test::hook_guard::add_global_hook(src_addr, dst_addr );                                    \
}

#define hook_member_function_no_swap( src_mem_fun, dst_mem_fun )                                    \
{                                                                                                   \
    get_member_function_address_vc8( src_addr, src_mem_fun );                                       \
    get_member_function_address_vc8( dst_addr, dst_mem_fun );                                       \
    unit_test::hook_guard::add_global_hook(src_addr, dst_addr, false );                             \
}

#define hook_dll_function_guard_impl(guard, dll_name, dll_function_name, dst_addr, dst_mem_fun)     \
    get_member_function_address_vc8( dst_addr, dst_mem_fun );                                       \
    unit_test::hook_guard guard(dll_name, dll_function_name, dst_addr )

#define hook_dll_function_guard( dll_name, dll_function_name, dst_mem_fun )                         \
    hook_dll_function_guard_impl( BOOST_PP_CAT(___hook_dll_function_guard___, __LINE__),            \
                                  dll_name,                                                         \
                                  dll_function_name,                                                \
                                  BOOST_PP_CAT(___hook_dll_function_guard__dst_addr___, __LINE__),  \
                                  dst_mem_fun )

#define hook_dll_function( dll_name, dll_function_name, dst_mem_fun )                               \
{                                                                                                   \
    get_member_function_address_vc8( dst_addr, dst_mem_fun );                                       \
    unit_test::hook_guard::add_global_dll_hook(dll_name, dll_function_name, dst_addr );             \
}


#define unit_test_hook_member_function_guard hook_member_function_guard
#define unit_test_hook_member_function hook_member_function

#define unit_test_hook_dll_function_guard hook_dll_function_guard
#define unit_test_hook_dll_function hook_dll_function


#endif // UNIT_TEST_HOOK_GUARD_H

