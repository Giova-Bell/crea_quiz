#include "main.h"

void add_question(std::string file)
{
	clear_cin();
	//input question
	Question q = Question();

	q.set_question(input_string("inserisci la domanda: "));
	q.set_right_answer(input_string("inserisci la risposta: "));
	
	std::cout << "\ninserisci '$' per terminare l'inserimento di risposte" << std::endl;

	std::string _in;
	do
	{
		_in = input_string(">");

		if(_in != "$" && _in != "\n")
			q.add_answer(_in);
	}
	while (_in != "$");

	q.serialize(file);
}