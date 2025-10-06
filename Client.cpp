/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:17:28 by huakbas           #+#    #+#             */
/*   Updated: 2025/10/06 12:07:50 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : _socketFd(-1) {}

Client::Client(std::string nick, int fd) : _nickname(nick), _socketFd(fd) {}

Client::~Client() {}

std::string	Client::getNickname() const
{	return (this->_nickname);	}

int	Client::getSocketFd() const
{	return (this->_socketFd);	}

void	Client::setSocketFd(int fd)
{	this->_socketFd = fd;	}

void	Client::setNickname(std::string nick)
{	this->_nickname = nick;	}

struct epoll_event	*Client::getEvent()
{	return (this->_event);	}

void	Client::setEvent(struct epoll_event *event)
{	this->_event = event;	}

int	Client::getConnected()
{	return (this->_connected);	}

void	Client::setConnected(int status)
{	this->_connected = status;	}
