use std::convert::TryFrom;
use std::str::FromStr;
use std::fmt::{self, Display, Formatter};
use std::cmp::PartialEq;

#[derive(Debug)]
pub struct ChunkType {
    ancillary: u8,
    private: u8,
    reserved: u8,
    safe: u8,
}

const MASK: u8 = 0b00100000;

impl ChunkType {
    pub fn bytes(&self) -> [u8; 4] {
        [self.ancillary, self.private, self.reserved, self.safe]
    }

    fn is_valid(&self) -> bool {
        for byte in self.bytes() {
            if !byte.is_ascii_uppercase() {
                return false;
            }
        }
        true
    }

    fn is_critical(&self) -> bool {
        self.ancillary & MASK == 0
    }

    fn is_public(&self) -> bool {
        self.private & MASK == 0
    }

    fn is_reserved_bit_valid(&self) -> bool {
        self.reserved & MASK == 0
    }

    fn is_safe_to_copy(&self) -> bool {
        self.safe & MASK != 0
    }
}

impl TryFrom<[u8; 4]> for ChunkType {
    type Error = &'static str;

    fn try_from(val: [u8; 4]) -> Result<Self, Self::Error> {
        Ok(ChunkType {
            ancillary: val[0],
            private: val[1],
            reserved: val[2],
            safe: val[3],
        })
    }
}

impl FromStr for ChunkType {
    type Err = &'static str;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let bytes = s.as_bytes();

        Ok(ChunkType {
            ancillary: bytes[0],
            private: bytes[1],
            reserved: bytes[2],
            safe: bytes[3],
        })
    }
}

impl Display for ChunkType {

    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        write!(f, "{}{}{}{}", self.ancillary, self.private, self.reserved, self.safe)
    }
}

impl PartialEq for ChunkType {
    fn eq(&self, chunk_type: &ChunkType) -> bool {
        self.ancillary == chunk_type.ancillary && self.private == chunk_type.private && self.reserved == chunk_type.reserved && self.safe == chunk_type.safe
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::convert::TryFrom;
    use std::str::FromStr;

    #[test]
    pub fn test_chunk_type_from_bytes() {
        let expected = [82, 117, 83, 116];
        let actual = ChunkType::try_from([82, 117, 83, 116]).unwrap();

        assert_eq!(expected, actual.bytes());
    }

    #[test]
    pub fn test_chunk_type_from_str() {
        let expected = ChunkType::try_from([82, 117, 83, 116]).unwrap();
        let actual = ChunkType::from_str("RuSt").unwrap();
        assert_eq!(expected, actual);
    }

    #[test]
    pub fn test_chunk_type_is_critical() {
        let chunk = ChunkType::from_str("RuSt").unwrap();
        assert!(chunk.is_critical());
    }

    #[test]
    pub fn test_chunk_type_is_not_critical() {
        let chunk = ChunkType::from_str("ruSt").unwrap();
        assert!(!chunk.is_critical());
    }

    #[test]
    pub fn test_chunk_type_is_public() {
        let chunk = ChunkType::from_str("RUSt").unwrap();
        assert!(chunk.is_public());
    }

    #[test]
    pub fn test_chunk_type_is_not_public() {
        let chunk = ChunkType::from_str("RuSt").unwrap();
        assert!(!chunk.is_public());
    }

    #[test]
    pub fn test_chunk_type_is_reserved_bit_valid() {
        let chunk = ChunkType::from_str("RuSt").unwrap();
        assert!(chunk.is_reserved_bit_valid());
    }

    #[test]
    pub fn test_chunk_type_is_reserved_bit_invalid() {
        let chunk = ChunkType::from_str("Rust").unwrap();
        assert!(!chunk.is_reserved_bit_valid());
    }

    #[test]
    pub fn test_chunk_type_is_safe_to_copy() {
        let chunk = ChunkType::from_str("RuSt").unwrap();
        assert!(chunk.is_safe_to_copy());
    }

    #[test]
    pub fn test_chunk_type_is_unsafe_to_copy() {
        let chunk = ChunkType::from_str("RuST").unwrap();
        assert!(!chunk.is_safe_to_copy());
    }

    #[test]
    pub fn test_valid_chunk_is_valid() {
        let chunk = ChunkType::from_str("RuSt").unwrap();
        assert!(chunk.is_valid());
    }

    #[test]
    pub fn test_invalid_chunk_is_valid() {
        let chunk = ChunkType::from_str("Rust").unwrap();
        assert!(!chunk.is_valid());

        let chunk = ChunkType::from_str("Ru1t");
        assert!(chunk.is_err());
    }

    #[test]
    pub fn test_chunk_type_string() {
        let chunk = ChunkType::from_str("RuSt").unwrap();
        assert_eq!(&chunk.to_string(), "RuSt");
    }

    #[test]
    pub fn test_chunk_type_trait_impls() {
        let chunk_type_1: ChunkType = TryFrom::try_from([82, 117, 83, 116]).unwrap();
        let chunk_type_2: ChunkType = FromStr::from_str("RuSt").unwrap();
        let _chunk_string = format!("{}", chunk_type_1);
        let _are_chunks_equal = chunk_type_1 == chunk_type_2;
    }
}
