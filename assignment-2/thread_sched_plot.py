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

trace1 = go.Bar(
   x = priorities,
   y = values_b,
   name = 'SCHED_RR'
)

trace2 = go.Bar(
   x = priorities,
   y = values_a,
   name = 'SCHED_OTHER'
)

trace3 = go.Bar(
   x = priorities,
   y = values_c,
   name = 'SCHED_FIFO'
)

data = [trace1, trace2, trace3]
layout = go.Layout(barmode = 'group')
fig = go.Figure(data = data, layout = layout)
iplot(fig)
