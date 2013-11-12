#include "core/utilities/test/unit_test_utlities/generic_stub.h"

namespace unit_test
{

    void compile_check_generic_stub_0()
    {
        unit_test_declare_stub_class_0(stub_int_0, int);
        unit_test_declare_stub_class_0(stub_bool_0, bool);

        stub_int_0 test1;
        stub_int_0::set_returns(1, 2, 3, 4, 5, 6, 7, 8, 9);
        test1.impl();
        test1.static_impl();

        stub_bool_0 test3;
        test3.impl();
        test3.static_impl();

        stub_int_0 test2;
        test2.impl();
        test2.static_impl();
    }


    void compile_check_generic_stub_1()
    {
        unit_test_declare_stub_class_1(stub_int_1, int, int);
        unit_test_declare_stub_class_1(stub_void_1, void, int&);

        stub_int_1 test1;
        int x = 0;
        int* px = NULL;
        const int* cpx = NULL;
        test1.set_returns(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        test1.set_outs_1(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        test1.impl(x);
        test1.static_impl(x);

        stub_void_1 test2;
        test2.set_outs_1(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        test2.impl(x);
        test2.static_impl(x);
    }


    void compile_check_generic_stub_7()
    {
        unit_test_declare_stub_class_7(stub_int_7, int, int, int&, const int&, int*, const int*, int*&, const int*&);
        unit_test_declare_stub_class_7(stub_void_7, void, int, int&, const int&, int*, const int*, int*&, const int*&);

        stub_int_7 test1;
        int x = 0;
        int* px = NULL;
        const int* cpx = NULL;
        test1.set_returns(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        test1.set_outs_1(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        test1.set_outs_3(px, px, px, px, px, px, px, px, px, px);
        test1.set_outs_5(px, px, px, px, px, px, px, px, px, px);
        test1.impl(x, x, x, px, cpx, px, cpx);
        test1.static_impl(x, x, x, px, cpx, px, cpx);

        stub_void_7 test2;
        test2.set_outs_1(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        test2.set_outs_3(px, px, px, px, px, px, px, px, px, px);
        test2.set_outs_5(px, px, px, px, px, px, px, px, px, px);
        test2.impl(x, x, x, px, cpx, px, cpx);
        test2.static_impl(x, x, x, px, cpx, px, cpx);
    }


    void compile_check_assign_value()
    {
        {
            int left;
            int right;
            generic_assign<int, false, false, false>( left, right );
            generic_assign<int&, false, false, true>( left, right );
            generic_assign<const int, false, true, false>( left, right );
            generic_assign<const int&, false, true, true>( left, right );
        }

        {
            int* left;
            int* right;
            generic_assign<int*, true, false, false>( left, right );
            generic_assign<int*&, true, false, true>( left, right );
        }

        {
            const int* left;
            const int* right;
            generic_assign<const int*, true, true, false>( left, right );
            generic_assign<const int*&, true, true, true>( left, right );
        }
    }

}
