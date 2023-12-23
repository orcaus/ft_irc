#include "./../headers/header.hpp"

void	topic_asked(t_server *serv, int i, std::string new_topic)
{
	std::string msg = "[server] Topic is : ";
	if (new_topic == " ")
		return;
	else if (new_topic == "\n")
	{
		for (int y = 0; y != NBR_CLIENTS - 1; y++)
		{
			if (serv->chan[y].name == serv->client[i].channel)
			{
				msg += serv->chan[y].topic;
				msg += "\n";
				break;
			}
			msg = "[server] Couldn't find the channel\n";
		}
		if ((send(serv->fds[i].fd, msg.c_str(), strlen(msg.c_str()), 0)) == -1)
		    std::cerr << "Error : send failed" << std::endl;
		return;
	}
	for (int y = 0; y != NBR_CLIENTS - 1; y++)
	{
		if (serv->chan[y].name == serv->client[i].channel)
		{
			if (serv->client[i].op == false)
			{
				if ((send(serv->fds[i].fd, "[server] Your not operator on this channel\n", sizeof("[server] Your not operator on this channel\n"), 0)) == -1)
					std::cerr << "Error : send failed" << std::endl;
				return;
			}
			serv->chan[y].topic = new_topic;
			break;
		}
	}
	msg = "[server] Couldn't find the channel\n";
	if ((send(serv->fds[i].fd, msg.c_str(), strlen(msg.c_str()), 0)) == -1)
		std::cerr << "Error : send failed" << std::endl;
	return;
}

std::string	get_new_topic(char *buff, t_server *serv, int i)
{
	char tmp[220] = {0}; tmp[0] = '\0';
    std::string top;
    int z = 0; int y = 0;
    while(buff[z] != '\0'&& buff[z] != ' ')
        z++;
    z++;
    while(buff[z] != '\0' && y < 200)
        tmp[y++] = buff[z++];
    if (y >= 200)
    {
        if ((send(serv->fds[i].fd, "Topic too long\n", sizeof("Topic too long\n"), 0)) == -1)
		    std::cerr << "Error : send failed" << std::endl;
        top = " ";
		return top;
    }
    if (tmp[0] != '\0')
        top = tmp;
    else
        top = "\n";
    return top;
}