#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "algo_cpp/DisjointSet.h"

using std::cout, std::endl, std::vector, std::shared_ptr, std::unique_ptr, std::cin, std::map, std::string;

template<typename Vert>
class IVertexOwner {
public:
  using VertType = Vert;
};

template<typename Id>
class IVertex {
  const shared_ptr<Id> identity;
public:

  explicit IVertex(Id id) : identity(std::make_shared<Id>(id)) {
  }

  const Id &Identity() {
    return *identity;
  }

  IVertex(const IVertex &other) = default;

  IVertex(IVertex &&other) noexcept = default;

  IVertex &operator=(const IVertex &other) = default;

  IVertex &operator=(IVertex &&other) noexcept = default;

  virtual ~IVertex() = default;
};

template<typename Id>
class LinkedVert final : public IVertex<Id> {
  shared_ptr<LinkedVert> parent{nullptr};
public:
  explicit LinkedVert(Id id) : IVertex<Id>(id) {

  }
};

template<typename Vert>
class BasicEdge : public IVertexOwner<Vert> {
  shared_ptr<Vert> former_vert;
  shared_ptr<Vert> latter_vert;

public:
  BasicEdge(Vert f, Vert l) : former_vert(std::make_shared<>(f)), latter_vert(std::make_shared<>(l)) {
  }

  shared_ptr<Vert> Former() {
    return former_vert;
  }

  shared_ptr<Vert> Latter() {
    return latter_vert;
  }
};

template<typename E>
class LinkedGraph {
  using VertexPtr_t = shared_ptr<typename E::VertType>;
  using EdgePtr_t = shared_ptr<E>;
  using EdgeMap_t = map<VertexPtr_t, vector<EdgePtr_t >>;
  vector<VertexPtr_t> vertices;
  EdgeMap_t edges_map;

public:
  explicit LinkedGraph(vector<EdgePtr_t> edges_vector) {
    for (EdgePtr_t &edge_ptr: edges_vector) {
      E &edge(*edge_ptr);
      // error below
//      auto entry(edges_map.find(edges_map.begin(), edges_map.end(), edge.Former()));
//      if(entry != edges_map.end())
//      {
//
//      }
//      else
//      {
//        vector<EdgePtr_t> v{edge_ptr};
//        edges_map.insert({edge.Former(), v});
//      }
    }
  }
};

class base {
private:
  int value;
public:
  base(int x) {
    value = x;
  }

  virtual void fun() {

  }
};

class derived : public base {
private:
  int a;
public:
  derived(int x, int y) : base(x) {
    base *b;
    b = this;
    b->fun();      //calls derived::fun()
  }

  void fun() {
    std::cout << "fun inside derived class" << std::endl;
  }
};

using org::nathan::algo_cpp::DisjointSet;

int foo() // code starts at memory address 0x002717f0
{
  return 5;
}

int main() // NOLINT
{
  DisjointSet a{};
  DisjointSet b{a};
  int (* fcnPtr)(){&foo};

  derived d{1, 2};
  std::cout << (*fcnPtr)() << std::endl;
  return 0;
}