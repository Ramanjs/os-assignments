import plotly.graph_objs as go
from plotly.offline import iplot

sched_other = open("thread-a", "r")
sched_rr = open("thread-b", "r")
sched_fifo = open("thread-c", "r")

priorities_a = [0] * 10
priorities_b = []
priorities_c = []

for i in range(0, 5):
    priorities_b.append(1 + 5 * i)
for i in range(0, 5):
    priorities_b.append(2 + 10 * i)

for i in range(0, 5):
    priorities_c.append(1 + 10 * i)
for i in range(0, 5):
    priorities_c.append(2 + 5 * i)


values_a = [float(x[0:len(x) - 2]) for x in sched_other.readlines()]
values_b = [float(x[0:len(x) - 2]) for x in sched_rr.readlines()]
values_c = [float(x[0:len(x) - 2]) for x in sched_fifo.readlines()]

priorities = []

for i in range(10):
    priorities.append(str((priorities_b[i], priorities_a[i], priorities_c[i])))

sched_rr = go.Bar(x = priorities, y = values_b, name = 'SCHED_RR')
sched_other = go.Bar(x = priorities, y = values_a, name = 'SCHED_OTHER')
sched_fifo = go.Bar(x = priorities, y = values_c, name = 'SCHED_FIFO')

data = [sched_rr, sched_other, sched_fifo]
layout = go.Layout(barmode = 'group')
fig = go.Figure(data = data, layout = layout)
iplot(fig)
