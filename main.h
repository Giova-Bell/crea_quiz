#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#if _WIN64 || _WIN32
#define CLEAR system("cls");
#else
#deifne CLEAR system("clear");
#endif

//utilities.cpp
void clear_cin();
void pause();
std::string input_string(std::string before_input = "");

class Question
{
private:
	int _id;
	int _wrong_answers = 0;
	std::string question = "";
	std::string right_answer = "";
	std::vector<std::string> answers;

public:
	Question();

	bool operator==(Question obj);

	void set_question(std::string question);
	void set_right_answer(std::string answer);
	void add_answer(std::string answer);
	void add_wrong_answer();

	std::string get_question();
	std::string get_right_answer();
	int get_wrong_answers();

	int print_answers();
	bool is_right(int answer);

	void serialize(std::string file);
	static std::string serialize_string(std::string str);
	static std::string deserialize_string(std::string str);
	static Question deserialize(std::string file, int& from_pos);
	static Question deserialize(std::string obj);
	static void delete_from_file(std::string file, Question obj);
};

class FileHandler
{
	friend Question Question::deserialize(std::string file, int& from_pos);
private:
	std::string _file;
	std::istream::pos_type _pos = 0;

public:
	FileHandler(std::string file_name);

	void append_to_file(std::string str);
	/*void operator<<(std::string str);*/
	void write_to_file(std::string str);

	std::string read_from_file();

	void set_pos(int pos);
	void set_start_file();

	int get_pos();
};

//utilitie.tpp
template<typename T>
T input(std::string before_input = "", std::string error = "\n")
{
	fflush(stdin);

	bool flag = false;
	T _user_input;

	do
	{
		if (flag)
		{
			clear_cin();
			std::cout << error << std::endl;
		}

		std::cout << before_input;
		std::cin >> _user_input;
		flag = true;
	} while (std::cin.fail());
	flag = false;

	return _user_input;
}

//add_question.cpp
void add_question(std::string file);

//answer_question.cpp
void answer_question(std::string file);

//see_ranking.cpp
void see_ranking(std::string file);