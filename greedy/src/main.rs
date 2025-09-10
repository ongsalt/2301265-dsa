use std::io;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Entry {
    Passenger,
    Grab,
    Empty,
}

type ParseError = ();

impl Entry {
    fn from_string(value: &str) -> Result<Vec<Self>, ParseError> {
        let mut out = vec![];
        for c in value.chars() {
            let entry = match c {
                'G' | 'g' => Entry::Grab,
                'P' | 'p' => Entry::Passenger,
                _ => return Err(()),
            };
            out.push(entry);
        }
        Ok(out)
    }

    fn match_pair(self, other: Self) -> bool {
        matches!(
            (self, other),
            (Entry::Passenger, Entry::Grab) | (Entry::Grab, Entry::Passenger)
        )
    }
}

// claude wrote this
fn brute_force(entries: Vec<Entry>, k: usize) -> (u64, u64) {
    fn dfs(entries: Vec<Entry>, k: usize) -> (u64, u64) {
        let len = entries.len();
        // find first non-empty entry
        let mut i = 0;
        while i < len && entries[i] == Entry::Empty {
            i += 1;
        }
        // no more entries to match: zero matches, one way
        if i >= len {
            return (0, 1);
        }
        let mut max_matches = 0;
        let mut sol_count = 0;
        // option: skip this entry
        let mut skipped = entries.clone();
        skipped[i] = Entry::Empty;
        let (m_skip, c_skip) = dfs(skipped, k);
        if m_skip > max_matches {
            max_matches = m_skip;
            sol_count = c_skip;
        } else if m_skip == max_matches {
            sol_count += c_skip;
        }
        // option: match this entry with any valid partner within k
        for d in 1..=k {
            let j = i + d;
            if j >= len {
                break;
            }
            if entries[i].match_pair(entries[j]) {
                let mut new_entries = entries.clone();
                new_entries[i] = Entry::Empty;
                new_entries[j] = Entry::Empty;
                let (m_sub, c_sub) = dfs(new_entries, k);
                let m_match = m_sub + 1;
                if m_match > max_matches {
                    max_matches = m_match;
                    sol_count = c_sub;
                } else if m_match == max_matches {
                    sol_count += c_sub;
                }
            }
        }
        (max_matches, sol_count)
    }
    dfs(entries, k)
}

// (count, solution)
fn brute_force2(entries: Vec<Entry>, k: usize) -> (u64, u64) {
    fn inner(left: Vec<Entry>, k: usize) -> (u64, u64) {
        if left.is_empty() || left.iter().all(|it| it.clone() == Entry::Empty) {
            return (0, 1);
        }

        let len = left.len();
        let first = left[0];
        let mut s: Vec<(u64, u64)> = vec![];

        // skip
        let skipped = left[1..].to_vec();
        let skipped_ans = inner(skipped, k);
        s.push(skipped_ans);

        // try to match
        for i in 1..=k {
            if i >= len {
                break;
            }
            if first.match_pair(left[i]) {
                let mut skipped = left[1..].to_vec();
                skipped[i - 1] = Entry::Empty;
                let (count, solution) = inner(skipped, k);
                s.push((count + 1, solution));
            }
        }

        // only those with highest count
        let max_count = s
            .iter()
            .map(|it| it.0)
            .fold(0, |acc, curr| if curr > acc { curr } else { acc });

        let solution: u64 = s
            .iter()
            .filter(|(count, _)| *count == max_count)
            .map(|(_, solution)| solution.clone())
            .sum();

        (max_count, solution as u64)
    }

    inner(entries, k)
}

fn greedy(entries: &Vec<Entry>, k: usize) -> u64 {
    let mut entries: Vec<Entry> = entries.clone();
    let mut count = 0;
    let len = entries.len();

    for i in 0..len {
        let a = entries[i];
        for distance in (1..=k).rev() {
            let j = i + distance as usize;
            if j >= len {
                continue;
            }

            let b = entries[j];
            if a.match_pair(b) {
                entries[i] = Entry::Empty;
                entries[j] = Entry::Empty;
                count += 1;
                break;
            }
        }
    }

    count
}

fn main() {
    let stdin = io::stdin();
    let mut input = String::new();

    stdin.read_line(&mut input).unwrap();
    let entries = Entry::from_string(&input.trim()).expect("invalid input");

    input.clear();
    stdin.read_line(&mut input).unwrap();
    // let len = input.len();
    // println!("{input} {len}");
    let k: usize = input
        .trim()
        .parse()
        .expect("not a number, or not in 0 to 2^64");

    let count = greedy(&entries, k);
    println!("{count}");

    // // Log brute-force result (max matches and number of solutions)
    // println!("Bruteforcing");
    // let (bf_matches, bf_solutions) = brute_force2(entries.clone(), k);
    // println!(
    //     "brute_force matches: {:?}, solutions: {:?}",
    //     bf_matches, bf_solutions
    // );
}

#[cfg(test)]
mod tests {
    use crate::{Entry, brute_force2, greedy};

    fn assert_matches(input: &str, k: usize, expected: u64) {
        let entries: Vec<Entry> = Entry::from_string(input).unwrap();
        let (bf_matches, _) = brute_force2(entries.clone(), k);
        let greedy_matches: u64 = greedy(&entries, k);

        assert_eq!(
            greedy_matches, bf_matches,
            "Greedy gave {} matches, but optimal is {} for input '{}' with k={}",
            greedy_matches, bf_matches, input, k
        );

        assert_eq!(
            bf_matches, expected,
            "Brute force gave {} matches, but expected {} for input '{}' with k={}",
            bf_matches, expected, input, k
        );
        assert_eq!(
            greedy_matches, expected,
            "Greedy gave {} matches, but expected {} for input '{}' with k={}",
            greedy_matches, expected, input, k
        );
    }

    #[test]
    fn test_example() {
        assert_matches("GPPGP", 1, 2);
        assert_matches("PPGGPG", 2, 3);
        assert_matches("GPGPPG", 3, 3);
    }

    #[test]
    fn test_1() {
        assert_matches("GPGPGPGPGPGPGPGPGPGP", 2, 10);
    }
}
