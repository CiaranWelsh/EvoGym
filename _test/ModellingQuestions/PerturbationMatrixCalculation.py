# Small script to manually compute the value of an objective function comparing
# distance of experimentally derived perturbation matrix with simulated one
#
# Question: Is this accurate?
#

import tellurium as te
import numpy as np

# data
# ----
# experimentally measured perturbation values
# values are the result of decreasing the amounts of network components and measuring their steady state.
# the steady states are then normalized to the unperturbed steady state values
data = np.array([
    # dk1  dk2
    [0.4, 0.7], # S1
    [0.3, 0.6]  # S2
])


k1 = 0.1
k2 = 0.5
ant = f"""
model simple
    r1: S1 -> S2; k1*S1;
    r2: S2 -> S1; k2*S2;
    S1 = 10; 
    S2 = 0; 
    k1 = {k1}; 
    k2 = {k2}; 
end 
"""

rr = te.loada(ant)
rr.conservedMoietyAnalysis = True

DELTA = 0.05
assert DELTA > 0
assert DELTA < 1

# 1. compute baseline steady state
rr.steadyState()
ss = rr.getFloatingSpeciesConcentrations()

# 2. Perturb parameter k1 by +5%
rr.reset()

rr.k1 = rr.k1 + (DELTA*rr.k1)
rr.steadyState()
ss_k1_plus = rr.getFloatingSpeciesConcentrations()
rr.k1 = k1

# 3. Perturb parameter k1 by -5%
rr.reset()
rr.k1 = rr.k1 - (DELTA*rr.k1)
rr.steadyState()
ss_k1_minus = rr.getFloatingSpeciesConcentrations()
rr.k1 = k1

# 4. average
ss_k1 = (ss_k1_plus + ss_k1_minus) / 2

# 5. normalize by original steady state values
ss_k1 /= ss

# 6. same for k2
rr.reset()
rr.k2 = rr.k2 + (DELTA*rr.k2)
rr.steadyState()
ss_k2_plus = rr.getFloatingSpeciesConcentrations()
rr.k2 = k2

rr.k2 = rr.k2 - (DELTA*rr.k2)
rr.steadyState()
ss_k2_minus = rr.getFloatingSpeciesConcentrations()
rr.k2 = k2

ss_k2 = (ss_k2_plus + ss_k2_minus) / 2
ss_k2 /= ss

print("baseline steady state: \n", ss)

P = np.vstack([ss_k1, ss_k2]).transpose()

print("perturbation matrix: \n", P)
# output
# ------
# baseline steady state:
#  [8.33333333 1.66666667] (s1, s2)
# perturbation matrix:
#       delta k1    delta k2
#  S1 [[0.99173554 0.99130435]
#  S2  [1.04132231 1.04347826]]

# 7. calculate residuals
top_left = (1.00006945 - 0.4)**2
residual = (data - P)**2 # divided by the experimentally measured standard deviations
assert np.isclose(top_left, residual[0, 0]), f"top_left != residual[0][0], {top_left} != {residual[0][0]}"

print("residual matrix:\n ", residual )

# Output
# ------
# residual matrix:
#   [[0.35015095 0.08485822]
#    [0.54955877 0.19667297]]

fitness_value = residual.sum().sum()
print(fitness_value) # 1.1812409102077475


