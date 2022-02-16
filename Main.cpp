#include "main.h"

void stampa_menu()
{
	CLEAR;
	std::cout <<\
	"1) aggiungi una domanda\n"\
	"2) rispondi alle domande\n"\
	"3) vedi il ranking\n"\
	"4) esci\n";
	std::cout << std::endl;
}

int main()
{
	std::string file = "questions.txt";
	bool exit = false;

	while (!exit)
	{
		stampa_menu();
		int _in = input<int>("> ");

		switch (_in)
		{
		case 1:
			CLEAR;
			add_question(file);
			break;
		case 2:
			CLEAR;
			answer_question(file);
			break;
		case 3:
			CLEAR;
			see_ranking(file);
			break;
		case 4:
			exit = true;
			break;
		default:
			std::cout << "choose one of the options" << std::endl;
			break;
		}
	}

	return 0;
}
