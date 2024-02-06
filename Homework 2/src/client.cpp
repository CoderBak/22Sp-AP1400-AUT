#include "crypto.h"
#include "server.h"
#include "client.h"
#include <random>

Client::Client(std::string id, const Server&server)
    : server(&server), id(std::move(id)) {
    crypto::generate_key(this->public_key, this->private_key);
}

std::string Client::get_id() const { return id; }

std::string Client::get_publickey() const { return public_key; }

double Client::get_wallet() const {
    return const_cast<Server *>(server)->get_wallet(id);
}

std::string Client::sign(const std::string&txt) const {
    return crypto::signMessage(private_key, txt);
}

bool Client::transfer_money(const std::string&receiver, const double value) const {
    const std::string toSign = id + "-" + receiver + "-" + std::to_string(value);
    return server->add_pending_trx(toSign, sign(toSign));
}

size_t Client::generate_nonce() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution getter(0, 999999999);
    return getter(gen);
}
