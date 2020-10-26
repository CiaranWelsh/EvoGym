//
// Created by Ciaran on 08/09/2020.
//

#ifndef EVOGYM_ROLETYPES_H
#define EVOGYM_ROLETYPES_H

namespace evo {
    enum RoleType {
        EVO_SUBSTRATE,
        EVO_PRODUCT,
        EVO_PARAMETER,
        EVO_MODIFIER,
        EVO_DEPENDENT_VARIABLE,
        EVO_INDEPENDENT_VARIABLE,
    };

    using RoleMap = std::unordered_map<std::string, RoleType>;
}
#endif //EVOGYM_ROLETYPES_H
