#include <iostream>
#include <stdexcept>

class CustomArray {
private:
    int* arr;         // Pointer to the dynamically allocated block on the Heap
    int capacity;     // Total physical slots allocated
    int size;         // Current number of logically active elements

public:
    // Constructor: Allocates continuous block of memory on the Heap
    CustomArray(int cap) {
        if (cap <= 0) {
            throw std::invalid_argument("Capacity must be greater than zero.");
        }
        capacity = cap;
        size = 0;
        arr = new int[capacity];
    }

    // Destructor: Cleans up physical allocation to prevent memory leaks
    ~CustomArray() {
        delete[] arr;
        arr = nullptr;
    }

    // 1. Traversal: O(n) Time | O(1) Space
    void traverse() const {
        if (size == 0) {
            std::cout << "Array is empty.\n";
            return;
        }
        std::cout << "Current Array State (Size: " << size << "/" << capacity << "): [ ";
        for (int i = 0; i < size; ++i) {
            std::cout << arr[i] << (i == size - 1 ? "" : ", ");
        }
        std::cout << " ]\n";
    }

    // 2. Access: O(1) Time | O(1) Space
    int access(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Access Error: Index out of bounds.");
        }
        return arr[index];
    }

    // 3. Update: O(1) Time | O(1) Space
    void update(int index, int newValue) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Update Error: Index out of bounds.");
        }
        arr[index] = newValue;
    }

    // 4. Insertion at End: O(1) Time | O(1) Space
    bool insertAtEnd(int value) {
        if (size >= capacity) {
            std::cout << "Insertion Failed: Array reached maximum capacity.\n";
            return false;
        }
        arr[size] = value;
        size++;
        return true;
    }

    // 5. Insertion at Beginning: O(n) Time | O(1) Space
    bool insertAtBeginning(int value) {
        if (size >= capacity) {
            std::cout << "Insertion Failed: Array reached maximum capacity.\n";
            return false;
        }
        // Shift all existing elements one slot to the right
        for (int i = size; i > 0; --i) {
            arr[i] = arr[i - 1];
        }
        arr[0] = value;
        size++;
        return true;
    }

    // 6. Insertion at Middle (Arbitrary Index k): O(n) Time | O(1) Space
    bool insertAtMiddle(int index, int value) {
        if (size >= capacity) {
            std::cout << "Insertion Failed: Array reached maximum capacity.\n";
            return false;
        }
        if (index < 0 || index > size) {
            std::cout << "Insertion Failed: Index out of logical bounds.\n";
            return false;
        }
        // Shift elements from the target index outward to the right
        for (int i = size; i > index; --i) {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
        size++;
        return true;
    }

    // 7. Deletion from End: O(1) Time | O(1) Space
    bool deleteFromEnd() {
        if (size == 0) {
            std::cout << "Deletion Failed: Array underflow (Empty).\n";
            return false;
        }
        // Logical deletion: Decrement tracking pointer size
        size--;
        return true;
    }

    // 8. Deletion from Beginning: O(n) Time | O(1) Space
    bool deleteFromBeginning() {
        if (size == 0) {
            std::cout << "Deletion Failed: Array underflow (Empty).\n";
            return false;
        }
        // Shift all trailing elements leftward by one slot
        for (int i = 0; i < size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        size--;
        return true;
    }

    // 9. Deletion from Middle (Arbitrary Index k): O(n) Time | O(1) Space
    bool deleteFromMiddle(int index) {
        if (size == 0) {
            std::cout << "Deletion Failed: Array underflow (Empty).\n";
            return false;
        }
        if (index < 0 || index >= size) {
            std::cout << "Deletion Failed: Index out of bounds.\n";
            return false;
        }
        // Shift elements to the right of index leftward to cover the gap
        for (int i = index; i < size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        size--;
        return true;
    }

    // 10. Linear Search: O(n) Time | O(1) Space
    int linearSearch(int key) const {
        for (int i = 0; i < size; ++i) {
            if (arr[i] == key) {
                return i; // Found: Return matching index slot
            }
        }
        return -1; // Not Found
    }

    // 11. Binary Search: O(log n) Time | O(1) Space
    // NOTE: The collection must be sorted before calling this method.
    int binarySearch(int key) const {
        int low = 0;
        int high = size - 1;

        while (low <= high) {
            // Using low + (high - low) / 2 to safely prevent explicit integer overflow bugs
            int mid = low + (high - low) / 2;

            if (arr[mid] == key) {
                return mid;
            } else if (arr[mid] < key) {
                low = mid + 1; // Discard left half
            } else {
                high = mid - 1; // Discard right half
            }
        }
        return -1; // Not Found
    }

    // Helper Utility: In-Place Bubble Sort to prepare for Binary Search demonstrations
    void bubbleSort() {
        for (int i = 0; i < size - 1; ++i) {
            bool swapped = false;
            for (int j = 0; j < size - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    swapped = true;
                }
            }
            if (!swapped) break; // Optimization if sub-array is already sorted
        }
    }
};

int main() {
    std::cout << "=== INITIALIZING HIGH-PERFORMANCE CUSTOM ARRAY (Capacity = 10) ===\n";
    CustomArray myArray(10);
    myArray.traverse();

    std::cout << "\n--- DEMONSTRATING INSERTIONS ---\n";
    myArray.insertAtEnd(10);
    myArray.insertAtEnd(20);
    myArray.insertAtEnd(30);
    myArray.traverse(); // Expecting: [10, 20, 30]

    myArray.insertAtBeginning(5);
    myArray.traverse(); // Expecting: [5, 10, 20, 30]

    myArray.insertAtMiddle(2, 15);
    myArray.traverse(); // Expecting: [5, 10, 15, 20, 30]

    std::cout << "\n--- DEMONSTRATING ACCESS & UPDATE ---\n";
    try {
        std::cout << "Element at Index 2: " << myArray.access(2) << "\n"; // Expecting: 15
        std::cout << "Updating Index 2 to 99...\n";
        myArray.update(2, 99);
        myArray.traverse(); // Expecting: [5, 10, 99, 20, 30]
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }

    std::cout << "\n--- DEMONSTRATING DELETIONS ---\n";
    myArray.deleteFromBeginning();
    myArray.traverse(); // Expecting: [10, 99, 20, 30]

    myArray.deleteFromEnd();
    myArray.traverse(); // Expecting: [10, 99, 20]

    myArray.deleteFromMiddle(1);
    myArray.traverse(); // Expecting: [10, 20]

    std::cout << "\n--- DEMONSTRATING SEARCH TECHNIQUES ---\n";
    // Adding values to broaden dataset range
    myArray.insertAtEnd(45);
    myArray.insertAtEnd(12);
    myArray.insertAtEnd(88);
    myArray.traverse(); // Current order: [10, 20, 45, 12, 88]

    // 1. Linear Search Run
    int searchKey = 12;
    int lsResult = myArray.linearSearch(searchKey);
    std::cout << "Linear Search for Key (" << searchKey << ") returned index: " << lsResult << "\n";

    // 2. Binary Search Run (Sorting array first)
    std::cout << "Sorting array via Bubble Sort to meet Binary Search prerequisite...\n";
    myArray.bubbleSort();
    myArray.traverse(); // Expecting sorted state: [10, 12, 20, 45, 88]

    searchKey = 45;
    int bsResult = myArray.binarySearch(searchKey);
    std::cout << "Binary Search for Key (" << searchKey << ") returned index: " << bsResult << "\n";

    searchKey = 100; // Testing non-existent entry case
    bsResult = myArray.binarySearch(searchKey);
    std::cout << "Binary Search for Key (" << searchKey << ") returned index: " << bsResult << " (Not Found)\n";

    std::cout << "\n=== EXECUTION COMPLETE (Heap memory successfully released via Destructor) ===\n";
    return 0;
}