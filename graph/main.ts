function alloc(size: number) {
  return Array.from({ length: size }).map(it => Array.from({ length: size }).map(() => false));
}

function get() {
  return (prompt("") ?? "").split(" ").map(it => parseInt(it));
}

function isReachable(graph: boolean[][]) {
  const next: number[] = [0];

  const visited = Array.from({ length: graph.length }, () => false);
  const components = Array.from({ length: graph.length }, () => -1);
  const l: number[] = [];
  // visited[0] = true;

  while (next.length > 0) {
    const start = next.shift()!;
    if (visited[start]) {
      continue;
    }
    l.push(start);
    visited[start] = true;
    for (let i = 0; i < graph.length; i++) {
      if (graph[start][i]) {
        next.push(i);
      }
    }
  }

  function assign(a: number, root: number) {
    if (components[a] !== -1) {
      return;
    }

    components[a] = root;
    for (let i = 0; i < graph.length; i++) {
      if (graph[a][i]) {
        assign(i, root);
      }
    }
  }

  for (const v of l) {
    assign(v, v);
  }

  // outputBuffer.push(components);
  return components.every(it => it === 0);
}

const outputBuffer: any[] = [];

while (true) {
  const [m, n] = get();
  if (m === 0 && n === 0) {
    break;
  }

  const graph = alloc(m);
  for (let i = 0; i < n; i++) {
    let [a, b, c] = get();
    a -= 1;
    b -= 1;

    graph[a][b] = true;

    if (c === 2) {
      graph[b][a] = true;
    }
  }

  const res = isReachable(graph) ? 1 : 0;
  outputBuffer.push(res);
  // outputBuffer.push("---------------");
}

console.log();
for (const output of outputBuffer) {
  console.log(output);
}