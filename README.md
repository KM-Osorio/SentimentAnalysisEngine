# High-Performance Sentiment Analysis Engine 🚀

![Language](https://img.shields.io/badge/Language-C%2B%2B20-blue) ![Build](https://img.shields.io/badge/Build-CMake-success) ![Status](https://img.shields.io/badge/Status-Prototype-orange)

A latency-optimized engine designed for **real-time customer feedback analysis** and **financial reporting**.

This project demonstrates the transition from linear data structures to a **hybrid architecture (BST + Maps)** to minimize lookup time complexity, implementing strict SOLID principles for scalability.

## 📖 The Story Behind the Code

I wrote an article detailing the architectural decisions and performance optimizations in this project:
👉 **Read on Medium:** [Optimizing for Latency: Why I Ditched Linked Lists for a Hybrid C++ Architecture](https://medium.com/@katia-osorio/optimizing-for-latency-why-i-ditched-linked-lists-for-a-hybrid-c-architecture-77e14aeb64de)

## ⚡ Key Technical Features

### 1. Hybrid Data Structure Architecture (Functions.cpp)

Standard linear searches were insufficient for scaling product and lexicon lookups. I implemented a hybrid approach to optimize data retrieval:
* **O(log n) Product Lookup:** Replaced linear lists with **Binary Search Trees (BST)** for the product menu, ensuring efficient insertion and retrieval of dish data by code.
* **O(1) Sentiment Analysis:** Utilized `std::map` (Red-Black Tree implementation) for the sentiment lexicon, allowing constant-time average complexity when scoring individual tokens against thousands of words.

### 2. SOLID-Compliant Design

The engine avoids "God Classes" by strictly adhering to clean architecture principles:
* **Single Responsibility Principle (SRP):** Complete decoupling of Business Logic (`Functions.cpp`) from I/O operations (`main.cpp`).
* **Open/Closed Principle (OCP):** The sentiment scoring algorithm is closed for modification but open for extension; the lexicon is injected dynamically.

## 🛠️ Tech Stack

* **Language:** C++20 (STL Maps, Recursion, String Streams).
* **Build System:** CMake.
* **Testing:** GoogleTest (GTest).
* **Deployment:** Docker.

## 🚀 How to Build and Run

This project uses **CMake**. Ensure you have a C++ compiler (GCC/Clang/MSVC) installed.

# 1. Clone the repository
git clone https://github.com/KM-Osorio/sentiment-analysis-engine.git
cd sentiment-analysis-engine

# 2. Create build directory
mkdir build
cd build

# 3. Configure and Build
cmake ..
cmake --build .

# 4. Run the Engine
./SentimentAnalysisEngine
