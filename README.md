# Hub Labeling Algorithm

This repository contains the C++ implementation of the Pruned Landmark Labeling (Hub Labeling) algorithm for answering shortest-path queries efficiently.

## 1. Project Structure
* `/lib`: Contains the header-only core libraries.
  * `graph.hpp`: Defines the Graph data structure (Adjacency List).
  * `labeling.hpp`: Contains the `PrunedLabeling` class and the core Pruned Dijkstra algorithm logic.
* `main.cpp`: The driver code that handles user input, graph initialization, vertex ordering, and query execution.
* `app.exe`: The compiled executable file (ready to run on Windows).

---

## 2. How to Run the Program

You can run the program using either the pre-compiled `.exe` file or by compiling it yourself.

### Method A: Run the `.exe` file directly (Easiest for Windows)
If you are on a Windows machine, you do not need to compile the code.
1. Open the project folder in File Explorer.
2. **Double-click** on the `app.exe` file.
3. A black console window (Command Prompt) will appear.
4. Type your input directly into this window following the Input Format guide below.

### Method B: Run via Terminal / Command Prompt (Recommended)
Running via terminal allows you to easily feed data from a `.txt` file instead of typing manually.
1. Open your terminal (CMD, PowerShell, or VS Code Terminal) in the project folder.
2. Run the executable:
   * **Windows:** `.\app.exe`
   * **Linux/macOS:** `./app`
3. *(Optional)* To feed a data file directly into the program, use:
   `.\app.exe < data/sample.txt`

---

## 3. How to Compile (If you modify the code)
If you make changes to `main.cpp` or the `/lib` files, you need to recompile the project. 
Open your terminal in the root folder and run (requires GCC/g++):
```bash
g++ -O3 main.cpp -o app