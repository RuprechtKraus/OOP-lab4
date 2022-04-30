#include "ShapesController.h"
#include <iostream>

int main()
{
	ShapesController controller(std::cin, std::cout);
	controller.ShowHelp();

	HandlingResult handlingResult{ HandlingResult::Success };

	while (handlingResult != HandlingResult::Exit)
	{
		std::cout << "> ";
		handlingResult = controller.HandleCommand();

		if (handlingResult == HandlingResult::UnknownCommand)
		{
			std::cout << "Unknown command" << std::endl;
			std::cin.clear();
		}
	}
}