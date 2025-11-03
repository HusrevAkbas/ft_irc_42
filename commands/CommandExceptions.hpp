#pragma once

#include <exception>
#include <string>

class UnknownCommandException : public std::exception
{
	private:
		std::string commandName;
		std::string message;

	public:
		UnknownCommandException(const std::string& cmd);
		UnknownCommandException(const UnknownCommandException& other);
		UnknownCommandException& operator=(const UnknownCommandException& other);
		virtual ~UnknownCommandException() throw();

		virtual const char* what() const throw();
		std::string getCommandName() const;
};

class MissingParametersException : public std::exception
{
	private:
		std::string commandName;
		std::string message;

	public:
		MissingParametersException(const std::string& cmd, const std::string& msg);
		MissingParametersException(const MissingParametersException& other);
		MissingParametersException& operator=(const MissingParametersException& other);
		virtual ~MissingParametersException() throw();

		virtual const char* what() const throw();
		std::string getCommandName() const;
};
