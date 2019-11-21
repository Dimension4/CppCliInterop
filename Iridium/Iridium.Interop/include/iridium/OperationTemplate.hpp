#pragma once

#include <string>
#include <vector>

struct ParameterInfo
{
    std::string name;
    std::string type;
};

struct OperationTemplate
{
    std::string name;
    std::vector<ParameterInfo> parameters;
    std::string returnType;

    friend bool operator==(OperationTemplate const& lhs, OperationTemplate const& rhs) noexcept
    {
        return lhs.name == rhs.name && lhs.parameters.size() == rhs.parameters.size();
    }
};