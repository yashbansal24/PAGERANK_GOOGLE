import networkx as nx
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

g = nx.DiGraph()
data = pd.read_csv('dataset.txt', delimiter='\t')
data = np.array(data)
data = data[:,:][data[:,0] < 30]
data = data[:,:][data[:,1] < 30]

for i in range(len(data)):
    g.add_edge(data[i,0], data[i,1], weight=1)
pos = nx.circular_layout(g)

d = {}
node_sz = pd.read_csv('output.txt', delimiter = '\t')
node_sz = np.array(node_sz)
for i in range(30):
    d[i] = node_sz[i]

nx.draw_networkx_nodes(g,pos,node_size=[v*10000 for v in d.values()])
nx.draw_networkx_edges(g,pos)
nx.draw_networkx_labels(g,pos)
plt.title("Node Visualisation")
plt.axis('off')

plt.savefig('output.png')
plt.show()
