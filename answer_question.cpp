#include "main.h"

void answer_question(std::string file)
{
	Question q;

	int _pos = 0;
	while(true)
	{
		CLEAR;
		q = Question::deserialize(file, (_pos));
		if (_pos == -1) break;

		std::cout << q.get_question() << "\n" << std::endl;

		int n_answers = q.print_answers();
		
		int _in;
		do
		{
			_in = input<int>(">");
		}
		while (_in < 0 || _in > n_answers);

		if (!q.is_right(_in-1))
		{
			_pos--;
			Question::delete_from_file(file, q);
			q.add_wrong_answer();
			q.serialize(file);
			std::cout <<"\n" << "Risposta sbagliata - Risposta giusta: " << q.get_right_answer() << std::endl;
			pause();
		}
		else
		{
			std::cout << "\nRisposta giusta!!!!!!!";
			pause();
		}
	}
}