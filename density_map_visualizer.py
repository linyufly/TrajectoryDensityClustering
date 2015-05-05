import matplotlib
import numpy as np
import matplotlib.pyplot as plt
import csv

density_map_file = 'density_map.csv'

def main():
  with open(density_map_file, 'r') as csv_file:
    table = [row for row in csv.reader(csv_file, delimiter = ',')]

  np_table = np.array([[float(element) for element in row] for row in table])

  fig, ax = plt.subplots()

  im = plt.imshow(np_table, cmap = matplotlib.cm.RdBu_r, vmin = np_table.min(), vmax = np_table.max(), extent = [0, 1, 0, 1])
  im.set_interpolation('bilinear')
  cb = fig.colorbar(im)

  plt.show()

if __name__ == '__main__':
  main()
