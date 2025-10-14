use std::io;

fn main() {
    let mut n = String::new();
    io::stdin().read_line(&mut n).expect("Failed to read line");

    let n = n.trim().parse::<u64>().expect("Must be positive integer") + 1;

    let mut seq: Vec<u64> = vec![0, 2, 1];
    while seq.len() < n as usize {
        seq = seq
            .iter()
            .map(|i| *i * 2)
            .chain(seq.iter().map(|i| *i * 2 + 1))
            .collect()
    }

    seq = seq.into_iter().filter(|it: &u64| *it < n).collect();

    println!(
        "{}",
        seq.iter()
            .map(|n| n.to_string())
            .reduce(|a, b| format!("{a} {b}"))
            .unwrap()
    );
    // println!("{:.?}", out.len());
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
