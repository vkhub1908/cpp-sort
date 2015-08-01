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
#ifndef CPPSORT_SORT_N_H_
#define CPPSORT_SORT_N_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>

namespace cppsort
{
    namespace detail
    {
        template<std::size_t N>
        struct sorter_n
        {
            // If there is no specialization to sort N value,
            // fall back to std::sort
            template<typename RandomAccessIterator, typename Compare>
            static auto do_it(RandomAccessIterator begin, Compare&& compare)
                -> void
            {
                std::sort(
                    begin, std::next(begin, N),
                    std::forward<Compare>(compare)
                );
            }
        };
    }

    template<
        std::size_t N,
        typename RandomAccessIterator,
        typename Compare = std::less<>
    >
    auto sort_n(RandomAccessIterator begin, Compare&& compare={})
        -> void
    {
        detail::sorter_n<N>::do_it(
            begin,
            std::forward<Compare>(compare)
        );
    }
}

// Specializations of sorter_n for some values of N
#include "detail/sort0.h"
#include "detail/sort1.h"
#include "detail/sort2.h"

#endif // CPPSORT_SORT_N_H_