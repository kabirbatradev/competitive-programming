
/*
nodes: dominos
directed edges: one domino --> another domino that will be knocked down

goal: get min # of dominos that need to be manually knocked down in order to knock down all dominos

ideas:

represent with SCCs:
if you knock any domino within a strongly connected component of dominos, it guarantees that the entire
SCC will be knocked down

SCCs are actually nodes!
  if one SCC has a one-way link to another SCC, then knocking down the first SCC is better

  note: the graph of SCCs is a DAG, because if there was a cycle, it would just be one SCC node

  we just need to find all the SCCs-nodes that have an in-degree of 0 
  because they will not be knocked down by other SCCs for sure (we have to knock them down ourselves)
  and other SCCs with some in-degree are now guaranteed to be knocked down
*/