#pragma once

#include <functional>
#include <map>

namespace Glue::Internal
{

#pragma managed(push, off)
    
    namespace Cache
    {
        template <typename TIndex, typename TReturn, typename ...TArgs>
        auto& getFunctionCache()
        {
            // heap allocation to avoid static destruction fiasco
            // may need a custom allocator for the superset of all std::functions to enable bulk allocations
            static auto cache = new std::map<TIndex, std::function<TReturn(TArgs...)>>();
            return *cache;
        }
    }

    template <typename TReturn, typename ...TArgs, typename TIndex>
    std::function<TReturn(TArgs...)>& getFunction(TIndex&& index)
    {
        auto& cache = Cache::getFunctionCache<TIndex, TReturn, TArgs...>();
        return cache[std::forward<TIndex>(index)];
    }

#pragma managed(pop)
   
}