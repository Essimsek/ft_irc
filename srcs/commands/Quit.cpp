#include "../../inc/irc.hpp"
#include "../../inc/Commands.hpp"
#include "../../inc/Channel.hpp"
#include "../../inc/Utils.hpp"

void Commands::runQuit(Server &sv, Client &cl) {
    for(std::vector<Channel>::iterator it = sv.chList.begin(); it < sv.chList.end(); it++) {
        it->removeClient(&cl);
    }
	for(std::vector<struct pollfd>::iterator it = sv.pollfds.begin(); it < sv.pollfds.end(); it++) {
        if (it->fd == cl.getClientFd())
			sv.pollfds.erase(it);
    }

	for(std::vector<Client>::iterator it = sv.clients.begin(); it < sv.clients.end(); it++) {
        if (it->getClientFd() == cl.getClientFd())
        {
            sv.clients.erase(it);
            break;
        }
	}
	sv.num_clients--;
    close(cl.getClientFd());
}
