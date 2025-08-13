import { gcd as gcd2 } from "./2";
import { gcd as gcd3 } from "./3";

import { readdirSync } from 'fs';
import { join } from "path";


const path = join(import.meta.dir, "./testcases");
const f = readdirSync(path);
const files = f.map(file => join(path, file));
// console.log(files);

const testcases = await Promise.all(files.map(f => Bun.file(f).text()
  .then(it => it.split("\n"))
  .then(it => it.map(line => line.split(",")))
  .then(it => it.map(line => line.map(num => parseInt(num))))
))
  .then(it => it.reduce((acc, current) => [...acc, ...current]));

// console.log(testcases);

for (const testcase of testcases) {
  const c = testcase.reduce((acc, n) => gcd2(acc, n));
  console.log(`${c}: [${testcase}]`);
}
