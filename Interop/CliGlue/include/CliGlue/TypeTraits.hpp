#pragma once

#include <functional>

#pragma managed(push, off)

namespace Glue 
{	
	namespace Internal::Trait
	{
		template <typename TSignature>
		TSignature signatureType(std::function<TSignature> func);
	}

	template <typename Function>
	using SignatureType = decltype(Internal::Trait::signatureType(std::declval<Function>()));

}

#pragma managed(pop)