from thunderstorm_pb2 import CloudList
import struct
import numpy as np
import matplotlib.pyplot as plt
import os

class ProtoFileList:
    def __init__(self, filename, proto_class):
        self.fin = open(filename, "rb")
        self.proto_class = proto_class
        self.buff_size = 8
        buff = self.fin.read(self.buff_size)
        if buff == b"": raise Exception("Empty file")
        size = struct.unpack("q", buff)[0]
        self.messege_sizes = [size]
        self.coords = [0]
        coord = 0
        while True:
            coord += self.buff_size+ size
            self.fin.seek(coord)
            self.coords.append(coord)
            buff = self.fin.read(self.buff_size)
            if buff == b"": break
            size = struct.unpack("q", buff)[0]
            self.messege_sizes.append(size)

    def __del__(self):
        self.fin.close()

    def __len__(self):
        return len(self.messege_sizes)

    def _read(self, item):
        self.fin.seek(self.coords[item] + self.buff_size)
        data = self.fin.read(self.messege_sizes[item])
        proto = self.proto_class()
        proto.ParseFromString(data)
        return proto

    def __getitem__(self, item):
        return self._read(item)


def main():
    path = "."
    proto_list = ProtoFileList(os.path.join(path, "thunderstorm.pb.bin"), CloudList)
    result = []
    bins = np.arange(-300, 301, 1)
    for i in range(len(proto_list)):
        data = proto_list[i].cloud
        temp = []
        for item in data:
            temp.append(item.z)
        hist, _ = np.histogram(temp, bins=bins)
        result.append(hist)
    hist = np.sum(result, axis=0)
    np.save(os.path.join(path, "hist.npy"), hist)
    plt.step(bins[:-1]+300, np.cumsum(hist[::-1]))
    plt.savefig(os.path.join(path, "plot.png"), transparent=True, dpi=600)


if __name__ == '__main__':
    main()