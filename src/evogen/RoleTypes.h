//
// Created by Ciaran on 08/09/2020.
//

#ifndef EVOGEN_ROLETYPES_H
#define EVOGEN_ROLETYPES_H

#include "rng_export.h"

namespace evo {
    enum RNG_EXPORT eRoleType {
        EVO_SUBSTRATE,
        EVO_PRODUCT,
        EVO_MODIFIER,
        EVO_PARAMETER,
        EVO_DEPENDENT_VARIABLE,
        EVO_INDEPENDENT_VARIABLE,
        };

    using RoleMap = std::unordered_map<std::string, eRoleType>;
}
#endif //EVOGEN_ROLETYPES_H
