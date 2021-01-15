import os
import sys

import numpy as np
import matplotlib.pyplot as plt
from tables import open_file
import matplotlib as mpl

mpl.rcParams["font.size"] = 16

def save_ratio(energy, ratio):
    plt.plot(energy, ratio, "*")
    plt.xlabel("Энергия, МэВ")
    plt.ylabel("Эффективность\n регистрации")
    plt.tight_layout()
    plt.savefig("plot/efficiency.pdf", transparent=True, format = "pdf")
    plt.clf()

def plot_response(bins_l, hist_l, bins_h, hist_h, energy):
    indx = np.argsort(energy)
    for i, e in enumerate(energy):
        fig = plt.figure(figsize=(10,5))
        fig.add_subplot(121)
        plt.step(bins_l[:-1], hist_l[i])
        plt.xlabel("Энергия, МэВ")
        plt.ylabel("Число событий")
        fig.add_subplot(122)
        plt.step(bins_h[:-1], hist_h[i])
        plt.xlabel("Энергия, МэВ")
        plt.ylabel("Число событий")
        # plt.tight_layout()
        plt.savefig("plot/hist_{:.2f}_MeV.pdf".format(energy[i]), format="pdf", transparent=True)
        plt.cla()
        plt.clf()


def main():
    os.makedirs("plot", exist_ok=True)
    energy_list = []
    ratio_list = []
    bins_low = np.linspace(0, 1, 1000)
    bins_high = np.linspace(1, 100, 100)
    hists_h = []
    hists_l = []
    with open_file(sys.argv[1]) as h5file:
        for group in h5file.root:
            data = h5file.get_node(group, "deposit")
            number = data.attrs["number"]
            energy = data.attrs["energy"]
            ratio = data.nrows / number
            energy_list.append(energy)
            ratio_list.append(ratio)
            data = data.read()
            hist_low, _ = np.histogram(data, bins_low)
            hist_high, _ = np.histogram(data, bins_high)
            hists_h.append(hist_high)
            hists_l.append(hist_low)

    save_ratio(energy_list, ratio_list)
    plot_response(bins_low, hists_l, bins_high, hists_h, energy_list)

    return 0


if __name__ == '__main__':
    main()