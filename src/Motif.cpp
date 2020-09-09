//
// Created by Ciaran on 09/09/2020.
//

#include "evo/Motif.h"

#include <utility>

namespace evo{

    Motif::Motif(std::string name, RateLaws rateLaws)
        : name_(std::move(name)), rate_laws_(std::move(rateLaws)){}
}