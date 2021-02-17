import json
import os
import sys
from dataclasses import dataclass
import shutil
import numpy as np
import matplotlib.pyplot as plt
from tables import open_file
import matplotlib as mpl

@dataclass
class Hist:
    hist: np.ndarray
    bins: np.ndarray
    number: int
    right_energy : float
    left_energy : float

    def to_dict(self):
        return {
            "hist" : list(map(int, self.hist)),
            "bins" : list(map(float, self.bins)),
            "number": int(self.number),
            "right_energy": float(self.right_energy),
            "left_energy" : float(self.left_energy)
        }

def dump_to_json(hists, filename):
    with open(filename, "w") as fout:
        json.dump([item.to_dict() for item in hists], fout)
    return 0



def collect_bins(h5file):
    energy = set()
    for group in h5file.root:
        data = h5file.get_node(group, "deposit")
        right_energy = data.attrs["right_energy"]
        left_energy  = data.attrs["left_energy"]
        energy.add(right_energy)
        energy.add(left_energy)
    # print(np.array(list(energy)))
    return np.sort(np.array(list(energy)))

def build_and_plot_matrix(hists, dirname, filename):
    bins = hists[0].bins
    n = bins.size - 1
    prob_energy = np.array([np.sum(it.hist/it.number) for it in hists], dtype="d")
    prob_energy /= np.sum(prob_energy)
    prob_dep_energy = np.zeros((n,n), dtype="d")
    assert np.allclose(np.sum(prob_energy), np.array(1.0))
    for indx, hist in enumerate(hists):
        prob_dep_energy[indx, :] = hist.hist/np.sum(hist.hist)
    prob_deposit = np.zeros(n, dtype="d")
    for j in range(n):
        prob_deposit[j] = np.dot(prob_energy, prob_dep_energy[:, j])
    prob_energy_deposit = np.zeros((n,n), dtype="d")
    for i in range(n):
        prob_energy_deposit[i, :] = prob_dep_energy[i, :]*prob_energy[i]/prob_deposit
    data = {
        "energy" : list(map(float, bins)),
        "channel" : list(map(float, bins)),
        "matrix" : [
            {
                "channel" : i,
                "probability" : list(map(float,prob_energy_deposit[:, i]))
            } for i in range(n)
        ]
    }
    with open(os.path.join(dirname, filename+"_matrix.json"), "w") as fout:
        json.dump(data, fout)
    plt.matshow(prob_energy_deposit)
    plt.tight_layout()
    plt.colorbar()
    plt.savefig(os.path.join(dirname, filename + ".pdf"), transparent=True)

def process_file(filename):
    results = []
    name = filename.split(".")[0]
    if os.path.exists(name):
        shutil.rmtree(name)
    os.mkdir(name)
    with open_file(filename) as h5file:
        energy_bins = collect_bins(h5file)
        for group in h5file.root:
            data = h5file.get_node(group, "deposit")
            number = data.attrs["number"]
            right_energy = data.attrs["right_energy"]
            left_energy  = data.attrs["left_energy"]
            data = data.read()
            hist, _ = np.histogram(data, bins=energy_bins)
            hist = Hist(hist, energy_bins, number, right_energy, left_energy)
            results.append(hist)
    results.sort(key=lambda x: x.left_energy)
    dump_to_json(results, os.path.join(name, name + ".json"))
    build_and_plot_matrix(results, name, name)
    return 0


def main():
    process_file(sys.argv[1])
    return 0

if __name__ == '__main__':
    main()