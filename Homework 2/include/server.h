#ifndef SERVER_H
#define SERVER_H
#include <map>

class Client;

class Server {
public:
    Server();
    std::shared_ptr<Client> add_client(const std::string&id);
    [[nodiscard]] std::shared_ptr<Client> get_client(const std::string&id) const;
    double get_wallet(const std::string&id);
    static bool parse_trx(const std::string&trx, std::string&sender, std::string&receiver, double& value);
    [[nodiscard]] bool add_pending_trx(const std::string&trx, const std::string&signature) const;
    size_t mine();
    friend void show_wallets(const Server&server);

private:
    std::map<std::shared_ptr<Client>, double> clients;
};

#endif //SERVER_H
