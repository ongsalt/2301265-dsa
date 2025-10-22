function buildLps<T>(pattern: T[]) {
    const lps: number[] = [0];
    let acc = 0;

    for (let i = 1; i < pattern.length; i++) {
        if (pattern[i] === pattern[acc]) {
            acc += 1;
            lps.push(acc);
        } else if (acc !== 0) {
            acc = lps[acc - 1]!;
            i--;
        } else {
            lps.push(0);
        }
    }

    return lps;
}

function solveInner<T>(lps: number[], pattern: T[], text: T[]) {
    const founded: number[] = [];

    let i = 0;
    let j = 0;

    while (i < text.length) {
        const matched = pattern[j] === text[i];
        // console.log({ i, j })
        if (matched) {
            // console.log("matched")
            j += 1;
            i += 1;
        }

        if (j === pattern.length) {
            // console.log("j hit pattern len")
            founded.push(i - j);
            j = lps[j - 1]!;
        } else if (!matched) {
            if (j > 0) {
                j = lps[j - 1]!;
            } else {
                i += 1;
            }
        }
    }

    return founded;
}

function solve<T>(pattern: T[], text: T[]) {
    const lps = buildLps(pattern);

    const lr = solveInner(lps, pattern, text).map(it => it + 1);
    const rl = solveInner(lps, pattern.toReversed(), text).map(it => it + pattern.length);

    return { rl, lr, lps }
}

function run(pattern: string, text: string) {
    const { lps, lr, rl } = solve(pattern.split(" "), text.split(" "))

    console.log(lps.join(" "))
    console.log(rl.length + lr.length);
    for (const index of lr) {
        console.log(index, "LR")
    }
    for (const index of rl) {
        console.log(index, "RL")
    }
}

function parse(content: string) {
    const [_, __, pattern, text] = content.split("\n")
    return { pattern: pattern!, text: text! }
}

const content = await Bun.file("./testcases/8.2.txt").text()
const { pattern, text } = parse(content)

run(pattern, text)

