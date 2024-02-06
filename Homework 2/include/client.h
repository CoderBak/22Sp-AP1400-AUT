#ifndef CLIENT_H
#define CLIENT_H
#include <string>

class Server;

class Client {
public:
    Client(std::string id, const Server&server);
    [[nodiscard]] std::string get_id() const;
    [[nodiscard]] std::string get_publickey() const;
    [[nodiscard]] double get_wallet() const;
    [[nodiscard]] std::string sign(const std::string& txt) const;
    [[nodiscard]] bool transfer_money(const std::string& receiver, double value) const;
    size_t generate_nonce() const;

private:
    Server const* const server;
    const std::string id;
    std::string public_key;
    std::string private_key;
};

#endif //CLIENT_H
