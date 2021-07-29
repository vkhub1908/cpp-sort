/*
 * Copyright (c) 2016-2021 Morwenn
 * SPDX-License-Identifier: MIT
 */
#ifndef CPPSORT_PROBES_PAR_H_
#define CPPSORT_PROBES_PAR_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <functional>
#include <iterator>
#include <new>
#include <type_traits>
#include <utility>
#include <cpp-sort/sorter_facade.h>
#include <cpp-sort/sorter_traits.h>
#include <cpp-sort/utility/functional.h>
#include <cpp-sort/utility/size.h>
#include <cpp-sort/utility/static_const.h>
#include "../detail/immovable_vector.h"
#include "../detail/is_p_sorted.h"
#include "../detail/iterator_traits.h"

namespace cppsort
{
namespace probe
{
    namespace detail
    {
        template<typename RandomAccessIterator, typename Compare, typename Projection>
        auto legacy_par_probe_algo(RandomAccessIterator first, RandomAccessIterator last,
                                   cppsort::detail::difference_type_t<RandomAccessIterator> size,
                                   Compare compare, Projection projection)
            -> ::cppsort::detail::difference_type_t<RandomAccessIterator>
        {
            // Simple algorithm in O(n log n) time and O(1) space

            auto res = 0;
            auto res_it = first;
            while (size > 0) {
                auto p = res;
                auto pth = res_it;
                p += size / 2;
                std::advance(pth, size / 2);
                if (cppsort::detail::is_p_sorted(first, last, pth, compare, projection)) {
                    size /= 2;
                } else {
                    res = ++p;
                    res_it = ++pth;
                    size -= size / 2 + 1;
                }
            }
            return res;
        }

        template<typename BidirectionalIterator, typename Compare, typename Projection>
        auto new_par_probe_algo(BidirectionalIterator first, BidirectionalIterator last,
                            cppsort::detail::difference_type_t<BidirectionalIterator> size,
                            Compare compare, Projection projection)
            -> ::cppsort::detail::difference_type_t<BidirectionalIterator>
        {
            using difference_type = ::cppsort::detail::difference_type_t<BidirectionalIterator>;
            auto&& comp = utility::as_function(compare);
            auto&& proj = utility::as_function(projection);

            // Algorithm described in *Roughly Sorting: Sequential and Parallel Approach*
            // by T. Altman and Y. Igarashi

            if (size < 2) {
                return 0;
            }

            // Algorithm LR
            cppsort::detail::immovable_vector<BidirectionalIterator> b(size);
            b.emplace_back(first);
            for (auto it = std::next(first) ; it != last ; ++it) {
                if (comp(proj(*b.back()), proj(*it))) {
                    b.emplace_back(it);
                } else {
                    b.emplace_back(b.back());
                }
            }

            // Algorithm RL
            cppsort::detail::immovable_vector<BidirectionalIterator> c(size);
            c.emplace_back(std::prev(last));
            auto rfirst = std::make_reverse_iterator(last);
            auto rlast = std::make_reverse_iterator(first);
            for (auto it = std::next(rfirst) ; it != rlast ; ++it) {
                if (comp(proj(*it), proj(*c.back()))) {
                    c.emplace_back(std::prev(it.base()));
                } else {
                    c.emplace_back(c.back());
                }
            }
            std::reverse(c.begin(), c.end());

            // Algorithm DM, without extra storage
            difference_type res = 0;
            difference_type i = size;
            for (auto j = i ; j > 0 ; --j) {
                while (j <= i && i >= 1 && not comp(proj(*b[j - 1]), proj(*c[i - 1]))
                       && (j == 1 || not comp(proj(*c[i - 1]), proj(*b[j - 2])))) {
                    res = std::max(res, i - j);
                    --i;
                }
            }

            return res;
        }

        template<typename BidirectionalIterator, typename Compare, typename Projection>
        auto par_probe_algo(BidirectionalIterator first, BidirectionalIterator last,
                            cppsort::detail::difference_type_t<BidirectionalIterator> size,
                            Compare compare, Projection projection,
                            std::bidirectional_iterator_tag)
            -> ::cppsort::detail::difference_type_t<BidirectionalIterator>
        {
            try {
                return new_par_probe_algo(first, last, size, compare, projection);
            } catch (std::bad_alloc&) {
                return legacy_par_probe_algo(
                    first, last, size,
                    std::move(compare), std::move(projection)
                );
            }
        }

        template<typename ForwardIterator, typename Compare, typename Projection>
        auto par_probe_algo(ForwardIterator first, ForwardIterator last,
                            cppsort::detail::difference_type_t<ForwardIterator> size,
                            Compare compare, Projection projection,
                            std::forward_iterator_tag)
            -> ::cppsort::detail::difference_type_t<ForwardIterator>
        {
            return legacy_par_probe_algo(first, last, size, compare, projection);
        }

        struct par_impl
        {
            template<
                typename ForwardIterable,
                typename Compare = std::less<>,
                typename Projection = utility::identity,
                typename = std::enable_if_t<
                    is_projection_v<Projection, ForwardIterable, Compare>
                >
            >
            auto operator()(ForwardIterable&& iterable, Compare compare={}, Projection projection={}) const
                -> decltype(auto)
            {
                using category = cppsort::detail::iterator_category_t<
                    cppsort::detail::remove_cvref_t<decltype(std::begin(iterable))>
                >;
                return par_probe_algo(std::begin(iterable), std::end(iterable),
                                      utility::size(iterable),
                                      std::move(compare), std::move(projection),
                                      category{});
            }

            template<
                typename ForwardIterator,
                typename Compare = std::less<>,
                typename Projection = utility::identity,
                typename = std::enable_if_t<
                    is_projection_iterator_v<Projection, ForwardIterator, Compare>
                >
            >
            auto operator()(ForwardIterator first, ForwardIterator last,
                            Compare compare={}, Projection projection={}) const
                -> decltype(auto)
            {
                using category = cppsort::detail::iterator_category_t<ForwardIterator>;
                return par_probe_algo(first, last, std::distance(first, last),
                                      std::move(compare), std::move(projection),
                                      category{});
            }

            template<typename Integer>
            static constexpr auto max_for_size(Integer n)
                -> Integer
            {
                return n == 0 ? 0 : n - 1;
            }
        };
    }

    namespace
    {
        constexpr auto&& par = utility::static_const<
            sorter_facade<detail::par_impl>
        >::value;
    }
}}

#endif // CPPSORT_PROBES_PAR_H_
