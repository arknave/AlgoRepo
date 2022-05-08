#!/usr/bin/env rust-script

use crate::scan::ContestReader;

fn main() {
    let stdin = std::io::stdin();
    let mut stdin = stdin.lock();
    let mut scanner = scan::Scanner::new(&mut stdin);

}

mod scan {
    use std::str::{self, FromStr};

    pub trait ContestReader {
        fn read<T>(&mut self) -> T
        where
            T: FromStr,
            <T as FromStr>::Err: std::fmt::Debug;

        #[allow(dead_code)]
        fn usize0(&mut self) -> usize {
            self.read::<usize>() - 1
        }

        #[allow(dead_code)]
        fn read_vec<T>(&mut self, n: usize) -> Vec<T>
        where
            T: FromStr,
            <T as FromStr>::Err: std::fmt::Debug {
            (0..n).map(|_| self.read()).collect()
        }
    }

    const BUF_SIZE: usize = 1 << 16;
    pub struct Scanner<R: std::io::Read> {
        input: R,
        // For whatever reason, reading into a static large buffer is 3-4x faster than the bytes iterator
        buf1: [u8; BUF_SIZE],
        // Reading non-spaces into a second massive buffer is also much faster than collecting into a Vec.
        buf2: [u8; BUF_SIZE],
        buf_size: usize,
        buf_ptr: usize,
    }

    impl<R: std::io::Read> Scanner<R> {
        pub fn new(input: R) -> Self {
            Scanner {
                input: input,
                buf1: [0; BUF_SIZE],
                buf2: [0; BUF_SIZE],
                buf_size: 0,
                buf_ptr: 0,
            }
        }

        fn pop(&mut self) -> u8 {
            if self.buf_ptr >= self.buf_size {
                self.buf_size = self.input.read(&mut self.buf1).unwrap();
                self.buf_ptr = 0;
            }

            // N.B. If we run out of data here, this will panic in debug and UB in release

            let x = self.buf1[self.buf_ptr];
            self.buf_ptr += 1;

            x
        }

        fn is_whitespace(c: u8) -> bool {
            c == b' ' || c == b'\n' || c == b'\t' || c == b'\r'
        }
    }

    impl<R: std::io::Read> ContestReader for Scanner<R> {
        fn read<T>(&mut self) -> T
        where
            T: FromStr,
            <T as FromStr>::Err: std::fmt::Debug,
        {
            let mut c = self.pop();
            while Self::is_whitespace(c) {
                c = self.pop();
            }

            let mut ptr: usize = 0;
            while !Self::is_whitespace(c) {
                self.buf2[ptr] = c;
                ptr += 1;
                c = self.pop();
            }

            unsafe { str::from_utf8_unchecked(&self.buf2[..ptr]).parse().unwrap() }
        }
    }
}
