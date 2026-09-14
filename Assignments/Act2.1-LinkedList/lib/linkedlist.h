#pragma once
#include <memory>
#include <utility>

template <typename T>
struct Node {
    T data;
    std::unique_ptr<Node> next;

    explicit Node(T val, std::unique_ptr<Node> nextNode = nullptr)
        : data(std::move(val)), next(std::move(nextNode)) {}
};