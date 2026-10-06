// Jared Aldana Palacios & Andrés Rodríguez Cantú
// A00844802 & A012870002

#pragma once

#include <string>

struct Client {
    std::string name;
    int tickets;

    Client() : name(""), tickets(0) {}
    Client(const std::string& n, int t) : name(n), tickets(t) {}
};
