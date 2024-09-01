#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>

//Inistalises the functions to create a taks, to show a task and to tick a task
void createTask(std::string task);
void showTasks();
void tickTask(int num);
void deleteTask(int num);

int main()
{
	//The boolean that maintains the while loop
	bool finnished = false;
	std::cout << "********TODO APP********\n\n";
	std::cout << "Welcome to the Todo App";
	//pauses the program for 5 seconds
	Sleep(5000);

	//The while loop where the main logic runs
	while (!finnished) {
		//Outputs tasks
		showTasks();
		//A choice for the functions
		int choice;
		std::cout << "Choose 1 to create a task, 2 to change a task to completed, 3 to delete a task or 0 to end the program: ";
		std::cin >> choice;
		//Validates input to be a choice and skips if not
		if (std::cin.fail()) {
			std::cin.clear(); std::cin.ignore(512, '\n');
			std::cout << "Not a number";
			continue;
		}
		std::string option;
		int num;
		//Selects one of the functions
		switch (choice){
			case 1:
				std::cout << "What is the name of the task that you want to create? ";
				std::getline(std::cin >> std::ws, option);
				createTask(option);
				break;
			case 2:
				showTasks();
				std::cout << "Which task have you completed? ";
				std::cin >> num;
				if (std::cin.fail()) {
					std::cin.clear(); std::cin.ignore(512, '\n');
					std::cout << "Not a number";
					continue;
				}
				else {
					tickTask(num);
				}
				break;
			case 3:
				showTasks();
				std::cout << "Which task have you completed? ";
				std::cin >> num;
				if (std::cin.fail()) {
					std::cin.clear(); std::cin.ignore(512, '\n');
					std::cout << "Not a number";
					continue;
				}
				else {
					deleteTask(num);
				}
				break;
			//Ends the program
			case 0:
				finnished = true;
				break;
		default:
			std::cout << "Enter a valid option";
			break;
		}
	}
	std::cout << "***********************";
}

//Creates a task that is stored in a file so it is non volatile
void createTask(std::string task) {
	system("cls");
	std::ofstream MyFile;
	MyFile.open("tasks.txt", std::ios::app);
	MyFile << task << "0"<<'\n';
	MyFile.close();
	std::cout << "Task completed";
}

//Gets the tasks from a file to be outputted
void showTasks() {
	system("cls");
	std::fstream data;
	data.open("tasks.txt", std::ios::in);
	std::string line;
	int i = 1;
	while (std::getline(data, line)) {
		int lastValue = line.length() - 1;
		
		if (line.at(lastValue) == '0') {
			std::cout <<i<<". " << line.substr(0, lastValue) << "   not done" << "\n";
		}
		else if (line.at(lastValue) == '1') {
			std::cout << i << ". " << line.substr(0, lastValue) <<  "   done" << "\n";
		}
		i++;
	}
	data.close();
}

//Changes a tasks state to completed
void tickTask(int num) {
	system("cls");
	std::fstream data;
	std::fstream tempFile;
	data.open("tasks.txt", std::ios::in);
	tempFile.open("temp.txt", std::ios::app);
	std::string line;
	int i = 1;
	bool changed = false;
	std::string temp;
	while (std::getline(data, line)) {
		int lastValue = line.length() - 1;
		if (i == num) {
			tempFile << line.substr(0, lastValue) + "1" + "\n";
			std::cout<< line.substr(0, lastValue) + "1" + "\n"; 
			changed = true;
		}
		else {
			tempFile << line.substr(0, lastValue) << "0" << "\n";
		}
		i++;
	}
	data.close();
	tempFile.close();
	if (!changed) {
		std::cout << "Enter a valid option\nPress enter to continue\n\n";
		Sleep(5000);
	}
	else {
		rename("tasks.txt", "x.txt");
		rename("temp.txt", "tasks.txt");
		Sleep(5000);
	}
	std::remove("x.txt");
	std::remove("temp.txt");
}

//Deletes a task from a file
void deleteTask(int num) {
	system("cls");
	std::fstream data;
	std::fstream tempFile;
	data.open("tasks.txt", std::ios::in);
	tempFile.open("temp.txt", std::ios::app);
	std::string line;
	int i = 1;
	bool changed = false;
	std::string temp;
	while (std::getline(data, line)) {
		int lastValue = line.length() - 1;
		if (i == num) {
			changed = true;
		}
		else {
			tempFile << line<<'\n';
		}
		i++;
	}
	data.close();
	tempFile.close();
	if (!changed) {
		std::cout << "Enter a valid option\nPress enter to continue\n\n";
		Sleep(5000);
	}
	else {
		rename("tasks.txt", "x.txt");
		rename("temp.txt", "tasks.txt");
	}
	std::remove("x.txt");
	std::remove("temp.txt");
}