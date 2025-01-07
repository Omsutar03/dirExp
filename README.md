# 📁 dirExp (Directory Explorer)  

dirExp is a terminal-based, cross-platform file explorer designed to enhance your productivity with a simple, intuitive interface. It works seamlessly on both Windows and Linux, making file management fast and efficient.  

---

## ✨ Features  
- **🌍 Cross-Platform:** Works on Windows and Linux.  
- **🖥️ Split Panes:** Efficiently navigate and manage files with multiple panes.  
- **⚡ Keyboard-Driven:** Fully keyboard-navigable for maximum speed.  

---

## 🛠️ Requirements  
- **Windows:**  
  - PDCurses library (already included in the repository).  
- **Linux:**  
  - ncurses library (commonly pre-installed).  

---

## 🚀 Installation  
### **Windows**  
1. Download the latest `.exe` installer from the [Releases](https://github.com/Omsutar03/dirExp/releases) page or [click here](https://github.com/Omsutar03/dirExp/releases/download/cross-platform/dirExp-1.0.0-win64.exe).  
2. Run the installer and follow the setup instructions.  
3. Add `dirExp` to your system PATH using this PowerShell script, save following script as `script.ps1`:  

    ```powershell
    # Save as script.ps1 and replace with the default installation path if needed
    $dirExpPath = "C:\Program Files\dirExp 1.0.0\bin"

    # Add dirExp to PATH
    [Environment]::SetEnvironmentVariable(
        "Path", 
        [Environment]::GetEnvironmentVariable("Path", [EnvironmentVariableTarget]::Machine) + ";$dirExpPath",
        [EnvironmentVariableTarget]::Machine
    )

    Write-Host "dirExp added to PATH successfully!"
    ```

4. Run the script with administrator privileges on Windows powershell:  
    ```powershell
    .\script.ps1
    ```

---

### **Linux**  
1. Download the `.tar.gz` file from the [Releases](https://github.com/Omsutar03/dirExp/releases) page or [click here](https://github.com/Omsutar03/dirExp/releases/download/cross-platform/dirExp-1.0.0-Linux.tar.gz).  
2. Extract and move the executable to a system directory:  
    ```bash
    tar -xvzf dirExp-1.0.0.tar.gz
    cd dirExp-1.0.0/bin
    sudo mv dirExp /usr/local/bin/
    ```
---

## 🔨 Build from Source  

### **Windows**  
1. Install MinGW and ensure it is added to your PATH.  
2. Clone the repository and build the project:  
    ```bash
    git clone https://github.com/Omsutar03/dirExp.git
    cd dirExp
    mkdir build
    cd build
    cmake .. -G "MinGW Makefiles"
    mingw32-make
    ```

### **Linux**  
1. Clone the repository and build the project:  
    ```bash
    git clone https://github.com/Omsutar03/dirExp.git
    cd dirExp
    mkdir build
    cd build
    cmake ..
    make
    sudo make install
    ```

---

## 📚 Usage  
- Open `cmd` on the preferable directory that you want, then type `dirExp` to start the application.
- **Navigate Directories:** Use arrow keys `↑` and `↓`.  
- **Open Files or Directories:** Press `ENTER`.  
- **Go Back:** Press `BACKSPACE`.  
- **Exit:** Press `q`, then `ENTER`.

    ![Example](/content/forREADME/dirExptrial.gif)

---

## 📝 License  
dirExp is licensed under the **GPL-3.0 License**. See [LICENSE](https://github.com/Omsutar03/dirExp?tab=GPL-3.0-1-ov-file) for details.  

---

## 🙏 Acknowledgments  
- **[PDCurses](https://github.com/wmcbrine/PDCurses):** For Windows terminal support.  
- **[ncurses](https://invisible-island.net/ncurses/):** For Linux terminal handling.  

---

## 📞 Contact  
- **Author:** Om Sutar  
- **Email:** omsutar03@gmail.com  
- **GitHub:** [Omsutar03](https://github.com/Omsutar03)  
- **LinkedIn:** [Om Sutar](https://www.linkedin.com/in/omsutar03)  

---

> 🚩 *Feel free to contribute, report issues, or suggest improvements on the [GitHub repository](https://github.com/Omsutar03/dirExp)!*  
