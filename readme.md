# Budget Allocation Project

This project is a C program that allocates a given budget among multiple projects using a greedy algorithm. The program uses a graphical user interface (GUI) built with the Win32 API to allow users to input project details and display the results.

## Prerequisites

To run this project, you need to have the following installed on your Windows machine:

1. **MSYS2**: A software distribution and building platform for Windows.
2. **GCC**: The GNU Compiler Collection.
3. **Win32 API**: Included with Windows.

## Installation Instructions

### Step 1: Install MSYS2

1. Download the MSYS2 installer from the [MSYS2 website](https://www.msys2.org/).
2. Run the installer and follow the instructions to install MSYS2.
3. Open the MSYS2 MSYS terminal from the Start menu.
4. Update the package database and core system packages:
   ```sh
   pacman -Syu
   ```
5. Close the terminal and open the MSYS2 MinGW 64-bit terminal.
6. Update the package database and core system packages again:
   ```sh
   pacman -Syu
   ```

### Step 2: Install GCC

1. Open the MSYS2 MinGW 64-bit terminal.
2. Install GCC and other necessary tools:
   ```sh
   pacman -S mingw-w64-x86_64-toolchain
   ```

### Step 3: Install Libraries

1. Open the MSYS2 MinGW 64-bit terminal.
2. Install the necessary libraries:
   ```sh
   pacman -S mingw-w64-x86_64-gtk3 mingw-w64-x86_64-glib2 mingw-w64-x86_64-pango mingw-w64-x86_64-cairo mingw-w64-x86_64-gdk-pixbuf2 mingw-w64-x86_64-atk mingw-w64-x86_64-harfbuzz
   ```

### Step 4: Set Up Visual Studio Code

1. Download and install [Visual Studio Code](https://code.visualstudio.com/).
2. Install the C/C++ extension for Visual Studio Code.
3. Open your project folder in Visual Studio Code.
4. Create a `.vscode` folder in your project directory.
5. Create a `c_cpp_properties.json` file in the `.vscode` folder with the following content:
   ```json
   {
     "configurations": [
       {
         "name": "windows-gcc-x64",
         "includePath": [
           "${workspaceFolder}/**",
           "C:/msys64/mingw64/include/gtk-3.0",
           "C:/msys64/mingw64/include/glib-2.0",
           "C:/msys64/mingw64/lib/glib-2.0/include",
           "C:/msys64/mingw64/include/pango-1.0",
           "C:/msys64/mingw64/include/cairo",
           "C:/msys64/mingw64/include/gdk-pixbuf-2.0",
           "C:/msys64/mingw64/include/atk-1.0",
           "C:/msys64/mingw64/include/harfbuzz"
         ],
         "compilerPath": "C:/msys64/mingw64/bin/gcc.exe",
         "cStandard": "c11",
         "cppStandard": "c++17",
         "intelliSenseMode": "windows-gcc-x64",
         "compilerArgs": [
           ""
         ]
       }
     ],
     "version": 4
   }
   ```

### Step 5: Compile and Run the Project

1. Open the MSYS2 MinGW 64-bit terminal.
2. Navigate to your project directory:
   ```sh
   cd /c/Users/YourUsername/Path/To/Your/Project
   ```
3. Compile the project using GCC:
   ```sh
   gcc -o budget_allocation new.c -mwindows
   ```
4. Run the compiled executable:
   ```sh
   ./budget_allocation.exe
   ```

## Project Structure

- `new.c`: The main source code file containing the implementation of the budget allocation program with a Win32 GUI.
- `README.md`: This file, containing instructions for setting up and running the project.

## Usage

1. Run the `budget_allocation.exe` executable.
2. Enter the number of projects and the total budget.
3. Click "Set Projects" to create input fields for each project's cost and benefit.
4. Enter the cost and benefit for each project.
5. Click "Allocate Budget" to perform the budget allocation.
6. The selected projects and total benefit achieved will be displayed in the output area.

## License

This project is licensed under the MIT License.
