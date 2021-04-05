//
// Created by Nathan on 2021/3/15.
//

#ifndef ORG_NATHAN_LEARNCPP_UTILS_H
#define ORG_NATHAN_LEARNCPP_UTILS_H

#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <exception>


namespace org::nathan::utils
{

    using std::chrono::steady_clock;
    using std::chrono::time_point;
    using std::chrono::duration;
    using std::vector;

    /**
     *
     * @return steady_clock::now()
     */
    [[maybe_unused]] typeof(steady_clock::now()) currentTime();


    /**
     *
     * @param current current steady_clock::now()
     * @param last last steady_clock::now()
     * @return milliseconds in double
     */
    [[maybe_unused]] double timeIntervalToMilli(
            time_point<steady_clock, duration<double>> current,
            time_point<steady_clock, duration<double>> last);


    /**
     * [low, high) shuffled vector
     * @tparam Number
     * @param low include
     * @param high exclude
     * @return
     */
    template<typename Number>
    [[maybe_unused]] vector<Number> shuffledRange(int low, int high)
    {
        if (high <= low)
        {
            throw std::range_error("low >= high");
        }
        vector<Number> r(high - low);
        std::generate(r.begin(), r.end(), [n = 0]() mutable
        { return n++; });
        std::shuffle(r.begin(), r.end(), std::mt19937{std::random_device{}()});
        return r;
    }
}


#endif //ORG_NATHAN_LEARNCPP_UTILS_H
