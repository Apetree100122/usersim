// Copyright (c) Microsoft Corporation
// SPDX-License-Identifier: MIT
#pragma once

#include "platform.h"

#include <mutex>
#include <unordered_map>
#include <vector>

typedef class _usersim_leak_detector
{
  public:
    _usersim_leak_detector() = default;
    ~_usersim_leak_detector() = default;

    void
    register_allocation(uintptr_t address, size_t size);

    void
    unregister_allocation(uintptr_t address);

    void
    dump_leaks();

  private:
    typedef struct _allocation
    {
        uintptr_t address;
        size_t size;
        unsigned long stack_hash;
    } allocation_t;

    std::unordered_map<unsigned long, std::vector<uintptr_t>> _stack_hashes;
    std::unordered_map<uintptr_t, allocation_t> _allocations;
    std::mutex _mutex;
    const size_t _stack_depth = 32;
    std::vector<std::string> _in_memory_log;
} usersim_leak_detector_t;

typedef std::unique_ptr<usersim_leak_detector_t> usersim_leak_detector_ptr;
