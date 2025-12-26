#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <gtest/gtest.h>

#include "Lib/Dice_lib_1.h"
void test(const DiceGenerator& generator, const int tryes)
{
    std::map<int,int> results;
    const int count_try = tryes;
    for(int i = 0; i < count_try; ++i)
    {
        int result = generator.generate_value();
        results[result]++;
    }

    std::cout << "=== STATISTICS FOR 2d6+2 ===" << std::endl;
    std::cout << "Total tries: " << count_try << std::endl;
    
    int min_value = results.begin()->first;
    int max_value = results.rbegin()->first;
    std::cout << "Range: " << min_value << " - " << max_value << std::endl;
    
    std::cout << "\nAll results:" << std::endl;
    std::cout << std::setw(10) << "Value" 
              << std::setw(12) << "Count" 
              << std::setw(12) << "Percent" << std::endl;
    std::cout << std::string(34, '-') << std::endl;
    
    int total_sum = 0;
    for(const auto& result : results)
    {
        double percent = (static_cast<double>(result.second) / count_try) * 100.0;
        std::cout << std::setw(10) << result.first
                  << std::setw(12) << result.second
                  << std::setw(11) << std::fixed << std::setprecision(2) << percent << "%" << std::endl;
        total_sum += result.second * result.first;
    }
    
    double average = static_cast<double>(total_sum) / count_try;
    std::cout << "\nAverage value: " << std::fixed << std::setprecision(2) << average << std::endl;
    
    auto mode_it = std::max_element(results.begin(), results.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
    std::cout << "Mode (most frequent): " << mode_it->first 
              << " (appeared " << mode_it->second << " times)" << std::endl;
    
    std::vector<int> all_values;
    all_values.reserve(count_try);
    for(const auto& result : results)
    {
        for(int i = 0; i < result.second; ++i)
        {
            all_values.push_back(result.first);
        }
    }
    std::sort(all_values.begin(), all_values.end());
    double median = 0.0;
    if (all_values.size() % 2 == 0)
    {
        median = (all_values[all_values.size()/2 - 1] + all_values[all_values.size()/2]) / 2.0;
    }
    else
    {
        median = all_values[all_values.size()/2];
    }
    std::cout << "Median: " << median << std::endl;
    
    std::cout << "\nDistribution histogram:" << std::endl;
    int max_count = mode_it->second;
    const int max_bar_width = 50;
    
    for(int value = min_value; value <= max_value; ++value)
    {
        auto it = results.find(value);
        int count = (it != results.end()) ? it->second : 0;
        int bar_width = (max_count > 0) ? (count * max_bar_width / max_count) : 0;
        
        std::cout << std::setw(3) << value << ": "
                  << std::string(bar_width, '#')
                  << " (" << count << ")" << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (1)
    {
        ::testing::InitGoogleTest(&argc, argv);
        RUN_ALL_TESTS();
    }
    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    DiceGenerator dice_generator;
    dice_generator.new_dices("d2,d5,2d7,8d10+5,2d6-2,gg");
    std::cout<<std::endl<<dice_generator.generate_value()<<std::endl;

    dice_generator.new_dices("2d6+2");
    test(dice_generator,10000);

    dice_generator.new_dices("2d6+2,3d10");
    test(dice_generator,10000);
}
