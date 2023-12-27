#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <signal.h>

#define NBR_CLIENTS 10

typedef struct s_channel {
	int here;
	int limit;
	bool invite;
	bool topic_perm;
	std::string name;
	std::string topic;
	std::string key;
}	t_channel;

typedef struct s_client {
	int id;
	bool taken;
	bool password;
	bool op;
	std::string in_wait;
	std::string channel;
	std::string nickname;
	std::string username;
	std::string full_msg;
}	t_client;

typedef struct s_server {
	int client_co;
	int id_gen;
	int server_socket;
	int client_socket;
	bool	skibidi_bot;
	std::string password;
	sockaddr_in server_addr;
	sockaddr_in client_addr;
	socklen_t client_addr_size;
	t_channel chan[NBR_CLIENTS];
	pollfd fds[NBR_CLIENTS];
	t_client client[NBR_CLIENTS + 1];
}	t_server;


// server config
int	server_configuration(t_server *serv, char *port, char *pwd);
int	server_socket_conf(t_server *serv);
int	server_addr_conf(t_server *serv, char *port);
int	server_fd_conf(t_server *serv);

// client config
void	full_setup_client(t_server *serv);
void	setup_client(t_server *serv);

// channel
void	setup_channel(t_server *serv, std::string name);
void	full_setup_channel(t_server *serv);
std::string get_channel_name(char *buff, t_server *serv, int i);
void    create_channel(t_server *serv, int i, std::string ch_name);
void    join(t_server *serv, int i, std::string chan_name);
// std::string get_channel_password(char *buff, t_server *serv, int i);
void	check_pass_chan(t_server *serv, int i, char *buff);
void	ok_to_join(t_server *serv, int i, char *buff);
void    change_count(t_server *serv, std::string old_name, std::string new_name);
void	limit(t_server *serv, int i, char *buff);
int getlimit(char *buff, t_server *serv, int i);
void	kick(t_server *serv, int i, std::string name);
void	change_pass(t_server *serv, int i, char *buff);
std::string	get_pwd(char *buff, t_server *serv, int i);

// poll loop
int poll_loop(t_server *serv);
int info_recv(t_server *serv);
int connection_ask(t_server *serv);
void    disconnect(t_server *serv, int i);
void	choose(t_server *serv, int i, char *buff);

// topic
void	topic_asked(t_server *serv, int i, std::string new_topic);
std::string	get_new_topic(char *buff, t_server *serv, int i);
void	topic_restriction(t_server *serv, int i);

// info check
int	check_password(t_server *serv, char *buff, int bytesread, int i);
int setusername(t_server *serv, int i, char *buff);


// aditional fonction
char	*ft_itoa(int n);
std::string find_username(char *buff, t_server *serv, int i);
std::string extract_msg(char *buff, t_server *serv, int i);

// nickname
std::string	extract_nick(char *buff, t_server *serv, int i);
void	change_nickname(t_server *serv, int i, std::string name);

// msg
void    send_msg(t_server *serv, int i, std::string msg, std::string name);
void    general_msg(t_server *serv, int i, char *buff);

// invite
void	change_invite(t_server *serv, int i);
void	invite(t_server *serv, int i, std::string name);

// op
void    give_op(t_server *serv, int i, std::string name);

// bot
void	skibidi_activ(t_server *serv);
void	skibidi_on(t_server *serv, int i);
