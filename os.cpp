#include <iostream>
#include <string>
#include <vector>
#include <windows.h> // Для опроса клавиш GetAsyncKeyState

// Функция для отрисовки текстового интерфейса "Рабочего стола"
void drawDesktop(const std::string& currentApp) {
    // Очищаем экран консоли и переносим курсор в верхний левый угол
    std::cout << "\x1B[2J\x1B[H";

    // Ваше точное текстовое меню:
    std::cout << "================================================================================\n";
    std::cout << "||                      CUSTOM TEXT OS SIMULATOR v1.0                         ||\n";
    std::cout << "================================================================================\n";
    std::cout << "|| [1] Open Text Editor    [2] Open Calculator    [3] System Info   [4] Exit  ||\n";
    std::cout << "================================================================================\n\n";

    std::cout << " Active Window: [ " << currentApp << " ]\n";
    std::cout << "--------------------------------------------------------------------------------\n\n";
}

// Функция быстрой проверки горячих клавиш Ctrl + R
bool checkRebootHotkey() {
    if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('R') & 0x8000)) {
        return true;
    }
    return false;
}

int main() {
    std::string currentWindow = "Desktop";
    std::vector<std::string> notes; // Временная память для заметок блокнота
    int choice = 0;

    std::cin.sync_with_stdio(false);

    while (true) {
        // Мгновенный тихий сброс системы при фиксации Ctrl + R (без мерцания)
        if (checkRebootHotkey()) {
            currentWindow = "Desktop";
            notes.clear();
            drawDesktop(currentWindow);
        }

        drawDesktop(currentWindow);

        if (currentWindow == "Desktop") {
            std::cout << " Choose an option (1-4): ";

            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            if (choice == 1) currentWindow = "Text Editor";
            else if (choice == 2) currentWindow = "Calculator";
            else if (choice == 3) currentWindow = "System Info";
            else if (choice == 4) {
                std::cout << "\n Shutting down Text OS... Goodbye!\n";
                break;
            }
        }
        else if (currentWindow == "Text Editor") {
            std::cout << " Your Notes:\n";
            if (notes.empty()) std::cout << "  (No notes saved yet)\n";
            for (const auto& note : notes) {
                std::cout << "  - " << note << "\n";
            }
            std::cout << "\n [1] Add Note   [2] Clear All   [3] Back to Desktop\n\n Choose: ";
            std::cin >> choice;

            if (choice == 1) {
                std::cout << " Enter text: ";
                std::cin.ignore();
                std::string temp;
                std::getline(std::cin, temp);
                notes.push_back(temp);
            }
            else if (choice == 2) {
                notes.clear();
            }
            else if (choice == 3) {
                currentWindow = "Desktop";
            }
        }
        else if (currentWindow == "Calculator") {
            double a, b;
            char op;
            std::cout << " Enter simple math (Example: 5 + 3): ";
            if (std::cin >> a >> op >> b) {
                std::cout << " Result: ";
                if (op == '+') std::cout << a + b;
                else if (op == '-') std::cout << a - b;
                else if (op == '*') std::cout << a * b;
                else if (op == '/') {
                    if (b != 0) std::cout << a / b;
                    else std::cout << "Error (Division by Zero)";
                }
                std::cout << "\n";
            }
            else {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << " Invalid input!\n";
            }
            std::cout << "\n [1] Try Again   [2] Back to Desktop\n\n Choose: ";
            std::cin >> choice;
            if (choice == 2) currentWindow = "Desktop";
        }
        else if (currentWindow == "System Info") {
            std::cout << " OS Name: Pure C++ Text-Based Operating System\n";
            std::cout << " Kernel: Standard C++17 Runtime\n";
            std::cout << " Hotkeys: [Ctrl + R] Silent Reboot\n";
            std::cout << " Status: Running Smoothly\n\n";
            std::cout << " [1] Back to Desktop\n\n Choose: ";
            std::cin >> choice;
            if (choice == 1) currentWindow = "Desktop";
        }
    }
    return 0;
}
