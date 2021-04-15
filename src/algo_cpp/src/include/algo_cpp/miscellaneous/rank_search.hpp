//
// Created by Nathan on 2021/4/4.
//

#ifndef ORG_NATHAN_CPP_ALL_IN_ONE_RANK_SEARCH_CPP
#define ORG_NATHAN_CPP_ALL_IN_ONE_RANK_SEARCH_CPP

#include <vector>
#include <random>
#include <iostream>
#include <exception>

namespace org::nathan::algo_cpp::miscellaneous
{
    using RandEngine_t = std::mt19937;
    using std::vector;
    using std::cout, std::endl;

    class RankSearch final
    {
    private:
        template<typename Comparable>
        static int randPartition(vector<Comparable> &a, int start, int end, RandEngine_t &engine)
        {
            std::uniform_int_distribution dist{start, end - 1};
            int pivot_idx{dist(engine)};

            auto pivot{a[pivot_idx]};

            auto temp{a[end - 1]};
            a[end - 1] = pivot;
            a[pivot_idx] = temp;

            int i{start - 1};
            for (int j{start}; j < end - 1; j++)
            {
                if (a[j] <= pivot)
                {
                    auto t{a[j]};
                    a[j] = a[++i];
                    a[i] = t;
                }
            }
            a[end - 1] = a[++i];
            a[i] = pivot;
            return i; //pivot idx
        }

        // select ith smallest element in array
        template<typename Comparable>
        static Comparable rankSearch(vector<Comparable> &a, int start, int end, int ith, RandEngine_t &engine)
        {
            if ((start - end) == 1)
            {
                return a[start];
            }
            int pivot_idx{randPartition(a, start, end, engine)};
            int left_total{pivot_idx - start};
            if (ith == left_total)
            {
                return a[pivot_idx];
            }
            else if (ith < left_total + 1)
            {
                return rankSearch(a, start, pivot_idx, ith, engine);
            }
            else
            {
                return rankSearch(a, pivot_idx + 1, end, ith - left_total - 1, engine);
            }
        }


    public:
        template<typename Comparable>
        [[maybe_unused]] static Comparable find(vector<Comparable> &a, int ith)
        {
            if (a.empty())
            {
                throw std::logic_error{"size is zero."};
            }
            std::random_device seed{};
            RandEngine_t engine{seed()};
            return rankSearch(a, 0, a.size(), ith, engine);
        }
    };
}


#endif //ORG_NATHAN_CPP_ALL_IN_ONE_RANK_SEARCH_CPP