#include "crypto.h"
#include "server.h"
#include "client.h"
#include <random>
#include <regex>
#include <iostream>

std::vector<std::string> pending_trxs;

std::string newID(const std::string&id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution getter(0, 9);
    std::string str = id;
    for (int k = 0; k < 4; k += 1) {
        str += static_cast<char>(getter(gen) + '0');
    }
    return str;
}

Server::Server() = default;

std::shared_ptr<Client> Server::add_client(const std::string&id) {
    constexpr double startup = 5;
    std::string str = id;
    while (get_client(str) != nullptr) {
        str = newID(id);
    }
    auto result = std::make_shared<Client>(str, *this);
    clients.insert(make_pair(result, startup));
    return result;
}

std::shared_ptr<Client> Server::get_client(const std::string&id) const {
    for (auto [u, v]: clients) {
        if (u->get_id() == id) { return u; }
    }
    return nullptr;
}

double Server::get_wallet(const std::string&id) {
    for (auto [u, v]: clients) {
        if (u->get_id() == id) { return v; }
    }
    return 0;
}

bool Server::parse_trx(const std::string&trx, std::string&sender, std::string&receiver, double&value) {
    const std::regex pat(R"((\w+)-(\w+)-(\d+(\.\d+)?))");
    std::smatch matches;
    if (!std::regex_match(trx, matches, pat)) {
        throw std::runtime_error("Unable to parse.");
    }
    sender = matches[1];
    receiver = matches[2];
    value = std::stod(matches[3]);
    return true;
}

bool Server::add_pending_trx(const std::string&trx, const std::string&signature) const {
    std::string sender, receiver;
    double value;
    parse_trx(trx, sender, receiver, value);
    if (crypto::verifySignature(get_client(sender)->get_publickey(), trx, signature)) {
        if (get_client(sender) != nullptr && get_client(receiver) != nullptr) {
            if (const_cast<Server *>(this)->get_wallet(sender) > value) {
                pending_trxs.push_back(trx);
                return true;
            }
        }
    }
    return false;
}

size_t Server::mine() {
    std::string mempool{};
    for (const auto&trx: pending_trxs) {
        mempool += trx;
    }
    while (true) {
        for (auto&cur: clients) {
            const size_t rdnum = cur.first->generate_nonce();
            if (crypto::sha256(mempool + std::to_string(rdnum)).substr(0, 10).find("000") != std::string::npos) {
                cur.second += 6.25;
                for (const auto&trx: pending_trxs) {
                    std::string sender, receiver;
                    double value;
                    parse_trx(trx, sender, receiver, value);
                    clients[get_client(sender)] -= value;
                    clients[get_client(receiver)] += value;
                }
                pending_trxs.clear();
                return rdnum;
            }
        }
    }
}

void show_wallets(const Server&server) {
    std::cout << std::string(20, '*') << std::endl;
    for (const auto&client: server.clients)
        std::cout << client.first->get_id() << " : " << client.second << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}

void show_pending_transactions() {
    std::cout << std::string(20, '*') << std::endl;
    for (const auto&trx: pending_trxs)
        std::cout << trx << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}
