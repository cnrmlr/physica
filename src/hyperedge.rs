use crate::vertex::Vertex;
use std::hash::{Hash, Hasher};
use std::rc::Rc;

pub struct Hyperedge {
    pub vertices: Vec<Rc<Vertex>>,
}

impl Hyperedge {
    pub fn new(vertices: Vec<Rc<Vertex>>) -> Self {
        Self { vertices }
    }

    pub fn set_vertices(&mut self, vertices: Vec<Rc<Vertex>>) {
        self.vertices.clear();
        self.vertices.extend(vertices);
    }

    pub fn has_vertex(&self, vertex: Rc<Vertex>) -> bool {
        self.vertices.contains(&vertex)
    }

    pub fn get_degree(&self) -> usize {
        self.vertices.len()
    }

    pub fn get_vertices(&self) -> &Vec<Rc<Vertex>> {
        &self.vertices
    }
}

impl Eq for Hyperedge {}

impl PartialEq for Hyperedge {
    fn eq(&self, other: &Self) -> bool {
        self.vertices == other.vertices
    }
}

impl Hash for Hyperedge {
    fn hash<H: Hasher>(&self, state: &mut H) {
        // Hashing each vertex in the vector
        for vertex in &self.vertices {
            vertex.hash(state);
        }
    }
}

impl Clone for Hyperedge {
    fn clone(&self) -> Self {
        Self {
            vertices: self.vertices.clone(), // Clones the vector of Rc<Vertex>
        }
    }
}
