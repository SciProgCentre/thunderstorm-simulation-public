import os
import sys

import numpy as np
import matplotlib.pyplot as plt
from tables import open_file
import matplotlib as mpl

def main():
    energy_list = []
    with open_file(sys.argv[1]) as h5file:
        for group in h5file.root:
            data = h5file.get_node(group, "deposit")
            # number = data.attrs["number"]
            energy = data.attrs["energy"]
            energy_list.append(energy)




    return 0


if __name__ == '__main__':
    main()