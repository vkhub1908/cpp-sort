/*
 * Copyright (C) 2015 Morwenn
 *
 * array_sort is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * array_sort is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */
#ifndef CPPSORT_DETAIL_SORT9_H_
#define CPPSORT_DETAIL_SORT9_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utility>

namespace cppsort
{
namespace detail
{
    template<typename FallbackSorter>
    struct sorter_n<9u, FallbackSorter>
    {
        template<typename RandomAccessIterable, typename Compare>
        static auto do_it(RandomAccessIterable& iterable, Compare compare)
            -> void
        {
            using std::swap;

            if (compare(iterable[1u], iterable[0u])) {
                swap(iterable[0u], iterable[1u]);
            }
            if (compare(iterable[4u], iterable[3u])) {
                swap(iterable[3u], iterable[4u]);
            }
            if (compare(iterable[7u], iterable[6u])) {
                swap(iterable[6u], iterable[7u]);
            }
            if (compare(iterable[2u], iterable[1u])) {
                swap(iterable[1u], iterable[2u]);
            }
            if (compare(iterable[5u], iterable[4u])) {
                swap(iterable[4u], iterable[5u]);
            }
            if (compare(iterable[8u], iterable[7u])) {
                swap(iterable[7u], iterable[8u]);
            }
            if (compare(iterable[1u], iterable[0u])) {
                swap(iterable[0u], iterable[1u]);
            }
            if (compare(iterable[4u], iterable[3u])) {
                swap(iterable[3u], iterable[4u]);
            }
            if (compare(iterable[7u], iterable[6u])) {
                swap(iterable[6u], iterable[7u]);
            }
            if (compare(iterable[3u], iterable[0u])) {
                swap(iterable[0u], iterable[3u]);
            }
            if (compare(iterable[6u], iterable[3u])) {
                swap(iterable[3u], iterable[6u]);
            }
            if (compare(iterable[3u], iterable[0u])) {
                swap(iterable[0u], iterable[3u]);
            }
            if (compare(iterable[4u], iterable[1u])) {
                swap(iterable[1u], iterable[4u]);
            }
            if (compare(iterable[7u], iterable[4u])) {
                swap(iterable[4u], iterable[7u]);
            }
            if (compare(iterable[4u], iterable[1u])) {
                swap(iterable[1u], iterable[4u]);
            }
            if (compare(iterable[5u], iterable[2u])) {
                swap(iterable[2u], iterable[5u]);
            }
            if (compare(iterable[8u], iterable[5u])) {
                swap(iterable[5u], iterable[8u]);
            }
            if (compare(iterable[5u], iterable[2u])) {
                swap(iterable[2u], iterable[5u]);
            }
            if (compare(iterable[3u], iterable[1u])) {
                swap(iterable[1u], iterable[3u]);
            }
            if (compare(iterable[7u], iterable[5u])) {
                swap(iterable[5u], iterable[7u]);
            }
            if (compare(iterable[6u], iterable[2u])) {
                swap(iterable[2u], iterable[6u]);
            }
            if (compare(iterable[6u], iterable[4u])) {
                swap(iterable[4u], iterable[6u]);
            }
            if (compare(iterable[4u], iterable[2u])) {
                swap(iterable[2u], iterable[4u]);
            }
            if (compare(iterable[3u], iterable[2u])) {
                swap(iterable[2u], iterable[3u]);
            }
            if (compare(iterable[6u], iterable[5u])) {
                swap(iterable[5u], iterable[6u]);
            }
        }
    };
}}

#endif // CPPSORT_DETAIL_SORT9_H_