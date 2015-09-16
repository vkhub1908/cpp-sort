/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Morwenn
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <algorithm>
#include <array>
#include <iterator>
#include <catch.hpp>
#include <cpp-sort/sort.h>

TEST_CASE( "sort arrays of size 3", "[sort]" )
{
    SECTION( "sort C arrays" )
    {
        int arr0[] = { 1, 2, 3 };
        int arr1[] = { 1, 3, 2 };
        int arr2[] = { 2, 1, 3 };
        int arr3[] = { 2, 3, 1 };
        int arr4[] = { 3, 1, 2 };
        int arr5[] = { 3, 2, 1 };

        cppsort::sort(arr0);
        cppsort::sort(arr1);
        cppsort::sort(arr2);
        cppsort::sort(arr3);
        cppsort::sort(arr4);
        cppsort::sort(arr5);

        CHECK( std::is_sorted(std::begin(arr0), std::end(arr0)) );
        CHECK( std::is_sorted(std::begin(arr1), std::end(arr1)) );
        CHECK( std::is_sorted(std::begin(arr2), std::end(arr2)) );
        CHECK( std::is_sorted(std::begin(arr3), std::end(arr3)) );
        CHECK( std::is_sorted(std::begin(arr4), std::end(arr4)) );
        CHECK( std::is_sorted(std::begin(arr5), std::end(arr5)) );
    }

    SECTION( "sort std::array" )
    {
        std::array<int, 3u> arr0 = { 1, 2, 3 };
        std::array<int, 3u> arr1 = { 1, 3, 2 };
        std::array<int, 3u> arr2 = { 2, 1, 3 };
        std::array<int, 3u> arr3 = { 2, 3, 1 };
        std::array<int, 3u> arr4 = { 3, 1, 2 };
        std::array<int, 3u> arr5 = { 3, 2, 1 };

        cppsort::sort(arr0);
        cppsort::sort(arr1);
        cppsort::sort(arr2);
        cppsort::sort(arr3);
        cppsort::sort(arr4);
        cppsort::sort(arr5);

        CHECK( std::is_sorted(std::begin(arr0), std::end(arr0)) );
        CHECK( std::is_sorted(std::begin(arr1), std::end(arr1)) );
        CHECK( std::is_sorted(std::begin(arr2), std::end(arr2)) );
        CHECK( std::is_sorted(std::begin(arr3), std::end(arr3)) );
        CHECK( std::is_sorted(std::begin(arr4), std::end(arr4)) );
        CHECK( std::is_sorted(std::begin(arr5), std::end(arr5)) );
    }
}