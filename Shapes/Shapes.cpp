#include "ShapesController.h"
#include <iostream>

int main()
{
	ShapesController controller(std::cout);
	controller.ShowHelp();

	std::string commandLine;
	HandlingResult handlingResult{ HandlingResult::Success };

	while (handlingResult != HandlingResult::Exit)
	{
		std::cout << "> ";
		std::getline(std::cin, commandLine);
		handlingResult = controller.HandleCommand(commandLine);

		if (handlingResult == HandlingResult::UnknownCommand)
		{
			std::cout << "Unknown command" << std::endl;
			std::cin.clear();
		}
	}
}