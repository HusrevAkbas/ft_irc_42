#include "CommandExceptions.hpp"

UnknownCommandException::UnknownCommandException(const std::string& cmd)
	: commandName(cmd), message("Unknown command: " + cmd) {}

UnknownCommandException::UnknownCommandException(const UnknownCommandException& other)
	: commandName(other.commandName), message(other.message) {}

UnknownCommandException& UnknownCommandException::operator=(const UnknownCommandException& other)
{
	if (this != &other)
	{
		commandName = other.commandName;
		message = other.message;
	}
	return *this;
}

UnknownCommandException::~UnknownCommandException() throw() {}

const char* UnknownCommandException::what() const throw()
{
	return message.c_str();
}

std::string UnknownCommandException::getCommandName() const
{
	return commandName;
}

MissingParametersException::MissingParametersException(const std::string& cmd, const std::string& msg)
	: commandName(cmd), message(msg) {}

MissingParametersException::MissingParametersException(const MissingParametersException& other)
	: commandName(other.commandName), message(other.message) {}

MissingParametersException& MissingParametersException::operator=(const MissingParametersException& other)
{
	if (this != &other)
	{
		commandName = other.commandName;
		message = other.message;
	}
	return *this;
}

MissingParametersException::~MissingParametersException() throw() {}

const char* MissingParametersException::what() const throw()
{
	return message.c_str();
}

std::string MissingParametersException::getCommandName() const
{
	return commandName;
}
