# Hub Labeling Algorithm

This repository contains the C++ implementation of the Pruned Landmark Labeling (Hub Labeling) algorithm for answering shortest-path queries efficiently.

## 1. Project Structure
* `/lib`: Contains the header-only core libraries (`graph.hpp` and `labeling.hpp`).
* `main.cpp`: The driver code that handles user input, graph initialization, and query execution.
* `app.exe`: The compiled executable file (ready to run on Windows).
* `/data`: Contains sample graphs (e.g., `sample.txt`) for testing.

---

## 2. How to Run the Program

You can run this project in several ways depending on your needs. 

### Option A: Run directly via Executable (Easiest for Windows)
If you just want to test the program by typing inputs manually:
1. Open the project folder in File Explorer.
2. **Double-click** on the `app.exe` file.
3. A black console window will open. Type your input step-by-step following the **Input Format Guide** below.

### Option B: Run with the provided Sample File (Recommended)
To automatically feed the 10-vertex sample graph into the program without typing:
1. Open your Terminal (or VS Code Terminal) in the project folder.
2. Run the appropriate command based on your terminal type:
   * **Command Prompt (CMD) / Linux / macOS:**
     `.\app.exe < data\sample.txt`  *(Use `./app < data/sample.txt` for Linux/Mac)*
   * **Windows PowerShell:**
     `cat data\sample.txt | .\app.exe`

### Option C: Run with your Custom Data
1. Create a text file (e.g., `my_test.txt`) inside the `/data` folder.
2. Write your graph data following the **Input Format Guide**. Make sure to end the file with `-1 -1`.
3. Run it using the terminal:
   * **CMD:** `.\app.exe < data\my_test.txt`
   * **PowerShell:** `cat data\my_test.txt | .\app.exe`

---

## 3. How to Compile (If you modify the source code)
If you edit `main.cpp` or any `.hpp` files in the `/lib` folder, you must recompile the `.exe` file before running it again.
1. Open your terminal in the root folder.
2. Run the GNU C++ Compiler command with O3 optimization:
   ```bash
   g++ -O3 main.cpp -o app