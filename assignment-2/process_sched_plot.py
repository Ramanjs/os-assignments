import plotly.graph_objs as go
from plotly.offline import iplot

sched_other = open("result-a", "r")
sched_rr = open("result-b", "r")
sched_fifo = open("result-c", "r")

values_a = [float(x[0:len(x) - 2]) for x in sched_other.readlines()]
values_b = [float(x[0:len(x) - 2]) for x in sched_rr.readlines()]
values_c = [float(x[0:len(x) - 2]) for x in sched_fifo.readlines()]

priorities = []
priorities.append(str((2, 0, 1)))

sched_rr = go.Bar(x = priorities, y = values_b, name = 'SCHED_RR')
sched_other = go.Bar(x = priorities, y = values_a, name = 'SCHED_OTHER')
sched_fifo = go.Bar(x = priorities, y = values_c, name = 'SCHED_FIFO')

data = [sched_rr, sched_other, sched_fifo]
layout = go.Layout(barmode = 'group')
fig = go.Figure(data = data, layout = layout)
iplot(fig)
