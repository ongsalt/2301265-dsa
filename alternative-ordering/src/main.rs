use rand::seq::SliceRandom;
use std::io;
// use std::time::Instant;

// mod gpu;

fn check(seq: Vec<u32>) -> bool {
    let n = seq.len();

    // all length 3 subsequences
    for i in 0..n {
        for j in (i + 1)..n {
            for k in (j + 1)..n {
                if seq[i] + seq[k] == seq[j] * 2 {
                    println!(" {} {} {} at {i} {j} {k}", seq[i], seq[j], seq[k]);
                    return false;
                }
            }
        }
    }

    true
}

fn solve(n: u32) -> Vec<u32> {
    let mut seq: Vec<u32> = vec![0, 2, 1];
    while seq.len() < n as usize {
        seq = seq
            .iter()
            .map(|i| *i * 2)
            .chain(seq.iter().map(|i| *i * 2 + 1))
            .collect()
    }

    seq.into_iter().filter(|it: &u32| *it < n).collect()
}

fn solve_optimized(n: u32) -> Vec<u32> {
    let mut p = 3;
    while p < n {
        p *= 2
    }

    let mut seq = vec![0u32; p as usize];

    let mut size = 3;
    seq[0] = 0;
    seq[1] = 2;
    seq[2] = 1;

    while size < n as usize {
        for i in 0..size {
            seq[i] *= 2;
            seq[i + size] = seq[i] + 1;
        }

        size *= 2;
    }

    seq.into_iter().filter(|it: &u32| *it < n).collect()
}

fn solve_3(n: u32) {
    (0, 2, 1);
}

fn brute_force(n: u32) -> Vec<u32> {
    let mut seq: Vec<u32> = (0..n).collect();
    let mut rng = rand::rng();
    let mut attempts = 0;

    loop {
        attempts += 1;
        if check(seq.clone()) {
            println!("Found solution after {} attempts", attempts);
            return seq;
        }
        seq.shuffle(&mut rng);
    }
}

fn main() {
    let mut n = String::new();
    io::stdin().read_line(&mut n).expect("Failed to read line");

    let n = n.trim().parse::<u32>().expect("Must be positive integer") + 1;

    // Or use GPU version
    // failed, probably because wsl
    // let seq = pollster::block_on(gpu::solve_gpu(n));

    let seq = solve_optimized(n);

    for i in seq {
        print!("{i} ");
    }

    // if !check(seq) {
    //     println!("failed");
    // }
}

/*
0 1 2 3 4 5

0 1 2 -> 0 2 1
3 4 5 -> 3 5 4

0 2 1
3 5 4

0 2 1 3
0 4 2 1 3
0 4 2 1 5 3

(0 4 2) + (1, 1, 1) = (1 5 3)

condition for any 3 numbers a b c: a < b < c -> if 2 * b == (a + c) then b must not be in between a and c

# Guess
n = 11
0 8 4 2 10 6 1 9 5 3 7 11



0 2 1 3

n = 23
0 16 8 4 20 12 2 18 10 6 22 14 1 17 9 5 21 13 3 19 11 7 15 23


bruh, its working

*/
