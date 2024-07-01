use std::hash::{Hash, Hasher};

pub struct Vertex {
    pub id: u128,
}

impl Vertex {
    pub fn new(id: u128) -> Self {
        Self { id }
    }

    pub fn get_id(&self) -> u128 {
        self.id
    }
}

impl PartialEq for Vertex {
    fn eq(&self, other: &Self) -> bool {
        self.id == other.id
    }
}

impl Eq for Vertex {}

impl Hash for Vertex {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.id.hash(state);
    }
}

impl Clone for Vertex {
    fn clone(&self) -> Self {
        Self { id: self.id }
    }
}
