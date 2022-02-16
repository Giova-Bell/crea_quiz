#include "main.h"

void shell_sort(std::vector<Question>& arr, int size)
{
	for (int gap = size / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < size; i += 1)
		{
			Question temp = arr[i];

			int j;
			for (j = i; j >= gap && arr[j - gap].get_wrong_answers() < temp.get_wrong_answers(); j -= gap)
				arr[j] = arr[j - gap];

			arr[j] = temp;
		}
	}
}

void see_ranking(std::string file)
{
	FileHandler f(file);

	std::vector<Question> list;

	std::string obj;
	while ((obj = f.read_from_file()) != "")
	{
		list.push_back(Question::deserialize(obj));
	}

	shell_sort(list, list.size());

	for (int i = 0; i < list.size(); i++)
	{
		if (i == 0)
		{
			std::cout << "Primo Posto:\n\n1) " << list[i].get_question() << "\n\n------------------------------\n\n";
		}
		else
		{
			std::cout << i << ") " << list[i].get_question() << "\n";
		}
	}
	std::cout << std::endl;
	pause();
}