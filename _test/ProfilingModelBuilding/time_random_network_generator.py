import os, glob, subprocess
import re
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

EXECUTABLE = r"/Users/ciaranwelsh/Documents/EvoGym/cmake-build-release/bin/HowLongDoesItTakeToCreateNRandomNetworksParallel"

if not os.path.isfile(EXECUTABLE):
    raise FileNotFoundError(EXECUTABLE)


# time = pd.Series(name="time")
# nmodels = pd.Series(name="nModels")
# ncores = pd.Series(name="nCores")

def collect_data(N, cores, with_simulation:bool=False, use_pickle: bool = False):
    if with_simulation:
        regex = b"It took : (\d*) milliseconds to build (\d*) models using (\d*) cores with 1000 step time series simulation"
        fname = os.path.join(os.path.dirname(__file__), "RNGPerformanceResultsWithSimulation.pickle")
    else:
        regex = b"It took : (\d*) milliseconds to build (\d*) models using (\d*) cores without simulation"
        fname = os.path.join(os.path.dirname(__file__), "RNGPerformanceResultsWithoutSimulation.pickle")

    if (use_pickle and os.path.isfile(fname)):
        return pd.read_pickle(fname)

    time = []
    nmodels = []
    ncores = []

    for i in N:
        for core in cores:
            if with_simulation:
                cmd = ["mpirun", "-n", f"{core}", EXECUTABLE, f'{i}', "true"]
            else:
                cmd = ["mpirun", "-n", f"{core}", EXECUTABLE, f'{i}', "false"]

            result = subprocess.run(cmd, stdout=subprocess.PIPE)
            result = result.stdout.split(b"\n")[0]
            match = re.findall(regex, result)
            if len(match) == 0:
                raise ValueError("No match. Youve got a problem")
            t, m, n = [int(j) for j in match[0]]
            time.append(t)
            nmodels.append(m)
            ncores.append(n)

    df = pd.DataFrame([ncores, nmodels, time], index=["ncores", "nmodels", "time"]).transpose()
    df.to_pickle(fname)
    return df

def plot_times(data, fname, with_simulation):
    fig, (ax1, ax2) = plt.subplots(ncols=2, sharey="row")

    sns.set_context("talk")

    sns.barplot(x="nmodels", y="time", hue="ncores", data=data, ax=ax1, edgecolor="black", linewidth=1.0)
    sns.despine(ax=ax1, top=True, right=True)
    plt.ylabel("Time (milliseconds)")

    sns.barplot(x="ncores", y="time", hue="nmodels", data=data, ax=ax2, edgecolor="black", linewidth=1.0)
    sns.despine(ax=ax2, top=True, right=True)
    plt.ylabel("Time (milliseconds)")

    if with_simulation:
        plt.suptitle("""Time taken to generate \"nmodels\" 
random models with 1 compartment, 1 Boundary, 
5 Floating and 10 reactions using \"ncores\" cores 
and simulate 1000 time steps""", y=1.15)
    else:
        plt.suptitle("""Time taken to generate \"nmodels\" 
random models with 1 compartment, 1 Boundary, 
5 Floating and 10 reactions using \"ncores\" cores""", y=1.1)
    plt.savefig(fname, bbox_inches="tight", dpi=250)

if __name__ == "__main__":
    # When true, read from pickle file and return data
    # when false or when the pickle file not exist, generate new data (can take time)
    READ_FROM_PICKLE = True
    PLOT = True

    N = [1, 10, 100, 1000]

    cores = range(1, 7)

    df_without_simulation = collect_data(N, cores, False, READ_FROM_PICKLE)
    df_with_simulation = collect_data(N, cores, True, READ_FROM_PICKLE)

    if PLOT:
        # call the plotting function
        plot_times(df_without_simulation, "PerformanceWithoutSimulation.png", False)
        plot_times(df_with_simulation, "PerformanceWithSimulation.png", True)

    # print(df["time"]  ( df["ncores"] * df["nmodels"] )   )
    # df["time/cores"] = df["time"] / df["ncores"]
    # df["time/models"] = df["time"] / df["nmodels"]
    # df["time/(cores*models)"] = df["time"] / (df["ncores"]*df["nmodels"])
    # print(df)
    # print(df.to_csv("data.csv"))


