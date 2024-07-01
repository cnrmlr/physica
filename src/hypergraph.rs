use crate::hyperedge::Hyperedge;
use crate::vertex::Vertex;
use std::collections::HashSet;
use std::rc::Rc;

pub struct Hypergraph {
    pub vertices: HashSet<Rc<Vertex>>,
    pub hyperedges: HashSet<Rc<Hyperedge>>,
}

impl Hypergraph {
    pub fn new() -> Self {
        Self {
            vertices: HashSet::new(),
            hyperedges: HashSet::new(),
        }
    }

    pub fn add_vertices(&mut self, vertices: Vec<Rc<Vertex>>) {
        self.vertices.extend(vertices.iter().cloned());
    }

    pub fn get_vertices(&self) -> &HashSet<Rc<Vertex>> {
        &self.vertices
    }

    pub fn add_edge(&mut self, edge: Rc<Hyperedge>) -> bool {
        // Check if all vertices in the set already exist in the Hypergraph
        let vertices_exist = edge
            .vertices
            .iter()
            .all(|vertex| self.vertices.contains(vertex));

        vertices_exist && self.hyperedges.insert(edge)
    }

    pub fn get_edges(&self) -> &HashSet<Rc<Hyperedge>> {
        &self.hyperedges
    }

    pub fn print(&self) {
        // Print the vertices
        print!("\nVertices: [");
        for (index, vertex) in self.vertices.iter().enumerate() {
            if index > 0 {
                print!(", ");
            }
            print!("{}", vertex.id);
        }
        println!("]");

        // Print the edges
        print!("Edges:");
        for hyperedge in &self.hyperedges {
            print!(" [");
            for (index, vertex) in hyperedge.get_vertices().iter().enumerate() {
                if index > 0 {
                    print!(", ");
                }
                print!("{}", vertex.id);
            }
            print!("]");
        }
        println!("\n");
    }
}
