#include <iostream>
#include <vector>
#include <cmath> 


// ЗАДАЧА 2: Удаление дубликатов
int removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) return 0;

    int write_index = 1;

    for (int read_index = 1; read_index < static_cast<int>(nums.size()); ++read_index) {
        if (nums[read_index] != nums[write_index - 1]) {
            nums[write_index] = nums[read_index];
            ++write_index;
        }
    }

    return write_index;
}

// ЗАДАЧА 3: Квадраты отсортированного массива
std::vector<int> sortedSquares(std::vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    std::vector<int> result(n); 

    int left = 0;
    int right = n - 1;
    int pos = n - 1;

    while (left <= right) {
        int left_sq = nums[left] * nums[left];
        int right_sq = nums[right] * nums[right];

        if (left_sq > right_sq) {
            result[pos] = left_sq;
            ++left;
        } else {
            result[pos] = right_sq;
            --right;
        }
        --pos;
    }

    return result;
}

// ЗАДАЧА 4: Переместить все нули в конец 
void moveZeroes(std::vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    int write_index = 0;

    for (int i = 0; i < n; ++i) {
        if (nums[i] != 0) {
            nums[write_index] = nums[i];
            ++write_index;
        }
    }

    for (int i = write_index; i < n; ++i) {
        nums[i] = 0;
    }
}

// ЗАДАЧА 5: Найти все пропущенные числа (от 1 до n)
std::vector<int> findMissingNumbers(std::vector<int> nums) {
    int n = static_cast<int>(nums.size());
    std::vector<int> missing;


    for (int i = 0; i < n; ++i) {
        int value = std::abs(nums[i]);
        int index = value - 1;      
        if (nums[index] > 0) {
            nums[index] = -nums[index];
        }
    }


    for (int i = 0; i < n; ++i) {
        if (nums[i] > 0) {
            missing.push_back(i + 1);
        }
    }

    return missing;
}


// ЗАДАЧА 6: Произведение всех элементов, кроме текущего

std::vector<int> productExceptSelf(const std::vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    std::vector<int> result(n, 1);


    for (int i = 1; i < n; ++i) {
        result[i] = result[i - 1] * nums[i - 1];
    }


    int right_product = 1;
    for (int i = n - 1; i >= 0; --i) {
        result[i] = result[i] * right_product;
        right_product = right_product * nums[i];
    }

    return result;
}


int main() {
    // --- Задача 2 ---
    std::vector<int> v2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int k2 = removeDuplicates(v2);
    std::cout << "Задача 2: ";
    for (int i = 0; i < k2; ++i) {
        std::cout << v2[i] << " ";
    }
    std::cout << "\n";

    // --- Задача 3 ---
    std::vector<int> v3 = {-4, -1, 0, 3, 10};
    std::vector<int> res3 = sortedSquares(v3);
    std::cout << "Задача 3: ";
    for (int x : res3) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // --- Задача 4 ---
    std::vector<int> v4 = {0, 1, 0, 3, 12};
    moveZeroes(v4);
    std::cout << "Задача 4: ";
    for (int x : v4) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // --- Задача 5 ---
    std::vector<int> v5 = {4, 3, 2, 7, 8, 2, 3, 1};
    std::vector<int> res5 = findMissingNumbers(v5);
    std::cout << "Задача 5: ";
    for (int x : res5) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // --- Задача 6 ---
    std::vector<int> v6 = {1, 2, 3, 4};
    std::vector<int> res6 = productExceptSelf(v6);
    std::cout << "Задача 6: ";
    for (int x : res6) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}