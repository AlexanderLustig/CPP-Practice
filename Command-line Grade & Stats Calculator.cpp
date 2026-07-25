#include <iostream>
#include <string>

// Requirements: constexpr at file scope (Ch. 5.6)
constexpr int PASSING_SCORE = 60;
constexpr int MAX_SCORES = 100;

// 1. Function to read and validate scores into the array
void getScores(int scores[], int count) {
    for (int i = 0; i < count; i++) {
        int inputScore;
        std::cout << "Enter test score " << i + 1 << ": ";
        std::cin >> inputScore;

        // Keep re-prompting until input is valid (0 to 100)
        while (inputScore < 0 || inputScore > 100) {
            std::cout << "Invalid score. Please enter a score between 0 and 100: ";
            std::cin >> inputScore;
        }

        scores[i] = inputScore;

        // Modulo requirement: flag every 3rd VALID score entered
        if ((i + 1) % 3 == 0) {
            std::cout << "Checkpoint reached!" << std::endl;
        }
    }
}

// 2. Function to compute total sum
int computeSum(int scores[], int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += scores[i];
    }
    return sum;
}

// 3. Function to compute average (returns double to avoid truncation)
double computeAverage(int sum, int count) {
    return static_cast<double>(sum) / count;
}

// 4. Function to find highest score
int findHighest(int scores[], int count) {
    int highest = scores[0];
    for (int i = 1; i < count; i++) {
        if (scores[i] > highest) {
            highest = scores[i];
        }
    }
    return highest;
}

// 5. Function to find lowest score
int findLowest(int scores[], int count) {
    int lowest = scores[0];
    for (int i = 1; i < count; i++) {
        if (scores[i] < lowest) {
            lowest = scores[i];
        }
    }
    return lowest;
}

// 6. Function to print final report
void printReport(int sum, double average, int highest, int lowest, int passed, int failed, double passPercentage) {
    std::cout << "\n--- STATS REPORT ---" << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Average: " << average << std::endl;
    std::cout << "Highest: " << highest << std::endl;
    std::cout << "Lowest: " << lowest << std::endl;
    std::cout << "Passed: " << passed << std::endl;
    std::cout << "Failed: " << failed << std::endl;
    std::cout << "Passing Rate: " << passPercentage << "%" << std::endl;
}

int main() {
    // std::string requirement
    std::string studentName;
    std::cout << "Enter student name: ";
    std::cin >> studentName;

    int n;
    std::cout << "How many test scores do you want to enter? ";
    std::cin >> n;

    // Bounds check to prevent stack overflow buffer overflow
    while (n <= 0 || n > MAX_SCORES) {
        std::cout << "Please enter a number between 1 and " << MAX_SCORES << ": ";
        std::cin >> n;
    }

    // Fixed-size array (no vectors/pointers)
    int numScores[MAX_SCORES];

    getScores(numScores, n);

    int sum = computeSum(numScores, n);
    double average = computeAverage(sum, n);
    int highest = findHighest(numScores, n);
    int lowest = findLowest(numScores, n);

    // Count passed vs failed
    int passed = 0;
    int failed = 0;
    for (int i = 0; i < n; i++) {
        if (numScores[i] >= PASSING_SCORE) {
            passed++;
        }
        else {
            failed++;
        }
    }

    double passPercentage = (static_cast<double>(passed) / n) * 100.0;

    printReport(sum, average, highest, lowest, passed, failed, passPercentage);

    return 0;
}
