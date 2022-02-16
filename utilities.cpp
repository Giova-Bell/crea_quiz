#include "main.h"

void clear_cin()
{
	std::cin.clear();
	std::cin.ignore(80, '\n');
}

void pause()
{
	clear_cin();
	do
	{
		std::cout << '\n' << "Press the Enter key to continue.";
	} while (std::cin.get() != '\n');
}

std::string input_string(std::string before_input)
{
	std::string _in;

	std::cout << before_input;
	getline(std::cin, _in);

	return _in;
}

////////////////////////////////////////////////////
// CLASS
////////////////////////////////////////////////////
void FileHandler::append_to_file(std::string str)
{
	std::ofstream f(this->_file, std::ios_base::app);
	f << str;
	f.close();
}

//void FileHandler::operator<<(std::string str)
//{
//	this->append_to_file(str);
//}

void FileHandler::write_to_file(std::string str)
{
	std::ofstream f(this->_file);
	f << str;
	f.close();
}

std::string FileHandler::read_from_file()
{
	std::string out = "";

	std::ifstream f(this->_file);
	f.seekg(this->_pos);

	if (!f.eof())
	{
		getline(f, out);
		this->_pos = f.tellg();
	}

	return out;
}

FileHandler::FileHandler(std::string file_name) { this->_file = file_name; }
void FileHandler::set_pos(int pos) { this->_pos = pos; }
void FileHandler::set_start_file() { this->_pos = 0; }
int FileHandler::get_pos() { return this->_pos; }

Question::Question()
{
	FileHandler f("id.txt");
	
	int id = std::stoi(f.read_from_file());
	this->_id = ++id;

	f.write_to_file(std::to_string(this->_id));
}

bool Question::operator==(Question obj)
{
	if (this->question == obj.question) return true;
	return false;
}

int  Question::print_answers()
{
	for (int i = 0; i < this->answers.size(); i++)
	{
		std::cout << i+1 << ") " << this->answers[i] << "\n";
	}
	std::cout << std::endl;

	return this->answers.size();
}

bool Question::is_right(int answer)
{
	if (this->answers[answer] == this->right_answer) return true;
	return false;
}

void Question::serialize(std::string file)
{
	FileHandler f(file);
	std::string delimiter = "§";

	std::string write = (std::to_string(this->_id) + delimiter + Question::serialize_string(this->question) + delimiter + Question::serialize_string(this->right_answer) + delimiter + "[" );
	for (std::string str : this->answers) { write += (Question::serialize_string(str) + delimiter); }
	write += ("]" + delimiter + std::to_string(this->_wrong_answers) + "\n");

	/*std::string write = ("{\n" + std::to_string(this->_id) + "\n" + this->question + "\n" + this->right_answer + "\n");
	for (std::string str : this->answers) { write += (str + ";"); }
	write += ("\n" + std::to_string(this->_wrong_answers) + "\n");*/

	f.append_to_file(write);
}

Question Question::deserialize(std::string file, int& from_pos)
{
	Question q;
	FileHandler f(file);
	
	for (int i = 0; i < from_pos; i++) f.read_from_file(); //goes to n line

	std::string delimiter = "§";

	std::string obj = f.read_from_file();
	if (obj == "")
	{
		from_pos = -1;
		return q;
	}

	q._id = std::stoi(obj.substr(0, obj.find(delimiter)));
	obj.erase(0, obj.find(delimiter) + delimiter.size());
	
	q.question = Question::deserialize_string(obj.substr(0, obj.find(delimiter)));
	obj.erase(0, obj.find(delimiter) + delimiter.size());

	q.right_answer = Question::deserialize_string(obj.substr(0, obj.find(delimiter)));
	obj.erase(0, obj.find(delimiter) + delimiter.size());

	std::string answers = obj.substr(0, obj.find(("]" + delimiter)));
	answers.erase(0, 1);
	while (answers != "")
	{
		q.add_answer(Question::deserialize_string(answers.substr(0, answers.find(delimiter))));
		answers.erase(0, answers.find(delimiter) + delimiter.size());
	}
	obj.erase(0, obj.find(("]" + delimiter)) + 2);

	q._wrong_answers = std::stoi(obj.substr(0, obj.find(delimiter)));

	/*if (f.read_from_file() == "{")
	{
		q._id = std::stoi(f.read_from_file());
		q.question = f.read_from_file();
		q.right_answer = f.read_from_file();

		std::string answer = f.read_from_file();
		while ((answer) != "")
		{
			q.add_answer(answer.substr(0, answer.find(";")));
			answer.erase(0, answer.find(";") + 1);
		}
		q._wrong_answers = std::stoi(f.read_from_file());
	}*/

	from_pos++;

	return q;
}

Question Question::deserialize(std::string obj)
{
	Question q;
	std::string delimiter = "§";

	q._id = std::stoi(obj.substr(0, obj.find(delimiter)));
	obj.erase(0, obj.find(delimiter) + delimiter.size());

	q.question = Question::deserialize_string(obj.substr(0, obj.find(delimiter)));
	obj.erase(0, obj.find(delimiter) + delimiter.size());

	q.right_answer = Question::deserialize_string(obj.substr(0, obj.find(delimiter)));
	obj.erase(0, obj.find(delimiter) + delimiter.size());

	std::string answers = obj.substr(0, obj.find(("]" + delimiter)));
	answers.erase(0, 1);
	while (answers != "")
	{
		q.add_answer(Question::deserialize_string(answers.substr(0, answers.find(delimiter))));
		answers.erase(0, answers.find(delimiter) + delimiter.size());
	}
	obj.erase(0, obj.find(("]" + delimiter)) + 2);

	q._wrong_answers = std::stoi(obj.substr(0, obj.find(delimiter)));

	return q;
}

void Question::delete_from_file(std::string file, Question obj)
{
	std::ifstream in(file);
	std::ofstream out("tmp");

	std::string str;

	while (getline(in, str))
	{
		if (!(Question::deserialize(str) == obj)) out << (str + "\n");
	}

	in.close();
	out.close();

	remove(file.c_str());
	rename("tmp", file.c_str());
}

std::string Question::serialize_string(std::string str) { return ("\"" + str + "\""); }
std::string Question::deserialize_string(std::string str) { return str.substr(0, str.size() - 1).erase(0, 1); }
void Question::set_question(std::string question) { this->question = question; }
void Question::set_right_answer(std::string answer) { this->right_answer = answer; }
void Question::add_answer(std::string answer) { this->answers.push_back(answer); }
void Question::add_wrong_answer() { this->_wrong_answers++; }
std::string Question::get_question() { return this->question; }
std::string Question::get_right_answer() { return this->right_answer; }
int Question::get_wrong_answers() { return this->_wrong_answers; }