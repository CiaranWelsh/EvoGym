//
// Created by Ciaran on 09/09/2020.
//

#ifndef EVOGYM_MOTIF_H
#define EVOGYM_MOTIF_H

#include <iostream>

#include "EvoRateLaw.h"

namespace evo{

    /**
     * A Motif is a collection of evo::RateLaw objects
     */
    class EVOGYM_EXPORT Motif {
        std::string name_;
        RateLaws rate_laws_;

    public:

        /**
         * @brief construct a Motif
         * @param name: Name this motif
         * @param rateLaws: a RateLaws object containing the collection
         * of rate laws that make up a network motif
         */
        Motif(std::string name, RateLaws rateLaws);

    };

    typedef std::vector<Motif> Motifs;

}


#endif //EVOGYM_MOTIF_H
