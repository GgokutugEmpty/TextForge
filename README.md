# 🛠️ **TextForge** 📝

TextForge is a powerful and lightweight text editor designed for developers! It features a hexadecimal editor and a customizable interface to support color schemes, making it easy to work with files in different formats.

✨ **Features**:
- 🖥️ Hexadecimal editor for inspecting binary files.
- 🌈 Customizable color schemes for syntax highlighting.
- 🔄 Load and save files with ease.
- 📝 Edit files with navigation support.

---

## 🧑‍💻 **Getting Started**

To get started with **TextForge**, you'll need to clone the repository and build the project.

### 🛠️ **Prerequisites**:
Make sure you have the following installed:
- `gcc` (GNU Compiler Collection) 📦
- `ncurses` (for terminal-based UI) 🌟

### 🚀 **Installation Instructions**:

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/GgokutugEmpty/TextForge.git
    cd TextForge
    ```

2. **Build the Project**:
    - To build the project, simply run:
    ```bash
    make
    ```

    This will create the `TextForge` executable.

3. **Run the Application**:
    - You can run the program like this:
    ```bash
    ./TextForge <filename>
    ```

    If you want to open the file with the hexadecimal editor, use the `-h` flag:
    ```bash
    ./TextForge <filename> -h
    ```

4. **Install the Program** (optional):
    - To install the program to your system:
    ```bash
    sudo make install
    ```

5. **Check the Version**:
    - To check the version of **TextForge**:
    ```bash
    make ver
    ```

---

## 🔧 **Development**:
You can contribute to **TextForge** by forking the repository, making changes, and submitting a pull request. Feel free to report bugs or suggest new features!

### 🧑‍💻 **Code Structure**:
- `main.c`: Entry point for the program.
- `write.c`: Contains logic for saving files.
- `loadconfig.c`: Handles loading configuration settings (coloring, etc.).
- `fhexedit.c`: Hexadecimal editing functionality.

---

## 📝 **License**:
This project is licensed under the GNU-GPLV3 License - see the [LICENSE](LICENSE) file for details.

---

### 👀 **Have fun editing with TextForge!** 💻✨

