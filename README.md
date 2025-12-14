# LogicArena – Console-Based Quiz Game (C++)

LogicArena is a **terminal-based quiz application** developed in **C++**, focusing strictly on **Programming Fundamentals**.
The project avoids advanced libraries and frameworks and instead demonstrates strong command over **core C++ concepts** such as arrays, loops, conditions, functions, and file handling.

This project was created as part of the **Programming Fundamentals course** to simulate a real-world mini system using structured logic.

---

 Key Highlights

 Quiz Gameplay

* **Subjects Available**

  * Science
  * Computer
  * IQ

* **Difficulty Modes**

  * Easy
  * Medium
  * Hard

* Each quiz:

  * Loads **30 questions** from a text file
  * Randomly selects **10 questions** per attempt
  * Enforces a **10-second time limit** for each question
  * Accepts answers in **any letter case** (case-insensitive checking)

---
 Scoring Mechanism

*  Correct Answer: **+2 points**
*  Wrong Answer Penalties:

  * Easy → **−2 points**
  * Medium → **−3 points**
  * Hard → **−5 points**

---

 Streak Reward System

To encourage consistency:

* 🎯 **3 correct answers in a row** → **+5 bonus points**
* 🚀 **5 correct answers in a row** → **+15 bonus points**

Streaks reset automatically after any incorrect response.

---

 Lifeline System (One-Time Use per Quiz)

Players can strategically use the following lifelines:

* **50/50** → Eliminates two incorrect options
* **Time Boost** → Adds **10 extra seconds** to the timer
* **Skip** → Skips the current question without penalty
* **Swap** → Replaces the current question with a new random one

Each lifeline can be used **only once** in a quiz attempt.

---

 Answer Review Mode

At the end of the quiz, players can review:

* Only the **incorrectly answered questions**
* The **option selected by the player**
* The **correct answer**

This feature helps players learn from mistakes instead of just seeing a score.

---

 Leaderboard System

* Stores **player names and scores** in a file
* Automatically **updates scores** if a player plays again
* Displays the **Top 5 highest scores**
* Implemented using file handling (`leaderboard.txt`)

---

Quiz History Logs

Every quiz session is recorded in **quizlogs.txt**, including:

* Player name
* Selected subject
* Difficulty level
* Final score
* Question indexes asked
* Player’s answers
* Correct answers

This creates a full record of each attempt.

---

 Admin Panel (Work in Progress)

A password-protected admin mode is being developed, which will include:

* Resetting the leaderboard
* Viewing quiz attempt logs
* Managing question banks

---

 Folder Structure

```
LogicArena/
│
├── main.cpp
├── leaderboard.txt
├── quizlogs.txt
│
├── science_easy.txt
├── science_medium.txt
├── science_hard.txt
│
├── computer_easy.txt
├── computer_medium.txt
├── computer_hard.txt
│
├── iq_easy.txt
├── iq_medium.txt
└── iq_hard.txt
```

---

 Functional Breakdown (main.cpp)

* `menu()` → Displays the main menu
* `subject()` → Handles subject selection
* `difficulty()` → Handles difficulty selection
* `loadQuestions()` → Reads questions from files
* `displayQuestion()` → Core quiz logic (timer, scoring, lifelines)

  * `showLifelines()` → Displays available lifelines
  * `applySwap()` → Replaces current question
* `reviewWrong()` → Shows incorrect answers after quiz
* `saveScore()` → Saves/updates leaderboard scores
* `leaderboard()` → Sorts and displays top players
* `adminMode()` → Admin controls (WIP)
* `saveQuizLog()` → Stores quiz attempt details


