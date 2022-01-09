#include "TwoSumConfig.h"
#include <chrono>
#include <iostream>
#ifdef USE_HM
#include <map>
#endif
#include <stdexcept>
#include <vector>

namespace TwoSum
{

using SizeType = size_t;
using ValueType = int;
using Vector = std::vector<ValueType>;
using TimeUnit = std::chrono::microseconds;

const SizeType minSize = 2;
const SizeType maxSize = 10'000;
const ValueType minValue = -1'000'000'000;
const ValueType maxValue = 1'000'000'000;

class Base
{
public:
    virtual const char* solutionName() const noexcept = 0;
    virtual Vector twoSum(Vector& nums, ValueType target) const = 0;

public:
    void checkSize(SizeType val) const
    {
        if (val < minSize || val > maxSize)
            throw std::out_of_range("Size");
    }

    void checkValue(ValueType val) const
    {
        if (val < minValue || val > maxValue)
            throw std::out_of_range("Value");
    }

    void init(Vector& nums, SizeType N) const
    {
        checkSize(N);

        nums.clear();
        nums.resize(N);

        for (SizeType i = 0; i < N; i++)
        {
            ValueType value = i - N / 2;
            checkValue(value);
            nums[i] = value;
        }
    }

    void print(const Vector& nums, const Vector& idxs, TimeUnit tm) const noexcept
    {
        printSolutionName();
        printSolutionVector("nums", nums);
        printSolutionVector("idxs", idxs);

        std::cout << "Solution time " << tm.count() << "us" << std::endl;
    }

private:
    void printSolutionName() const noexcept
    {
        std::cout << "Solution: " << solutionName() << std::endl;
    }

    void printSolutionVector(const char* name, const Vector& vec) const noexcept
    {
        std::cout << "Vector " << name << " = [";
        for (Vector::const_iterator i = vec.begin(); i != vec.end(); i++)
        {
            std::cout << *i;
            if ((i + 1) != vec.end())
                std::cout << " ";
        }
        std::cout << "]" << std::endl;
    }
};

#if !defined(USE_BF) && !defined(USE_HM)
#error "No solution's alog choosen (define USE_BF or USE_HM at compile time)"
#endif

#ifdef USE_BF
class BruteForce : public Base
{
public:
    const char* solutionName() const noexcept
    {
        return "Brute Force";
    }

    Vector twoSum(Vector& nums, ValueType target) const
    {
        checkValue(target);
        checkSize(nums.size());

        int idx1 = 0;
        int idx2 = 1;
        if (nums.size() == 2)
            return std::vector<int>({idx1, idx2});
        bool stop = false;
        while (!stop)
        {
            if ((nums[idx1] + nums[idx2]) == target)
                stop = true;
            else 
            {
                idx2++;
                if (idx2 >= nums.size()) {
                    idx1++;
                    idx2 = idx1 + 1;
                    if (idx1 >= nums.size() - 2)
                        stop = true;
                }
            }
        }
        return std::vector<int>({idx1, idx2});
    }
};

using Solution = BruteForce;
#endif

#ifdef USE_HM
class HashMap : public Base
{
public:
    const char* solutionName() const noexcept
    {
        return "Hash Map";
    }

    Vector twoSum(Vector& nums, ValueType target) const
    {
        checkValue(target);
        checkSize(nums.size());

        int idx1 = 0;
        int idx2 = 1;
        std::map<int, size_t> value_map;

        for (Vector::iterator it1 = nums.begin(); it1 < nums.end(); it1++)
        {
            int el1 = *it1;
            int el2 = target - el1;

            std::map<int, size_t>::iterator it2 = value_map.find(el2);

            if (it2 != value_map.end())
            {
                idx1 = it2->second;
                idx2 = it1 - nums.begin();
                break;
            }
            else
                value_map.emplace(el1, it1 - nums.begin());
        }
        return std::vector<int>({idx1, idx2});
    }
};

using Solution = HashMap;
#endif

}; // namespace TwoSum

int main(int argc, char* argv[])
{
    const TwoSum::SizeType N = 10000;
    const TwoSum::ValueType Target = 9997;

    TwoSum::Vector nums;
    TwoSum::Vector idxs;

    TwoSum::TimeUnit diff_us; 

    TwoSum::Solution S;

    try
    {
        S.init(nums, N);

        const auto start = std::chrono::steady_clock::now();
        idxs = S.twoSum(nums, Target);
        const auto stop = std::chrono::steady_clock::now();
        diff_us = std::chrono::duration_cast<TwoSum::TimeUnit>(stop - start);
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << "Error: out of range " << e.what() << '\n';
        return 1;
    }
    
    S.print(nums, idxs, diff_us);

    return 0;
}
