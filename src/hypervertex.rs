use std::hash::{Hash, Hasher};

pub struct Hypervertex {
    pub id: u128,
}

impl Hypervertex {
    pub fn new(id: u128) -> Self {
        Self { id }
    }

    pub fn get_id(&self) -> u128 {
        self.id
    }
}

impl PartialEq for Hypervertex {
    fn eq(&self, other: &Self) -> bool {
        self.id == other.id
    }
}

impl Eq for Hypervertex {}

impl Hash for Hypervertex {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.id.hash(state);
    }
}

impl Clone for Hypervertex {
    fn clone(&self) -> Self {
        Self { id: self.id }
    }
}
