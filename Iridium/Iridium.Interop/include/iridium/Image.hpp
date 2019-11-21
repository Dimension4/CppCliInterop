#pragma once

#include <vector>
#include <cstdint>

struct Image
{
    int width = 0;
    int height = 0;
    std::vector<std::uint8_t> data;
};