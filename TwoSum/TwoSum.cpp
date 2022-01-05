#include "TwoSumConfig.h"
#include <iostream>
#ifdef USE_HM
#include <map>
#endif
#include <stdexcept>
#include <vector>

using namespace std;

class Solution
{
public:
    Solution(size_t _N, int _target)
    {
        #ifdef USE_BF
        std::cout << "Solution: Brute Force" << std::endl;
        #elif USE_HM
        std::cout << "Solution: Optimal with hash map" << std::endl;
        #endif

        if (_N >= 2 && _N <= 10'000)
            m_N = _N;
        else
            throw std::out_of_range("N");
        if (_target >= -1'000'000'000 && _target <= 1'000'000'000)
            m_Target = _target;
        else
            throw std::out_of_range("Target");
    }
public:
    virtual vector<int> twoSum(vector<int>& nums, int target) = 0;

    void initialize(vector<int>& nums)
    {
        nums.clear();
        nums.resize(m_N);
        for (size_t i = 0; i < m_N; i++)
            nums[i] = i - m_N / 2;
    }
private:
    size_t m_N;
    int m_Target;
};

#ifdef USE_BF
class SolutionBruteForce: public Solution
{
public:
    SolutionBruteForce(size_t _N, int _target) : Solution(_N, _target) {}
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        int idx1 = 0;
        int idx2 = 1;
        if (nums.size() == 2)
            return vector<int>({idx1, idx2});
        bool stop = false;
        while (!stop)
        {
            if ((nums[idx1] + nums[idx2]) == target)
                stop = true;
            else {
                idx2++;
                if (idx2 >= nums.size()) {
                    idx1++;
                    idx2 = idx1 + 1;
                    if (idx1 >= nums.size() - 2)
                        stop = true;
                }
            }
        }
        return vector<int>({idx1, idx2});
    }
};
#elif USE_HM
class SolutionHashMap: public Solution
{
public:
    SolutionHashMap(size_t _N, int _target) : Solution(_N, _target) {}
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        int idx1 = 0;
        int idx2 = 1;
        std::map<int, size_t> value_map;

        for (vector<int>::iterator it1 = nums.begin(); it1 < nums.end(); it1++)
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
        return vector<int>({idx1, idx2});
    }
};
#endif

int main(int argc, char* argv[])
{
    const size_t N = 100;
    const int Target = 0;
    vector<int> nums;
    vector<int> indexes;

    try
    {
        #ifdef USE_BF
        SolutionBruteForce sol(N, Target);
        #elif USE_HM
        SolutionHashMap sol(N, Target);
        #else
        #error Choose solution: USE_BF, USE_HM
        #endif

        sol.initialize(nums);
        indexes = sol.twoSum(nums, 0);
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    for (const auto& el: nums)
        std::cout << el << " ";
    std::cout << std::endl;

    std::cout << "[ ";
    for (const auto& ix: indexes)
        std::cout << ix << " ";
    std::cout << "]" << std::endl;

    return 0;
}
