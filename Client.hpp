/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:14:27 by huakbas           #+#    #+#             */
/*   Updated: 2025/10/06 14:41:38 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <errno.h>

#include "headers.hpp"

typedef struct epoll_event t_epoll_event;

class Client
{
	private:
		std::string		_nickname;
		int				_socketFd;
		t_epoll_event	*_event;
		int				_connected;
		// Channel[]	rooms
	public:
		Client();
		Client(std::string nick, int socketFd);
		~Client();
		std::string	getNickname() const;
		void	setNickname(std::string nick);
		int		getSocketFd() const;
		void	setSocketFd(int fd);
		struct epoll_event	*getEvent();
		void	setEvent(struct epoll_event *event);
		int		getConnected();
		void	setConnected(int status);
};

void	checkConnection(std::string input, Client &client);
