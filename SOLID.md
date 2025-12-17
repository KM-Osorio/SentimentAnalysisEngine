# SOLID Principles Implementation in Sentiment Analysis Engine

This project was designed following Clean Architecture and SOLID principles to ensure scalability and maintainability.

## 1. Single Responsibility Principle (SRP)
**Principle:** A module should have one, and only one, reason to change.
**Implementation:**
- `Functions.cpp`: Handles business logic exclusively (text cleaning, tokenization, and mathematical scoring).
- `main.cpp`: Handles User Interface (I/O) and workflow orchestration exclusively.
- Presentation logic is strictly decoupled from calculation logic.

## 2. Open/Closed Principle (OCP)
**Principle:** Software entities should be open for extension, but closed for modification.
**Implementation:**
- The `Lexicon` (Dictionary) system is injected via data structures (`std::map`).
- This allows adding new languages or modifying word polarities without rewriting or recompiling the core analysis algorithm in `analyzeSentiment`.

## 3. Interface Segregation Principle (ISP)
**Principle:** Clients should not be forced to depend on interfaces they do not use.
**Implementation:**
- Header files are segregated into `Functions.h` (logic) and `Models.h` (data structures), avoiding a "God Object" or monolithic headers that force unnecessary recompilations.