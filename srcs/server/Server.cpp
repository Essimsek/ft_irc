#include "../../inc/Server.hpp"
#include "../../inc/Commands.hpp"
#include "../../inc/Utils.hpp"

Server::Server() {
    this->num_clients = 0;
}

Server::~Server() {}

int Server::getServerFd() {
    return (this->serverFd);
}

void Server::setUpServer(int port, std::string pw) {
    this->password = pw;
    this->num_clients = 0;
    this->serverFd = socket(AF_INET, SOCK_STREAM, 0);
    (this->server_address).sin_family = AF_INET;
    (this->server_address).sin_port = htons(port);
    (this->server_address).sin_addr.s_addr = INADDR_ANY;
}

struct sockaddr_in Server::getServerAddress(){
    return (this->server_address);
}

void Server::getInformation()
{
    std::cout<<"Server Password   : "<< this->password<<" Password Length: "<<this->password.length()<< std::endl;
    std::cout<<"Server Hostname   : "<<this->hostname<<std::endl;
    std::cout<<"Server Fd         : "<<this->serverFd<<std::endl;
    std::cout<<"Server port       : "<<ntohs((this->server_address).sin_port)<<std::endl;
    std::cout<<"Server family     : "<<static_cast<int>((this->server_address).sin_family) << std::endl;
    std::cout<<"Server address    : "<<(this->server_address).sin_addr.s_addr<<std::endl;
}

int Server::checkPassword(std::string pw)
{
    pw = Utils::trimString(pw);
    return (pw.compare(this->password));
}
