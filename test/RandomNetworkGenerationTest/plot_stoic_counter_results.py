import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

# N100000 = [
#     2771,
#     5615,
#     5526,
#     2793,
#     5531,
#     11233,
#     11000,
#     5573,
#     5459,
#     2796,
#     11039,
#     5512,
#     11158,
#     5500,
#     5635,
#     2859
# ]

N10000 = [
    285, 294, 267, 270, 260, 303, 303, 253, 275, 270, 278, 268, 276, 254, 281, 267, 293, 245, 333, 287, 261, 295, 283,
    283, 241, 258, 292, 262, 260, 278, 284, 293, 314, 286, 260,
    288
]

# N100k = pd.DataFrame(N100000).transpose()
# N100k.loc[0] = N100k.loc[0] / 100000 * 100
N10k = pd.DataFrame(N10000).transpose()
N10k.loc[0] = N10k.loc[0] / 10000 * 100
# print(N100k)\
fig = plt.figure()
sns.set_context("talk")
sns.barplot(data=N10k, edgecolor="black", linewidth=1.0)
sns.despine(fig=fig, top=True, right=True)
plt.title("Counting instances of stoichiometry matrices\n normalized by N in 100K random models")
plt.ylabel("Frequency %")
plt.xlabel("Model Index")
fname = os.path.join(os.path.dirname(__file__), "StoichiometryInstanceCount.png")
plt.savefig(fname, bbox_inches='tight', dpi=300)
