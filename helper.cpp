#include "Client.hpp"

void	checkConnection(std::string input, Client &client)
{
	size_t	nick = input.find("NICK");
	size_t	pass = input.find("PASS");

	std::string	nickname = input.substr(nick + 5, input.find('\r', nick) - nick - 5);
	std::string	password = input.substr(pass + 5, input.find('\r', pass) - pass - 5);

	std::cout << " name:" << nickname << "\npass:" << "\n";
	client.setNickname(nickname);
}
