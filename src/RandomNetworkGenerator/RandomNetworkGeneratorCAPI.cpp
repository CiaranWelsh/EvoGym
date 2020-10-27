//
// Created by Ciaran Welsh on 26/10/2020.
//

#include "RandomNetworkGenerator.h"
#include "RNGOptions.h"
#include "evoRateLaw.h"
#include "RoleTypes.h"
#include "StoicCounter.h"
#include "random_network_generator_c_api_export.h"

using namespace evo;

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
* Misc functions
*/

/**
 * @brief free a dynamically allocated char*
 */
int free_c_char_star(char *c);

/************************************************************************
 * Role Map
 */

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RoleMap *RoleMap_new();

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RoleMap *RoleMap_insert(RoleMap *role_map_ptr, const char *variable_name, int role_id);


/************************************************************************
 * RateLaw
 */

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
evoRateLaw *evoRateLaw_new(evoRateLaw *evo_rate_law_ptr, const char *name, const char *rate_law_string, RoleMap *roles);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
void evoRateLaw_delete(evoRateLaw *evo_rate_law_ptr);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
char *evoRateLaw_getRateLawElement(evoRateLaw *evo_rate_law_ptr, int index);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int evoRateLaw_getNumRateLawElements(evoRateLaw *evo_rate_law_ptr);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int evoRateLaw_numParameters(evoRateLaw *evo_rate_law_ptr);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int evoRateLaw_numSubstrates(evoRateLaw *evo_rate_law_ptr);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int evoRateLaw_numModifiers(evoRateLaw *evo_rate_law_ptr);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int evoRateLaw_numProducts(evoRateLaw *evo_rate_law_ptr);

/************************************************************************
 * RateLaws
 */

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RateLaws *RateLaws_new();

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
void RateLaws_delete();

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RateLaws *massActionRateLaws();

/************************************************************************
 * RandomNetworkGeneratorOptions
 */

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_new(
        evoRateLaw *);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
void RandomNetworkGeneratorOptions_delete();

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
char *RandomNetworkGeneratorOptions_getCoreSbml(
        RNGOptions *random_network_generator_options_ptr
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int RandomNetworkGeneratorOptions_setCoreSbml(
        RNGOptions *random_network_generator_options_ptr, const char *core_sbml
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
unsigned long long RandomNetworkGeneratorOptions_getSeed(
        RNGOptions *random_network_generator_options_ptr
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_setSeed(
        RNGOptions *random_network_generator_options_ptr, unsigned long long seed
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int RandomNetworkGeneratorOptions_getBoundarySpeciesLowerBound(
        RNGOptions *random_network_generator_options_ptr
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_setBoundarySpeciesLowerBound(
        RNGOptions *random_network_generator_options_ptr, int lower_bound
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int RandomNetworkGeneratorOptions_getBoundarySpeciesUpperBound(
        RNGOptions *random_network_generator_options_ptr, int upper_bound
);
RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_setBoundarySpeciesUpperBound(
        RNGOptions *random_network_generator_options_ptr, int upper_bound
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int RandomNetworkGeneratorOptions_getNFloatingSpecies(
        RNGOptions *random_network_generator_options_ptr
);
RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_setNFloatingSpecies(
        RNGOptions *random_network_generator_options_ptr, int n
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int RandomNetworkGeneratorOptions_getNBoundarySpecies(
        RNGOptions *random_network_generator_options_ptr
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_setNBoundarySpecies(
        RNGOptions *random_network_generator_options_ptr, int n
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int RandomNetworkGeneratorOptions_getNReactions(
        RNGOptions *random_network_generator_options_ptr
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_setNReactions(
        RNGOptions *random_network_generator_options_ptr, int n
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int RandomNetworkGeneratorOptions_getNCompartments(
        RNGOptions *random_network_generator_options_ptr
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_setNCompartments(
        RNGOptions *random_network_generator_options_ptr, int n
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int RandomNetworkGeneratorOptions_getSpeciesLowerBound(
        RNGOptions *random_network_generator_options_ptr
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_setFloatingSpeciesLowerBound(
        RNGOptions *random_network_generator_options_ptr, double n
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int RandomNetworkGeneratorOptions_getSpeciesUpperBound(
        RNGOptions *random_network_generator_options_ptr
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_setFloatingSpeciesUpperBound(
        RNGOptions *random_network_generator_options_ptr, double n
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int RandomNetworkGeneratorOptions_getParameterLowerBound(
        RNGOptions *random_network_generator_options_ptr
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_setParameterLowerBound(
        RNGOptions *random_network_generator_options_ptr, double n
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int RandomNetworkGeneratorOptions_getParameterUpperBound(
        RNGOptions *random_network_generator_options_ptr
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_setParameterUpperBound(
        RNGOptions *random_network_generator_options_ptr, double n
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int RandomNetworkGeneratorOptions_getCompartmentLowerBound(
        RNGOptions *random_network_generator_options_ptr
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_setCompartmentLowerBound(
        RNGOptions *random_network_generator_options_ptr, double n
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
int RandomNetworkGeneratorOptions_getCompartmentUpperBound(
        RNGOptions *random_network_generator_options_ptr);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_setCompartmentUpperBound(
        RNGOptions *random_network_generator_options_ptr, double n
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RateLaws *RandomNetworkGeneratorOptions_getRateLaws(
        RNGOptions *random_network_generator_options_ptr
);

RANDOM_NETWORK_GENERATOR_C_API_EXPORT
RNGOptions *RandomNetworkGeneratorOptions_setRateLaws(
        RNGOptions *random_network_generator_options_ptr, RateLaws *rate_laws
);

#ifdef __cplusplus
}
#endif


