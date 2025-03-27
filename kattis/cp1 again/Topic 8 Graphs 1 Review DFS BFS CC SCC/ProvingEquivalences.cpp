
/*
given some directed edges between nodes (and total # nodes)
goal: get minimum number of new edges needed so that all nodes are in SCC

case: no edges
  create a circle of all of the nodes --> minimum # edges used

case: some chains of nodes
  treat each chain of nodes as a single node
  then create the circle (just like no edges case)
  if there is only one chain, then you have to link it to itself...

case: some SCCs of nodes
  treat each SCC as a single node
  create a circle (like no edges case)
  single SCC is not the same as single chain though...

case: single node, or single SCC
  alr SCC, so alr done

case: weird tree-like structure with no cycles
  i guess each leaf should be linked back to the start.. 
  but we could just link leaf ends to new nodes?
    3 leafs means 3 new edges, but they could all be to new nodes which is more efficient than to the same node

case: weird tree-like structure with cycles

yeah idk if this case by case idea the way to go 



*/