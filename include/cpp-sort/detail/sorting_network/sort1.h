/*
 * Copyright (c) 2015-2021 Morwenn
 * SPDX-License-Identifier: MIT
 */
#ifndef CPPSORT_DETAIL_SORTING_NETWORK_SORT1_H_
#define CPPSORT_DETAIL_SORTING_NETWORK_SORT1_H_

namespace cppsort
{
namespace detail
{
    template<>
    struct sorting_network_sorter_impl<1u>
    {
        template<
            typename RandomAccessIterator,
            typename Compare = std::less<>,
            typename Projection = utility::identity,
            typename = std::enable_if_t<is_projection_iterator_v<
                Projection, RandomAccessIterator, Compare
            >>
        >
        auto operator()(RandomAccessIterator, RandomAccessIterator,
                        Compare={}, Projection={}) const
            -> void
        {}
    };
}}

#endif // CPPSORT_DETAIL_SORTING_NETWORK_SORT1_H_
