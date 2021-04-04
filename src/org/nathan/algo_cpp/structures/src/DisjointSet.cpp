#include "algo_cpp_structures/DisjointSet.h"

void DisjointSet::link(DisjointSet &x, DisjointSet &y)
{
    if (x.rank > y.rank)
    {
        y.parent = &x;
    }
    else
    {
        x.parent = &y;
        if (x.rank == y.rank)
        {
            y.rank = y.rank + 1;
        }
    }
}

DisjointSet &DisjointSet::findSet(DisjointSet &x)
{
    if (&x != x.parent)
    {
        x.parent = &findSet(*x.parent);
    }
    return *x.parent;
}

DisjointSet &DisjointSet::findSet()
{
    if (this != this->parent)
    {
        this->parent = &findSet(*this->parent);
    }
    return *this->parent;
}

[[maybe_unused]] void DisjointSet::unionSet(DisjointSet &a, DisjointSet &b)
{
    link(findSet(a), findSet(b));
}

[[maybe_unused]] void DisjointSet::unionSet(DisjointSet &a)
{
    link(findSet(), findSet(a));
}