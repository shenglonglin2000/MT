#include "core/utilities/test/unit_test_utlities/hook_guard.h"
#include "windows.h"
#include <cassert>


namespace unit_test
{


    hook_guard::hook_guard() {}


    hook_guard::hook_guard( void* src, void* dst, bool is_swap )
    {
        add_local_hook( src, dst, is_swap );
    }


    hook_guard::hook_guard( const char* dll_name, const char* dll_function_name, void* dst )
    {
        add_local_dll_hook( dll_name, dll_function_name, dst );
    }


    hook_guard::~hook_guard()
    {
        remove_all_items_from_map( m_local_src_backup );
        remove_all_items_from_map( m_local_dst_backup );
    }


    void hook_guard::add_local_hook( void* src, void* dst, bool is_swap )
    {
        add_hook_impl( m_local_src_backup, m_local_dst_backup, src, dst, is_swap );
    }


    void hook_guard::remove_local_hook( void* src, void* dst )
    {
        remove_hook_impl( m_local_src_backup, m_local_dst_backup, src, dst );
    }


    void hook_guard::add_global_hook( void* src, void* dst, bool is_swap )
    {
        add_hook_impl( m_global_src_backup(), m_global_dst_backup(), src, dst, is_swap );
    }


    void hook_guard::remove_global_hook( void* src, void* dst )
    {
        remove_hook_impl( m_global_src_backup(), m_global_dst_backup(), src, dst );
    }


    void hook_guard::add_local_dll_hook( const char* dll_name, const char* dll_function_name, void* dst )
    {
        add_dll_hook_impl( m_local_src_backup, m_local_dst_backup, dll_name, dll_function_name, dst );
    }


    void hook_guard::remove_local_dll_hook( const char* dll_name, const char* dll_function_name, void* dst )
    {
        remove_dll_hook_impl( m_local_src_backup, m_local_dst_backup, dll_name, dll_function_name, dst );
    }


    void hook_guard::add_global_dll_hook( const char* dll_name, const char* dll_function_name, void* dst )
    {
        add_dll_hook_impl( m_global_src_backup(), m_global_dst_backup(), dll_name, dll_function_name, dst );
    }


    void hook_guard::remove_global_dll_hook( const char* dll_name, const char* dll_function_name, void* dst )
    {
        remove_dll_hook_impl( m_global_src_backup(), m_global_dst_backup(), dll_name, dll_function_name, dst );
    }


    void hook_guard::add_hook_impl( std::map<long*, long>& src_backup, std::map<long*, long>& dst_backup, void* src, void* dst, bool is_swap )
    {
        long* src_jmp_operand_address = get_address_of_operand_of_jmp_instruction( src );
        long src_jmp_operand = *src_jmp_operand_address;
        src_backup[src_jmp_operand_address] = src_jmp_operand;

        long* dst_jmp_operand_address = get_address_of_operand_of_jmp_instruction( dst );
        long dst_jmp_operand = *dst_jmp_operand_address;
        dst_backup[dst_jmp_operand_address] = dst_jmp_operand;

        long new_src_jmp_operand = dst_jmp_operand + reinterpret_cast<unsigned long>( dst ) - reinterpret_cast<unsigned long>( src );
        long new_dst_jmp_operand = src_jmp_operand + reinterpret_cast<unsigned long>( src ) - reinterpret_cast<unsigned long>( dst );

        modify_memory( src_jmp_operand_address, new_src_jmp_operand );

        if ( true == is_swap )
        {
            modify_memory( dst_jmp_operand_address, new_dst_jmp_operand );
        }
    }


    void hook_guard::remove_hook_impl( std::map<long*, long>& src_backup, std::map<long*, long>& dst_backup, void* src, void* dst )
    {
        remove_item_from_map( src_backup, get_address_of_operand_of_jmp_instruction( src ) );
        remove_item_from_map( dst_backup, get_address_of_operand_of_jmp_instruction( dst ) );
    }


    void hook_guard::add_dll_hook_impl( std::map<long*, long>& src_backup, std::map<long*, long>& dst_backup, const char* dll_name, const char* dll_function_name, void* dst )
    {
        long* src_address = get_address_of_dll_function( dll_name, dll_function_name );
        long src_value = *src_address;
        src_backup[ src_address ] = src_value;

        //long* dst_address = get_address_of_operand_of_jmp_instruction( dst );
        //long dst_value = *dst_address;
        //dst_backup[ dst_address ] = dst_value;

        modify_memory( src_address, reinterpret_cast<long>( dst ) );
        // modify_memory( dst_address, src_value ); // IMPORTANT: DO NOT MODIFY THIS ADDRESS
    }


    void hook_guard::remove_dll_hook_impl( std::map<long*, long>& src_backup, std::map<long*, long>& dst_backup, const char* dll_name, const char* dll_function_name, void* dst )
    {
        remove_item_from_map( src_backup, get_address_of_dll_function( dll_name, dll_function_name ) );
        // remove_item_from_map( dst_backup, get_address_of_operand_of_jmp_instruction( dst ) );
    }


    std::map<long*, long>& hook_guard::m_global_src_backup()
    {
        static std::map<long*, long> global_src_jmp_operand_backup;
        return global_src_jmp_operand_backup;
    }


    std::map<long*, long>& hook_guard::m_global_dst_backup()
    {
        static std::map<long*, long> global_dst_jmp_operand_backup;
        return global_dst_jmp_operand_backup;
    }


    long* hook_guard::get_address_of_operand_of_jmp_instruction( void* instruction_address )
    {
        return reinterpret_cast<long*>( reinterpret_cast<unsigned long>( instruction_address ) + 1 );
    }


    long* hook_guard::get_address_of_dll_function( const char* dll_name, const char* dll_function_name )
    {
        #define make_ptr( cast, ptr, add_value )( cast )( ( DWORD )( ptr ) + ( DWORD )( add_value ) )

        PIMAGE_DOS_HEADER dos_header_ptr;
        PIMAGE_NT_HEADERS nt_header_ptr;
        PIMAGE_IMPORT_DESCRIPTOR import_desc_ptr;
        PIMAGE_THUNK_DATA thunk_ptr;
        void *old_function;

        if ( !( old_function = GetProcAddress( GetModuleHandle( dll_name ), dll_function_name ) ) )
        {
            return NULL;
        }

        dos_header_ptr = ( PIMAGE_DOS_HEADER )GetModuleHandle(NULL );;
        if ( dos_header_ptr->e_magic != IMAGE_DOS_SIGNATURE )
        {
            return NULL;
        }

        nt_header_ptr = make_ptr( PIMAGE_NT_HEADERS, dos_header_ptr, dos_header_ptr->e_lfanew );
        if ( nt_header_ptr->Signature != IMAGE_NT_SIGNATURE ||
             ( import_desc_ptr = make_ptr( PIMAGE_IMPORT_DESCRIPTOR, dos_header_ptr, nt_header_ptr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress ) ) == ( PIMAGE_IMPORT_DESCRIPTOR )nt_header_ptr )
        {
            return NULL;
        }

        while ( import_desc_ptr->Name )
        {
            const char* module_name = make_ptr( const char* , dos_header_ptr, import_desc_ptr->Name );
            if ( !_stricmp( module_name, dll_name ) )
            {
                break;
            }

            import_desc_ptr++;
        }

        if ( import_desc_ptr->Name == NULL )
        {
            return NULL;
        }

        thunk_ptr = make_ptr( PIMAGE_THUNK_DATA, dos_header_ptr, import_desc_ptr->FirstThunk );

        while ( thunk_ptr->u1.Function )
        {
            if ( thunk_ptr->u1.Function == ( DWORD )old_function )
            {
                return reinterpret_cast<long*>( &thunk_ptr->u1.Function );
            }

            thunk_ptr++;
        }

        #undef make_ptr
        return NULL;
    }


    void hook_guard::remove_item_from_map( std::map<long*, long>& the_map, long* the_item )
    {
        std::map<long*, long>::iterator find_it = the_map.find( the_item );

        if ( find_it != the_map.end() )
        {
            modify_memory( find_it->first, find_it->second );
            the_map.erase( find_it );
        }
    }


    void hook_guard::remove_all_items_from_map( std::map<long*, long>& the_map )
    {
        for ( std::map<long*, long>::iterator it = the_map.begin(); it != the_map.end(); ++it )
        {
            modify_memory( it->first, it->second );
        }

        the_map.clear();
    }


    void hook_guard::modify_memory( long* address, long value )
    {
        unsigned long m_old_protect;
        VirtualProtect( address, 4, PAGE_EXECUTE_WRITECOPY, &m_old_protect );
        *address = value;
        VirtualProtect( address, 4, m_old_protect, &m_old_protect );
    }


}

