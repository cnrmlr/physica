#include <physica/hypergraph.h>
#include <physica/uuid.h>

class Obj
{
 public:
   Obj() {}
   Obj(size_t val) : val(val) {}
   size_t getVal() { return val; }

 private:
   size_t val;
};

int main()
{
   // ********************************************
   //
   // Example usage of phys::node
   //
   // ********************************************

   {
      auto node = phys::make_node<Obj>(42); // construct with arguments
   }

   {
      Obj obj(42);
      auto node = phys::make_node<Obj>(obj); // construct with lvalue
   }

   {
      Obj obj(42);
      auto node = phys::make_node<Obj>(std::move(obj)); // construct with rvalue
   }

   {
      auto node = phys::make_node<Obj>(Obj(42)); // construct with rvalue
   }

   {
      auto node = phys::make_node<Obj>(42);

      Obj obj = node.data(); // extract object from node
      const phys::uuid& id = node.uuid(); // read the node's unique identifier
   }

   // ********************************************
   //
   // Example usage of phys::hyperedge
   //
   // ********************************************
   {
      auto node_1 = phys::make_node<Obj>();
      auto node_2 = phys::make_node<Obj>();
      auto node_3 = phys::make_node<Obj>();

      {
         auto edge = phys::make_hyperedge<Obj>({node_1, node_2, node_3});
      }
   }

   // ********************************************
   //
   // Example usage of phys::hypergraph
   //
   // ********************************************
   {
      auto node_1 = phys::make_node<Obj>();
      auto node_2 = phys::make_node<Obj>();
      auto node_3 = phys::make_node<Obj>();
      auto node_4 = phys::make_node<Obj>();
      auto node_5 = phys::make_node<Obj>();
      auto node_6 = phys::make_node<Obj>();

      auto edge_1 = phys::make_hyperedge<Obj>({node_1, node_2, node_3});
      auto edge_2 = phys::make_hyperedge<Obj>({node_4, node_5, node_6});

      auto graph = phys::make_hypergraph<Obj>({edge_1, edge_2});
   }

   return 1;
}