mod hyperedge;
mod hypergraph;
mod hypervertex;

use hyperedge::Hyperedge;
use hypergraph::Hypergraph;
use hypervertex::Hypervertex;
use std::rc::Rc;

/// This is the main function of the program.
/// It demonstrates the usage of the Graph, Vertex, and Edge structs.
fn main() {
    // Create an empty graph
    // A mutable reference to a Graph instance.
    let mut hypergraph = Hypergraph::new();

    // Add some vertices
    // Create new Rc (Reference Counted) instances of Vertex with unique IDs.
    let v1 = Rc::new(Hypervertex::new(1));
    let v2 = Rc::new(Hypervertex::new(2));
    let v3 = Rc::new(Hypervertex::new(3));

    // Add vertices to the graph
    // Add a vector of Rc<Vertex> instances to the graph.
    hypergraph.add_vertices(vec![v1.clone(), v2.clone(), v3.clone()]);

    // Add edges between vertices
    // Create new Rc (Reference Counted) instances of Edge with vectors of Rc<Vertex> instances.
    let e1 = Rc::new(Hyperedge::new(vec![v1.clone(), v2.clone()]));
    let e2 = Rc::new(Hyperedge::new(vec![v1.clone(), v3.clone()]));

    println!("e1 is degree: {}", e1.get_degree());
    println!("e2 is degree: {}", e2.get_degree());

    // Add edges to the graph
    // Add an Rc<Edge> instance to the graph.
    hypergraph.add_edge(e1);
    hypergraph.add_edge(e2);

    // Print the graph and its contents
    hypergraph.print();
}
