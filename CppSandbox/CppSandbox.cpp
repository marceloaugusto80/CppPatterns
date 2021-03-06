#include <iostream>
#include <limits>
#include "ObserverPat.h"
#include "MethodTemplatePat.h"
#include "StrategyPat.h"



typedef void (*Snippet)();



int main()
{

	Snippet snippets[] = {
		MethodTemplate::MethodTemplateSnippet,
		Strategy::StrategySnippet,
		Observer::ObserverSnippet
	};


	while (true)
	{
		std::system("cls");

		// evaluating snippets

		for (auto snippet : snippets)
		{
			std::cout << "\n\n------------------------------------\n\n";
			snippet();
		}

		// end evaluating snippets

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();
	}

    return 0;

}

